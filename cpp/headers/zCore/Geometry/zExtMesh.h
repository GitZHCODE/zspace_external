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
     * Create a simple cube mesh for testing purposes.
     * 
     * @param size Size of the cube.
     * @return True if successful, false otherwise.
     */
    bool createTestCube(double size = 1.0);
    
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
    friend int zext_mesh_create_test_cube(zExtMeshHandle, double);
};

} // namespace zSpace

#endif // ZEXT_MESH_H 