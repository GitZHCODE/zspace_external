/**
 * \file zExtMeshField.h
 * \brief External mesh scalar field class for zSpace - Minimal MVP
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
#include "headers/zCore/Geometry/zExtMesh.h"

// Forward declaration to avoid including zObjMeshField.h directly
namespace zSpace {
    template<typename T> class zObjMeshField;
    using zObjMeshScalarField = zObjMeshField<float>;
}

// Handle type forward declaration (should be defined in zSpace_External_C_API.h)
typedef void* zExtMeshFieldHandle;

namespace zSpace {

/**
 * External mesh scalar field class that provides a simplified interface for field operations.
 * Minimal MVP implementation.
 */
class zExtMeshField {
public:
    /**
     * Default constructor. Creates an empty field.
     */
    zExtMeshField();
    
    /**
     * Constructor that takes ownership of a zObjMeshScalarField pointer.
     * 
     * @param field Pointer to a zObjMeshScalarField object to take ownership of.
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
     * Check if the field is valid.
     * 
     * @return True if the field is valid, false otherwise.
     */
    bool isValid() const;
    
    /**
     * Get the number of vertices in the field mesh.
     * 
     * @return Number of vertices.
     */
    int getVertexCount() const;
    
    /**
     * Get the number of scalar values in the field.
     * 
     * @return Number of values.
     */
    int getValueCount() const;
    
    /**
     * Get the raw internal field object.
     * Use with caution as this exposes the internal implementation.
     * 
     * @return Reference to the internal zObjMeshScalarField object.
     */
    zObjMeshScalarField& getRawField() const;
    
    /**
     * Create a field with the given bounding box and resolution.
     * 
     * @param minBB Array of 3 doubles representing minimum bounding box point (x, y, z)
     * @param maxBB Array of 3 doubles representing maximum bounding box point (x, y, z)
     * @param numX Number of grid points in X direction
     * @param numY Number of grid points in Y direction
     * @return True if successful, false otherwise.
     */
    bool createField(
        const double* minBB,
        const double* maxBB,
        int numX,
        int numY
    );

    /**
     * Set field values.
     * 
     * @param values Array of scalar field values
     * @param valueCount Number of values in the array
     * @return True if successful, false otherwise.
     */
    bool setFieldValues(
        const float* values, int valueCount
    );
    
    /**
     * Get field values.
     * 
     * @param out_scalars Output vector to store the field scalar values
     * @return True if successful, false otherwise.
     */
    bool getFieldValues(
        std::vector<float>& out_scalars
    );

    /**
     * Calculate scalar field values based on distance to a graph's edges.
     * 
     * @param out_scalars Output vector to store the field scalar values
     * @param graph Pointer to a graph object
     * @param offset Distance offset value
     * @param normalise Whether to normalize the resulting values
     * @return True if successful, false otherwise.
     */
    bool getScalars_graphEdgeDistance(
        std::vector<float>& out_scalars,
        const zExtGraph* graph,
        const float offset,
        const bool normalise
    );

    /**
     * Calculate scalar field values based on distance to a circle.
     * 
     * @param out_scalars Output vector to store the field scalar values
     * @param centre Array of 3 doubles representing the circle center (x, y, z)
     * @param radius Radius of the circle
     * @param offset Distance offset value
     * @param normalise Whether to normalize the resulting values
     * @return True if successful, false otherwise.
     */
    bool getScalars_circle(
        std::vector<float>& out_scalars,
        const double* centre,
        const float radius,
        const float offset,
        const bool normalise
    );

    /**
     * Calculate scalar field values based on distance to a line.
     * 
     * @param out_scalars Output vector to store the field scalar values
     * @param start Array of 3 doubles representing the line start point (x, y, z)
     * @param end Array of 3 doubles representing the line end point (x, y, z)
     * @param offset Distance offset value
     * @param normalise Whether to normalize the resulting values
     * @return True if successful, false otherwise.
     */
    bool getScalars_line(
        std::vector<float>& out_scalars,
        const double* start,
        const double* end,
        const float offset,
        const bool normalise
    );

    /**
     * Calculate scalar field values based on distance to a polygon defined by a graph.
     * 
     * @param out_scalars Output vector to store the field scalar values
     * @param graph Pointer to a graph object representing the polygon
     * @param normalise Whether to normalize the resulting values
     * @return True if successful, false otherwise.
     */
    bool getScalars_polygon(
        std::vector<float>& out_scalars,
        const zExtGraph* graph,
        const bool normalise
    );

