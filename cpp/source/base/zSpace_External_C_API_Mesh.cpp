/**
 * \file zSpace_External_C_API_Mesh.cpp
 * \brief Implementation of C API mesh functions - Minimal MVP
 * \date 2023
 */

#include "../../../cpp/headers/base/zSpace_External_C_API.h"
#include "../../../cpp/headers/base/zSpace_External_C_API_Common.h"
#include "../../../cpp/headers/zCore/Geometry/zExtMesh.h"

#include <vector>

extern "C" {

ZSPACE_EXTERNAL_API zExtMeshHandle zext_mesh_create() {
    TRY_CATCH_RETURN(
        auto mesh = new zSpace::zExtMesh();
        return static_cast<zExtMeshHandle>(mesh);
    , nullptr)
}

ZSPACE_EXTERNAL_API int zext_mesh_destroy(zExtMeshHandle mesh_handle) {
    if (!mesh_handle) {
        return 1; // Not an error, already null
    }
    
    TRY_CATCH_RETURN(
        auto* mesh = static_cast<zSpace::zExtMesh*>(mesh_handle);
        delete mesh;
        return 1;
    , 0)
}

ZSPACE_EXTERNAL_API int zext_mesh_is_valid(zExtMeshHandle mesh_handle) {
    if (!mesh_handle) {
        return 0;
    }
    
    TRY_CATCH_RETURN(
        auto* mesh = static_cast<zSpace::zExtMesh*>(mesh_handle);
        return mesh->isValid() ? 1 : 0;
    , 0)
}

ZSPACE_EXTERNAL_API int zext_mesh_get_vertex_count(zExtMeshHandle mesh_handle) {
    TRY_CATCH_RETURN(
        if (!mesh_handle) {
            zSpace::SetError("Invalid mesh handle");
            return -1;
        }
        
        auto* mesh = static_cast<zSpace::zExtMesh*>(mesh_handle);
        return mesh->getVertexCount();
    , -1)
}

ZSPACE_EXTERNAL_API int zext_mesh_get_face_count(zExtMeshHandle mesh_handle) {
    TRY_CATCH_RETURN(
        if (!mesh_handle) {
            zSpace::SetError("Invalid mesh handle");
            return -1;
        }
        
        auto* mesh = static_cast<zSpace::zExtMesh*>(mesh_handle);
        return mesh->getFaceCount();
    , -1)
}

ZSPACE_EXTERNAL_API int zext_mesh_create_test_cube(zExtMeshHandle mesh_handle, double size) {
    TRY_CATCH_RETURN(
        if (!mesh_handle) {
            zSpace::SetError("Invalid mesh handle");
            return 0;
        }
        
        auto* mesh = static_cast<zSpace::zExtMesh*>(mesh_handle);
        return mesh->createTestCube(size) ? 1 : 0;
    , 0)
}

ZSPACE_EXTERNAL_API int zext_mesh_create_mesh(zExtMeshHandle mesh_handle, 
                                          const double* vertexPositions, int vertexCount,
                                          const int* polyCounts, int polyCountsSize,
                                          const int* polyConnections, int polyConnectionsSize) {
    TRY_CATCH_RETURN(
        if (!mesh_handle) {
            zSpace::SetError("Invalid mesh handle");
            return 0;
        }
        
        auto* mesh = static_cast<zSpace::zExtMesh*>(mesh_handle);
        return mesh->createMesh(vertexPositions, vertexCount, polyCounts, polyCountsSize, polyConnections, polyConnectionsSize) ? 1 : 0;
    , 0)
}

} // extern "C" 