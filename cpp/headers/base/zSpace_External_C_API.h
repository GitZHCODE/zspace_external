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
 * Create a simple test cube mesh.
 * 
 * @param mesh_handle Handle to the mesh.
 * @param size Size of the cube.
 * @return 1 if successful, 0 if an error occurred.
 */
ZSPACE_EXTERNAL_API int zext_mesh_create_test_cube(zExtMeshHandle mesh_handle, double size);

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
 * @param out_geodesic_scalars Output array for computed geodesic distances (pre-allocated with size equal to vertex count).
 * @return 1 if successful, 0 if an error occurred.
 */
ZSPACE_EXTERNAL_API int zext_mesh_compute_geodesic_heat(zExtMeshHandle mesh_handle,
                                                      const int* source_vertex_ids, int source_vertex_count,
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
 * Compute shortest path between two vertices.
 * 
 * @param graph_handle Handle to the graph.
 * @param startVertexId Start vertex index.
 * @param endVertexId End vertex index.
 * @param out_pathVertices Output array for vertex indices along the path (pre-allocated).
 * @param out_pathVertexCount Output for the number of vertices in the path.
 * @param maxPathLength Maximum number of vertices in the path (size of out_pathVertices array).
 * @return 1 if successful, 0 if an error occurred.
 */
ZSPACE_EXTERNAL_API int zext_graph_compute_shortest_path(zExtGraphHandle graph_handle,
                                                       int startVertexId, int endVertexId,
                                                       int* out_pathVertices, int* out_pathVertexCount,
                                                       int maxPathLength);

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

#ifdef __cplusplus
}
#endif

#endif // ZSPACE_EXTERNAL_C_API_H 