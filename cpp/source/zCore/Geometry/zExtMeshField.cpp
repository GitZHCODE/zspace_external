/**
 * \file zExtGraph.cpp
 * \brief Implementation of the External graph class for zSpace - Minimal MVP
 * \date 2023
 */

// Include local header (relative to cpp directory)
#include "headers/zCore/Geometry/zExtMeshField.h"

// Include zspace_core headers
#include <headers/zInterface/functionsets/zFnMeshField.h>
#include <headers/zInterface/objects/zObjMeshField.h>
#include <source/zCore/Utilities/zSMin.h>

namespace zSpace {

    zExtMeshField::zExtMeshField() : m_field(new zObjMeshField<float>()), m_vertexCount(0), m_valueCount(0) {}

    zExtMeshField::zExtMeshField(zObjMeshScalarField* field) : m_field(field), m_vertexCount(0), m_valueCount(0) {
        if (m_field) {
            updateAttributes();
        }
    }

    zExtMeshField::zExtMeshField(const zExtMeshField& other) : m_vertexCount(other.m_vertexCount), m_valueCount(other.m_valueCount) {
        if (other.m_field) {
            m_field.reset(new zExtMeshField(*other.m_field));
        }
        else {
            m_field.reset(new zExtMeshField());
        }
    }

    zExtMeshField::~zExtMeshField(){}


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
        zFnMeshScalarField fnField(*m_field);
        zPoint min(minBB[0], minBB[1], minBB[2]);
        zPoint max(maxBB[0], maxBB[1], maxBB[2]);
        fnField.create(min, max, numX, numY);
        updateAttributes();
        return true;
    }

    bool zExtMeshField::setFieldValues(
        const float* values, int valueCount
    ) {
        zFnMeshScalarField fnField(*m_field);

        vector<float> vals;
        vals.reserve(valueCount);
        for (int i = 0; i < valueCount; i++)
            vals.push_back(values[i]);

        fnField.setFieldValues(vals);
        updateAttributes();
        return true;
    }


    bool zExtMeshField::getFieldValues(
        std::vector<float>& out_scalars
    ) {
        zFnMeshScalarField fnField(*m_field);
        fnField.getFieldValues(out_scalars);
    }

    bool zExtMeshField::getScalars_graphEdgeDistance(
        std::vector<float>& out_scalars,
        const zExtGraph* graph,
        const float offset,
        const bool normalise
    ) {
        zFnMeshScalarField fnField(*m_field);
        fnField.getScalarsAsEdgeDistance(out_scalars, graph->getRawGraph(), offset, normalise);
        return true;
    }

    bool zExtMeshField::getScalars_circle(
        std::vector<float>& out_scalars,
        const double* centre,
        const float radius,
        const float offset,
        const bool normalise
    ) {
		zFnMeshScalarField fnField(*m_field);
		zPoint cen(centre[0], centre[1], centre[2]);
		fnField.getScalars_Circle(out_scalars, cen, radius, offset, normalise);
		return true;
	}

    bool zExtMeshField::getScalars_line(
        std::vector<float>& out_scalars,
        const double* start,
        const double* end,
        const float offset,
        const bool normalise
    ){
        zFnMeshScalarField fnField(*m_field);
        zPoint vStart(start[0], start[1], start[2]);
        zPoint vEnd(end[0], end[1], end[2]);
        fnField.getScalars_Line(out_scalars, vStart, vEnd, offset, normalise);
        return true;
    }

    bool zExtMeshField::getScalars_polygon(
        std::vector<float>& out_scalars,
        const zExtGraph* graph,
        const bool normalise
    ) {
        zFnMeshScalarField fnField(*m_field);
        fnField.getScalars_Polygon(out_scalars, graph->getRawGraph(), normalise);
        return true;
    }

    bool zExtMeshField::boolean_union(
        std::vector<float>& out_scalars,
        const std::vector<float>& scalars_A,
        const std::vector<float>& scalars_B,
        const bool normalise
    ) {
        zFnMeshScalarField fnField(*m_field);
        std::vector<float> aCopy(scalars_A.begin(), scalars_A.end());
        std::vector<float> bCopy(scalars_B.begin(), scalars_B.end());
        fnField.boolean_union(aCopy, bCopy, out_scalars, normalise);
        return true;
    }

    bool zExtMeshField::boolean_subtract(
        std::vector<float>& out_scalars,
        const std::vector<float>& scalars_A,
        const std::vector<float>& scalars_B,
        const bool normalise
    ) {
        zFnMeshScalarField fnField(*m_field);
        std::vector<float> aCopy(scalars_A.begin(), scalars_A.end());
        std::vector<float> bCopy(scalars_B.begin(), scalars_B.end());
        fnField.boolean_subtract(aCopy, bCopy, out_scalars, normalise);
        return true;
    }

    bool zExtMeshField::boolean_intersect(
        std::vector<float>& out_scalars,
        const std::vector<float>& scalars_A,
        const std::vector<float>& scalars_B,
        const bool normalise
    ) {
        zFnMeshScalarField fnField(*m_field);
        std::vector<float> aCopy(scalars_A.begin(), scalars_A.end());
        std::vector<float> bCopy(scalars_B.begin(), scalars_B.end());
        fnField.boolean_intersect(aCopy, bCopy, out_scalars, normalise);
        return true;
    }

    bool zExtMeshField::boolean_difference(
        std::vector<float>& out_scalars,
        const std::vector<float>& scalars_A,
        const std::vector<float>& scalars_B,
        const bool normalise
    ) {
        zFnMeshScalarField fnField(*m_field);
        std::vector<float> aCopy(scalars_A.begin(), scalars_A.end());
        std::vector<float> bCopy(scalars_B.begin(), scalars_B.end());
        fnField.boolean_difference(aCopy, bCopy, out_scalars, normalise);
        return true;
    }

    bool zExtMeshField::getScalars_smin(
        std::vector<float>& out_scalars,
        const std::vector<float>& scalars_A,
        const std::vector<float>& scalars_B,
        float k,
        int mode = 0
    ) {
        zSpace::zSMin smin;

        smin.smin(scalars_A, scalars_B, out_scalars, k, smin.selectMode(mode));
        return true;
    }

    bool zExtMeshField::getScalars_smin_multiple(
        std::vector<float>& out_scalars,
        const std::vector<std::vector<float>>& inputs,
        float k,
        int mode = 0
    ) {
        zSpace::zSMin smin;

        smin.smin_multiple(inputs, out_scalars, k, smin.selectMode(mode));
        return true;
    }

    bool zExtMeshField::getBounds(
        double* minBB,
        double* maxBB
    ) {
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

    bool zExtMeshField::getIsoContour(
        zExtGraph* graph,
        float threshold
    ) {
        int precision = 6;
        float tolerance = std::pow(10, -precision);

        zFnMeshScalarField fnField(*m_field);
        fnField.getIsocontour(graph->getRawGraph(), threshold, precision, tolerance);
        return true;
    }

    bool zExtMeshField::getGradients(
        std::vector<double>& gradientVecs
    ) {
        zFnMeshScalarField fnField(*m_field);
        vector<zVector> vectors = fnField.getGradients();

        gradientVecs.clear();
        gradientVecs.reserve(vectors.size() * 3);
        for (size_t i = 0; i < vectors.size(); i++)
        {
            gradientVecs.push_back(vectors[i].x);
            gradientVecs.push_back(vectors[i].y);
            gradientVecs.push_back(vectors[i].z);
        }
        return true;
    }

} // namespace zSpace 