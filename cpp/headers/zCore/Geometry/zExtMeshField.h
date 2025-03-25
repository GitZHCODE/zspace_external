/**
 * \file zExtMeshField.h
 * \brief External mesh field class for zSpace - Minimal MVP
 * \date 2023
 */

#ifndef ZEXT_MESH_FIELD_H
#define ZEXT_MESH_FIELD_H

#include <memory>
#include <vector>
#include <string>

// Include the C API header for declarations
#include "headers/base/zSpace_External_C_API.h"
#include "headers/zCore/Geometry/zExtGraph.h"

// Forward declaration to avoid including zObjGraph.h directly
namespace zSpace {
    class zObjMeshf;
}

// Handle type forward declaration
typedef void* zExtMeshFieldHandle;

namespace zSpace {

/**
 * External graph class that provides a simplified interface for graph operations.
 * Minimal MVP implementation.
 */
class zExtMeshField {
public:
    /**
     * Default constructor. Creates an empty graph.
     */
    zExtMeshField();
    
    /**
     * Constructor that takes ownership of a zObjGraph pointer.
     * 
     * @param graph Pointer to a zObjGraph object to take ownership of.
     */
    explicit zExtMeshField(zObjMeshScalarField* field);
    
    /**
     * Copy constructor.
     */
    zExtMeshField(const zExtMeshField& other);
    
    /**
     * Destructor.
     */
    ~zExtMeshField();
    
    /**
     * Check if the graph is valid.
     * 
     * @return True if the graph is valid, false otherwise.
     */
    bool isValid() const;
    
    /**
     * Get the number of vertices in the graph.
     * 
     * @return Number of vertices.
     */
    int getVertexCount() const;
    
    /**
     * Get the number of edges in the graph.
     * 
     * @return Number of edges.
     */
    int getValueCount() const;
    
    /**
     * Get the raw internal graph object.
     * Use with caution as this exposes the internal implementation.
     * 
     * @return Reference to the internal zObjGraph object.
     */
    zObjMeshScalarField& getRawField() const;
    
    /**
     * Create a graph from the given vertex positions and edge data.
     * 
     * @param vertexPositions Array of vertex positions (x1, y1, z1, x2, y2, z2, ...)
     * @param vertexCount Number of vertices (vertexPositions.length / 3)
     * @param edgeConnections Array of vertex indices for each edge (start1, end1, start2, end2, ...)
     * @param edgeConnectionsSize Size of the edgeConnections array (number of edges * 2)
     * @return True if successful, false otherwise.
     */
    bool createField(
        const double* minBB,
        const double* maxBB,
        int numX,
        int numY
    );

    /**
     * Set vertex positions in the graph.
     * 
     * @param vertexPositions Array of vertex positions (x1, y1, z1, x2, y2, z2, ...)
     * @param vertexCount Number of vertices (vertexPositions.length / 3)
     * @return True if successful, false otherwise.
     */
    bool setFieldValues(
        const float* values, int valueCount
    );
    
    /**
     * Get vertex positions from the graph.
     * 
     * @param out_vertexPositions Output array for vertex positions (pre-allocated with size equal to vertex count * 3)
     * @return True if successful, false otherwise.
     */
    bool getFieldValues(
        std::vector<float>& out_scalars
    );

    bool getScalars_graphEdgeDistance(
        std::vector<float>& out_scalars,
        const zExtGraph* graph,
        const float offset,
        const bool normalise
    );

    bool getScalars_circle(
        std::vector<float>& out_scalars,
        const double* centre,
        const float radius,
        const float offset,
        const bool normalise
    );

    bool getScalars_line(
        std::vector<float>& out_scalars,
        const double* start,
        const double* end,
        const float offset,
        const bool normalise
    );

    bool getScalars_polygon(
        std::vector<float>& out_scalars,
        const zExtGraph* graph,
        const bool normalise
    );

    bool boolean_union(
        std::vector<float>& out_scalars,
        const std::vector<float>& scalars_A,
        const std::vector<float>& scalars_B,
        const bool normalise
    );

    bool boolean_subtract(
        std::vector<float>& out_scalars,
        const std::vector<float>& scalars_A,
        const std::vector<float>& scalars_B,
        const bool normalise
    );

    bool boolean_intersect(
        std::vector<float>& out_scalars,
        const std::vector<float>& scalars_A,
        const std::vector<float>& scalars_B,
        const bool normalise
    );

    bool boolean_difference(
        std::vector<float>& out_scalars,
        const std::vector<float>& scalars_A,
        const std::vector<float>& scalars_B,
        const bool normalise
    );

    bool getScalars_smin(
        std::vector<float>& out_scalars,
        const std::vector<float>& scalars_A,
        const std::vector<float>& scalars_B,
        float k,
        int mode = 0
    );

    bool getScalars_smin_multiple(
        std::vector<float>& out_scalars,
        const std::vector<std::vector<float>>& inputs,
        float k,
        int mode = 0
    );

    bool getBounds(
        double* minBB,
        double* maxBB
    );

    bool getIsoContour(
        zExtGraph* graph,
        float threshold
    );

    bool getGradients(
        std::vector<double>& gradientVecs
    );

private:
    /**
     * Update internal attributes (vertex and edge counts).
     */
    void updateAttributes();
    
    // The underlying graph object
    std::unique_ptr<zObjMeshField<float>> m_field;
    
    // Cached attributes for quick access
    int m_vertexCount;
    int m_valueCount;
    
    // Friend declarations for C API access
    friend zExtMeshFieldHandle zext_field_create();
    friend int zext_field_destroy(zExtMeshFieldHandle);
    friend int zext_field_is_valid(zExtMeshFieldHandle);

};

} // namespace zSpace

#endif // ZEXT_MESH_FIELD_H 