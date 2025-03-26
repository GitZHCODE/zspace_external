/**
 * \file zSpace_External_C_API_MeshField.cpp
 * \brief Implementation of the C API for zSpace External Mesh Field - Minimal MVP
 * \date 2023
 */

#include "headers/base/zSpace_External_C_API.h"
#include "headers/base/zSpace_External_C_API_Common.h"
#include "headers/zCore/Geometry/zExtMeshField.h"

// Type conversion helpers
#define FIELD_CAST(handle) static_cast<zSpace::zExtMeshField*>(handle)
#define GRAPH_CAST(handle) static_cast<zSpace::zExtGraph*>(handle)

// Error handling macros (defined in zSpace_External_C_API_Common.h)
// TRY_CATCH_RETURN - Execute code inside a try-catch block

// Implementation
extern "C" {

    ZSPACE_EXTERNAL_API zExtMeshFieldHandle zext_field_create() {
        TRY_CATCH_RETURN(
            auto field = new zSpace::zExtMeshField();
        return static_cast<zExtMeshFieldHandle>(field);
        , nullptr)
    }

    ZSPACE_EXTERNAL_API int zext_field_destroy(zExtMeshFieldHandle field_handle) {
        if (!field_handle) {
            return 1; // Not an error, already null
        }

        TRY_CATCH_RETURN(
            auto * field = FIELD_CAST(field_handle);
        delete field;
        return 1;
        , 0)
    }

    ZSPACE_EXTERNAL_API int zext_field_is_valid(zExtMeshFieldHandle field_handle) {
        TRY_CATCH_RETURN(
            if (!field_handle) {
                return 0;
            }

        auto* field = FIELD_CAST(field_handle);
        return field->isValid() ? 1 : 0;
        , 0)
    }

    ZSPACE_EXTERNAL_API int zext_field_get_vertex_count(zExtMeshFieldHandle field_handle) {
        TRY_CATCH_RETURN(
            if (!field_handle) {
                zSpace::SetError("Invalid field handle");
                return -1;
            }

        auto* field = FIELD_CAST(field_handle);
        return field->getVertexCount();
        , -1)
    }

    ZSPACE_EXTERNAL_API int zext_field_get_value_count(zExtMeshFieldHandle field_handle) {
        TRY_CATCH_RETURN(
            if (!field_handle) {
                zSpace::SetError("Invalid field handle");
                return -1;
            }

        auto* field = FIELD_CAST(field_handle);
        return field->getValueCount();
        , -1)
    }

    ZSPACE_EXTERNAL_API int zext_field_create_field(zExtMeshFieldHandle field_handle,
        const double* minBB,
        const double* maxBB,
        int numX,
        int numY) {
        TRY_CATCH_RETURN(
            if (!field_handle) {
                zSpace::SetError("Invalid field handle");
                return 0;
            }

        if (!minBB || !maxBB) {
            zSpace::SetError("Invalid bounding box parameters");
            return 0;
        }

        auto* field = FIELD_CAST(field_handle);
        return field->createField(minBB, maxBB, numX, numY) ? 1 : 0;
        , 0)
    }

    ZSPACE_EXTERNAL_API int zext_field_set_field_values(zExtMeshFieldHandle field_handle,
        const float* values,
        int valueCount) {
        TRY_CATCH_RETURN(
            if (!field_handle) {
                zSpace::SetError("Invalid field handle");
                return 0;
            }

        if (!values || valueCount <= 0) {
            zSpace::SetError("Invalid field values");
            return 0;
        }

        auto* field = FIELD_CAST(field_handle);
        return field->setFieldValues(values, valueCount) ? 1 : 0;
        , 0)
    }

    ZSPACE_EXTERNAL_API int zext_field_get_field_values(zExtMeshFieldHandle field_handle,
        bool checkCount,
        float* out_values,
        int* out_value_count) {
        TRY_CATCH_RETURN(
            if (!field_handle) {
                zSpace::SetError("Invalid field handle");
                return 0;
            }

        if (!out_value_count) {
            zSpace::SetError("Invalid output parameter");
            return 0;
        }

        auto* field = FIELD_CAST(field_handle);

        // Get values into a temporary vector
        std::vector<float> values;
        if (!field->getFieldValues(values)) {
            return 0;
        }

        // Set the output count
        *out_value_count = static_cast<int>(values.size());

        // If checkCount is true, we only return the count
        if (checkCount) return 1;

        // Otherwise, copy the data to the output array
        if (!out_values) {
            zSpace::SetError("Invalid output array");
            return 0;
        }

        for (int i = 0; i < values.size(); i++) {
            out_values[i] = values[i];
        }

        return 1;
        , 0)
    }

    ZSPACE_EXTERNAL_API int zext_field_get_scalars_graph_edge_distance(zExtMeshFieldHandle field_handle,
        zExtGraphHandle graph_handle,
        float offset,
        bool normalise,
        float* out_values,
        int* out_value_count) {
        TRY_CATCH_RETURN(
            if (!field_handle || !graph_handle) {
                zSpace::SetError("Invalid handles");
                return 0;
            }

        if (!out_value_count) {
            zSpace::SetError("Invalid output parameter");
            return 0;
        }

        auto* field = FIELD_CAST(field_handle);
        auto* graph = GRAPH_CAST(graph_handle);

        // Get values into a temporary vector
        std::vector<float> values;
        if (!field->getScalars_graphEdgeDistance(values, graph, offset, normalise)) {
            return 0;
        }

        // Set the output count
        *out_value_count = static_cast<int>(values.size());

        // If out_values is null, we only return the count
        if (!out_values) return 1;

        // Otherwise, copy the data to the output array
        for (int i = 0; i < values.size(); i++) {
            out_values[i] = values[i];
        }

        return 1;
        , 0)
    }

    ZSPACE_EXTERNAL_API int zext_field_get_scalars_circle(zExtMeshFieldHandle field_handle,
        const double* centre,
        float radius,
        float offset,
        bool normalise,
        float* out_values,
        int* out_value_count) {
        TRY_CATCH_RETURN(
            if (!field_handle) {
                zSpace::SetError("Invalid field handle");
                return 0;
            }

        if (!centre) {
            zSpace::SetError("Invalid centre parameter");
            return 0;
        }

        if (!out_value_count) {
            zSpace::SetError("Invalid output parameter");
            return 0;
        }

        auto* field = FIELD_CAST(field_handle);

        // Get values into a temporary vector
        std::vector<float> values;
        if (!field->getScalars_circle(values, centre, radius, offset, normalise)) {
            return 0;
        }

        // Set the output count
        *out_value_count = static_cast<int>(values.size());

        // If out_values is null, we only return the count
        if (!out_values) return 1;

        // Otherwise, copy the data to the output array
        for (int i = 0; i < values.size(); i++) {
            out_values[i] = values[i];
        }

        return 1;
        , 0)
    }

    ZSPACE_EXTERNAL_API int zext_field_get_scalars_line(zExtMeshFieldHandle field_handle,
        const double* start,
        const double* end,
        float offset,
        bool normalise,
        float* out_values,
        int* out_value_count) {
        TRY_CATCH_RETURN(
            if (!field_handle) {
                zSpace::SetError("Invalid field handle");
                return 0;
            }

        if (!start || !end) {
            zSpace::SetError("Invalid line parameters");
            return 0;
        }

        if (!out_value_count) {
            zSpace::SetError("Invalid output parameter");
            return 0;
        }

        auto* field = FIELD_CAST(field_handle);

        // Get values into a temporary vector
        std::vector<float> values;
        if (!field->getScalars_line(values, start, end, offset, normalise)) {
            return 0;
        }

        // Set the output count
        *out_value_count = static_cast<int>(values.size());

        // If out_values is null, we only return the count
        if (!out_values) return 1;

        // Otherwise, copy the data to the output array
        for (int i = 0; i < values.size(); i++) {
            out_values[i] = values[i];
        }

        return 1;
        , 0)
    }

    ZSPACE_EXTERNAL_API int zext_field_get_scalars_polygon(zExtMeshFieldHandle field_handle,
        zExtGraphHandle graph_handle,
        bool normalise,
        float* out_values,
        int* out_value_count) {
        TRY_CATCH_RETURN(
            if (!field_handle || !graph_handle) {
                zSpace::SetError("Invalid handles");
                return 0;
            }

        if (!out_value_count) {
            zSpace::SetError("Invalid output parameter");
            return 0;
        }

        auto* field = FIELD_CAST(field_handle);
        auto* graph = GRAPH_CAST(graph_handle);

        // Get values into a temporary vector
        std::vector<float> values;
        if (!field->getScalars_polygon(values, graph, normalise)) {
            return 0;
        }

        // Set the output count
        *out_value_count = static_cast<int>(values.size());

        // If out_values is null, we only return the count
        if (!out_values) return 1;

        // Otherwise, copy the data to the output array
        for (int i = 0; i < values.size(); i++) {
            out_values[i] = values[i];
        }

        return 1;
        , 0)
    }

    ZSPACE_EXTERNAL_API int zext_field_boolean_union(zExtMeshFieldHandle field_handle,
        const float* scalars_A,
        int scalars_A_count,
        const float* scalars_B,
        int scalars_B_count,
        bool normalise,
        float* out_values,
        int* out_value_count) {
        TRY_CATCH_RETURN(
            if (!field_handle) {
                zSpace::SetError("Invalid field handle");
                return 0;
            }

        if (!scalars_A || scalars_A_count <= 0 || !scalars_B || scalars_B_count <= 0) {
            zSpace::SetError("Invalid scalar arrays");
            return 0;
        }

        if (!out_value_count) {
            zSpace::SetError("Invalid output parameter");
            return 0;
        }

        auto* field = FIELD_CAST(field_handle);

        // Convert C arrays to vector
        std::vector<float> vecA(scalars_A, scalars_A + scalars_A_count);
        std::vector<float> vecB(scalars_B, scalars_B + scalars_B_count);

        // Get result into a temporary vector
        std::vector<float> result;
        if (!field->boolean_union(result, vecA, vecB, normalise)) {
            return 0;
        }

        // Set the output count
        *out_value_count = static_cast<int>(result.size());

        // If out_values is null, we only return the count
        if (!out_values) return 1;

        // Otherwise, copy the data to the output array
        for (int i = 0; i < result.size(); i++) {
            out_values[i] = result[i];
        }

        return 1;
        , 0)
    }

    ZSPACE_EXTERNAL_API int zext_field_boolean_subtract(zExtMeshFieldHandle field_handle,
        const float* scalars_A,
        int scalars_A_count,
        const float* scalars_B,
        int scalars_B_count,
        bool normalise,
        float* out_values,
        int* out_value_count) {
        TRY_CATCH_RETURN(
            if (!field_handle) {
                zSpace::SetError("Invalid field handle");
                return 0;
            }

        if (!scalars_A || scalars_A_count <= 0 || !scalars_B || scalars_B_count <= 0) {
            zSpace::SetError("Invalid scalar arrays");
            return 0;
        }

        if (!out_value_count) {
            zSpace::SetError("Invalid output parameter");
            return 0;
        }

        auto* field = FIELD_CAST(field_handle);

        // Convert C arrays to vector
        std::vector<float> vecA(scalars_A, scalars_A + scalars_A_count);
        std::vector<float> vecB(scalars_B, scalars_B + scalars_B_count);

        // Get result into a temporary vector
        std::vector<float> result;
        if (!field->boolean_subtract(result, vecA, vecB, normalise)) {
            return 0;
        }

        // Set the output count
        *out_value_count = static_cast<int>(result.size());

        // If out_values is null, we only return the count
        if (!out_values) return 1;

        // Otherwise, copy the data to the output array
        for (int i = 0; i < result.size(); i++) {
            out_values[i] = result[i];
        }

        return 1;
        , 0)
    }

    ZSPACE_EXTERNAL_API int zext_field_boolean_intersect(zExtMeshFieldHandle field_handle,
        const float* scalars_A,
        int scalars_A_count,
        const float* scalars_B,
        int scalars_B_count,
        bool normalise,
        float* out_values,
        int* out_value_count) {
        TRY_CATCH_RETURN(
            if (!field_handle) {
                zSpace::SetError("Invalid field handle");
                return 0;
            }

        if (!scalars_A || scalars_A_count <= 0 || !scalars_B || scalars_B_count <= 0) {
            zSpace::SetError("Invalid scalar arrays");
            return 0;
        }

        if (!out_value_count) {
            zSpace::SetError("Invalid output parameter");
            return 0;
        }

        auto* field = FIELD_CAST(field_handle);

        // Convert C arrays to vector
        std::vector<float> vecA(scalars_A, scalars_A + scalars_A_count);
        std::vector<float> vecB(scalars_B, scalars_B + scalars_B_count);

        // Get result into a temporary vector
        std::vector<float> result;
        if (!field->boolean_intersect(result, vecA, vecB, normalise)) {
            return 0;
        }

        // Set the output count
        *out_value_count = static_cast<int>(result.size());

        // If out_values is null, we only return the count
        if (!out_values) return 1;

        // Otherwise, copy the data to the output array
        for (int i = 0; i < result.size(); i++) {
            out_values[i] = result[i];
        }

        return 1;
        , 0)
    }

    ZSPACE_EXTERNAL_API int zext_field_boolean_difference(zExtMeshFieldHandle field_handle,
        const float* scalars_A,
        int scalars_A_count,
        const float* scalars_B,
        int scalars_B_count,
        bool normalise,
        float* out_values,
        int* out_value_count) {
        TRY_CATCH_RETURN(
            if (!field_handle) {
                zSpace::SetError("Invalid field handle");
                return 0;
            }

        if (!scalars_A || scalars_A_count <= 0 || !scalars_B || scalars_B_count <= 0) {
            zSpace::SetError("Invalid scalar arrays");
            return 0;
        }

        if (!out_value_count) {
            zSpace::SetError("Invalid output parameter");
            return 0;
        }

        auto* field = FIELD_CAST(field_handle);

        // Convert C arrays to vector
        std::vector<float> vecA(scalars_A, scalars_A + scalars_A_count);
        std::vector<float> vecB(scalars_B, scalars_B + scalars_B_count);

        // Get result into a temporary vector
        std::vector<float> result;
        if (!field->boolean_difference(result, vecA, vecB, normalise)) {
            return 0;
        }

        // Set the output count
        *out_value_count = static_cast<int>(result.size());

        // If out_values is null, we only return the count
        if (!out_values) return 1;

        // Otherwise, copy the data to the output array
        for (int i = 0; i < result.size(); i++) {
            out_values[i] = result[i];
        }

        return 1;
        , 0)
    }

    ZSPACE_EXTERNAL_API int zext_field_get_scalars_smin(zExtMeshFieldHandle field_handle,
        const float* scalars_A,
        int scalars_A_count,
        const float* scalars_B,
        int scalars_B_count,
        float k,
        int mode,
        float* out_values,
        int* out_value_count) {
        TRY_CATCH_RETURN(
            if (!field_handle) {
                zSpace::SetError("Invalid field handle");
                return 0;
            }

        if (!scalars_A || scalars_A_count <= 0 || !scalars_B || scalars_B_count <= 0) {
            zSpace::SetError("Invalid scalar arrays");
            return 0;
        }

        if (!out_value_count) {
            zSpace::SetError("Invalid output parameter");
            return 0;
        }

        auto* field = FIELD_CAST(field_handle);

        // Convert C arrays to vector
        std::vector<float> vecA(scalars_A, scalars_A + scalars_A_count);
        std::vector<float> vecB(scalars_B, scalars_B + scalars_B_count);

        // Get result into a temporary vector
        std::vector<float> result;
        if (!field->getScalars_smin(result, vecA, vecB, k, mode)) {
            return 0;
        }

        // Set the output count
        *out_value_count = static_cast<int>(result.size());

        // If out_values is null, we only return the count
        if (!out_values) return 1;

        // Otherwise, copy the data to the output array
        for (int i = 0; i < result.size(); i++) {
            out_values[i] = result[i];
        }

        return 1;
        , 0)
    }

    ZSPACE_EXTERNAL_API int zext_field_get_scalars_smin_multiple(zExtMeshFieldHandle field_handle,
        const float* const* scalar_arrays,
        const int* scalar_counts,
        int array_count,
        float k,
        int mode,
        float* out_values,
        int* out_value_count) {
        TRY_CATCH_RETURN(
            if (!field_handle) {
                zSpace::SetError("Invalid field handle");
                return 0;
            }

        if (!scalar_arrays || !scalar_counts || array_count <= 0) {
            zSpace::SetError("Invalid scalar arrays");
            return 0;
        }

        if (!out_value_count) {
            zSpace::SetError("Invalid output parameter");
            return 0;
        }

        auto* field = FIELD_CAST(field_handle);

        // Convert C arrays to vector of vectors
        std::vector<std::vector<float>> vectors;
        for (int i = 0; i < array_count; i++) {
            if (!scalar_arrays[i] || scalar_counts[i] <= 0) {
                zSpace::SetError("Invalid scalar array");
                return 0;
            }

            std::vector<float> vec(scalar_arrays[i], scalar_arrays[i] + scalar_counts[i]);
            vectors.push_back(vec);
        }

        // Get result into a temporary vector
        std::vector<float> result;
        if (!field->getScalars_smin_multiple(result, vectors, k, mode)) {
            return 0;
        }

        // Set the output count
        *out_value_count = static_cast<int>(result.size());

        // If out_values is null, we only return the count
        if (!out_values) return 1;

        // Otherwise, copy the data to the output array
        for (int i = 0; i < result.size(); i++) {
            out_values[i] = result[i];
        }

        return 1;
        , 0)
    }

    ZSPACE_EXTERNAL_API int zext_field_get_bounds(zExtMeshFieldHandle field_handle,
        double* minBB,
        double* maxBB) {
        TRY_CATCH_RETURN(
            if (!field_handle) {
                zSpace::SetError("Invalid field handle");
                return 0;
            }

        if (!minBB || !maxBB) {
            zSpace::SetError("Invalid bounding box parameters");
            return 0;
        }

        auto* field = FIELD_CAST(field_handle);
        return field->getBounds(minBB, maxBB) ? 1 : 0;
        , 0)
    }

    ZSPACE_EXTERNAL_API int zext_field_get_iso_contour(zExtMeshFieldHandle field_handle,
        zExtGraphHandle graph_handle,
        float threshold) {
        TRY_CATCH_RETURN(
            if (!field_handle || !graph_handle) {
                zSpace::SetError("Invalid handles");
                return 0;
            }

        auto* field = FIELD_CAST(field_handle);
        auto* graph = GRAPH_CAST(graph_handle);

        return field->getIsoContour(graph, threshold) ? 1 : 0;
        , 0)
    }

    ZSPACE_EXTERNAL_API int zext_field_get_gradients(zExtMeshFieldHandle field_handle,
        bool checkCount,
        double* out_gradient_vectors,
        int* out_vector_count) {
        TRY_CATCH_RETURN(
            if (!field_handle) {
                zSpace::SetError("Invalid field handle");
                return 0;
            }

        if (!out_vector_count) {
            zSpace::SetError("Invalid output parameter");
            return 0;
        }

        auto* field = FIELD_CAST(field_handle);

        // Get values into a temporary vector
        std::vector<double> gradients;
        if (!field->getGradients(gradients)) {
            return 0;
        }

        // Calculate vector count (each vector is 3 doubles: x, y, z)
        int vectorCount = static_cast<int>(gradients.size() / 3);

        // Set the output count
        *out_vector_count = vectorCount;

        // If checkCount is true, we only return the count
        if (checkCount) return 1;

        // Otherwise, copy the data to the output array
        if (!out_gradient_vectors) {
            zSpace::SetError("Invalid output array");
            return 0;
        }

        for (int i = 0; i < gradients.size(); i++) {
            out_gradient_vectors[i] = gradients[i];
        }

        return 1;
        , 0)
    }

    ZSPACE_EXTERNAL_API int zext_field_get_id(zExtMeshFieldHandle field_handle,
        double* position,
        int* out_id) {
        TRY_CATCH_RETURN(
            if (!field_handle) {
                zSpace::SetError("Invalid field handle");
                return 0;
            }

        if (!position) {
            zSpace::SetError("Invalid position parameter");
            return 0;
        }

        if (!out_id) {
            zSpace::SetError("Invalid output parameter");
            return 0;
        }

        auto* field = FIELD_CAST(field_handle);
        
        // Call the method to get the ID
        int vertex_id = 0;
        if (!field->getId(vertex_id, position)) {
            zSpace::SetError("Failed to get vertex ID");
            return 0;
        }

        // Set the output value
        *out_id = vertex_id;
        return 1;
        , 0)
    }

    ZSPACE_EXTERNAL_API int zext_field_get_positions(zExtMeshFieldHandle field_handle,
        double* out_positions) {
        TRY_CATCH_RETURN(
            if (!field_handle) {
                zSpace::SetError("Invalid field handle");
                return 0;
            }

            if (!out_positions) {
                zSpace::SetError("Invalid output parameter");
                return 0;
            }

            auto* field = FIELD_CAST(field_handle);
            
            // Get the positions
            std::vector<double> positions;
            if (!field->getPositions(positions)) {
                zSpace::SetError("Failed to get vertex positions");
                return 0;
            }

            // Copy the positions to the output array
            std::copy(positions.begin(), positions.end(), out_positions);
            return 1;
            , 0)
    }
}