// This file is part of zspace, a simple C++ collection of geometry data-structures & algorithms, 
// data analysis & visualization framework.
//
// Copyright (C) 2019 ZSPACE 
// 
// This Source Code Form is subject to the terms of the MIT License 
// If a copy of the MIT License was not distributed with this file, You can 
// obtain one at https://opensource.org/licenses/MIT.
//
// Author : Heba Eiz <heba.eiz@zaha-hadid.com>
//

#ifndef ZSPACE_EXT_CORE_MESH_H
#define ZSPACE_EXT_CORE_MESH_H



#pragma once
#include "headers/base/zSpace_External.h"
#include "headers/base/zStatus.h"
#include "headers/zCore/Base/zExtPoint.h"
#include "headers/zCore/Base/zExtColor.h"
#include "headers/zCore/Utils/zExtUtilsCore.h"
#include "headers/zCore/Utils/zExtJSON.h"
#include "headers/zCore/Interop/zExtOV.h"
#include "headers/zCore/Geometry/zExtGraph.h"
#include "headers/zCore/Base/zExtTransform.h"


#include <headers/zCore/base/zExtern.h>
#include <headers/zInterface/functionsets/zFnMesh.h>


#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>

#include<execution>

using namespace std;


namespace zSpace
{
	//struct zExtjson;
	//struct zExtGraph;
	//struct zExtGraphArray;

	/*! \brief A structure representing an extended mesh.
	*/
	struct ZSPACE_EXTERNAL zExtMesh
	{
	public:
		zObjMesh* pointer = nullptr; ///< Pointer to the underlying zObjMesh.
		int vCount;     ///< The number of vertices in the mesh.
		int fCount;     ///< The number of faces in the mesh.
		//zExtPointArray verticesArray; ///< PointerArray for the vertices of a mesh
		//zExtColorArray colorsArray; ///< 
		//zExtIntArray polyCount; ///< 
		//zExtIntArray polyConnect; ///< 
		//zExtColorArray colorsArray; ///< PointerArray for the vertices of a mesh
		zExtMesh();
		~zExtMesh();
		/*! \brief Constructs a zExtMesh object.
		 *  \param m Pointer to the underlying zObjMesh.
		 */
		zExtMesh(zObjMesh* m);
		zExtMesh(zObjMesh& m);

		zStatus checkMemAlloc(bool allocateMemory = true);

		/*! \brief Updates the attributes of the zExtMesh object.
		 */
		void updateAttributes();

		bool createMeshFromJson(json* pointer);
		bool createMeshFromJson(string path);


		//void createMedialGraphFromMeshes(zObjMeshArray& oMeshes, zObjGraph& outMedialGraph);

		void graphFromMeshHEArray(zItMeshHalfEdgeArray& meshItHE, zObjGraph& outGraph);
		void graphFromMeshHEArray(vector<zItMeshHalfEdgeArray>& meshItHE, zObjGraph& outGraph);
		void getEdgeLoop(zObjMesh& mesh, vector<zItMeshHalfEdgeArray>& outUDirection, vector<zItMeshHalfEdgeArray>& outVDirection);
		void smoothMesh(int numDivisions, bool smoothCorner, zIntArray fixedIndex = zIntArray(), bool smoothFixedEdges = false);
		void smoothMesh1D( int numDivisions, bool flip = false, bool smoothCorner = true, zIntArray fixedIndex = zIntArray());

	private:
		void createMedialGraph(vector<zItMeshHalfEdgeArray>& meshHalfEdges, zObjGraph& outGraph);
		void computeLoops(zObjMesh& oMesh, zItMeshHalfEdge& heStart, zItMeshHalfEdgeArray& v_Loops);
	};
	/*! \brief A structure representing an extended mesh.
	*/
	struct ZSPACE_EXTERNAL zExtMeshArray
	{
		zObjMeshArray* pointer = nullptr;
		int arrayCount;

