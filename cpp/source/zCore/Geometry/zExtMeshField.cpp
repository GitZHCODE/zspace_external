/**
 * \file zExtMeshField.cpp
 * \brief Implementation of the External mesh scalar field class for zSpace - Minimal MVP
 * \date 2023
 */

// Include local header (relative to cpp directory)
#include "headers/zCore/Geometry/zExtMeshField.h"

// Include zspace_core headers
#include <headers/zInterface/functionsets/zFnMeshField.h>
#include <headers/zInterface/objects/zObjMeshField.h>
#include <source/zCore/Utilities/zSMin.h>

#include <cmath>

namespace zSpace {

    zExtMeshField::zExtMeshField() : m_field(new zObjMeshScalarField()), m_vertexCount(0), m_valueCount(0) {}

    zExtMeshField::zExtMeshField(zObjMeshScalarField* field) : m_field(field), m_vertexCount(0), m_valueCount(0) {
        if (m_field) {
            updateAttributes();
        }
    }

    zExtMeshField::zExtMeshField(const zExtMeshField& other) : m_vertexCount(other.m_vertexCount), m_valueCount(other.m_valueCount) {
        if (other.m_field) {
            m_field.reset(new zObjMeshScalarField(*other.m_field));
        }
        else {
            m_field.reset(new zObjMeshScalarField());
        }
    }

    zExtMeshField::~zExtMeshField(){}

    void zExtMeshField::updateAttributes() {
        if (m_field) {
            zFnMeshScalarField fnField(*m_field);
            m_vertexCount = fnField.numFieldValues();
            m_valueCount = fnField.numFieldValues();
        }
        else {
            m_vertexCount = 0;
            m_valueCount = 0;
        }
    }

    bool zExtMeshField::isValid() const
    {
        return m_field != nullptr;
    }

    int zExtMeshField::getVertexCount() const
    {
        return m_vertexCount;
    }

    int zExtMeshField::getValueCount() const
    {
        return m_valueCount;
    }

    zObjMeshScalarField& zExtMeshField::getRawField() const
    {
        if (!m_field) {
            throw std::runtime_error("Field is not initialized");
        }
        return *m_field;
    }

    bool zExtMeshField::createField(
        const double* minBB,
        const double* maxBB,
        int numX,
        int numY
    ) {
        try {
            zFnMeshScalarField fnField(*m_field);
            zPoint min(minBB[0], minBB[1], minBB[2]);
            zPoint max(maxBB[0], maxBB[1], maxBB[2]);
            fnField.create(min, max, numX, numY);

            vector<float> defaultFieldValues;
            defaultFieldValues.assign(numX * numY, -1);
            fnField.setFieldValues(defaultFieldValues);

            updateAttributes();
            return true;
        }
        catch (const std::exception&) {
            return false;
        }
    }

    bool zExtMeshField::setFieldValues(
        const float* values, int valueCount
    ) {
        try {
            zFnMeshScalarField fnField(*m_field);

            std::vector<float> vals;
            vals.reserve(valueCount);
            for (int i = 0; i < valueCount; i++)
                vals.push_back(values[i]);

            fnField.setFieldValues(vals);
            updateAttributes();
            return true;
        }
        catch (const std::exception&) {
            return false;
        }
    }

    bool zExtMeshField::getFieldValues(
        std::vector<float>& out_scalars
    ) {
        try {
            zFnMeshScalarField fnField(*m_field);
            fnField.getFieldValues(out_scalars);
            return true;
        }
        catch (const std::exception&) {
            return false;
        }
    }

    bool zExtMeshField::getScalars_graphEdgeDistance(
        std::vector<float>& out_scalars,
        const zExtGraph* graph,
        const float offset,
        const bool normalise
    ) {
        try {
            zFnMeshScalarField fnField(*m_field);
            fnField.getScalarsAsEdgeDistance(out_scalars, graph->getRawGraph(), offset, normalise);
            return true;
        }
        catch (const std::exception&) {
            return false;
        }
    }

