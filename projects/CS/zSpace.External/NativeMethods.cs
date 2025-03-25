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
        
        // MeshField Functions
        
        /// <summary>
        /// Creates a new mesh field.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr zext_field_create();
        
        /// <summary>
        /// Destroys a mesh field.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void zext_field_destroy(IntPtr field_handle);
        
        /// <summary>
        /// Checks if a mesh field is valid.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool zext_field_is_valid(IntPtr field_handle);
        
        /// <summary>
        /// Gets the number of vertices in a mesh field.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int zext_field_get_vertex_count(IntPtr field_handle);
        
        /// <summary>
        /// Gets the number of scalar values in a mesh field.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int zext_field_get_value_count(IntPtr field_handle);
        
        /// <summary>
        /// Creates a field with the given bounding box and resolution.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool zext_field_create_field(
            IntPtr field_handle,
            [MarshalAs(UnmanagedType.LPArray, SizeConst = 3)] double[] minBB,
            [MarshalAs(UnmanagedType.LPArray, SizeConst = 3)] double[] maxBB,
            int numX,
            int numY);
        
        /// <summary>
        /// Sets the field values.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool zext_field_set_field_values(
            IntPtr field_handle,
            [MarshalAs(UnmanagedType.LPArray)] float[] values,
            int valueCount);
        
        /// <summary>
        /// Gets the field values.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool zext_field_get_field_values(
            IntPtr field_handle,
            bool checkCount,
            [MarshalAs(UnmanagedType.LPArray)] float[] outValues,
            ref int outValueCount);
        
        /// <summary>
        /// Calculates scalar field values based on distance to a graph's edges.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool zext_field_get_scalars_graph_edge_distance(
            IntPtr field_handle,
            IntPtr graph_handle,
            float offset,
            bool normalise,
            [MarshalAs(UnmanagedType.LPArray)] float[] outValues,
            ref int outValueCount);
        
        /// <summary>
        /// Calculates scalar field values based on distance to a circle.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool zext_field_get_scalars_circle(
            IntPtr field_handle,
            [MarshalAs(UnmanagedType.LPArray, SizeConst = 3)] double[] centre,
            float radius,
            float offset,
            bool normalise,
            [MarshalAs(UnmanagedType.LPArray)] float[] outValues,
            ref int outValueCount);
        
        /// <summary>
        /// Calculates scalar field values based on distance to a line.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool zext_field_get_scalars_line(
            IntPtr field_handle,
            [MarshalAs(UnmanagedType.LPArray, SizeConst = 3)] double[] start,
            [MarshalAs(UnmanagedType.LPArray, SizeConst = 3)] double[] end,
            float offset,
            bool normalise,
            [MarshalAs(UnmanagedType.LPArray)] float[] outValues,
            ref int outValueCount);
        
        /// <summary>
        /// Calculates scalar field values based on distance to a polygon defined by a graph.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool zext_field_get_scalars_polygon(
            IntPtr field_handle,
            IntPtr graph_handle,
            bool normalise,
            [MarshalAs(UnmanagedType.LPArray)] float[] outValues,
            ref int outValueCount);
        
        /// <summary>
        /// Performs a boolean union operation between two scalar fields.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool zext_field_boolean_union(
            IntPtr field_handle,
            [MarshalAs(UnmanagedType.LPArray)] float[] scalarsA,
            int scalarsACount,
            [MarshalAs(UnmanagedType.LPArray)] float[] scalarsB,
            int scalarsBCount,
            bool normalise,
            [MarshalAs(UnmanagedType.LPArray)] float[] outValues,
            ref int outValueCount);
        
        /// <summary>
        /// Performs a boolean subtraction operation between two scalar fields.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool zext_field_boolean_subtract(
            IntPtr field_handle,
            [MarshalAs(UnmanagedType.LPArray)] float[] scalarsA,
            int scalarsACount,
            [MarshalAs(UnmanagedType.LPArray)] float[] scalarsB,
            int scalarsBCount,
            bool normalise,
            [MarshalAs(UnmanagedType.LPArray)] float[] outValues,
            ref int outValueCount);
        
        /// <summary>
        /// Performs a boolean intersection operation between two scalar fields.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool zext_field_boolean_intersect(
            IntPtr field_handle,
            [MarshalAs(UnmanagedType.LPArray)] float[] scalarsA,
            int scalarsACount,
            [MarshalAs(UnmanagedType.LPArray)] float[] scalarsB,
            int scalarsBCount,
            bool normalise,
            [MarshalAs(UnmanagedType.LPArray)] float[] outValues,
            ref int outValueCount);
        
        /// <summary>
        /// Performs a boolean difference operation between two scalar fields.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool zext_field_boolean_difference(
            IntPtr field_handle,
            [MarshalAs(UnmanagedType.LPArray)] float[] scalarsA,
            int scalarsACount,
            [MarshalAs(UnmanagedType.LPArray)] float[] scalarsB,
            int scalarsBCount,
            bool normalise,
            [MarshalAs(UnmanagedType.LPArray)] float[] outValues,
            ref int outValueCount);
        
        /// <summary>
        /// Computes smooth minimum between two scalar fields.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool zext_field_get_scalars_smin(
            IntPtr field_handle,
            [MarshalAs(UnmanagedType.LPArray)] float[] scalarsA,
            int scalarsACount,
            [MarshalAs(UnmanagedType.LPArray)] float[] scalarsB,
            int scalarsBCount,
            float k,
            int mode,
            [MarshalAs(UnmanagedType.LPArray)] float[] outValues,
            ref int outValueCount);
        
        /// <summary>
        /// Gets the field bounds.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool zext_field_get_bounds(
            IntPtr field_handle,
            [MarshalAs(UnmanagedType.LPArray, SizeConst = 3)] double[] minBB,
            [MarshalAs(UnmanagedType.LPArray, SizeConst = 3)] double[] maxBB);
        
        /// <summary>
        /// Gets iso contour from the field at a given threshold value.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool zext_field_get_iso_contour(
            IntPtr field_handle,
            IntPtr graph_handle,
            float threshold);
        
        /// <summary>
        /// Gets field gradient vectors.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool zext_field_get_gradients(
            IntPtr field_handle,
            bool checkCount,
            [MarshalAs(UnmanagedType.LPArray)] double[] outGradientVectors,
            ref int outVectorCount);
            
        /// <summary>
        /// Gets the vertex ID at the given position.
        /// </summary>
        [DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool zext_field_get_id(
            IntPtr field_handle,
            [MarshalAs(UnmanagedType.LPArray, SizeConst = 3)] double[] position,
            out int outId);
    }
} 