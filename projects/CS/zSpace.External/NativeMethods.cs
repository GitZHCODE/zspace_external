using System;
using System.Runtime.InteropServices;

namespace zSpace.External
{
    /// <summary>
    /// Contains the native method declarations for the zSpace External API.
    /// </summary>
    internal static class NativeMethods
    {
        private const string DllName = "zSpace_External";
        
        // Common Functions
        
        /// <summary>
        /// Gets the last error code from the native library.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int zext_get_last_error();
        
        /// <summary>
        /// Gets the last error message from the native library.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        public static extern string zext_get_last_error_message();
        
        /// <summary>
        /// Clears the last error in the native library.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void zext_clear_last_error();
        
        // Mesh Functions
        
        /// <summary>
        /// Creates a new mesh.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr zext_mesh_create();
        
        /// <summary>
        /// Destroys a mesh.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void zext_mesh_destroy(IntPtr mesh_handle);
        
        /// <summary>
        /// Checks if a mesh is valid.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool zext_mesh_is_valid(IntPtr mesh_handle);
        
        /// <summary>
        /// Gets the number of vertices in a mesh.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int zext_mesh_get_vertex_count(IntPtr mesh_handle);
        
        /// <summary>
        /// Gets the number of faces in a mesh.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int zext_mesh_get_face_count(IntPtr mesh_handle);
        
        /// <summary>
        /// Creates a mesh from vertex positions and face data.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool zext_mesh_create_mesh(
            IntPtr mesh_handle, 
            [MarshalAs(UnmanagedType.LPArray)] double[] vertexPositions, 
            int vertexCount,
            [MarshalAs(UnmanagedType.LPArray)] int[] polyCounts, 
            int polyCountsSize,
            [MarshalAs(UnmanagedType.LPArray)] int[] polyConnections, 
            int polyConnectionsSize);
            
        /// <summary>
        /// Computes geodesic distances on the mesh using the heat method.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool zext_mesh_compute_geodesic_heat(
            IntPtr mesh_handle,
            [MarshalAs(UnmanagedType.LPArray)] int[] sourceVertexIds,
            int sourceVertexCount,
            [MarshalAs(UnmanagedType.LPArray)] float[] outGeodesicScalars);
    }
} 