    bool zExtMeshField::getScalars_circle(
        std::vector<float>& out_scalars,
        const double* centre,
        const float radius,
        const float offset,
        const bool normalise
    ) {
        try {
            zFnMeshScalarField fnField(*m_field);
            zPoint cen(centre[0], centre[1], centre[2]);
            fnField.getScalars_Circle(out_scalars, cen, radius, offset, normalise);
            return true;
        }
        catch (const std::exception&) {
            return false;
        }
    }

    bool zExtMeshField::getScalars_line(
        std::vector<float>& out_scalars,
        const double* start,
        const double* end,
        const float offset,
        const bool normalise
    ){
        try {
            zFnMeshScalarField fnField(*m_field);
            zPoint vStart(start[0], start[1], start[2]);
            zPoint vEnd(end[0], end[1], end[2]);
            fnField.getScalars_Line(out_scalars, vStart, vEnd, offset, normalise);
            return true;
        }
        catch (const std::exception&) {
            return false;
        }
    }

    bool zExtMeshField::getScalars_polygon(
        std::vector<float>& out_scalars,
        const zExtGraph* graph,
        const bool normalise
    ) {
        try {
            zFnMeshScalarField fnField(*m_field);
            fnField.getScalars_Polygon(out_scalars, graph->getRawGraph(), normalise);
            return true;
        }
        catch (const std::exception&) {
            return false;
        }
    }

    bool zExtMeshField::boolean_union(
        std::vector<float>& out_scalars,
        const std::vector<float>& scalars_A,
        const std::vector<float>& scalars_B,
        const bool normalise
    ) {
        try {
            zFnMeshScalarField fnField(*m_field);
            std::vector<float> aCopy(scalars_A.begin(), scalars_A.end());
            std::vector<float> bCopy(scalars_B.begin(), scalars_B.end());
            fnField.boolean_union(aCopy, bCopy, out_scalars, normalise);
            return true;
        }
        catch (const std::exception&) {
            return false;
        }
    }

    bool zExtMeshField::boolean_subtract(
        std::vector<float>& out_scalars,
        const std::vector<float>& scalars_A,
        const std::vector<float>& scalars_B,
        const bool normalise
    ) {
        try {
            zFnMeshScalarField fnField(*m_field);
            std::vector<float> aCopy(scalars_A.begin(), scalars_A.end());
            std::vector<float> bCopy(scalars_B.begin(), scalars_B.end());
            fnField.boolean_subtract(aCopy, bCopy, out_scalars, normalise);
            return true;
        }
        catch (const std::exception&) {
            return false;
        }
    }

    bool zExtMeshField::boolean_intersect(
        std::vector<float>& out_scalars,
        const std::vector<float>& scalars_A,
        const std::vector<float>& scalars_B,
        const bool normalise
    ) {
        try {
            zFnMeshScalarField fnField(*m_field);
            std::vector<float> aCopy(scalars_A.begin(), scalars_A.end());
            std::vector<float> bCopy(scalars_B.begin(), scalars_B.end());
            fnField.boolean_intersect(aCopy, bCopy, out_scalars, normalise);
            return true;
        }
        catch (const std::exception&) {
            return false;
        }
    }

    bool zExtMeshField::boolean_difference(
        std::vector<float>& out_scalars,
        const std::vector<float>& scalars_A,
        const std::vector<float>& scalars_B,
        const bool normalise
    ) {
        try {
            zFnMeshScalarField fnField(*m_field);
            std::vector<float> aCopy(scalars_A.begin(), scalars_A.end());
            std::vector<float> bCopy(scalars_B.begin(), scalars_B.end());
            fnField.boolean_difference(aCopy, bCopy, out_scalars, normalise);
            return true;
        }
        catch (const std::exception&) {
            return false;
        }
    }

    bool zExtMeshField::getScalars_smin(
        std::vector<float>& out_scalars,
        const std::vector<float>& scalars_A,
        const std::vector<float>& scalars_B,
        float k,
        int mode
    ) {
        try {
            zSpace::zSMin smin;
            smin.smin(scalars_A, scalars_B, out_scalars, k, smin.selectMode(mode));
            return true;
        }
        catch (const std::exception&) {
            return false;
        }
    }

