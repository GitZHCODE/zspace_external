/**
 * \file zSpace_External_C_API.h
 * \brief C API for zSpace External Library - Minimal MVP
 * \date 2023
 *
 * This file provides a C API for the zSpace External library, allowing
 * interoperability with other languages like C#.
 */

#ifndef ZSPACE_EXTERNAL_C_API_H
#define ZSPACE_EXTERNAL_C_API_H

#ifdef __cplusplus
extern "C" {
#endif

// Define API export macro for Windows DLL
#ifdef _WIN32
    #ifdef ZSPACEEXTERNAL_EXPORTS
        #define ZSPACE_EXTERNAL_API __declspec(dllexport)
    #else
        #define ZSPACE_EXTERNAL_API __declspec(dllimport)
    #endif
#else
    #define ZSPACE_EXTERNAL_API
#endif

// Opaque handle types for C API
typedef void* zExtMeshHandle;
typedef void* zExtGraphHandle;
typedef void* zExtMeshFieldHandle;

// Error handling
/**
 * Get the last error message.
 * 
 * @return The last error message as a null-terminated string.
 */
ZSPACE_EXTERNAL_API const char* zext_get_last_error();

//--- MESH API ---//

/**
 * Create a new empty mesh.
 * 
 * @return Handle to the created mesh, or NULL if an error occurred.
 */
ZSPACE_EXTERNAL_API zExtMeshHandle zext_mesh_create();

/**
 * Destroy a mesh and free its resources.
 * 
 * @param mesh_handle Handle to the mesh to destroy.
 * @return 1 if successful, 0 if an error occurred.
 */
ZSPACE_EXTERNAL_API int zext_mesh_destroy(zExtMeshHandle mesh_handle);

/**
 * Check if a mesh handle is valid.
 * 
 * @param mesh_handle Handle to the mesh to check.
 * @return 1 if valid, 0 if invalid.
 */
ZSPACE_EXTERNAL_API int zext_mesh_is_valid(zExtMeshHandle mesh_handle);

/**
 * Get the number of vertices in a mesh.
 * 
 * @param mesh_handle Handle to the mesh.
 * @return Number of vertices, or -1 if an error occurred.
 */
ZSPACE_EXTERNAL_API int zext_mesh_get_vertex_count(zExtMeshHandle mesh_handle);

/**
 * Get the number of faces in a mesh.
 * 
 * @param mesh_handle Handle to the mesh.
 * @return Number of faces, or -1 if an error occurred.
 */
ZSPACE_EXTERNAL_API int zext_mesh_get_face_count(zExtMeshHandle mesh_handle);

/**
 * Create a mesh from vertex positions and face data.
 * 
 * @param mesh_handle Handle to the mesh.
 * @param vertexPositions Array of vertex positions (x1, y1, z1, x2, y2, z2, ...).
 * @param vertexCount Number of vertices (vertexPositions.length / 3).
 * @param polyCounts Array specifying number of vertices per face.
 * @param polyCountsSize Size of the polyCounts array.
 * @param polyConnections Array of vertex indices for each face.
 * @param polyConnectionsSize Size of the polyConnections array.
 * @return 1 if successful, 0 if an error occurred.
 */
ZSPACE_EXTERNAL_API int zext_mesh_create_mesh(zExtMeshHandle mesh_handle, 
                                              const double* vertexPositions, int vertexCount,
                                              const int* polyCounts, int polyCountsSize,
                                              const int* polyConnections, int polyConnectionsSize);

/**
 * Compute geodesic distances on the mesh using the heat method.
 * 
 * @param mesh_handle Handle to the mesh.
 * @param source_vertex_ids Array of source vertex indices.
 * @param source_vertex_count Number of source vertices.
 * @param source_vertex_count Number of source vertices.
 * @param nomarlised Option to normalise the output geodesicScalars
 * @param out_geodesic_scalars Output array for computed geodesic distances (pre-allocated with size equal to vertex count).
 * @return 1 if successful, 0 if an error occurred.
 */
ZSPACE_EXTERNAL_API int zext_mesh_compute_geodesic_heat(zExtMeshHandle mesh_handle,
                                                      const int* source_vertex_ids, int source_vertex_count, bool normalised,
                                                      float* out_geodesic_scalars);

/**
 * Compute interpolated geodesic distances between two sets of vertices using the heat method.
 * 
 * @param mesh_handle Handle to the mesh.
 * @param start_vertex_ids Array of start vertex indices.
 * @param start_vertex_count Number of start vertices.
 * @param end_vertex_ids Array of end vertex indices.
 * @param end_vertex_count Number of end vertices.
 * @param weight Interpolation weight between 0 and 1.
 * @param out_geodesic_scalars Output array for computed geodesic distances (pre-allocated with size equal to vertex count).
 * @return 1 if successful, 0 if an error occurred.
 */
ZSPACE_EXTERNAL_API int zext_mesh_compute_geodesic_heat_interpolated(zExtMeshHandle mesh_handle,
                                                                  const int* start_vertex_ids, int start_vertex_count,
                                                                  const int* end_vertex_ids, int end_vertex_count,
                                                                  float weight,
                                                                  float* out_geodesic_scalars);

/**
 * Compute geodesic contours on a mesh.
 * 
 * @param mesh_handle Handle to the mesh
 * @param checkCount If true, only gets the count without copying data. If false, copies data to the output array.
 * @param source_vertex_ids Array of source vertex indices
 * @param source_vertex_count Number of source vertices
 * @param steps Number of contour steps to generate
 * @param dist Distance between contours (if 0, uses steps instead)
 * @param out_contours Output array for contour handles (can be null when checkCount is true)
 * @param out_contour_count Pointer to receive the number of contours
 * @return 1 if successful, 0 if an error occurred (boolean semantics)
 */
ZSPACE_EXTERNAL_API int zext_mesh_compute_geodesic_contours(zExtMeshHandle mesh_handle,
                                                         bool checkCount,
                                                         const int* source_vertex_ids, int source_vertex_count,
                                                         int steps, float dist,
                                                         zExtGraphHandle* out_contours, int* out_contour_count);

/**
 * Compute interpolated geodesic contours on a mesh between two sets of vertices.
 *
 * @param mesh_handle Handle to the mesh
 * @param checkCount If true, only gets the count without copying data. If false, copies data to the output array.
 * @param start_vertex_ids Array of start vertex indices
 * @param start_vertex_count Number of start vertices
 * @param end_vertex_ids Array of end vertex indices
 * @param end_vertex_count Number of end vertices
 * @param steps Number of contour steps to generate
 * @param dist Distance between contours (if 0, uses steps instead)
 * @param out_contours Output array for contour handles (can be null when checkCount is true)
 * @param out_contour_count Pointer to receive the number of contours
 * @return 1 if successful, 0 if an error occurred (boolean semantics)
 */
ZSPACE_EXTERNAL_API int zext_mesh_compute_geodesic_contours_interpolated(zExtMeshHandle mesh_handle,
                                                                      bool checkCount,
                                                                      const int* start_vertex_ids, int start_vertex_count,
                                                                      const int* end_vertex_ids, int end_vertex_count,
                                                                      int steps, float dist,
                                                                      zExtGraphHandle* out_contours, int* out_contour_count);

/**
 * Get mesh data including vertex positions, polygon counts, and polygon connections.
 * 
 * @param mesh_handle Handle to the mesh.
 * @param checkCount If true, only gets the counts without copying data. If false, copies data to the output arrays.
 * @param vertexPositions Output array for vertex positions (pre-allocated with size vertexCount*3).
 * @param vertexCount Pointer to receive the number of vertex positions.
 * @param polyCounts Output array for polygon counts (pre-allocated with size polyCountsSize).
 * @param polyCountsSize Pointer to receive the number of polygon counts.
 * @param polyConnections Output array for polygon connections (pre-allocated with size polyConnectionsSize).
 * @param polyConnectionsSize Pointer to receive the number of polygon connections.
 * @return 1 if successful, 0 if an error occurred.
 */
ZSPACE_EXTERNAL_API int zext_mesh_get_mesh_data(zExtMeshHandle mesh_handle, bool checkCount,
                                               double* vertexPositions, int* vertexCount,
                                               int* polyCounts, int* polyCountsSize,
                                               int* polyConnections, int* polyConnectionsSize);

//--- GRAPH API ---//

/**
 * Create a new empty graph.
 * 
 * @return Handle to the created graph, or NULL if an error occurred.
 */
ZSPACE_EXTERNAL_API zExtGraphHandle zext_graph_create();

/**
 * Destroy a graph and free its resources.
 * 
 * @param graph_handle Handle to the graph to destroy.
 * @return 1 if successful, 0 if an error occurred.
 */
ZSPACE_EXTERNAL_API int zext_graph_destroy(zExtGraphHandle graph_handle);

/**
 * Check if a graph handle is valid.
 * 
 * @param graph_handle Handle to the graph to check.
 * @return 1 if valid, 0 if invalid.
 */
ZSPACE_EXTERNAL_API int zext_graph_is_valid(zExtGraphHandle graph_handle);

/**
 * Get the number of vertices in a graph.
 * 
 * @param graph_handle Handle to the graph.
 * @return Number of vertices, or -1 if an error occurred.
 */
ZSPACE_EXTERNAL_API int zext_graph_get_vertex_count(zExtGraphHandle graph_handle);

/**
 * Get the number of edges in a graph.
 * 
 * @param graph_handle Handle to the graph.
 * @return Number of edges, or -1 if an error occurred.
 */
ZSPACE_EXTERNAL_API int zext_graph_get_edge_count(zExtGraphHandle graph_handle);

/**
 * Create a graph from vertex positions and edge data.
 * 
 * @param graph_handle Handle to the graph.
 * @param vertexPositions Array of vertex positions (x1, y1, z1, x2, y2, z2, ...).
 * @param vertexCount Number of vertices (vertexPositions.length / 3).
 * @param edgeConnections Array of vertex indices for each edge (start1, end1, start2, end2, ...).
 * @param edgeConnectionsSize Size of the edgeConnections array (number of edges * 2).
 * @return 1 if successful, 0 if an error occurred.
 */
ZSPACE_EXTERNAL_API int zext_graph_create_graph(zExtGraphHandle graph_handle, 
                                              const double* vertexPositions, int vertexCount,
                                              const int* edgeConnections, int edgeConnectionsSize);

/**
 * Set vertex positions in the graph.
 * 
 * @param graph_handle Handle to the graph.
 * @param vertexPositions Array of vertex positions (x1, y1, z1, x2, y2, z2, ...).
 * @param vertexCount Number of vertices (vertexPositions.length / 3).
 * @return 1 if successful, 0 if an error occurred.
 */
ZSPACE_EXTERNAL_API int zext_graph_set_vertex_positions(zExtGraphHandle graph_handle,
                                                      const double* vertexPositions, int vertexCount);

/**
 * Get vertex positions from the graph.
 * 
 * @param graph_handle Handle to the graph.
 * @param out_vertexPositions Output array for vertex positions (pre-allocated with size equal to vertex count * 3).
 * @return 1 if successful, 0 if an error occurred.
 */
ZSPACE_EXTERNAL_API int zext_graph_get_vertex_positions(zExtGraphHandle graph_handle,
                                                      double* out_vertexPositions);

/**
 * Get graph data including vertex positions and edge connections.
 * 
 * @param graph_handle Handle to the graph.
 * @param checkCount If true, only gets the counts without copying data. If false, copies data to the output arrays.
 * @param vertexPositions Output array for vertex positions (pre-allocated with size vertexCount*3).
 * @param vertexCount Pointer to receive the number of vertex positions.
 * @param edgeConnections Output array for edge connections (pre-allocated with size edgeConnectionsSize).
 * @param edgeConnectionsSize Pointer to receive the number of edge connections.
 * @return 1 if successful, 0 if an error occurred.
 */
ZSPACE_EXTERNAL_API int zext_graph_get_graph_data(zExtGraphHandle graph_handle, bool checkCount,
                                               double* vertexPositions, int* vertexCount,
                                               int* edgeConnections, int* edgeConnectionsSize);

/**
 * Merge vertices in the graph that are within a given tolerance distance of each other.
 * This operation is useful for cleaning up graphs with duplicate or nearly-duplicate vertices.
 * After merging, edges will be reindexed to use the updated vertex indices.
 *
 * @param graph_handle Handle to the graph.
 * @param tolerance Maximum distance between vertices to be considered for merging.
 * @return 1 if successful, 0 if an error occurred.
 */
ZSPACE_EXTERNAL_API int zext_graph_merge_vertices(zExtGraphHandle graph_handle, double tolerance);

/**
 * Separates a graph into its disconnected components.
 * Each component is a subgraph that has no connections to other components.
 * 
 * @param graph_handle Handle to the graph.
 * @param checkCount If true, only gets the count without copying data. If false, copies data to the output array.
 * @param out_components Output array for component graph handles (can be null when checkCount is true).
 * @param out_component_count Pointer to receive the number of components.
 * @return 1 if successful, 0 if an error occurred.
 */
ZSPACE_EXTERNAL_API int zext_graph_separate_graph(zExtGraphHandle graph_handle, bool checkCount,
                                              zExtGraphHandle* out_components, int* out_component_count);

//--- MESH FIELD API ---//

/**
 * Create a new empty mesh field.
 * 
 * @return Handle to the created mesh field, or NULL if an error occurred.
 */
ZSPACE_EXTERNAL_API zExtMeshFieldHandle zext_field_create();

/**
 * Destroy a mesh field and free its resources.
 * 
 * @param field_handle Handle to the mesh field to destroy.
 * @return 1 if successful, 0 if an error occurred.
 */
ZSPACE_EXTERNAL_API int zext_field_destroy(zExtMeshFieldHandle field_handle);

/**
 * Check if a mesh field handle is valid.
 * 
 * @param field_handle Handle to the mesh field to check.
 * @return 1 if valid, 0 if invalid.
 */
ZSPACE_EXTERNAL_API int zext_field_is_valid(zExtMeshFieldHandle field_handle);

/**
 * Get the number of vertices in a mesh field.
 * 
 * @param field_handle Handle to the mesh field.
 * @return Number of vertices, or -1 if an error occurred.
 */
ZSPACE_EXTERNAL_API int zext_field_get_vertex_count(zExtMeshFieldHandle field_handle);

/**
 * Get the number of scalar values in a mesh field.
 * 
 * @param field_handle Handle to the mesh field.
 * @return Number of values, or -1 if an error occurred.
 */
ZSPACE_EXTERNAL_API int zext_field_get_value_count(zExtMeshFieldHandle field_handle);

/**
 * Create a field with the given bounding box and resolution.
 * 
 * @param field_handle Handle to the mesh field.
 * @param minBB Array of 3 doubles representing minimum bounding box point (x, y, z)
 * @param maxBB Array of 3 doubles representing maximum bounding box point (x, y, z)
 * @param numX Number of grid points in X direction
 * @param numY Number of grid points in Y direction
 * @return 1 if successful, 0 if an error occurred.
 */
ZSPACE_EXTERNAL_API int zext_field_create_field(zExtMeshFieldHandle field_handle,
                                               const double* minBB,
                                               const double* maxBB,
                                               int numX,
                                               int numY);

/**
 * Set field values.
 * 
 * @param field_handle Handle to the mesh field.
 * @param values Array of scalar field values
 * @param valueCount Number of values in the array
 * @return 1 if successful, 0 if an error occurred.
 */
ZSPACE_EXTERNAL_API int zext_field_set_field_values(zExtMeshFieldHandle field_handle,
                                                   const float* values,
                                                   int valueCount);

/**
 * Get field values.
 * 
 * @param field_handle Handle to the mesh field.
 * @param checkCount If true, only gets the count without copying data. If false, copies data to the output array.
 * @param out_values Output array for field values (pre-allocated with size equal to value count)
 * @param out_value_count Pointer to receive the number of values
 * @return 1 if successful, 0 if an error occurred.
 */
ZSPACE_EXTERNAL_API int zext_field_get_field_values(zExtMeshFieldHandle field_handle,
                                                   bool checkCount,
                                                   float* out_values,
                                                   int* out_value_count);

/**
 * Calculate scalar field values based on distance to a graph's edges.
 * 
 * @param field_handle Handle to the mesh field.
 * @param graph_handle Handle to the graph.
 * @param offset Distance offset value
 * @param normalise Whether to normalize the resulting values
 * @param out_values Output array for field values (pre-allocated with size equal to value count)
 * @param out_value_count Pointer to receive the number of values
 * @return 1 if successful, 0 if an error occurred.
 */
ZSPACE_EXTERNAL_API int zext_field_get_scalars_graph_edge_distance(zExtMeshFieldHandle field_handle,
                                                                  zExtGraphHandle graph_handle,
                                                                  float offset,
                                                                  bool normalise,
                                                                  float* out_values,
                                                                  int* out_value_count);

/**
 * Calculate scalar field values based on distance to a circle.
 * 
 * @param field_handle Handle to the mesh field.
 * @param centre Array of 3 doubles representing the circle center (x, y, z)
 * @param radius Radius of the circle
 * @param offset Distance offset value
 * @param normalise Whether to normalize the resulting values
 * @param out_values Output array for field values (pre-allocated with size equal to value count)
 * @param out_value_count Pointer to receive the number of values
 * @return 1 if successful, 0 if an error occurred.
 */
ZSPACE_EXTERNAL_API int zext_field_get_scalars_circle(zExtMeshFieldHandle field_handle,
                                                     const double* centre,
                                                     float radius,
                                                     float offset,
                                                     bool normalise,
                                                     float* out_values,
                                                     int* out_value_count);

/**
 * Calculate scalar field values based on distance to a line.
 * 
 * @param field_handle Handle to the mesh field.
 * @param start Array of 3 doubles representing the line start point (x, y, z)
 * @param end Array of 3 doubles representing the line end point (x, y, z)
 * @param offset Distance offset value
 * @param normalise Whether to normalize the resulting values
 * @param out_values Output array for field values (pre-allocated with size equal to value count)
 * @param out_value_count Pointer to receive the number of values
 * @return 1 if successful, 0 if an error occurred.
 */
ZSPACE_EXTERNAL_API int zext_field_get_scalars_line(zExtMeshFieldHandle field_handle,
                                                   const double* start,
                                                   const double* end,
                                                   float offset,
                                                   bool normalise,
                                                   float* out_values,
                                                   int* out_value_count);

/**
 * Calculate scalar field values based on distance to a polygon defined by a graph.
 * 
 * @param field_handle Handle to the mesh field.
 * @param graph_handle Handle to the graph representing the polygon.
 * @param normalise Whether to normalize the resulting values
 * @param out_values Output array for field values (pre-allocated with size equal to value count)
 * @param out_value_count Pointer to receive the number of values
 * @return 1 if successful, 0 if an error occurred.
 */
ZSPACE_EXTERNAL_API int zext_field_get_scalars_polygon(zExtMeshFieldHandle field_handle,
                                                      zExtGraphHandle graph_handle,
                                                      bool normalise,
                                                      float* out_values,
                                                      int* out_value_count);

/**
 * Perform a boolean union operation between two scalar fields.
 * 
 * @param field_handle Handle to the mesh field.
 * @param scalars_A First input scalar field values
 * @param scalars_A_count Number of values in the first input array
 * @param scalars_B Second input scalar field values
 * @param scalars_B_count Number of values in the second input array
 * @param normalise Whether to normalize the resulting values
 * @param out_values Output array for field values (pre-allocated with size equal to value count)
 * @param out_value_count Pointer to receive the number of values
 * @return 1 if successful, 0 if an error occurred.
 */
ZSPACE_EXTERNAL_API int zext_field_boolean_union(zExtMeshFieldHandle field_handle,
                                                const float* scalars_A,
                                                int scalars_A_count,
                                                const float* scalars_B,
                                                int scalars_B_count,
                                                bool normalise,
                                                float* out_values,
                                                int* out_value_count);

/**
 * Perform a boolean subtraction operation between two scalar fields.
 * 
 * @param field_handle Handle to the mesh field.
 * @param scalars_A First input scalar field values
 * @param scalars_A_count Number of values in the first input array
 * @param scalars_B Second input scalar field values
 * @param scalars_B_count Number of values in the second input array
 * @param normalise Whether to normalize the resulting values
 * @param out_values Output array for field values (pre-allocated with size equal to value count)
 * @param out_value_count Pointer to receive the number of values
 * @return 1 if successful, 0 if an error occurred.
 */
ZSPACE_EXTERNAL_API int zext_field_boolean_subtract(zExtMeshFieldHandle field_handle,
                                                   const float* scalars_A,
                                                   int scalars_A_count,
                                                   const float* scalars_B,
                                                   int scalars_B_count,
                                                   bool normalise,
                                                   float* out_values,
                                                   int* out_value_count);

/**
 * Perform a boolean intersection operation between two scalar fields.
 * 
 * @param field_handle Handle to the mesh field.
 * @param scalars_A First input scalar field values
 * @param scalars_A_count Number of values in the first input array
 * @param scalars_B Second input scalar field values
 * @param scalars_B_count Number of values in the second input array
 * @param normalise Whether to normalize the resulting values
 * @param out_values Output array for field values (pre-allocated with size equal to value count)
 * @param out_value_count Pointer to receive the number of values
 * @return 1 if successful, 0 if an error occurred.
 */
ZSPACE_EXTERNAL_API int zext_field_boolean_intersect(zExtMeshFieldHandle field_handle,
                                                    const float* scalars_A,
                                                    int scalars_A_count,
                                                    const float* scalars_B,
                                                    int scalars_B_count,
                                                    bool normalise,
                                                    float* out_values,
                                                    int* out_value_count);

/**
 * Perform a boolean difference operation between two scalar fields.
 * 
 * @param field_handle Handle to the mesh field.
 * @param scalars_A First input scalar field values
 * @param scalars_A_count Number of values in the first input array
 * @param scalars_B Second input scalar field values
 * @param scalars_B_count Number of values in the second input array
 * @param normalise Whether to normalize the resulting values
 * @param out_values Output array for field values (pre-allocated with size equal to value count)
 * @param out_value_count Pointer to receive the number of values
 * @return 1 if successful, 0 if an error occurred.
 */
ZSPACE_EXTERNAL_API int zext_field_boolean_difference(zExtMeshFieldHandle field_handle,
                                                     const float* scalars_A,
                                                     int scalars_A_count,
                                                     const float* scalars_B,
                                                     int scalars_B_count,
                                                     bool normalise,
                                                     float* out_values,
                                                     int* out_value_count);

/**
 * Compute smooth minimum between two scalar fields.
 * 
 * @param field_handle Handle to the mesh field.
 * @param scalars_A First input scalar field values
 * @param scalars_A_count Number of values in the first input array
 * @param scalars_B Second input scalar field values
 * @param scalars_B_count Number of values in the second input array
 * @param k Smoothing factor
 * @param mode Smooth minimum mode (0=polynomial, 1=exponential)
 * @param out_values Output array for field values (pre-allocated with size equal to value count)
 * @param out_value_count Pointer to receive the number of values
 * @return 1 if successful, 0 if an error occurred.
 */
ZSPACE_EXTERNAL_API int zext_field_get_scalars_smin(zExtMeshFieldHandle field_handle,
                                                   const float* scalars_A,
                                                   int scalars_A_count,
                                                   const float* scalars_B,
                                                   int scalars_B_count,
                                                   float k,
                                                   int mode,
                                                   float* out_values,
                                                   int* out_value_count);

/**
 * Compute smooth minimum across multiple scalar fields.
 * 
 * @param field_handle Handle to the mesh field.
 * @param scalar_arrays Array of pointers to arrays of scalar values
 * @param scalar_counts Array of counts for each scalar array
 * @param array_count Number of arrays
 * @param k Smoothing factor
 * @param mode Smooth minimum mode (0=polynomial, 1=exponential)
 * @param out_values Output array for field values (pre-allocated with size equal to value count)
 * @param out_value_count Pointer to receive the number of values
 * @return 1 if successful, 0 if an error occurred.
 */
ZSPACE_EXTERNAL_API int zext_field_get_scalars_smin_multiple(zExtMeshFieldHandle field_handle,
                                                            const float* const* scalar_arrays,
                                                            const int* scalar_counts,
                                                            int array_count,
                                                            float k,
                                                            int mode,
                                                            float* out_values,
                                                            int* out_value_count);

/**
 * Get the field bounds.
 * 
 * @param field_handle Handle to the mesh field.
 * @param minBB Output array of 3 doubles to store minimum bounding box point (x, y, z)
 * @param maxBB Output array of 3 doubles to store maximum bounding box point (x, y, z)
 * @return 1 if successful, 0 if an error occurred.
 */
ZSPACE_EXTERNAL_API int zext_field_get_bounds(zExtMeshFieldHandle field_handle,
                                             double* minBB,
                                             double* maxBB);

/**
 * Get iso contour from the field at a given threshold value.
 * 
 * @param field_handle Handle to the mesh field.
 * @param graph_handle Handle to the graph where the contour will be stored.
 * @param threshold Iso value
 * @return 1 if successful, 0 if an error occurred.
 */
ZSPACE_EXTERNAL_API int zext_field_get_iso_contour(zExtMeshFieldHandle field_handle,
                                                  zExtGraphHandle graph_handle,
                                                  float threshold);

/**
 * Get field gradient vectors.
 * 
 * @param field_handle Handle to the mesh field.
 * @param checkCount If true, only gets the count without copying data. If false, copies data to the output array.
 * @param out_gradient_vectors Output array for gradient vectors (x1, y1, z1, x2, y2, z2, ...)
 * @param out_vector_count Pointer to receive the number of vectors (not the size of the array which is 3x this value)
 * @return 1 if successful, 0 if an error occurred.
 */
ZSPACE_EXTERNAL_API int zext_field_get_gradients(zExtMeshFieldHandle field_handle,
                                                bool checkCount,
                                                double* out_gradient_vectors,
                                                int* out_vector_count);

/**
 * Get the vertex ID at the given position.
 * 
 * @param field_handle Handle to the mesh field.
 * @param position Array of 3 doubles representing the position (x, y, z)
 * @param out_id Pointer to receive the vertex ID
 * @return 1 if successful, 0 if an error occurred.
 */
ZSPACE_EXTERNAL_API int zext_field_get_id(zExtMeshFieldHandle field_handle,
                                         double* position,
                                         int* out_id);

#ifdef __cplusplus
}
#endif

#endif // ZSPACE_EXTERNAL_C_API_H 