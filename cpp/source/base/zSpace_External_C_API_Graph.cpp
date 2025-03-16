/**
 * \file zSpace_External_C_API_Graph.cpp
 * \brief Implementation of C API graph functions - Minimal MVP
 * \date 2023
 */

#include "../../../cpp/headers/base/zSpace_External_C_API.h"
#include "../../../cpp/headers/base/zSpace_External_C_API_Common.h"
#include "../../../cpp/headers/zCore/Geometry/zExtGraph.h"

#include <vector>

extern "C" {

ZSPACE_EXTERNAL_API zExtGraphHandle zext_graph_create() {
    TRY_CATCH_RETURN(
        auto graph = new zSpace::zExtGraph();
        return static_cast<zExtGraphHandle>(graph);
    , nullptr)
}

ZSPACE_EXTERNAL_API int zext_graph_destroy(zExtGraphHandle graph_handle) {
    if (!graph_handle) {
        return 1; // Not an error, already null
    }
    
    TRY_CATCH_RETURN(
        auto* graph = static_cast<zSpace::zExtGraph*>(graph_handle);
        delete graph;
        return 1;
    , 0)
}

ZSPACE_EXTERNAL_API int zext_graph_is_valid(zExtGraphHandle graph_handle) {
    if (!graph_handle) {
        return 0;
    }
    
    TRY_CATCH_RETURN(
        auto* graph = static_cast<zSpace::zExtGraph*>(graph_handle);
        return graph->isValid() ? 1 : 0;
    , 0)
}

ZSPACE_EXTERNAL_API int zext_graph_get_vertex_count(zExtGraphHandle graph_handle) {
    TRY_CATCH_RETURN(
        if (!graph_handle) {
            zSpace::SetError("Invalid graph handle");
            return -1;
        }
        
        auto* graph = static_cast<zSpace::zExtGraph*>(graph_handle);
        return graph->getVertexCount();
    , -1)
}

ZSPACE_EXTERNAL_API int zext_graph_get_edge_count(zExtGraphHandle graph_handle) {
    TRY_CATCH_RETURN(
        if (!graph_handle) {
            zSpace::SetError("Invalid graph handle");
            return -1;
        }
        
        auto* graph = static_cast<zSpace::zExtGraph*>(graph_handle);
        return graph->getEdgeCount();
    , -1)
}

ZSPACE_EXTERNAL_API int zext_graph_create_graph(zExtGraphHandle graph_handle, 
                                             const double* vertexPositions, int vertexCount,
                                             const int* edgeConnections, int edgeConnectionsSize) {
    TRY_CATCH_RETURN(
        if (!graph_handle) {
            zSpace::SetError("Invalid graph handle");
            return 0;
        }
        
        auto* graph = static_cast<zSpace::zExtGraph*>(graph_handle);
        return graph->createGraph(vertexPositions, vertexCount, edgeConnections, edgeConnectionsSize) ? 1 : 0;
    , 0)
}

ZSPACE_EXTERNAL_API int zext_graph_compute_shortest_path(zExtGraphHandle graph_handle,
                                                      int startVertexId, int endVertexId,
                                                      int* out_pathVertices, int* out_pathVertexCount,
                                                      int maxPathLength) {
    TRY_CATCH_RETURN(
        if (!graph_handle) {
            zSpace::SetError("Invalid graph handle");
            return 0;
        }
        
        if (!out_pathVertices || !out_pathVertexCount) {
            zSpace::SetError("Invalid output arrays");
            return 0;
        }
        
        auto* graph = static_cast<zSpace::zExtGraph*>(graph_handle);
        return graph->computeShortestPath(startVertexId, endVertexId, out_pathVertices, out_pathVertexCount, maxPathLength) ? 1 : 0;
    , 0)
}

ZSPACE_EXTERNAL_API int zext_graph_set_vertex_positions(zExtGraphHandle graph_handle,
                                                     const double* vertexPositions, int vertexCount) {
    TRY_CATCH_RETURN(
        if (!graph_handle) {
            zSpace::SetError("Invalid graph handle");
            return 0;
        }
        
        if (!vertexPositions || vertexCount <= 0) {
            zSpace::SetError("Invalid vertex positions");
            return 0;
        }
        
        auto* graph = static_cast<zSpace::zExtGraph*>(graph_handle);
        return graph->setVertexPositions(vertexPositions, vertexCount) ? 1 : 0;
    , 0)
}

ZSPACE_EXTERNAL_API int zext_graph_get_vertex_positions(zExtGraphHandle graph_handle,
                                                     double* out_vertexPositions) {
    TRY_CATCH_RETURN(
        if (!graph_handle) {
            zSpace::SetError("Invalid graph handle");
            return 0;
        }
        
        if (!out_vertexPositions) {
            zSpace::SetError("Invalid output array");
            return 0;
        }
        
        auto* graph = static_cast<zSpace::zExtGraph*>(graph_handle);
        return graph->getVertexPositions(out_vertexPositions) ? 1 : 0;
    , 0)
}

} // extern "C" 