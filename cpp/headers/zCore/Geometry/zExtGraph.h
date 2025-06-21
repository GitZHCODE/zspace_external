/**
 * \file zExtGraph.h
 * \brief External graph class for zSpace - Minimal MVP
 * \date 2023
 */

#ifndef ZEXT_GRAPH_H
#define ZEXT_GRAPH_H

#include <memory>
#include <vector>
#include <string>

// Include the C API header for declarations
#include "headers/base/zSpace_External_C_API.h"

// Forward declaration to avoid including zObjGraph.h directly
namespace zSpace {
    class zObjGraph;
}

// Handle type forward declaration
typedef void* zExtGraphHandle;

namespace zSpace {

/**
 * External graph class that provides a simplified interface for graph operations.
 * Minimal MVP implementation.
 */
class zExtGraph {
public:
    /**
     * Default constructor. Creates an empty graph.
     */
    zExtGraph();
    
    /**
     * Constructor that takes ownership of a zObjGraph pointer.
     * 
     * @param graph Pointer to a zObjGraph object to take ownership of.
     */
    explicit zExtGraph(zObjGraph* graph);
    
    /**
     * Copy constructor.
     */
    zExtGraph(const zExtGraph& other);
    
    /**
     * Destructor.
     */
    ~zExtGraph();
    
    /**
     * Check if the graph is valid.
     * 
     * @return True if the graph is valid, false otherwise.
     */
    bool isValid() const;
    
    /**
     * Get the number of vertices in the graph.
     * 
     * @return Number of vertices.
     */
    int getVertexCount() const;
    
    /**
     * Get the number of edges in the graph.
     * 
     * @return Number of edges.
     */
    int getEdgeCount() const;
    
    /**
     * Get the raw internal graph object.
     * Use with caution as this exposes the internal implementation.
     * 
     * @return Reference to the internal zObjGraph object.
     */
    zObjGraph& getRawGraph() const;
    
    /**
     * Create a graph from the given vertex positions and edge data.
     * 
     * @param vertexPositions Array of vertex positions (x1, y1, z1, x2, y2, z2, ...)
     * @param vertexCount Number of vertices (vertexPositions.length / 3)
     * @param edgeConnections Array of vertex indices for each edge (start1, end1, start2, end2, ...)
     * @param edgeConnectionsSize Size of the edgeConnections array (number of edges * 2)
     * @return True if successful, false otherwise.
     */
    bool createGraph(
        const double* vertexPositions, int vertexCount,
        const int* edgeConnections, int edgeConnectionsSize
    );

    /**
     * Get graph data including vertex positions and edge connections.
     *
     * @param vertexPositions Output vector for vertex positions (x1, y1, z1, x2, y2, z2, ...)
     * @param edgeConnections Output vector for edge connections (start1, end1, start2, end2, ...)
     * @return True if successful, false otherwise.
     */
    bool getGraphData(
        std::vector<double>& vertexPositions,
        std::vector<int>& edgeConnections
    );
    
    /**
     * Set vertex positions in the graph.
     * 
     * @param vertexPositions Array of vertex positions (x1, y1, z1, x2, y2, z2, ...)
     * @param vertexCount Number of vertices (vertexPositions.length / 3)
     * @return True if successful, false otherwise.
     */
    bool setVertexPositions(
        const double* vertexPositions, int vertexCount
    );
    
    /**
     * Get vertex positions from the graph.
     * 
     * @param out_vertexPositions Output array for vertex positions (pre-allocated with size equal to vertex count * 3)
     * @return True if successful, false otherwise.
     */
    bool getVertexPositions(
        double* out_vertexPositions
    );
    
    /**
     * Merge vertices in the graph that are within a given tolerance distance of each other.
     * This operation is useful for cleaning up graphs with duplicate or nearly-duplicate vertices.
     * After merging, edges will be reindexed to use the updated vertex indices.
     *
     * @param tolerance Maximum distance between vertices to be considered for merging
     * @return True if successful, false otherwise
     */
    bool mergeVertices(
        double tolerance
    );
    
    /**
     * Separates a graph into its disconnected components.
     * Each component is a subgraph that has no connections to other components.
     * 
     * @param out_components Output vector of separated graph components
     * @return True if successful, false otherwise
     */
    bool separateGraph(
        std::vector<zExtGraph*>& out_components
    );
    
    /**
    * Update internal attributes (vertex and edge counts).
    */
    void updateAttributes();

private:
    // The underlying graph object
    std::unique_ptr<zObjGraph> m_graph;
    
    // Cached attributes for quick access
    int m_vertexCount;
    int m_edgeCount;
    
    // Friend declarations for C API access
    friend zExtGraphHandle zext_graph_create();
    friend int zext_graph_destroy(zExtGraphHandle);
    friend int zext_graph_is_valid(zExtGraphHandle);
    friend int zext_graph_get_vertex_count(zExtGraphHandle);
    friend int zext_graph_get_edge_count(zExtGraphHandle);
    friend int zext_graph_create_graph(zExtGraphHandle, const double*, int, const int*, int);
    friend int zext_graph_set_vertex_positions(zExtGraphHandle, const double*, int);
    friend int zext_graph_get_vertex_positions(zExtGraphHandle, double*);
    friend int zext_graph_merge_vertices(zExtGraphHandle, double);
};

} // namespace zSpace

#endif // ZEXT_GRAPH_H 