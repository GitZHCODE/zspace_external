/**
 * \file zExtMesh.cpp
 * \brief Implementation of the External mesh class for zSpace - Minimal MVP
 * \date 2023
 */

// Include local header (relative to cpp directory)
#include "headers/zCore/Geometry/zExtMesh.h"

// Include zspace_core headers
#include <headers/zInterface/functionsets/zFnMesh.h>
#include <headers/zInterface/objects/zObjMesh.h>
#include <headers/zToolsets/geometry/zTsMeshParameterization.h>

#include <algorithm>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <math.h>

namespace zSpace {

zExtMesh::zExtMesh() : m_mesh(new zObjMesh()), m_vertexCount(0), m_faceCount(0) {
}

zExtMesh::zExtMesh(zObjMesh* mesh) : m_mesh(mesh), m_vertexCount(0), m_faceCount(0) {
    if (m_mesh) {
		updateAttributes();
	}
}

zExtMesh::zExtMesh(const zExtMesh& other) : m_vertexCount(other.m_vertexCount), m_faceCount(other.m_faceCount) {
    if (other.m_mesh) {
        m_mesh.reset(new zObjMesh(*other.m_mesh));
    } else {
        m_mesh.reset(new zObjMesh());
    }
}

zExtMesh::~zExtMesh() = default;

bool zExtMesh::isValid() const {
    return m_mesh != nullptr;
}

int zExtMesh::getVertexCount() const {
    return m_vertexCount;
}

int zExtMesh::getFaceCount() const {
    return m_faceCount;
}

zObjMesh& zExtMesh::getRawMesh() const {
    if (!m_mesh) {
        throw std::runtime_error("Mesh is not initialized");
    }
    return *m_mesh;
}

void zExtMesh::updateAttributes() {
    if (m_mesh) {
        m_vertexCount = static_cast<int>(m_mesh->mesh.n_v);
        m_faceCount = static_cast<int>(m_mesh->mesh.n_f);
    } else {
        m_vertexCount = 0;
        m_faceCount = 0;
    }
}

bool zExtMesh::createMesh(
    const double* vertexPositions, int vertexCount,
    const int* polyCounts, int polyCountsSize,
    const int* polyConnections, int polyConnectionsSize
) {
    try {
        if (!m_mesh) {
            m_mesh.reset(new zObjMesh());
        }

        // Create a function object for the mesh
        zFnMesh fnMesh(*m_mesh);

        // Clear existing mesh
        fnMesh.clear();

        // Convert vertex positions to zPoint array
        zPointArray positions;
        positions.reserve(vertexCount);

        for (int i = 0; i < vertexCount; i++) {
            int baseIndex = i * 3; // Each vertex has 3 components (x, y, z)
            positions.push_back(zPoint(
                vertexPositions[baseIndex],
                vertexPositions[baseIndex + 1],
                vertexPositions[baseIndex + 2]
            ));
        }

        // Convert polygon counts to zIntArray
        zIntArray polyCountsArray;
        polyCountsArray.reserve(polyCountsSize);
        for (int i = 0; i < polyCountsSize; i++) {
            polyCountsArray.push_back(polyCounts[i]);
        }

        // Convert polygon connections to zIntArray
        zIntArray polyConnectionsArray;
        polyConnectionsArray.reserve(polyConnectionsSize);
        for (int i = 0; i < polyConnectionsSize; i++) {
            polyConnectionsArray.push_back(polyConnections[i]);
        }

        // Create the mesh
        fnMesh.create(positions, polyCountsArray, polyConnectionsArray);

        // Check if creation was successful
        if (fnMesh.numVertices() > 0) {
            updateAttributes();
            return true;
        } else {
            // Reset mesh in case of failure
            m_mesh.reset(new zObjMesh());
            m_vertexCount = 0;
            m_faceCount = 0;
            return false;
        }
    } catch (const std::exception&) {
        // Reset mesh in case of failure
        m_mesh.reset(new zObjMesh());
        m_vertexCount = 0;
        m_faceCount = 0;
        return false;
    }
}

bool zExtMesh::getMeshData(
    vector<double>& vertexPositions,
    vector<int>& polyConnects,
    vector<int>& polyCounts
) {
    try {
        if (!m_mesh) {
            return false;
        }

        zFnMesh fnMesh(*m_mesh);
        vector<zPoint> positions;
        fnMesh.getVertexPositions(positions);

        vertexPositions.reserve(fnMesh.numVertices() * 3);
        for (size_t i = 0; i < positions.size(); i++)
        {
            vertexPositions.push_back(positions[i].x);
            vertexPositions.push_back(positions[i].y);
            vertexPositions.push_back(positions[i].z);
        }

        fnMesh.getPolygonData(polyConnects, polyCounts);

        return true;
    }
    catch (const std::exception&) {
        return false;
    }
}

bool zExtMesh::intersect_plane(
    const float* origin,
    const float* normal,
    zExtGraph* out_intersection
)
{
    try {
        if (!m_mesh || !origin || !normal || !out_intersection) {
            return false;
        }

        zFnMesh fnMesh(*m_mesh);
        if(!fnMesh.isTriMesh()) fnMesh.triangulate();

        vector<zVector> positions;
        vector<int> pConnects;

        int counter = 0;
        int faceCount = 0;

        for (zItMeshFace f(*m_mesh); !f.end(); f++)
        {
            faceCount++;
            vector<zPoint> vertices;
            f.getVertexPositions(vertices);

            zVector o(origin[0], origin[1], origin[2]);
            zVector n(normal[0], normal[1], normal[2]);

             float d0 = n* vertices[0]  - n * o;
             float d1 = n* vertices[1]  - n * o;
             float d2 = n* vertices[2]  - n * o;

             // Check if triangle is intersected by the plane
             bool pos = (d0 > 0) || (d1 > 0) || (d2 > 0);
             bool neg = (d0 < 0) || (d1 < 0) || (d2 < 0);

             if (!(pos && neg)) continue; // Triangle does not cross the plane

             // Find edges that cross the plane
             std::vector<std::pair<zVector, zVector>> edges;

             if ((d0 * d1) < 0) edges.emplace_back(vertices[0], vertices[1]);
             if ((d1 * d2) < 0) edges.emplace_back(vertices[1], vertices[2]);
             if ((d2 * d0) < 0) edges.emplace_back(vertices[2], vertices[0]);
             if (edges.size() < 2) continue;

             // Intersect each edge with plane
             zVector pts[2];
             for (int j = 0; j < 2; ++j)
             {
                 zVector& a = edges[j].first;
                 zVector& b = edges[j].second;
                 float da = n * a - n * o;
                 float db = n * b - n * o;
                 float denom = da - db;
                 if (fabs(denom) < EPS) continue;  // coplanar edge
                 float t = da / denom;
                 pts[j] = a + (b - a) * t;
             }

             positions.push_back(pts[0]);
             positions.push_back(pts[1]);
             pConnects.push_back(counter++);
             pConnects.push_back(counter++);
        }

        // Create the intersection graph using the provided zExtGraph
        zFnGraph fnGraph(out_intersection->getRawGraph());
        
        // Check if we have any intersection data
        if (positions.empty() || pConnects.empty()) {
            // No intersection found, create empty graph
            fnGraph.clear();
            return true;
        }
        
        fnGraph.create(positions, pConnects);

        // Make sure to update the graph's internal state
        out_intersection->updateAttributes();

        return true;
    }
    catch (const std::exception&) {
        return false;
    }
}

bool zExtMesh::computeGeodesicHeat(
    const int* sourceVIds, int sourceVCount, bool normalised,
    float* out_geodesicScalars
	)
{
    try {
        if (!m_mesh || !out_geodesicScalars || !sourceVIds || sourceVCount <= 0) {
            // Initialize the output array to zeros in case of error
            if (out_geodesicScalars && m_vertexCount > 0) {
                for (int i = 0; i < m_vertexCount; i++) {
                    out_geodesicScalars[i] = 0.0f;
                }
            }
            return false;
        }

        // Validate if all source vertex IDs are in valid range
        for (int i = 0; i < sourceVCount; i++) {
            if (sourceVIds[i] < 0 || sourceVIds[i] >= m_vertexCount) {
                // Invalid vertex index detected
                for (int j = 0; j < m_vertexCount; j++) {
                    out_geodesicScalars[j] = 0.0f;
                }
                return false;
            }
        }

        // Setup mesh parameterization
	zTsMeshParam myMeshParam;
	myMeshParam.o_TriMesh = *m_mesh;

        zFnMesh fnMesh(myMeshParam.o_TriMesh);
        fnMesh.computeMeshNormals();
        fnMesh.getMatrices_trimesh(myMeshParam.triMesh_V, myMeshParam.triMesh_FTris);

        // Initialize the output array to zeros
        for (int i = 0; i < m_vertexCount; i++) {
            out_geodesicScalars[i] = 0.0f;
        }

        // Compute geodesic heat
        // Convert source IDs to vector
        vector<int> sourceVertices;
        sourceVertices.reserve(sourceVCount);
        for (int i = 0; i < sourceVCount; i++) {
            sourceVertices.push_back(sourceVIds[i]);
        }

        // Compute geodesic distances
	vector<float> geodesicScalars;
        myMeshParam.computeGeodesics_Exact(sourceVertices, geodesicScalars);
        
        // Check if we got valid results
        if (geodesicScalars.size() == 0 || geodesicScalars.size() != (size_t)m_vertexCount) {
            return false;
        }

        if (normalised)
        {
            // Normalize values to [0,1] range
            zDomainFloat startMinMax(myMeshParam.coreUtils.zMin(geodesicScalars), myMeshParam.coreUtils.zMax(geodesicScalars));
            zDomainFloat outMinMax(0, 1);
            for (auto& v : geodesicScalars) {
                v = myMeshParam.coreUtils.ofMap(v, startMinMax, outMinMax);
            }
        }

        // Copy results to output array (safely handling size differences)
        int copySize = min((int)geodesicScalars.size(), m_vertexCount);
        for (int i = 0; i < copySize; i++) {
            out_geodesicScalars[i] = geodesicScalars[i];
        }

        // Color the mesh
	zColor* mesh_vColors = fnMesh.getRawVertexColors();

	zScalar minScalar = myMeshParam.coreUtils.zMin(geodesicScalars);
	zScalar maxScalar = myMeshParam.coreUtils.zMax(geodesicScalars);

	zDomainFloat distanceDomain(minScalar, maxScalar);
	zDomainColor colDomain(zColor(1, 0, 0, 1), zColor(0, 1, 0, 1));

        for (int i = 0; i < min(fnMesh.numVertices(), (int)geodesicScalars.size()); i++) {
		mesh_vColors[i] = myMeshParam.coreUtils.blendColor(geodesicScalars[i], distanceDomain, colDomain, zRGB);
	}

	fnMesh.computeFaceColorfromVertexColor();

        return true;
    }
    catch (const std::exception& e) {
        // Initialize the output array to zeros in case of error
        if (out_geodesicScalars && m_vertexCount > 0) {
            for (int i = 0; i < m_vertexCount; i++) {
                out_geodesicScalars[i] = 0.0f;
            }
        }
        return false;
    }
    catch (...) {
        // Initialize the output array to zeros in case of error
        if (out_geodesicScalars && m_vertexCount > 0) {
            for (int i = 0; i < m_vertexCount; i++) {
                out_geodesicScalars[i] = 0.0f;
            }
        }
        return false;
    }
}

bool zExtMesh::computeGeodesicHeat_interpolated(
    const int* startVIds, int startCount,
    const int* endVIds, int endCount,
    float weight,
    float* out_geodesicScalars
) {
    try {
        if (!m_mesh || !out_geodesicScalars || !startVIds || !endVIds || startCount <= 0 || endCount <= 0 || weight <= 0 || weight >= 1) {
            // Initialize the output array to zeros in case of error
            if (out_geodesicScalars && m_vertexCount > 0) {
                for (int i = 0; i < m_vertexCount; i++) {
                    out_geodesicScalars[i] = 0.0f;
                }
            }
            return false;
        }

        // Allocate memory for the start and end geodesic distances
        std::vector<float> geodesicStart(m_vertexCount, 0.0f);
        std::vector<float> geodesicEnd(m_vertexCount, 0.0f);

        // Compute geodesic distances from start and end vertices
		if (!computeGeodesicHeat(startVIds, startCount, true, geodesicStart.data())) {
            return false;
        }

		if (!computeGeodesicHeat(endVIds, endCount, true, geodesicEnd.data())) {
            return false;
        }

        // Interpolate between the start and end geodesic distances
        for (int j = 0; j < m_vertexCount; j++) {
            out_geodesicScalars[j] = weight * geodesicStart[j] + (1.0f - weight) * geodesicEnd[j];
        }

        return true;
    }
    catch (const std::exception& e) {
        // Initialize the output array to zeros in case of error
        if (out_geodesicScalars && m_vertexCount > 0) {
            for (int i = 0; i < m_vertexCount; i++) {
                out_geodesicScalars[i] = 0.0f;
            }
        }
        return false;
    }
    catch (...) {
        // Initialize the output array to zeros in case of error
        if (out_geodesicScalars && m_vertexCount > 0) {
            for (int i = 0; i < m_vertexCount; i++) {
                out_geodesicScalars[i] = 0.0f;
            }
        }
        return false;
    }
}

bool zExtMesh::computeGeodesicContours(
    const int* sourceVIds, int sourceVCount,
    int steps, float dist,
    std::vector<zExtGraph*>& out_contours
)
{
    try {
        if (!m_mesh || !sourceVIds || sourceVCount <= 0 || steps <= 0) {
            return false;
        }

        // Clear any existing contours in the output vector
        for (auto& graph : out_contours) {
            delete graph;
        }
        out_contours.clear();

        // Compute geodesic distances from source vertices
        std::vector<float> geodesicScalars(m_vertexCount, 0.0f);
		if (!computeGeodesicHeat(sourceVIds, sourceVCount, false, geodesicScalars.data())) {
            return false;
        }

        // Get min/max values for the scalar field
        zUtilsCore core;
        zScalar minScalar = core.zMin(geodesicScalars);
        zScalar maxScalar = core.zMax(geodesicScalars);
        zScalar range = maxScalar - minScalar;

        // Determine how many contours to generate based on user input
        int numContours;
        if (dist == 0.0f) {
            // If dist is 0, use the fixed number of steps
            numContours = steps;
        } else {
            // Otherwise, calculate how many contours fit in the range based on dist
            numContours = (int)(range / dist);
            // Ensure we have at least one contour
            numContours = std::max(1, numContours);
        }

        // Normalize values to [0,1] range
		zDomainFloat startMinMax(minScalar, maxScalar);
		zDomainFloat outMinMax(0, 1);
        for (auto& v : geodesicScalars) {
            v = core.ofMap(v, startMinMax, outMinMax);
        }

        // Create function object for the mesh
        zFnMesh fnMesh(*m_mesh);

        // Create contours at regular intervals
        for (int i = 0; i < numContours; i++) {
            // Calculate normalized weight for this contour
            float weight = (float)(i + 1) / (float)(numContours + 1);
            
            // Generate the isocontour using the threshold value
            zPointArray positions;
            zIntArray edgeConnects;
            zColorArray vColors;
            int precision = 6;
            float tolerance = std::pow(10, -precision);

            // Extract contour at the current iso value
            fnMesh.getIsoContour(geodesicScalars, weight, positions, edgeConnects, vColors, precision, tolerance);
            
            // Create graph from the isocontour (only if we have valid geometry)
            if (!positions.empty() && !edgeConnects.empty()) {
                zObjGraph* contourPtr = new zObjGraph();
                zFnGraph fnGraph(*contourPtr);
                fnGraph.create(positions, edgeConnects);

                out_contours.push_back(new zExtGraph(contourPtr));
            }
        }

        // Color the mesh based on the geodesic field (optional)
        zColor* mesh_vColors = fnMesh.getRawVertexColors();
        zDomainFloat distanceDomain(minScalar, maxScalar);
        zDomainColor colDomain(zColor(1, 0, 0, 1), zColor(0, 1, 0, 1));

        for (int i = 0; i < fnMesh.numVertices(); i++) {
            mesh_vColors[i] = core.blendColor(geodesicScalars[i], distanceDomain, colDomain, zRGB);
        }
        fnMesh.computeFaceColorfromVertexColor();

        return !out_contours.empty();
    }
    catch (const std::exception&) {
        // Clean up any contours created so far
        for (auto& graph : out_contours) {
            delete graph;
        }
        out_contours.clear();
        return false;
    }
}

bool zExtMesh::computeGeodesicContours_interpolated(
    const int* startVIds, int startCount,
    const int* endVIds, int endCount,
    int steps, float dist,
    std::vector<zExtGraph*>& out_contours
)
{
    try {
        if (!m_mesh || !startVIds || !endVIds || startCount <= 0 || endCount <= 0 || steps <= 0) {
            return false;
        }

        // Clear any existing contours in the output vector
        for (auto& graph : out_contours) {
            delete graph;
        }
        out_contours.clear();

        // Compute geodesic distances from start and end vertices
        std::vector<float> geodesicStart(m_vertexCount, 0.0f);
        std::vector<float> geodesicEnd(m_vertexCount, 0.0f);
        
		if (!computeGeodesicHeat(startVIds, startCount, false, geodesicStart.data())) {
            return false;
        }

		if (!computeGeodesicHeat(endVIds, endCount, true, geodesicEnd.data())) {
            return false;
        }

        // Get min/max values for this interpolated field
        zUtilsCore core;
        zScalar minScalar = core.zMin(geodesicStart);
        zScalar maxScalar = core.zMax(geodesicStart);
        zScalar range = maxScalar - minScalar;

        // Determine how many contours to generate based on user input
        int numContours;
        if (dist == 0.0f) {
            // If dist is 0, use the fixed number of steps
            numContours = steps;
        }
        else {
            // Otherwise, calculate how many contours fit in the range based on dist
            numContours = (int)(range / dist);
            // Number of contours will be half of one side because we blend two scalars
            numContours *= 0.5;
            // Ensure we have at least one contour
            numContours = std::max(1, numContours);
        }

        // Normalize values to [0,1] range
        zDomainFloat startMinMax(minScalar, maxScalar);
        zDomainFloat outMinMax(0, 1);
        for (auto& v : geodesicStart) {
            v = core.ofMap(v, startMinMax, outMinMax);
        }

        // Create function object for the mesh
        zFnMesh fnMesh(*m_mesh);

        // Initialize working scalar field for interpolation
        std::vector<float> geodesicScalars(m_vertexCount, 0.0f);
        
        // For each step, generate a contour
        for (int i = 0; i < numContours; i++) {
            // Calculate interpolation weight for this contour
            float weight = (float)(i + 1) / (float)(numContours + 1);
            
            // Interpolate between start and end geodesic distances
            for (int j = 0; j < m_vertexCount; j++) {
                geodesicScalars[j] = weight * geodesicStart[j] - (1.0f - weight) * geodesicEnd[j];
            }

            // Generate the isocontour at a mid-value
            zPointArray positions;
            zIntArray edgeConnects;
            zColorArray vColors;
            int precision = 6;
            float tolerance = std::pow(10, -precision);
            
            // Use fixed iso value at 0.0
            float isoValue = 0.0f;

            // Extract contour at the current iso value
            fnMesh.getIsoContour(geodesicScalars, isoValue, positions, edgeConnects, vColors, precision, tolerance);
            
            // Create graph from the isocontour (only if we have valid geometry)
            if (!positions.empty() && !edgeConnects.empty()) {
                zObjGraph* contourPtr = new zObjGraph();
                zFnGraph fnGraph(*contourPtr);
                fnGraph.create(positions, edgeConnects);
                
                out_contours.push_back(new zExtGraph(contourPtr));
            }
        }

        return !out_contours.empty();
    }
    catch (const std::exception&) {
        // Clean up any contours created so far
        for (auto& graph : out_contours) {
            delete graph;
        }
        out_contours.clear();
        return false;
    }
}

bool zExtMesh::transform(
    const float* tMatrix
)
{
    try {
        if (!m_mesh || !tMatrix) {
            return false;
        }

        Eigen::Matrix4f transformationMatrix = Eigen::Matrix4f::Identity();
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
            {
                // IMPORTANT
                // the input matrix should be column major but we feed eigen matrix in a row major
                // this is because eigen will pick it up internally to a column major matrix
                // this step is meant to avoid confusion since the input format will eventually match eigen format.

                transformationMatrix(i, j) = tMatrix[i * 4 + j]; // row-major
            }

        zTransform transform(transformationMatrix);
        zFnMesh fnMesh(*m_mesh);
        fnMesh.setTransform(transform, false, true);

        return true;
    }
    catch (const std::exception&) {
        return false;
    }
}

} // namespace zSpace 