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
        [return: MarshalAs(UnmanagedType.LPStr)]
        public static extern string zext_get_last_error();
        
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
            bool normalised,
            [MarshalAs(UnmanagedType.LPArray)] float[] outGeodesicScalars);
            
        /// <summary>
        /// Computes interpolated geodesic distances between two sets of vertices using the heat method.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool zext_mesh_compute_geodesic_heat_interpolated(
            IntPtr mesh_handle,
            [MarshalAs(UnmanagedType.LPArray)] int[] startVertexIds,
            int startVertexCount,
            [MarshalAs(UnmanagedType.LPArray)] int[] endVertexIds,
            int endVertexCount,
            float weight,
            [MarshalAs(UnmanagedType.LPArray)] float[] outGeodesicScalars);
        
        /// <summary>
        /// Computes geodesic contours on the mesh.
        /// 
        /// This method can be called in two ways:
        /// 1. To get the number of contours without retrieving them: set checkCount to true
        /// 2. To retrieve the contours: set checkCount to false and provide a pre-allocated array
        /// 
        /// The return value indicates success or failure.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool zext_mesh_compute_geodesic_contours(
            IntPtr mesh_handle,
            bool checkCount,
            [MarshalAs(UnmanagedType.LPArray)] int[] sourceVertexIds,
            int sourceVertexCount,
            int steps,
            float dist,
            [MarshalAs(UnmanagedType.LPArray)] IntPtr[] outContours,
            ref int outContourCount);
            
        /// <summary>
        /// Computes interpolated geodesic contours on the mesh between two sets of vertices.
        /// 
        /// This method can be called in two ways:
        /// 1. To get the number of contours without retrieving them: set checkCount to true
        /// 2. To retrieve the contours: set checkCount to false and provide a pre-allocated array
        /// 
        /// The return value indicates success or failure.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool zext_mesh_compute_geodesic_contours_interpolated(
            IntPtr mesh_handle,
            bool checkCount,
            [MarshalAs(UnmanagedType.LPArray)] int[] startVertexIds,
            int startVertexCount,
            [MarshalAs(UnmanagedType.LPArray)] int[] endVertexIds,
            int endVertexCount,
            int steps,
            float dist,
            [MarshalAs(UnmanagedType.LPArray)] IntPtr[] outContours,
            ref int outContourCount);
        
        /// <summary>
        /// Gets mesh data including vertex positions, polygon counts, and polygon connections.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool zext_mesh_get_mesh_data(
            IntPtr mesh_handle,
            bool checkCount,
            [MarshalAs(UnmanagedType.LPArray)] double[] vertexPositions,
            ref int vertexCount,
            [MarshalAs(UnmanagedType.LPArray)] int[] polyCounts,
            ref int polyCountsSize,
            [MarshalAs(UnmanagedType.LPArray)] int[] polyConnections,
            ref int polyConnectionsSize);
        
        // Graph Functions
        
        /// <summary>
        /// Creates a new graph.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr zext_graph_create();
        
        /// <summary>
        /// Destroys a graph.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void zext_graph_destroy(IntPtr graph_handle);
        
        /// <summary>
        /// Checks if a graph is valid.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool zext_graph_is_valid(IntPtr graph_handle);
        
        /// <summary>
        /// Gets the number of vertices in a graph.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int zext_graph_get_vertex_count(IntPtr graph_handle);
        
        /// <summary>
        /// Gets the number of edges in a graph.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int zext_graph_get_edge_count(IntPtr graph_handle);
        
        /// <summary>
        /// Creates a graph from vertex positions and edge data.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool zext_graph_create_graph(
            IntPtr graph_handle, 
            [MarshalAs(UnmanagedType.LPArray)] double[] vertexPositions, 
            int vertexCount,
            [MarshalAs(UnmanagedType.LPArray)] int[] edgeConnections, 
            int edgeConnectionsSize);
            
        /// <summary>
        /// Sets vertex positions in the graph.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool zext_graph_set_vertex_positions(
            IntPtr graph_handle,
            [MarshalAs(UnmanagedType.LPArray)] double[] vertexPositions,
            int vertexCount);
            
        /// <summary>
        /// Gets vertex positions from the graph.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool zext_graph_get_vertex_positions(
            IntPtr graph_handle,
            [MarshalAs(UnmanagedType.LPArray)] double[] outVertexPositions);
        
        /// <summary>
        /// Gets graph data including vertex positions and edge connections.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool zext_graph_get_graph_data(
            IntPtr graph_handle,
            bool checkCount,
            [MarshalAs(UnmanagedType.LPArray)] double[] vertexPositions,
            ref int vertexCount,
            [MarshalAs(UnmanagedType.LPArray)] int[] edgeConnections,
            ref int edgeConnectionsSize);
            
        /// <summary>
        /// Merges vertices in the graph that are within a given tolerance distance of each other.
        /// This is useful for cleaning up graphs with duplicate or nearly-duplicate vertices.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool zext_graph_merge_vertices(
            IntPtr graph_handle,
            double tolerance);
            
        /// <summary>
        /// Separates a graph into its disconnected components.
        /// Each component is a subgraph that has no connections to other components.
        /// 
        /// This method can be called in two ways:
        /// 1. To get the number of components without retrieving them: set checkCount to true
        /// 2. To retrieve the components: set checkCount to false and provide a pre-allocated array
        /// 
        /// The return value indicates success or failure.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool zext_graph_separate_graph(
            IntPtr graph_handle,
            bool checkCount,
            [MarshalAs(UnmanagedType.LPArray)] IntPtr[] outComponents,
            ref int outComponentCount);
    }
} 