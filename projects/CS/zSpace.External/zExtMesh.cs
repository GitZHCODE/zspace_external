using System;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace zSpace.External
{
    /// <summary>
    /// Represents a 3D mesh for use with zSpace.
    /// </summary>
    public class zExtMesh : IDisposable
    {
        private IntPtr _handle;
        private bool _disposed;

        /// <summary>
        /// Gets the number of vertices in the mesh.
        /// </summary>
        public int VertexCount
        {
            get
            {
                ThrowIfDisposed();
                return NativeMethods.zext_mesh_get_vertex_count(_handle);
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
                return NativeMethods.zext_mesh_get_face_count(_handle);
            }
        }

        /// <summary>
        /// Gets whether the mesh is valid.
        /// </summary>
        public bool IsValid
        {
            get
            {
                // Check if the mesh is disposed first to avoid accessing a disposed handle
                if (_disposed)
                    return false;
                    
                return _handle != IntPtr.Zero && 
                       NativeMethods.zext_mesh_is_valid(_handle);
            }
        }

        /// <summary>
        /// Creates a new, empty mesh.
        /// </summary>
        public zExtMesh()
        {
            try
            {
                Debug.WriteLine("Initializing native library...");
                NativeLibrary.Initialize();
                
                Debug.WriteLine("Creating native mesh handle...");
                _handle = NativeMethods.zext_mesh_create();
                if (_handle == IntPtr.Zero)
                {
                    ThrowLastError("Failed to create mesh");
                }
                
                Debug.WriteLine($"Mesh created successfully: {_handle}");
            }
            catch (Exception ex)
            {
                Debug.WriteLine($"Error creating mesh: {ex.Message}");
                if (_handle != IntPtr.Zero)
                {
                    try { NativeMethods.zext_mesh_destroy(_handle); } catch { }
                    _handle = IntPtr.Zero;
                }
                throw;
            }
        }

        /// <summary>
        /// Creates a mesh from vertex positions and face data.
        /// </summary>
        /// <param name="vertexPositions">Array of vertex positions (x1, y1, z1, x2, y2, z2, ...)</param>
        /// <param name="polyCounts">Array specifying number of vertices per face</param>
        /// <param name="polyConnections">Array of vertex indices for each face</param>
        /// <exception cref="ZSpaceExternalException">Thrown if the operation fails.</exception>
        /// <exception cref="ArgumentNullException">Thrown if any array is null.</exception>
        /// <exception cref="ArgumentException">Thrown if any array has invalid length.</exception>
        public void CreateMesh(double[] vertexPositions, int[] polyCounts, int[] polyConnections)
        {
            ThrowIfDisposed();
            
            if (vertexPositions == null) throw new ArgumentNullException(nameof(vertexPositions));
            if (polyCounts == null) throw new ArgumentNullException(nameof(polyCounts));
            if (polyConnections == null) throw new ArgumentNullException(nameof(polyConnections));
            
            if (vertexPositions.Length % 3 != 0)
                throw new ArgumentException("Vertex positions array length must be divisible by 3.", nameof(vertexPositions));
            
            int vertexCount = vertexPositions.Length / 3;
            
            Debug.WriteLine($"Creating mesh with {vertexCount} vertices and {polyCounts.Length} faces...");
            if (!NativeMethods.zext_mesh_create_mesh(_handle, vertexPositions, vertexCount, 
                                                   polyCounts, polyCounts.Length, 
                                                   polyConnections, polyConnections.Length))
            {
                ThrowLastError("Failed to create mesh");
            }
            
            Debug.WriteLine("Mesh created successfully");
        }

        /// <summary>
        /// Disposes the mesh resources.
        /// </summary>
        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        /// <summary>
        /// Disposes the mesh resources.
        /// </summary>
        /// <param name="disposing">Whether the method was called from Dispose() or the finalizer.</param>
        protected virtual void Dispose(bool disposing)
        {
            if (_disposed)
                return;

            if (_handle != IntPtr.Zero)
            {
                Debug.WriteLine($"Destroying mesh handle: {_handle}");
                NativeMethods.zext_mesh_destroy(_handle);
                _handle = IntPtr.Zero;
            }

            _disposed = true;
        }

        /// <summary>
        /// Finalizer to clean up native resources if the object is not disposed.
        /// </summary>
        ~zExtMesh()
        {
            Dispose(false);
        }

        /// <summary>
        /// Throws an exception if the object has been disposed.
        /// </summary>
        private void ThrowIfDisposed()
        {
            if (_disposed)
            {
                throw new ObjectDisposedException(nameof(zExtMesh), "Cannot access a disposed mesh.");
            }
        }

        /// <summary>
        /// Throws an exception with the last error message from the native library.
        /// </summary>
        /// <param name="message">The error message prefix.</param>
        private void ThrowLastError(string message)
        {
            int errorCode = NativeMethods.zext_get_last_error();
            string errorMessage = NativeMethods.zext_get_last_error_message();
            NativeMethods.zext_clear_last_error();

            string fullMessage = $"{message}: {errorMessage} (Error code: {errorCode})";
            Debug.WriteLine($"ERROR: {fullMessage}");
            throw new ZSpaceExternalException(fullMessage, errorCode);
        }
    }
} 