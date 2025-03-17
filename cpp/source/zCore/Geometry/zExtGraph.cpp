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
        vertexPositions.clear();
        vertexPositions.reserve(positions.size() * 3);
        for (size_t i = 0; i < positions.size(); i++) {
            vertexPositions.push_back(positions[i].x);
            vertexPositions.push_back(positions[i].y);
            vertexPositions.push_back(positions[i].z);
        }
        
        // Get edge connections
        fnGraph.getEdgeData(edgeConnections);
        
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

} // namespace zSpace 