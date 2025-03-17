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

ZSPACE_EXTERNAL_API int zext_mesh_get_mesh_data(zExtMeshHandle mesh_handle, 
                                            bool checkCount,
                                            double* vertexPositions, int* vertexCount,
                                            int* polyCounts, int* polyCountsSize,
                                            int* polyConnections, int* polyConnectionsSize)
{
    TRY_CATCH_RETURN(
        if (!mesh_handle) {
            zSpace::SetError("Invalid mesh handle");
            return 0;
        }
        
        // Check if output pointers for sizes are valid
        if (!vertexCount || !polyCountsSize || !polyConnectionsSize) {
            zSpace::SetError("Invalid output size pointers");
            return 0;
        }
        
        auto* mesh = static_cast<zSpace::zExtMesh*>(mesh_handle);
        
        // Create vectors to hold the data
        std::vector<double> positions;
        std::vector<int> pCounts;
        std::vector<int> pConnects;
        
        // Get the mesh data
        bool success = mesh->getMeshData(positions, pConnects, pCounts);
        
        if (!success) {
            zSpace::SetError("Failed to get mesh data");
            return 0;
        }
        
        // Store the counts
        int numPositions = static_cast<int>(positions.size());
        int numPCounts = static_cast<int>(pCounts.size());
        int numPConnects = static_cast<int>(pConnects.size());
        
        // Set the output count values
        *vertexCount = numPositions;
        *polyCountsSize = numPCounts;
        *polyConnectionsSize = numPConnects;
        
        // If checkCount is true, we only return the sizes without copying data
        if (checkCount) {
            return 1; // Success
        }
        
        // When not just checking counts, make sure output arrays are valid
        if (!vertexPositions || !polyCounts || !polyConnections) {
            zSpace::SetError("Invalid output array pointers");
            return 0;
        }
        
        // Copy the data to the output arrays
        for (int i = 0; i < numPositions; i++) {
            vertexPositions[i] = positions[i];
        }
        
        for (int i = 0; i < numPCounts; i++) {
            polyCounts[i] = pCounts[i];
        }
        
        for (int i = 0; i < numPConnects; i++) {
            polyConnections[i] = pConnects[i];
        }
        
        return 1; // Success
    , 0) // Return 0 on exception
}

ZSPACE_EXTERNAL_API int zext_mesh_compute_geodesic_heat(zExtMeshHandle mesh_handle, 
                                                    const int* source_vertex_ids, int source_vertex_count, bool normalised,
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
		return mesh->computeGeodesicHeat(source_vertex_ids, source_vertex_count, normalised, out_geodesic_scalars) ? 1 : 0;
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
                                                         bool checkCount,
                                                         const int* source_vertex_ids, int source_vertex_count,
                                                         int steps, float dist,
                                                         zExtGraphHandle* out_contours, int* out_contour_count) {
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
        
        // Check if output count pointer is valid
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
        *out_contour_count = totalContours;
        
        // If checkCount is true, we only return the count without copying data
        if (checkCount) {
            // Free all contours
            for (auto& graph : contourGraphs) {
                delete graph;
            }
            return 1; // Success
        }
        
        // When not just checking counts, make sure output array is valid
        if (!out_contours) {
            zSpace::SetError("Invalid output array pointer");
            
            // Free all contours
            for (auto& graph : contourGraphs) {
                delete graph;
            }
            return 0;
        }
        
        // Copy the contours to the output array
        for (int i = 0; i < totalContours; i++) {
            out_contours[i] = static_cast<zExtGraphHandle>(contourGraphs[i]);
        }
        
        return 1;
    , 0)
}

ZSPACE_EXTERNAL_API int zext_mesh_compute_geodesic_contours_interpolated(zExtMeshHandle mesh_handle,
                                                                      bool checkCount,
                                                                      const int* start_vertex_ids, int start_vertex_count,
                                                                      const int* end_vertex_ids, int end_vertex_count,
                                                                      int steps, float dist,
                                                                      zExtGraphHandle* out_contours, int* out_contour_count) {
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
        
        // Check if output count pointer is valid
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
        *out_contour_count = totalContours;
        
        // If checkCount is true, we only return the count without copying data
        if (checkCount) {
            // Free all contours
            for (auto& graph : contourGraphs) {
                delete graph;
            }
            return 1; // Success
        }
        
        // When not just checking counts, make sure output array is valid
        if (!out_contours) {
            zSpace::SetError("Invalid output array pointer");
            
            // Free all contours
            for (auto& graph : contourGraphs) {
                delete graph;
            }
            return 0;
        }
        
        // Copy the contours to the output array
        for (int i = 0; i < totalContours; i++) {
            out_contours[i] = static_cast<zExtGraphHandle>(contourGraphs[i]);
        }
        
        return 1;
    , 0)
}
} // extern "C" 