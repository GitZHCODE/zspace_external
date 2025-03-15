/**
 * \file zExtMesh.h
 * \brief External mesh class for zSpace - Minimal MVP
 * \date 2023
 */

#ifndef ZEXT_MESH_H
#define ZEXT_MESH_H

#include <memory>
#include <vector>
#include <string>

// Include the C API header for declarations
#include "headers/base/zSpace_External_C_API.h"

// Forward declaration to avoid including zObjMesh.h directly
namespace zSpace {
    class zObjMesh;
}

// Handle type forward declaration
typedef void* zExtMeshHandle;

namespace zSpace {

/**
 * External mesh class that provides a simplified interface for mesh operations.
 * Minimal MVP implementation.
 */
class zExtMesh {
public:
    /**
     * Default constructor. Creates an empty mesh.
     */
    zExtMesh();
    
    /**
     * Constructor that takes ownership of a zObjMesh pointer.
     * 
     * @param mesh Pointer to a zObjMesh object to take ownership of.
     */
    explicit zExtMesh(zObjMesh* mesh);
    
    /**
     * Copy constructor.
     */
    zExtMesh(const zExtMesh& other);
    
    /**
     * Destructor.
     */
    ~zExtMesh();
    
    /**
     * Check if the mesh is valid.
     * 
     * @return True if the mesh is valid, false otherwise.
     */
    bool isValid() const;
    
    /**
     * Get the number of vertices in the mesh.
     * 
     * @return Number of vertices.
     */
    int getVertexCount() const;
    
    /**
     * Get the number of faces in the mesh.
     * 
     * @return Number of faces.
     */
    int getFaceCount() const;
    
    /**
     * Create a mesh from the given vertex positions and face data.
     * 
     * @param vertexPositions Array of vertex positions (x1, y1, z1, x2, y2, z2, ...)
     * @param vertexCount Number of vertices (vertexPositions.length / 3)
     * @param polyCounts Array specifying number of vertices per face
     * @param polyCountsSize Size of the polyCounts array
     * @param polyConnections Array of vertex indices for each face
     * @param polyConnectionsSize Size of the polyConnections array
     * @return True if successful, false otherwise.
     */
    bool createMesh(
        const double* vertexPositions, int vertexCount,
        const int* polyCounts, int polyCountsSize,
        const int* polyConnections, int polyConnectionsSize
    );
    
    /**
     * Compute geodesic distances using the heat method.
     * 
     * @param sourceVIds Array of source vertex indices
     * @param sourceVCount Number of source vertices
     * @param out_geodesicScalars Output array for computed geodesic distances (pre-allocated with size equal to vertex count)
     * @return True if successful, false otherwise.
     */
    bool computeGeodesicHeat(
        const int* sourceVIds, int sourceVCount,
        float* out_geodesicScalars
    );
    
private:
    /**
     * Update internal attributes (vertex and face counts).
     */
    void updateAttributes();
    
    // The underlying mesh object
    std::unique_ptr<zObjMesh> m_mesh;
    
    // Cached attributes for quick access
    int m_vertexCount;
    int m_faceCount;
    
    // Friend declarations for C API access
    friend zExtMeshHandle zext_mesh_create();
    friend int zext_mesh_destroy(zExtMeshHandle);
    friend int zext_mesh_is_valid(zExtMeshHandle);
    friend int zext_mesh_get_vertex_count(zExtMeshHandle);
    friend int zext_mesh_get_face_count(zExtMeshHandle);
    friend int zext_mesh_compute_geodesic_heat(zExtMeshHandle, const int*, int, float*);
};

} // namespace zSpace

#endif // ZEXT_MESH_H 