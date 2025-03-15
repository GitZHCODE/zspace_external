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

bool zExtMesh::createTestCube(double size) {
    try {
        if (!m_mesh) {
            m_mesh.reset(new zObjMesh());
        }

        // Create a function object for the mesh
        zFnMesh fnMesh(*m_mesh);

        // Clear existing mesh
        fnMesh.clear();

        // Create vertex positions for a cube
        zPointArray positions;
        double halfSize = size / 2.0;

        // Bottom face
        positions.push_back(zPoint(-halfSize, -halfSize, -halfSize));  // 0
        positions.push_back(zPoint(halfSize, -halfSize, -halfSize));   // 1
        positions.push_back(zPoint(halfSize, halfSize, -halfSize));    // 2
        positions.push_back(zPoint(-halfSize, halfSize, -halfSize));   // 3

        // Top face
        positions.push_back(zPoint(-halfSize, -halfSize, halfSize));   // 4
        positions.push_back(zPoint(halfSize, -halfSize, halfSize));    // 5
        positions.push_back(zPoint(halfSize, halfSize, halfSize));     // 6
        positions.push_back(zPoint(-halfSize, halfSize, halfSize));    // 7

        // Create the polygon indices for faces
        zIntArray polyCounts = { 4, 4, 4, 4, 4, 4 }; // 6 faces, each with 4 vertices
        zIntArray polyConnections = {
            // Bottom face
            0, 1, 2, 3,
            // Top face
            4, 7, 6, 5,
            // 4 side faces
            0, 4, 5, 1,  // Front
            1, 5, 6, 2,  // Right
            2, 6, 7, 3,  // Back
            3, 7, 4, 0   // Left
        };

        // Use zFnMesh create method to properly create the mesh
        fnMesh.create(positions, polyCounts, polyConnections);
        bool success = true;
        if (success) {
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

void zExtMesh::updateAttributes() {
    //if (m_mesh) {
    //    m_vertexCount = static_cast<int>(m_mesh->vertices.size());
    //    m_faceCount = static_cast<int>(m_mesh->faces.size());
    //} else {
    //    m_vertexCount = 0;
    //    m_faceCount = 0;
    //}
}

} // namespace zSpace 