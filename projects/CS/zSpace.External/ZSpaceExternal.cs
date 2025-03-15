using System;
using System.Runtime.InteropServices;
using System.Runtime.ConstrainedExecution;
using System.Security;

namespace zSpace.External
{
    /// <summary>
    /// Provides a C# wrapper for the zSpace External native library.
    /// </summary>
    public static class ZSpaceExternal
    {
        // Name of the native DLL
        private const string DllName = "zSpace_External";

        #region Native API Imports

        /// <summary>
        /// Gets the last error message from the native library.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr zext_get_last_error();

        /// <summary>
        /// Creates a new empty mesh.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr zext_mesh_create();

        /// <summary>
        /// Destroys a mesh and frees its resources.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        [ReliabilityContract(Consistency.WillNotCorruptState, Cer.Success)]
        [SuppressUnmanagedCodeSecurity]
        private static extern int zext_mesh_destroy(IntPtr meshHandle);

        /// <summary>
        /// Checks if a mesh handle is valid.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        private static extern int zext_mesh_is_valid(IntPtr meshHandle);

        /// <summary>
        /// Gets the number of vertices in a mesh.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        private static extern int zext_mesh_get_vertex_count(IntPtr meshHandle);

        /// <summary>
        /// Gets the number of faces in a mesh.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        private static extern int zext_mesh_get_face_count(IntPtr meshHandle);

        /// <summary>
        /// Creates a test cube mesh.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        private static extern int zext_mesh_create_test_cube(IntPtr meshHandle, double size);

        #endregion

        #region Helper Methods

        /// <summary>
        /// Gets the last error message from the native library.
        /// </summary>
        public static string GetLastError()
        {
            IntPtr errorPtr = zext_get_last_error();
            if (errorPtr == IntPtr.Zero)
                return string.Empty;
                
            return Marshal.PtrToStringAnsi(errorPtr);
        }

        /// <summary>
        /// Throws an exception with the last error message if the condition is false.
        /// </summary>
        private static void ThrowIfFailed(bool condition, string message = null)
        {
            if (!condition)
            {
                string error = GetLastError();
                if (string.IsNullOrEmpty(error) && !string.IsNullOrEmpty(message))
                {
                    error = message;
                }
                throw new ZSpaceExternalException(error);
            }
        }

        #endregion

        #region Wrapper Classes

        /// <summary>
        /// Represents a mesh in the zSpace External library.
        /// </summary>
        public class Mesh : IDisposable
        {
            private IntPtr _handle;
            private bool _disposed = false;

            /// <summary>
            /// Creates a new empty mesh.
            /// </summary>
            public Mesh()
            {
                _handle = zext_mesh_create();
                ThrowIfFailed(_handle != IntPtr.Zero, "Failed to create mesh");
            }

            /// <summary>
            /// Finalizer to ensure resources are freed.
            /// </summary>
            ~Mesh()
            {
                Dispose(false);
            }

            /// <summary>
            /// Gets whether the mesh is valid.
            /// </summary>
            public bool IsValid
            {
                get
                {
                    ThrowIfDisposed();
                    return zext_mesh_is_valid(_handle) != 0;
                }
            }

            /// <summary>
            /// Gets the number of vertices in the mesh.
            /// </summary>
            public int VertexCount
            {
                get
                {
                    ThrowIfDisposed();
                    int count = zext_mesh_get_vertex_count(_handle);
                    ThrowIfFailed(count >= 0, "Failed to get vertex count");
                    return count;
                }
            }

            /// <summary>
            /// Gets the number of faces in the mesh.
            /// </summary>
            public int FaceCount
            {
                get
                {
                    ThrowIfDisposed();
                    int count = zext_mesh_get_face_count(_handle);
                    ThrowIfFailed(count >= 0, "Failed to get face count");
                    return count;
                }
            }

            /// <summary>
            /// Creates a test cube mesh.
            /// </summary>
            public bool CreateTestCube(double size = 1.0)
            {
                ThrowIfDisposed();
                int result = zext_mesh_create_test_cube(_handle, size);
                ThrowIfFailed(result != 0, "Failed to create test cube");
                return result != 0;
            }

            /// <summary>
            /// Disposes of the mesh resources.
            /// </summary>
            public void Dispose()
            {
                Dispose(true);
                GC.SuppressFinalize(this);
            }

            /// <summary>
            /// Disposes of the mesh resources.
            /// </summary>
            protected virtual void Dispose(bool disposing)
            {
                if (!_disposed)
                {
                    if (_handle != IntPtr.Zero)
                    {
                        zext_mesh_destroy(_handle);
                        _handle = IntPtr.Zero;
                    }
                    _disposed = true;
                }
            }

            /// <summary>
            /// Throws an exception if the object has been disposed.
            /// </summary>
            private void ThrowIfDisposed()
            {
                if (_disposed)
                {
                    throw new ObjectDisposedException(nameof(Mesh));
                }
            }
        }

        /// <summary>
        /// Exception thrown when an error occurs in the zSpace External library.
        /// </summary>
        public class ZSpaceExternalException : Exception
        {
            /// <summary>
            /// Creates a new instance of the ZSpaceExternalException class.
            /// </summary>
            public ZSpaceExternalException(string message) : base(message)
            {
            }
        }

        #endregion
    }
} 