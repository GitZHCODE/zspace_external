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

ZSPACE_EXTERNAL_API int zext_graph_get_graph_data(zExtGraphHandle graph_handle, 
                                              bool checkCount,
                                              double* vertexPositions, int* vertexCount,
                                              int* edgeConnections, int* edgeConnectionsSize)
{
    TRY_CATCH_RETURN(
        if (!graph_handle) {
            zSpace::SetError("Invalid graph handle");
            return 0;
        }
        
        // Check if output pointers for sizes are valid
        if (!vertexCount || !edgeConnectionsSize) {
            zSpace::SetError("Invalid output size pointers");
            return 0;
        }
        
        auto* graph = static_cast<zSpace::zExtGraph*>(graph_handle);
        
        // Create vectors to hold the data
        std::vector<double> positions;
        std::vector<int> connects;
        
        // Get the graph data
        bool success = graph->getGraphData(positions, connects);
        
        if (!success) {
            zSpace::SetError("Failed to get graph data");
            return 0;
        }
        
        // Store the counts
        int numPositions = static_cast<int>(positions.size());
        int numConnects = static_cast<int>(connects.size());
        
        // Set the output count values
        *vertexCount = numPositions;
        *edgeConnectionsSize = numConnects;
        
        // If checkCount is true, we only return the sizes without copying data
        if (checkCount) {
            return 1; // Success
        }
        
        // When not just checking counts, make sure output arrays are valid
        if (!vertexPositions || !edgeConnections) {
            zSpace::SetError("Invalid output array pointers");
            return 0;
        }
        
        // Copy the data to the output arrays
        for (int i = 0; i < numPositions; i++) {
            vertexPositions[i] = positions[i];
        }
        
        for (int i = 0; i < numConnects; i++) {
            edgeConnections[i] = connects[i];
        }
        
        return 1; // Success
    , 0) // Return 0 on exception
}

ZSPACE_EXTERNAL_API int zext_graph_merge_vertices(zExtGraphHandle graph_handle, double tolerance) {
    TRY_CATCH_RETURN(
        if (!graph_handle) {
            zSpace::SetError("Invalid graph handle");
            return 0;
        }
        
        if (tolerance < 0) {
            zSpace::SetError("Tolerance must be non-negative");
            return 0;
        }
        
        auto* graph = static_cast<zSpace::zExtGraph*>(graph_handle);
        return graph->mergeVertices(tolerance) ? 1 : 0;
    , 0)
}

ZSPACE_EXTERNAL_API int zext_graph_separate_graph(zExtGraphHandle graph_handle, bool checkCount,
                                             zExtGraphHandle* out_components, int* out_component_count) {
    TRY_CATCH_RETURN(
        if (!graph_handle) {
            zSpace::SetError("Invalid graph handle");
            return 0;
        }
        
        // Check if output count pointer is valid
        if (!out_component_count) {
            zSpace::SetError("Invalid output count parameter");
            return 0;
        }
        
        auto* graph = static_cast<zSpace::zExtGraph*>(graph_handle);
        
        // Temporary storage for the components
        std::vector<zSpace::zExtGraph*> componentGraphs;
        
        // Compute the components
        bool success = graph->separateGraph(componentGraphs);
        
        if (!success) {
            *out_component_count = 0;
            return 0;
        }
        
        // Return the count of components
        int totalComponents = static_cast<int>(componentGraphs.size());
        *out_component_count = totalComponents;
        
        // If checkCount is true, we only return the count without copying data
        if (checkCount) {
            // Free all components
            for (auto& component : componentGraphs) {
                delete component;
            }
            return 1; // Success
        }
        
        // When not just checking counts, make sure output array is valid
        if (!out_components) {
            zSpace::SetError("Invalid output array pointer");
            
            // Free all components
            for (auto& component : componentGraphs) {
                delete component;
            }
            return 0;
        }
        
        // Copy the components to the output array
        for (int i = 0; i < totalComponents; i++) {
            out_components[i] = static_cast<zExtGraphHandle>(componentGraphs[i]);
        }
        
        return 1;
    , 0)
}

ZSPACE_EXTERNAL_API int zext_graph_transform(zExtGraphHandle graph_handle,
	const float* tMatrix) {
	TRY_CATCH_RETURN(
		if (!graph_handle) {
			zSpace::SetError("Invalid graph handle");
			return 0;
		}

	if (!tMatrix) {
		zSpace::SetError("Invalid transformation matrix");
		return 0;
	}

	auto* graph = static_cast<zSpace::zExtGraph*>(graph_handle);
	return graph->transform(tMatrix) ? 1 : 0;
	, 0)
}

} // extern "C" 