		zExtMeshArray(zObjMeshArray* m);
		~zExtMeshArray();
		zStatus checkMemAlloc(bool allocateMemory = true);
		void updateAttributes();
		void getItems(zObjMesh* items);
		void setItems(zObjMesh* items, int count);
	};
	struct ZSPACE_EXTERNAL zExtMeshPointerArray
	{
		zObjMeshPointerArray* pointer = nullptr;
		int arrayCount;

		zExtMeshPointerArray(zObjMeshPointerArray* m);
		~zExtMeshPointerArray();
		zStatus checkMemAlloc(bool allocateMemory = true);

		void updateAttributes();
	};

	ZSPACE_EXTERNAL_C 
	{
		//--------------------------
		//----CREATE METHODS
		//--------------------------

		/*! \brief Creates a new zExtMesh object from vertex and face data.
		 *  \param [in]		_vertexPositions			-Pointer to an array of vertex positions.
		 *  \param [in]		_polyCounts					-Pointer to an array of polygon counts.
		 *  \param [in]		_polyConnects				-Pointer to an array of polygon vertex indices.
		 *  \param [in]		numVerts					-The number of vertices in the mesh.
		 *  \param [in]		numFaces					-The number of faces in the mesh.
		 *  \param [in,out] out_mesh					-Reference to the zExtMesh object to be created.
		 */
		ZSPACE_EXTERNAL void ext_mesh_createFromRawArrays(double* _vertexPositions, int* _polyCounts, int* _polyConnects, int numVerts, int numFaces, zExtMesh & out_mesh);

		/*! \brief Creates a new zExtMesh object from vertex and face data.
		 *  \param [in]		_vertexPositions			-Pointer to an array of vertex positions.
		 *  \param [in]		_polyCounts					-Pointer to an array of polygon counts.
		 *  \param [in]		_polyConnects				-Pointer to an array of polygon vertex indices.
		 *  \param [in]		numVerts					-The number of vertices in the mesh.
		 *  \param [in]		numFaces					-The number of faces in the mesh.
		 *  \param [in,out] out_mesh					-Reference to the zExtMesh object to be created.
		 */
		ZSPACE_EXTERNAL zStatusCode ext_mesh_createFromArrays(zExtPointArray& _vertexPositions, zExtIntArray& _polyCounts, zExtIntArray& _polyConnects, zExtMesh& out_mesh);

		/*! \brief Set colors of mesh vertices.
		 *  \param [in]		extMesh						-Reference to the zExtMesh object to be created.
		 *  \param [in]		vertexColors				-Array of colors for each vertex.
		 */
		ZSPACE_EXTERNAL zStatusCode ext_mesh_setMeshVertexColors(zExtMesh& extMesh, zExtColorArray& vertexColors);

		/*! \brief Set colors of mesh vertices.
		*  \param [in]		extMesh						-Reference to the zExtMesh object to be created.
		*  \param [in]		faceColors					-Array of colors for each face.
		*/
		ZSPACE_EXTERNAL zStatusCode ext_mesh_setMeshFaceColors(zExtMesh& extMesh, zExtColorArray& faceColors);
		
		/*! \brief Set colors of mesh vertices.
		 *  \param [in]		inMesh						-Mesh to duplicate
		 *  \param [out]	outMesh						-Duplicated mesh
		 */
		ZSPACE_EXTERNAL zStatusCode ext_mesh_duplicate(zExtMesh& inMesh, zExtMesh& outMesh);




		//--------------------------
		//----EXCHANGE METHODS
		//--------------------------	

		/*! \brief Creates a new ExtMesh object from a file path.
		* \param[in]		filePath		- The path of the file to be read.
		* \param[in, out]	outMesh			- The output zExtMesh object.
		* \return 1 if the file was read successfully, 0 if the file was not read successfully.
		*/
		ZSPACE_EXTERNAL zStatusCode ext_mesh_from(char* filePath, zExtMesh& outMesh);

		/*! \brief Export zExtMesh
		* \param[in]	extMesh				- The input zExtMesh object.
		* \param[in]	filePath			- The path of the file to be written.
		* \return 1 if the file was written successfully, 0 if the file was not written successfully.
		*/
		ZSPACE_EXTERNAL zStatusCode ext_mesh_to(zExtMesh& extMesh, char* filePath);

		/*! \brief Creates a new zExtMesh object from a JSON object.
		* \param[in] json The input zExtJSON object.
		* \param[in, out] outMesh The output zExtMesh object.
		* \return 1 if the file was read successfully, 0 if the file was not read successfully.
		*/
		ZSPACE_EXTERNAL zStatusCode ext_mesh_fromJSON(zExtJSON& extjson, zExtMesh& outMesh);

		/*! \brief Export zExtMesh to JSON format
		* \param[in] extGraph The input zExtMesh object.
		* \param[in] json The output zExtJSON object.
		* \return 1 if the file was written successfully, 0 if the file was not written successfully.
		*/
		ZSPACE_EXTERNAL zStatusCode ext_mesh_toJSON(zExtMesh& extGraph, zExtJSON& json);

		#if defined(ZSPACE_USD_INTEROP)  
		/*! \brief Creates a new zExtMesh object from a JSON object.
		* \param[in] json The input zExtJSON object.
		* \param[in, out] outMesh The output zExtMesh object.
		* \return 1 if the file was read successfully, 0 if the file was not read successfully.
		*/
		ZSPACE_EXTERNAL zStatusCode ext_mesh_fromUSD(zExtUSD& extUsd, zExtMesh& outMesh);

		/*! \brief Export zExtMesh to JSON format
				* \param[in] extGraph The input zExtMesh object.
				* \param[in] json The output zExtJSON object.
				* \return 1 if the file was written successfully, 0 if the file was not written successfully.
				*/
		ZSPACE_EXTERNAL zStatusCode ext_mesh_toUSD(zExtMesh& extMesh, zExtUSD& extUsd);
		#endif
		
		
		//--------------------------
		//----GET METHODS
		//--------------------------

		/*! \brief Gets the number of faces in a zExtMesh object.
		*
		 *  \param [in] objMesh The zExtMesh object to retrieve face count from.
		 *  \param [out] outfCounts Pointer to an integer to store the face count.
		 *  \return 1 on success, 0 on failure.
		 *
		 */
		ZSPACE_EXTERNAL zStatusCode ext_mesh_getMeshFaceCounts(zExtMesh& objMesh, int* outfCounts);

		/*! \brief Gets the position and color data for the vertices of a zExtMesh object.
		*
		 *  \param [in]		objMesh The			-zExtMesh object to retrieve vertex data from.
		 *  \param [out]	outVPostions		-Pointer to an array to store vertex positions.
		 *  \param [out]	outVColors			-Pointer to an array to store vertex colors.
		 *  \return 1 on success, 0 on failure.
		 *
		 */
		ZSPACE_EXTERNAL zStatusCode ext_mesh_getVertexPositionsRaw(zExtMesh& objMesh, float* outVPostions, float* outVColors);

		/*! \brief Gets the face connectivity data for a zExtMesh object.
		 *  \param [in]		objMesh				-The zExtMesh object to retrieve face connectivity data from.
		 *  \param [out]	outfConnects		-Pointer to an array to store face connectivity data.
		 *  \return 1 on success, 0 on failure.
		 */
		ZSPACE_EXTERNAL zStatusCode ext_mesh_getMeshFaceConnect(zExtMesh& objMesh, int* outfConnects);

		/*! \brief Gets the center point of the mesh.
		 *  \param [in]		objMesh				-The zExtMesh object to retrieve face connectivity data from.
		 *  \param [out]	outCenter			-Pointer to an array to store centre position.
		 *  \return 1 on success, 0 on failure.
		 */
		ZSPACE_EXTERNAL zStatusCode ext_mesh_getMeshCentre(zExtMesh& objMesh, float* outCentre);

		/*! \brief Gets the the vertices in a zExtMesh object.
		 *  \param [in]		objMesh				-The zExtMesh object to retrieve vertex count from.
		 *  \param [out]	outVCount			-out array of position.
		 *  \return 1 on success, 0 on failure.
		 */

		ZSPACE_EXTERNAL zStatusCode ext_mesh_getVertexPositions(zExtMesh& objMesh, zExtPointArray& extPointArray);

		/*! \brief Get the mesh colors in a zExtMesh object.
		   *  \param [in]  objMesh    -The zExtMesh object to retrieve vertex count from.
		   *  \param [out] extPointArray   -Array to store colors of a mesh.
		   *  \return 1 on success, 0 on failure.
		  */
		ZSPACE_EXTERNAL zStatusCode ext_mesh_getMeshColors(zExtMesh& objMesh, zExtColorArray& extPointArray);

		/*! \brief Gets the polygon data for a zExtMesh object.
		 *  \param [in]  objMesh    -The zExtMesh object to retrieve polygon data from.
		 *  \param [out] pCount  -Pointer to an array to store polygon vertex count.
		 *  \param [out] pConnect  -Pointer to an array to store polygon vertex indices.
		 *  \return 1 on success, 0 on failure.
		 */
		ZSPACE_EXTERNAL zStatusCode ext_mesh_getMeshPolygonDate(zExtMesh& objMesh, zExtIntArray& pCount, zExtIntArray& pConnect);


		ZSPACE_EXTERNAL zStatusCode ext_mesh_getEdgeLoops(zExtMesh& objMesh, zExtGraphArray& graphArrayU, zExtGraphArray& graphArrayV);

		ZSPACE_EXTERNAL zStatusCode ext_mesh_getEdgeLoopsGraph(zExtMesh& objMesh, zExtGraph& graphU, zExtGraph& graphV);

		/*! \brief Gets the planarity deviation per face for a zExtMesh object.
		 *  \param [in]  objMesh    -The zExtMesh object to retrieve planarity deviation data from.
		 *  \param [out] outPlanarityDevs  -Pointer to an array to store planarity deviation data.
		 *  \param [in]  type  -The type of planarity deviation to calculate.
		 *  \param [in]  colorFaces  -Whether to color the faces of the mesh.
		 *  \param [in]  tolerance  -The tolerance for the planarity deviation calculation.
		 *  \return 1 on success, 0 on failure.
		 */
		ZSPACE_EXTERNAL zStatusCode ext_mesh_getPlanarityDeviationPerFace(zExtMesh& objMesh, zExtDoubleArray& outPlanarityDevs, int type, bool colorFaces = false, double tolerance = 0.05);

		/*! \brief Gets the Gaussian curvature for a zExtMesh object.
		 *  \param [in]  objMesh    -The zExtMesh object to retrieve Gaussian curvature data from.
		 *  \param [out] outGaussianCurvature  -Pointer to an array to store Gaussian curvature data.
		 *  \return 1 on success, 0 on failure.
		 */
		ZSPACE_EXTERNAL zStatusCode ext_mesh_getGaussianCurvature(zExtMesh& objMesh, zExtDoubleArray& outGaussianCurvature);

		/*! \brief Checks the planarity of a zExtMesh object.
		 *  \param [in]  objMesh    -The zExtMesh object to check planarity for.
		 *  \param [in]  tolerance  -The tolerance for the planarity check.
		 *  \param [in]  planarityType  -The type of planarity to check.
		 *  \param [in]  colorFaces  -Whether to color the faces of the mesh.
		 *  \param [out] outDeviations  -Pointer to an array to store planarity deviation data.
		 *  \return 1 on success, 0 on failure.
		 */
		ZSPACE_EXTERNAL zStatusCode ext_mesh_checkPlanarity(zExtMesh& objMesh, float tolerance, int planarityType, bool colorFaces, zExtDoubleArray& outDeviations);

		/*! \brief Gets the face color data for a given zExtMesh object.
		•	\param [in]  objMesh    -The zExtMesh object to retrieve face color data from.
		•	\param [out] extColorArray  -Pointer to an array to store the face color data.
		•	\return 1 on success, 0 on failure.
		*/
		ZSPACE_EXTERNAL zStatusCode ext_mesh_getFaceColor(zExtMesh& objMesh, zExtColorArray& extPointArray);

		//--------------------------
		//----OPERATORS METHODS
		//--------------------------

		/*! \brief Smooths a zExtMesh object.
		 *  \param [in]  objMesh		-The zExtMesh object to smooth.
		 *  \param [in]  level			-The number of times to smooth the mesh.
		 *  \param [in]  smoothCorner	-If TRUE, mesh corner (vertices with two connected edges) will be smoothed.
		 *  \param [in]  fixedVerts		-Array of fixed vertices.
		 *  \return 1 on success, 0 on failure.
		 */
		ZSPACE_EXTERNAL zStatusCode ext_mesh_smoothMesh(zExtMesh& objMesh, int level, bool smoothCorner, zExtIntArray& fixedVerts, bool smoothFixedEdges);

		/*! \brief Smooths a zExtMesh object in 1 Direction.
		 *  \param [in]  objMesh		-The zExtMesh object to smooth.
		 *  \param [in]  level			-The number of times to smooth the mesh.
		 *  \param [in]  smoothCorner	-If TRUE, mesh corner (vertices with two connected edges) will be smoothed.
		 *  \param [in]  flip			-Flip the direction of 1D smoothening.
		 *  \param [in]  fixedVerts		-Array of fixed vertices.
		 *  \return 1 on success, 0 on failure.
		 */
		ZSPACE_EXTERNAL zStatusCode ext_mesh_smoothMesh1D(zExtMesh& objMesh, int level, bool smoothCorner, bool flip, zExtIntArray& fixedVerts);


		ZSPACE_EXTERNAL zStatusCode ext_mesh_meshPlaneIntersection(zExtMesh& inMesh, zExtPoint& origin, zExtPoint& normal, zExtGraph& outGraph, int inPres);




		ZSPACE_EXTERNAL zPoint ext_mesh_meshTest(int num);
		ZSPACE_EXTERNAL int ext_mesh_meshTest2(zStatus2& num);
		


	}
	
	
	ZSPACE_EXTERNAL_C
	{
		//--------------------------
		//----ARRAY METHODS
		//--------------------------

		/*! \brief Gets an array of zExtMesh from zExtMeshArray object.
		*  \param [in]		inArray				-zExtMeshArray to get zExtMesh from.
		*  \param [out]		zExtMesh			-Out array of meshes.
		*  \return 1 on success, 0 on failure.
		*/
		ZSPACE_EXTERNAL zStatusCode ext_mesh_getMeshsFromMeshArray(zExtMeshArray& inArray, zExtMesh* outMeshes);

		/*! \brief Gets an array of zExtMesh from zExtMeshPointerArray object.
		*  \param [in]		inArray				-zExtMeshPointerArray to get zExtMesh from.
		*  \param [out]		zExtMesh			-Out array of meshes.
		*  \return 1 on success, 0 on failure.
		*/
		ZSPACE_EXTERNAL zStatusCode ext_mesh_getMeshsFromMeshPointerArray(zExtMeshPointerArray& inArray, zExtMesh* outMeshes);

	}

}




#if defined(ZSPACE_EXTERNAL_STATIC_LIBRARY)  || defined(ZSPACE_EXTERNAL_DYNAMIC_LIBRARY)
// All defined OK so do nothing
#else
#include<source/zCore/Geometry/zExtMesh.cpp>
#endif

#endif