    /**
     * Perform a boolean union operation between two scalar fields.
     * 
     * @param out_scalars Output vector to store the resulting field values
     * @param scalars_A First input scalar field values
     * @param scalars_B Second input scalar field values
     * @param normalise Whether to normalize the resulting values
     * @return True if successful, false otherwise.
     */
    bool boolean_union(
        std::vector<float>& out_scalars,
        const std::vector<float>& scalars_A,
        const std::vector<float>& scalars_B,
        const bool normalise
    );

    /**
     * Perform a boolean subtraction operation between two scalar fields.
     * 
     * @param out_scalars Output vector to store the resulting field values
     * @param scalars_A First input scalar field values
     * @param scalars_B Second input scalar field values
     * @param normalise Whether to normalize the resulting values
     * @return True if successful, false otherwise.
     */
    bool boolean_subtract(
        std::vector<float>& out_scalars,
        const std::vector<float>& scalars_A,
        const std::vector<float>& scalars_B,
        const bool normalise
    );

    /**
     * Perform a boolean intersection operation between two scalar fields.
     * 
     * @param out_scalars Output vector to store the resulting field values
     * @param scalars_A First input scalar field values
     * @param scalars_B Second input scalar field values
     * @param normalise Whether to normalize the resulting values
     * @return True if successful, false otherwise.
     */
    bool boolean_intersect(
        std::vector<float>& out_scalars,
        const std::vector<float>& scalars_A,
        const std::vector<float>& scalars_B,
        const bool normalise
    );

    /**
     * Perform a boolean difference operation between two scalar fields.
     * 
     * @param out_scalars Output vector to store the resulting field values
     * @param scalars_A First input scalar field values
     * @param scalars_B Second input scalar field values
     * @param normalise Whether to normalize the resulting values
     * @return True if successful, false otherwise.
     */
    bool boolean_difference(
        std::vector<float>& out_scalars,
        const std::vector<float>& scalars_A,
        const std::vector<float>& scalars_B,
        const bool normalise
    );

    /**
     * Compute smooth minimum between two scalar fields.
     * 
     * @param out_scalars Output vector to store the resulting field values
     * @param scalars_A First input scalar field values
     * @param scalars_B Second input scalar field values
     * @param k Smoothing factor
     * @param mode Smooth minimum mode (0=polynomial, 1=exponential)
     * @return True if successful, false otherwise.
     */
    bool getScalars_smin(
        std::vector<float>& out_scalars,
        const std::vector<float>& scalars_A,
        const std::vector<float>& scalars_B,
        float k,
        int mode
    );

    /**
       * Compute weighted smooth minimum between two scalar fields using exponential mode.
       *
       * @param out_scalars Output vector to store the resulting field values
       * @param scalars_A First input scalar field values
       * @param scalars_B Second input scalar field values
       * @param k Smoothing factor
       * @param wt Weight between two input scalar field values (0=first, 1=second)
       * @return True if successful, false otherwise.
       */
    bool getScalars_smin_exponential_weighted(
        std::vector<float>& out_scalars,
        const std::vector<float>& scalars_A,
        const std::vector<float>& scalars_B,
        float k,
        float wt
    );

    /**
     * Compute smooth minimum across multiple scalar fields.
     * 
     * @param out_scalars Output vector to store the resulting field values
     * @param inputs Vector of input scalar field values
     * @param k Smoothing factor
     * @param mode Smooth minimum mode (0=polynomial, 1=exponential)
     * @return True if successful, false otherwise.
     */
    bool getScalars_smin_multiple(
        std::vector<float>& out_scalars,
        const std::vector<std::vector<float>>& inputs,
        float k,
        int mode
    );

    /**
     * Get the field bounds.
     * 
     * @param minBB Output array of 3 doubles to store minimum bounding box point (x, y, z)
     * @param maxBB Output array of 3 doubles to store maximum bounding box point (x, y, z)
     * @return True if successful, false otherwise.
     */
    bool getBounds(
        double* minBB,
        double* maxBB
    );

