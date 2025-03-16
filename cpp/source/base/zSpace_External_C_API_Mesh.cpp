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

ZSPACE_EXTERNAL_API int zext_mesh_compute_geodesic_heat(zExtMeshHandle mesh_handle, 
                                                    const int* source_vertex_ids, int source_vertex_count,
                                                    float* out_geodesic_scalars) {
    TRY_CATCH_RETURN(
        if (!mesh_handle) {
            zSpace::SetError("Invalid mesh handle");
            return 0;
        }
        
        if (!source_vertex_ids || source_vertex_count <= 0) {
            zSpace::SetError("Invalid source vertices");
            return 0;
        }
        
        if (!out_geodesic_scalars) {
            zSpace::SetError("Invalid output array");
            return 0;
        }
        
        auto* mesh = static_cast<zSpace::zExtMesh*>(mesh_handle);
        return mesh->computeGeodesicHeat(source_vertex_ids, source_vertex_count, out_geodesic_scalars) ? 1 : 0;
    , 0)
}

ZSPACE_EXTERNAL_API int zext_mesh_compute_geodesic_heat_interpolated(zExtMeshHandle mesh_handle,
                                                                 const int* start_vertex_ids, int start_vertex_count,
                                                                 const int* end_vertex_ids, int end_vertex_count,
                                                                 float weight,
                                                                 float* out_geodesic_scalars) {
    TRY_CATCH_RETURN(
        if (!mesh_handle) {
            zSpace::SetError("Invalid mesh handle");
            return 0;
        }
        
        if (!start_vertex_ids || start_vertex_count <= 0) {
            zSpace::SetError("Invalid start vertices");
            return 0;
        }
        
        if (!end_vertex_ids || end_vertex_count <= 0) {
            zSpace::SetError("Invalid end vertices");
            return 0;
        }
        
        if (weight <= 0.0f || weight >= 1.0f) {
            zSpace::SetError("Invalid weight value (must be between 0 and 1 exclusive)");
            return 0;
        }
        
        if (!out_geodesic_scalars) {
            zSpace::SetError("Invalid output array");
            return 0;
        }
        
        auto* mesh = static_cast<zSpace::zExtMesh*>(mesh_handle);
        return mesh->computeGeodesicHeat_interpolated(start_vertex_ids, start_vertex_count, 
                                        end_vertex_ids, end_vertex_count, 
                                        weight, 
                                        out_geodesic_scalars) ? 1 : 0;
    , 0)
}

ZSPACE_EXTERNAL_API int zext_mesh_compute_geodesic_contours(zExtMeshHandle mesh_handle,
                                                         const int* source_vertex_ids, int source_vertex_count,
                                                         int steps, float dist,
                                                         zExtGraphHandle* out_contours, int* out_contour_count,
                                                         int max_contours) {
    TRY_CATCH_RETURN(
        if (!mesh_handle) {
            zSpace::SetError("Invalid mesh handle");
            return 0;
        }
        
        if (!source_vertex_ids || source_vertex_count <= 0) {
            zSpace::SetError("Invalid source vertices");
            return 0;
        }
        
        if (steps <= 0) {
            zSpace::SetError("Invalid number of steps");
            return 0;
        }
        
        // Allow null out_contours when just getting the count
        if (!out_contour_count) {
            zSpace::SetError("Invalid output count parameter");
            return 0;
        }
        
        auto* mesh = static_cast<zSpace::zExtMesh*>(mesh_handle);
        
        // Temporary storage for the contours
        std::vector<zSpace::zExtGraph*> contourGraphs;
        
        // Compute the contours
        bool success = mesh->computeGeodesicContours(source_vertex_ids, source_vertex_count, steps, dist, contourGraphs);
        
        if (!success) {
            *out_contour_count = 0;
            return 0;
        }
        
        // Return the count of contours
        int totalContours = static_cast<int>(contourGraphs.size());
        
        // If only getting the count, return it
        if (!out_contours || max_contours <= 0) {
            *out_contour_count = totalContours;
            return 1;
        }
        
        // Copy the contours to the output array, limited by max_contours
        *out_contour_count = std::min(totalContours, max_contours);
        
        for (int i = 0; i < *out_contour_count; i++) {
            out_contours[i] = static_cast<zExtGraphHandle>(contourGraphs[i]);
        }
        
        // Free any extra contours that won't fit in the output array
        for (int i = *out_contour_count; i < totalContours; i++) {
            delete contourGraphs[i];
        }
        
        return 1;
    , 0)
}

ZSPACE_EXTERNAL_API int zext_mesh_compute_geodesic_contours_interpolated(zExtMeshHandle mesh_handle,
                                                                      const int* start_vertex_ids, int start_vertex_count,
                                                                      const int* end_vertex_ids, int end_vertex_count,
                                                                      int steps, float dist,
                                                                      zExtGraphHandle* out_contours, int* out_contour_count,
                                                                      int max_contours) {
    TRY_CATCH_RETURN(
        if (!mesh_handle) {
            zSpace::SetError("Invalid mesh handle");
            return 0;
        }
        
        if (!start_vertex_ids || start_vertex_count <= 0) {
            zSpace::SetError("Invalid start vertices");
            return 0;
        }
        
        if (!end_vertex_ids || end_vertex_count <= 0) {
            zSpace::SetError("Invalid end vertices");
            return 0;
        }
        
        if (steps <= 0) {
            zSpace::SetError("Invalid number of steps");
            return 0;
        }
        
        // Allow null out_contours when just getting the count
        if (!out_contour_count) {
            zSpace::SetError("Invalid output count parameter");
            return 0;
        }
        
        auto* mesh = static_cast<zSpace::zExtMesh*>(mesh_handle);
        
        // Temporary storage for the contours
        std::vector<zSpace::zExtGraph*> contourGraphs;
        
        // Compute the contours
        bool success = mesh->computeGeodesicContours_interpolated(start_vertex_ids, start_vertex_count, 
                                                               end_vertex_ids, end_vertex_count,
                                                               steps, dist, contourGraphs);
        
        if (!success) {
            *out_contour_count = 0;
            return 0;
        }
        
        // Return the count of contours
        int totalContours = static_cast<int>(contourGraphs.size());
        
        // If only getting the count, return it
        if (!out_contours || max_contours <= 0) {
            *out_contour_count = totalContours;
            return 1;
        }
        
        // Copy the contours to the output array, limited by max_contours
        *out_contour_count = std::min(totalContours, max_contours);
        
        for (int i = 0; i < *out_contour_count; i++) {
            out_contours[i] = static_cast<zExtGraphHandle>(contourGraphs[i]);
        }
        
        // Free any extra contours that won't fit in the output array
        for (int i = *out_contour_count; i < totalContours; i++) {
            delete contourGraphs[i];
        }
        
        return 1;
    , 0)
}

} // extern "C" 