/**
 * \file zExtGraph.cpp
 * \brief Implementation of the External graph class for zSpace - Minimal MVP
 * \date 2023
 */

// Include local header (relative to cpp directory)
#include "headers/zCore/Geometry/zExtGraph.h"

// Include zspace_core headers
#include <headers/zInterface/functionsets/zFnGraph.h>
#include <headers/zInterface/objects/zObjGraph.h>

#include <algorithm>
#include <stdexcept>
#include <stack>
#include <set>

namespace zSpace {

zExtGraph::zExtGraph() : m_graph(new zObjGraph()), m_vertexCount(0), m_edgeCount(0) {
}

zExtGraph::zExtGraph(zObjGraph* graph) : m_graph(graph), m_vertexCount(0), m_edgeCount(0) {
    if (m_graph) {
		updateAttributes();
	}
}

zExtGraph::zExtGraph(const zExtGraph& other) : m_vertexCount(other.m_vertexCount), m_edgeCount(other.m_edgeCount) {
    if (other.m_graph) {
        m_graph.reset(new zObjGraph(*other.m_graph));
    } else {
        m_graph.reset(new zObjGraph());
    }
}

zExtGraph::~zExtGraph() = default;

bool zExtGraph::isValid() const {
    return m_graph != nullptr;
}

int zExtGraph::getVertexCount() const {
    return m_vertexCount;
}

int zExtGraph::getEdgeCount() const {
    return m_edgeCount;
}

zObjGraph& zExtGraph::getRawGraph() const {
    if (!m_graph) {
        throw std::runtime_error("Graph is not initialized");
    }
    return *m_graph;
}

void zExtGraph::updateAttributes() {
    if (m_graph) {
        m_vertexCount = static_cast<int>(m_graph->graph.n_v);
        m_edgeCount = static_cast<int>(m_graph->graph.n_e);
    } else {
        m_vertexCount = 0;
        m_edgeCount = 0;
    }
}

bool zExtGraph::createGraph(
    const double* vertexPositions, int vertexCount,
    const int* edgeConnections, int edgeConnectionsSize
) {
    try {
        if (!m_graph) {
            m_graph.reset(new zObjGraph());
        }

        // Create a function object for the graph
        zFnGraph fnGraph(*m_graph);

        // Clear existing graph
        fnGraph.clear();

        // Convert vertex positions to zPoint array
        zPointArray positions;
        positions.reserve(vertexCount);

        for (int i = 0; i < vertexCount; i++) {
            int baseIndex = i * 3; // Each vertex has 3 components (x, y, z)
            positions.push_back(zPoint(
                vertexPositions[baseIndex],
                vertexPositions[baseIndex + 1],
                vertexPositions[baseIndex + 2]
            ));
        }

        // Create edges
        zIntArray edgeConnects;
        edgeConnects.reserve(edgeConnectionsSize);
        for (int i = 0; i < edgeConnectionsSize; i++) {
            edgeConnects.push_back(edgeConnections[i]);
        }

        fnGraph.create(positions, edgeConnects);

        // Check if creation was successful
        if (fnGraph.numVertices() > 0) {
            updateAttributes();
            return true;
        } else {
            // Reset graph in case of failure
            m_graph.reset(new zObjGraph());
            m_vertexCount = 0;
            m_edgeCount = 0;
            return false;
        }
    } catch (const std::exception&) {
        // Reset graph in case of failure
        m_graph.reset(new zObjGraph());
        m_vertexCount = 0;
        m_edgeCount = 0;
        return false;
    }
}

bool zExtGraph::getGraphData(
    std::vector<double>& vertexPositions,
    std::vector<int>& edgeConnections
)
{
    try {
        if (!m_graph) {
            return false;
        }

        zFnGraph fnGraph(*m_graph);
        
        // Get vertex positions (zPoint array)
        std::vector<zPoint> positions;
        fnGraph.getVertexPositions(positions);
        
        // Convert zPoint array to flat double array (x1,y1,z1,x2,y2,z2,...)
        // This is for easier interop with external applications
        vertexPositions.clear();
        vertexPositions.reserve(positions.size() * 3);
        for (size_t i = 0; i < positions.size(); i++) {
            vertexPositions.push_back(positions[i].x);
            vertexPositions.push_back(positions[i].y);
            vertexPositions.push_back(positions[i].z);
        }
        
        // Special handling for edge connections:
        // First check if graph has a "polyline form" - a continuous sequence
        // where vertices have valency 1 (endpoints) or 2 (interior points)
        bool hasPolylineForm = true;
        int numEndVertices = 0;  // Vertices with valency 1 (endpoints)

        zItGraphVertex v(*m_graph);
        int heId = 0;  // Store half-edge ID for traversal starting point
        for (; !v.end(); v++)
        {
            if (v.checkValency(1))  // Found an endpoint
            {
                heId = v.getHalfEdge().getId();
                numEndVertices++;
            }
            else if (v.checkValency(2)) continue;  // Interior point in polyline
            else
            {
                // Found vertex with valency != 1 or 2, not a polyline
                hasPolylineForm = false;
                break;
            }
        }

        // A polyline can have at most 2 endpoints (unless it's a cycle)
        if (numEndVertices > 2) hasPolylineForm = false;

        if (hasPolylineForm)
        {
            // For polyline form, we need to traverse from one end to the other
            // to maintain proper ordering of edge connections
            edgeConnections.clear();

            // Start traversal from one endpoint
            zItGraphHalfEdge he(*m_graph, heId);
            bool quit = false;
            do {
                // Add current edge connection
                edgeConnections.push_back(he.getStartVertex().getId());
                edgeConnections.push_back(he.getVertex().getId());

                he = he.getNext();

                // Stop if we reach the starting point (closed polyline)
                if (he.getId() == heId) quit = true;
                // Or if we reach the other endpoint (open polyline)
                else if (he.getVertex().checkValency(1))
                {
                    edgeConnections.push_back(he.getStartVertex().getId());
                    edgeConnections.push_back(he.getVertex().getId());
                    quit = true;
                }
            } while (!quit);
        }
        else
        {
            // For non-polyline graphs (general case), use standard edge data extraction
			fnGraph.getEdgeData(edgeConnections);
        }
        
        return true;
    }
    catch (const std::exception&) {
        return false;
    }
}

bool zExtGraph::setVertexPositions(
    const double* vertexPositions, int vertexCount
) {
    try {
        if (!m_graph || !vertexPositions || vertexCount <= 0) {
            return false;
        }

        // Create a function object for the graph
        zFnGraph fnGraph(*m_graph);
        
        // Validate vertex count
        if (vertexCount != m_vertexCount) {
            return false;
        }

        // Update vertex positions
        zPointArray pos;
        pos.reserve(vertexCount);
        for (int i = 0; i < vertexCount; i++) {
            int baseIndex = i * 3; // Each vertex has 3 components (x, y, z)
            pos.emplace_back(
                vertexPositions[baseIndex],
                vertexPositions[baseIndex + 1],
                vertexPositions[baseIndex + 2]
            );
        }
        fnGraph.setVertexPositions(pos);


        return true;
    } catch (const std::exception&) {
        return false;
    }
}

bool zExtGraph::getVertexPositions(
    double* out_vertexPositions
) {
    try {
        if (!m_graph || !out_vertexPositions || m_vertexCount <= 0) {
            return false;
        }

        // Create a function object for the graph
        zFnGraph fnGraph(*m_graph);

        // Get vertex positions
        zPointArray pos;
        fnGraph.getVertexPositions(pos);
        for (int i = 0; i < m_vertexCount; i++) {
            int baseIndex = i * 3; // Each vertex has 3 components (x, y, z)
            out_vertexPositions[baseIndex] = pos[i].x;
            out_vertexPositions[baseIndex + 1] = pos[i].y;
            out_vertexPositions[baseIndex + 2] = pos[i].z;
        }

        return true;
    } catch (const std::exception&) {
        return false;
    }
}

bool zExtGraph::mergeVertices(
    double tolerance
)
{
    try {
        if (!m_graph) {
            return false;
        }
        // Square distance tolerance
        tolerance *= tolerance;

        // Create a function object for the graph
        zFnGraph fnGraph(*m_graph);

        // Get original data
        zPointArray vertexPositions;
        zIntArray edgeConnections;
        fnGraph.getVertexPositions(vertexPositions);
        fnGraph.getEdgeData(edgeConnections);

        // Maps original vertex indices to new indices
        std::vector<int> vertexMapping(vertexPositions.size(), -1);

        // New vertex positions
        zPointArray newPositions;

        // First pass: Group vertices by proximity
        for (int i = 0; i < vertexPositions.size(); i++) {
            // Skip if this vertex is already mapped
            if (vertexMapping[i] != -1) continue;

            // This is a new unique vertex
            int newIndex = newPositions.size();
            newPositions.push_back(vertexPositions[i]);
            vertexMapping[i] = newIndex;

            // Find all vertices close to this one
            for (int j = i + 1; j < vertexPositions.size(); j++) {
                if (vertexMapping[j] == -1 &&
                    vertexPositions[i].squareDistanceTo(vertexPositions[j]) < tolerance) {
                    // Merge j into i
                    vertexMapping[j] = newIndex;
                }
            }
        }

        // Second pass: Update edge connections
        zIntArray newConnections;
        for (int i = 0; i < edgeConnections.size(); i++) {
            newConnections.push_back(vertexMapping[edgeConnections[i]]);
        }

        // Recreate graph with new data
        fnGraph.create(newPositions, newConnections);
        updateAttributes();

        return true;
    }
    catch (const std::exception&) {
        return false;
    }
}

bool zExtGraph::separateGraph(
    std::vector<zExtGraph*>& out_components
) {
    try {
        if (!m_graph) {
            return false;
        }

        // Clear any existing components in the output vector
        for (auto& component : out_components) {
            delete component;
        }
        out_components.clear();

        // Create a function object for the graph
        zFnGraph fnGraph(*m_graph);

        // If graph is empty, return true (no components)
        if (fnGraph.numVertices() == 0) {
            return true;
        }

        // Track visited vertices
        std::vector<bool> visited(fnGraph.numVertices(), false);

        // Process each unvisited vertex to find components
        for (int startVertex = 0; startVertex < fnGraph.numVertices(); startVertex++) {
            if (visited[startVertex]) continue;

            // Initialize new component
            zPointArray componentVertices;
            zIntArray componentEdges;
            std::map<int, int> oldToNewIndex;

            // Use stack for DFS
            std::stack<int> dfsStack;
            dfsStack.push(startVertex);

            // First pass: collect vertices
            while (!dfsStack.empty()) {
                int currentVertex = dfsStack.top();
                dfsStack.pop();

                if (!visited[currentVertex]) {
                    visited[currentVertex] = true;

                    // Add vertex to component
                    zItGraphVertex v(*m_graph, currentVertex);
                    if (!v.checkValency(0)) {
                        componentVertices.push_back(v.getPosition());
                        oldToNewIndex[currentVertex] = componentVertices.size() - 1;

                        // Get connected vertices
                        zIntArray connectedVerts;
                        v.getConnectedVertices(connectedVerts);

                        // Add unvisited neighbors to stack
                        for (int neighbor : connectedVerts) {
                            if (!visited[neighbor]) {
                                dfsStack.push(neighbor);
                            }
                        }
                    }
                }
            }

            // Second pass: collect edges - using a set to track added edges
            std::set<std::pair<int, int>> addedEdges;
            
            for (auto& pair : oldToNewIndex) {
                int oldIndex = pair.first;
                zItGraphVertex v(*m_graph, oldIndex);

                zIntArray connectedVerts;
                v.getConnectedVertices(connectedVerts);

                for (int neighbor : connectedVerts) {
                    // Add edge if both vertices are in this component
                    if (oldToNewIndex.find(neighbor) != oldToNewIndex.end()) {
                        // Create a normalized pair (smaller index first) to avoid duplicates
                        int newIndex1 = oldToNewIndex[oldIndex];
                        int newIndex2 = oldToNewIndex[neighbor];
                        std::pair<int, int> edgePair = newIndex1 < newIndex2 ? 
                            std::make_pair(newIndex1, newIndex2) : 
                            std::make_pair(newIndex2, newIndex1);
                            
                        // Only add edge if we haven't added it yet
                        if (addedEdges.find(edgePair) == addedEdges.end()) {
                            componentEdges.push_back(edgePair.first);
                            componentEdges.push_back(edgePair.second);
                            addedEdges.insert(edgePair);
                        }
                    }
                }
            }

            // Create new graph component if valid
            if (componentVertices.size() >= 2 && !componentEdges.empty()) {
                zObjGraph* component = new zObjGraph();
                zFnGraph fnComponent(*component);
                fnComponent.create(componentVertices, componentEdges);
                out_components.push_back(new zExtGraph(component));
            }
        }

        return true;
    } catch (const std::exception&) {
        // Clean up any components created so far
        for (auto& component : out_components) {
            delete component;
        }
        out_components.clear();
        return false;
    }
}

} // namespace zSpace 