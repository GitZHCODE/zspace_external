/**
 * \file zExtMesh.cpp
 * \brief Implementation of the External mesh class for zSpace - Minimal MVP
 * \date 2023
 */

// Include local header (relative to cpp directory)
#include "headers/zCore/Geometry/zExtMesh.h"

// Include zspace_core headers
#include <headers/zInterface/functionsets/zFnMesh.h>
#include <headers/zInterface/objects/zObjMesh.h>
#include <headers/zToolsets/geometry/zTsMeshParameterization.h>

#include <algorithm>
#include <stdexcept>

namespace zSpace {

zExtMesh::zExtMesh() : m_mesh(new zObjMesh()), m_vertexCount(0), m_faceCount(0) {
}

zExtMesh::zExtMesh(zObjMesh* mesh) : m_mesh(mesh), m_vertexCount(0), m_faceCount(0) {
    if (m_mesh) {
		updateAttributes();
	}
}

zExtMesh::zExtMesh(const zExtMesh& other) : m_vertexCount(other.m_vertexCount), m_faceCount(other.m_faceCount) {
    if (other.m_mesh) {
        m_mesh.reset(new zObjMesh(*other.m_mesh));
    } else {
        m_mesh.reset(new zObjMesh());
    }
}

zExtMesh::~zExtMesh() = default;

bool zExtMesh::isValid() const {
    return m_mesh != nullptr;
}

int zExtMesh::getVertexCount() const {
    return m_vertexCount;
}

int zExtMesh::getFaceCount() const {
    return m_faceCount;
}

void zExtMesh::updateAttributes() {
    if (m_mesh) {
        m_vertexCount = static_cast<int>(m_mesh->mesh.n_v);
        m_faceCount = static_cast<int>(m_mesh->mesh.n_f);
    } else {
        m_vertexCount = 0;
        m_faceCount = 0;
    }
}

bool zExtMesh::createMesh(
    const double* vertexPositions, int vertexCount,
    const int* polyCounts, int polyCountsSize,
    const int* polyConnections, int polyConnectionsSize
) {
    try {
        if (!m_mesh) {
            m_mesh.reset(new zObjMesh());
        }

        // Create a function object for the mesh
        zFnMesh fnMesh(*m_mesh);

        // Clear existing mesh
        fnMesh.clear();

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

        // Convert polygon counts to zIntArray
        zIntArray polyCountsArray;
        polyCountsArray.reserve(polyCountsSize);
        for (int i = 0; i < polyCountsSize; i++) {
            polyCountsArray.push_back(polyCounts[i]);
        }

        // Convert polygon connections to zIntArray
        zIntArray polyConnectionsArray;
        polyConnectionsArray.reserve(polyConnectionsSize);
        for (int i = 0; i < polyConnectionsSize; i++) {
            polyConnectionsArray.push_back(polyConnections[i]);
        }

        // Create the mesh
        fnMesh.create(positions, polyCountsArray, polyConnectionsArray);

        // Check if creation was successful
        if (fnMesh.numVertices() > 0) {
            updateAttributes();
            return true;
        } else {
            // Reset mesh in case of failure
            m_mesh.reset(new zObjMesh());
            m_vertexCount = 0;
            m_faceCount = 0;
            return false;
        }
    } catch (const std::exception&) {
        // Reset mesh in case of failure
        m_mesh.reset(new zObjMesh());
        m_vertexCount = 0;
        m_faceCount = 0;
        return false;
    }
}

bool zExtMesh::computeGeodesicHeat(
    const int* sourceVIds, int sourceVCount,
    float* out_geodesicScalars
)
{
    try {
        if (!m_mesh || !out_geodesicScalars || !sourceVIds || sourceVCount <= 0) {
            // Initialize the output array to zeros in case of error
            if (out_geodesicScalars && m_vertexCount > 0) {
                for (int i = 0; i < m_vertexCount; i++) {
                    out_geodesicScalars[i] = 0.0f;
                }
            }
            return false;
        }

        // Validate if all source vertex IDs are in valid range
        for (int i = 0; i < sourceVCount; i++) {
            if (sourceVIds[i] < 0 || sourceVIds[i] >= m_vertexCount) {
                // Invalid vertex index detected
                for (int j = 0; j < m_vertexCount; j++) {
                    out_geodesicScalars[j] = 0.0f;
                }
                return false;
            }
        }

        // Setup mesh parameterization
        zTsMeshParam myMeshParam;
        myMeshParam.o_TriMesh = *m_mesh;
        
        zFnMesh fnMesh(myMeshParam.o_TriMesh);
        fnMesh.computeMeshNormals();
        fnMesh.getMatrices_trimesh(myMeshParam.triMesh_V, myMeshParam.triMesh_FTris);

        // Initialize the output array to zeros
        for (int i = 0; i < m_vertexCount; i++) {
            out_geodesicScalars[i] = 0.0f;
        }

        // Compute geodesic heat
        zDomainFloat outMinMax(0, 1);

        // Convert source IDs to vector
        vector<int> sourceVertices;
        sourceVertices.reserve(sourceVCount);
        for (int i = 0; i < sourceVCount; i++) {
            sourceVertices.push_back(sourceVIds[i]);
        }

        // Compute geodesic distances
        vector<float> geodesicsScalars;
        myMeshParam.computeGeodesics_Heat(sourceVertices, geodesicsScalars);
        
        // Check if we got valid results
        if (geodesicsScalars.size() == 0 || geodesicsScalars.size() != (size_t)m_vertexCount) {
            return false;
        }

        // Normalize values to [0,1] range
        zDomainFloat startMinMax(myMeshParam.coreUtils.zMin(geodesicsScalars), myMeshParam.coreUtils.zMax(geodesicsScalars));
        for (auto& v : geodesicsScalars) {
            v = myMeshParam.coreUtils.ofMap(v, startMinMax, outMinMax);
        }

        // Copy results to output array (safely handling size differences)
        int copySize = min((int)geodesicsScalars.size(), m_vertexCount);
        for (int i = 0; i < copySize; i++) {
            out_geodesicScalars[i] = geodesicsScalars[i];
        }

        // Color the mesh
        zColor* mesh_vColors = fnMesh.getRawVertexColors();

        zScalar minScalar = myMeshParam.coreUtils.zMin(geodesicsScalars);
        zScalar maxScalar = myMeshParam.coreUtils.zMax(geodesicsScalars);

        zDomainFloat distanceDomain(minScalar, maxScalar);
        zDomainColor colDomain(zColor(1, 0, 0, 1), zColor(0, 1, 0, 1));

        for (int i = 0; i < min(fnMesh.numVertices(), (int)geodesicsScalars.size()); i++) {
            mesh_vColors[i] = myMeshParam.coreUtils.blendColor(geodesicsScalars[i], distanceDomain, colDomain, zRGB);
        }

        fnMesh.computeFaceColorfromVertexColor();

        return true;
    }
    catch (const std::exception& e) {
        // Initialize the output array to zeros in case of error
        if (out_geodesicScalars && m_vertexCount > 0) {
            for (int i = 0; i < m_vertexCount; i++) {
                out_geodesicScalars[i] = 0.0f;
            }
        }
        return false;
    }
    catch (...) {
        // Initialize the output array to zeros in case of error
        if (out_geodesicScalars && m_vertexCount > 0) {
            for (int i = 0; i < m_vertexCount; i++) {
                out_geodesicScalars[i] = 0.0f;
            }
        }
        return false;
    }
}

} // namespace zSpace 