    bool zExtMeshField::getScalars_smin_multiple(
        std::vector<float>& out_scalars,
        const std::vector<std::vector<float>>& inputs,
        float k,
        int mode
    ) {
        try {
            zSpace::zSMin smin;
            smin.smin_multiple(inputs, out_scalars, k, smin.selectMode(mode));
            return true;
        }
        catch (const std::exception&) {
            return false;
        }
    }

    bool zExtMeshField::getBounds(
        double* minBB,
        double* maxBB
    ) {
        try {
            zFnMeshScalarField fnField(*m_field);
            zPoint min, max;
            fnField.getBounds(min, max);
            minBB[0] = min.x;
            minBB[1] = min.y;
            minBB[2] = min.z;

            maxBB[0] = max.x;
            maxBB[1] = max.y;
            maxBB[2] = max.z;
            return true;
        }
        catch (const std::exception&) {
            return false;
        }
    }

    bool zExtMeshField::getIsoContour(
        zExtGraph* graph,
        float threshold
    ) {
        try {
            if (!m_field || !graph) {
                return false;
            }

            int precision = 6;
            float tolerance = std::pow(10, -precision);

            // Get the raw graph object to modify
            zObjGraph& rawGraph = graph->getRawGraph();
            
            // Extract the contour
            zFnMeshScalarField fnField(*m_field);

            vector<float> vals;
            fnField.getFieldValues(vals);
            fnField.normliseValues(vals);
            fnField.setFieldValues(vals);
            
            // Now extract the contour directly into our graph
            fnField.getIsocontour(rawGraph, threshold, precision, tolerance);
            
            // Make sure to update the graph's internal state
            graph->updateAttributes();
            
            return true;
        }
        catch (const std::exception&) {
            return false;
        }
    }

    bool zExtMeshField::getGradients(
        std::vector<double>& gradientVecs
    ) {
        try {
            zFnMeshScalarField fnField(*m_field);
            std::vector<zVector> vectors = fnField.getGradients();

            gradientVecs.clear();
            gradientVecs.reserve(vectors.size() * 3);
            for (size_t i = 0; i < vectors.size(); i++)
            {
                vectors[i].normalize();
                gradientVecs.push_back(vectors[i].x);
                gradientVecs.push_back(vectors[i].y);
                gradientVecs.push_back(vectors[i].z);
            }
            return true;
        }
        catch (const std::exception&) {
            return false;
        }
    }

	bool zExtMeshField::getId(
		int& out_id,
		const double* position
	) {
		try {
			if (!m_field) {
				return false;
			}
			
			zPoint pos(position[0], position[1], position[2]);
            zItMeshScalarField it(*m_field, pos);
			
			// Find the closest vertex ID to the given position
			out_id = it.getId();
			return true;
		}
		catch (const std::exception&) {
			return false;
		}
	}

    bool zExtMeshField::getPositions(
        std::vector<double>& positions
    ) {
        try {
            if (!m_field) {
                return false;
            }
            zFnMeshScalarField fnField(*m_field);
            vector<zPoint> pos;
            fnField.getPositions(pos);
            
            positions.reserve(pos.size() * 3);
            for (size_t i = 0; i < pos.size(); i++)
            {
                positions.push_back(pos[i].x);
                positions.push_back(pos[i].y);
                positions.push_back(pos[i].z);
            }
            return true;
        }
        catch (const std::exception&) {
            return false;
        }
    }

    bool zExtMeshField::getMesh(zExtMesh* mesh) {
        try {
            if (!m_field) {
                return false;
            }
            zObjMesh& m = mesh->getRawMesh();

            zFnMeshScalarField fnField(*m_field);
            m = *fnField.getRawMesh();

            // Update the mesh attributes to ensure vertex and face counts are correct
            mesh->updateAttributes();

            return true;
        }
        catch (const std::exception& e) {
            return false;
        }
    }


} // namespace zSpace 