    /**
     * Get iso contour from the field at a given threshold value.
     * 
     * @param graph Output graph to store the contour
     * @param threshold Iso value
     * @return True if successful, false otherwise.
     */
    bool getIsoContour(
        zExtGraph* graph,
        float threshold
    );

    /**
     * Get gradients of the field.
     * 
     * @param gradientVecs Output vector to store gradient vectors (x1, y1, z1, x2, y2, z2, ...)
     * @return True if successful, false otherwise.
     */
    bool getGradients(
        std::vector<double>& gradientVecs
    );

    /**
     * Get the vertex ID at the given position.
     * 
     * @param out_id Output variable to store the closest vertex ID
     * @param position Array of 3 doubles representing the position (x, y, z)
     * @return True if successful, false otherwise.
     */
    bool getId(
        int& out_id,
        const double* position
    );

    /**
     * Get all vertex positions from the field.
     *
     * @param position Output array of 3 doubles representing the position (x, y, z)
     * @return True if successful, false otherwise.
     */
    bool getPositions(
        std::vector<double>& positions
    );

    /**
     * Get the mesh representation of the field.
     * 
     * @param mesh Output pointer to store the mesh object
     * @return True if successful, false otherwise.
     */
    bool getMesh(
        zExtMesh* mesh
    );

    /**
    * Update internal attributes (vertex and value counts).
    */
    void updateAttributes();

private:
    // The underlying field object
    std::unique_ptr<zObjMeshScalarField> m_field;
    
    // Cached attributes for quick access
    int m_vertexCount;
    int m_valueCount;
    
    // Friend declarations for C API access
    friend zExtMeshFieldHandle zext_field_create();
    friend int zext_field_destroy(zExtMeshFieldHandle);
    friend int zext_field_is_valid(zExtMeshFieldHandle);
    friend int zext_field_get_vertex_count(zExtMeshFieldHandle);
    friend int zext_field_get_value_count(zExtMeshFieldHandle);
    friend int zext_field_create_field(zExtMeshFieldHandle, const double*, const double*, int, int);
    friend int zext_field_set_field_values(zExtMeshFieldHandle, const float*, int);
    friend int zext_field_get_field_values(zExtMeshFieldHandle, float*, int*);
    friend int zext_field_get_scalars_graph_edge_distance(zExtMeshFieldHandle, zExtGraphHandle, float, bool, float*, int*);
    friend int zext_field_get_scalars_circle(zExtMeshFieldHandle, const double*, float, float, bool, float*, int*);
    friend int zext_field_get_scalars_line(zExtMeshFieldHandle, const double*, const double*, float, bool, float*, int*);
    friend int zext_field_get_scalars_polygon(zExtMeshFieldHandle, zExtGraphHandle, bool, float*, int*);
    friend int zext_field_boolean_union(zExtMeshFieldHandle, const float*, int, const float*, int, bool, float*, int*);
    friend int zext_field_boolean_subtract(zExtMeshFieldHandle, const float*, int, const float*, int, bool, float*, int*);
    friend int zext_field_boolean_intersect(zExtMeshFieldHandle, const float*, int, const float*, int, bool, float*, int*);
    friend int zext_field_boolean_difference(zExtMeshFieldHandle, const float*, int, const float*, int, bool, float*, int*);
    friend int zext_field_get_scalars_smin(zExtMeshFieldHandle, const float*, int, const float*, int, float, int, float*, int*);
    friend int zext_field_get_scalars_smin_exponential_weighted(zExtMeshFieldHandle, const float*, int, const float*, int, float, int, float*, float*);
    friend int zext_field_get_scalars_smin_multiple(zExtMeshFieldHandle, const float* const*, const int*, int, float, int, float*, int*);
    friend int zext_field_get_bounds(zExtMeshFieldHandle, double*, double*);
    friend int zext_field_get_iso_contour(zExtMeshFieldHandle, zExtGraphHandle, float);
    friend int zext_field_get_gradients(zExtMeshFieldHandle, double*, int*);
    friend int zext_field_get_id(zExtMeshFieldHandle, double*, int*);
    friend int zext_field_get_positions(zExtMeshFieldHandle, double*, int*);
    friend int zext_field_get_mesh(zExtMeshFieldHandle, zExtMeshHandle);
};

} // namespace zSpace

#endif // ZEXT_MESH_FIELD_H 