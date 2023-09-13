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

#ifndef ZSPACE_EXT_CORE_H
#define ZSPACE_EXT_CORE_H



#pragma once
#include <headers/base/zSpace_External.h>
#include <headers/zCore/zExtPoint.h>
#include <headers/zCore/zExtColor.h>
#include <headers/zCore/zExtUtilsCore.h>

#include <headers/zCore/base/zExtern.h>
#include <headers/zInterface/functionsets/zFnMesh.h>
#include <headers/zInterface/functionsets/zFnGraph.h>

//#include <pxr/usd/sdf/path.h>
//#include <pxr/usd/usd/modelAPI.h>
//#include <pxr/usd/usd/stage.h>
//#include <pxr/usd/usdGeom/sphere.h>

//#include <USD/headers/pxr/usd/sdf/path.h>
//#include <USD/headers/pxr/usd/usd/modelAPI.h>
//#include <USD/headers/pxr/usd/usd/stage.h>
//#include <USD/headers/pxr/usd/usdGeom/sphere.h>

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>

#include<execution>

using namespace std;


namespace zSpace
{

	/*! \brief A structure representing an extended mesh.
	*/
	struct zExtMesh
	{
		zObjMesh* extPointer; ///< Pointer to the underlying zObjMesh.
		int vCount;     ///< The number of vertices in the mesh.
		int fCount;     ///< The number of faces in the mesh.
		//zExtPointArray verticesArray; ///< PointerArray for the vertices of a mesh
		//zExtColorArray colorsArray; ///< 
		//zExtIntArray polyCount; ///< 
		//zExtIntArray polyConnect; ///< 
		//zExtColorArray colorsArray; ///< PointerArray for the vertices of a mesh
		zExtMesh();
		/*! \brief Constructs a zExtMesh object.
		 *  \param m Pointer to the underlying zObjMesh.
		 */
		zExtMesh(zObjMesh* m);

		/*! \brief Updates the attributes of the zExtMesh object.
		 */
		void updateAttributes();

		bool createMeshFromJson(json* pointer);
		bool createMeshFromJson(string path);
	};
	/*! \brief A structure representing an extended mesh.
	*/
	struct zExtMeshArray
	{
		zObjMeshArray* pointer;
		int arrayCount;

		zExtMeshArray(zObjMeshArray* m);
		void updateAttributes();
	};
	struct zExtMeshPointerArray
	{
		zObjMeshPointerArray* pointer;
		int arrayCount;

		zExtMeshPointerArray(zObjMeshPointerArray* m);
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
		ZSPACE_EXTERNAL void ext_meshUtil_createMeshOBJFromRawArray(double* _vertexPositions, int* _polyCounts, int* _polyConnects, int numVerts, int numFaces, zExtMesh& out_mesh);

		/*! \brief Creates a new zExtMesh object from vertex and face data.
		 *  \param [in]		_vertexPositions			-Pointer to an array of vertex positions.
		 *  \param [in]		_polyCounts					-Pointer to an array of polygon counts.
		 *  \param [in]		_polyConnects				-Pointer to an array of polygon vertex indices.
		 *  \param [in]		numVerts					-The number of vertices in the mesh.
		 *  \param [in]		numFaces					-The number of faces in the mesh.
		 *  \param [in,out] out_mesh					-Reference to the zExtMesh object to be created.
		 */
		ZSPACE_EXTERNAL int ext_meshUtil_createMeshOBJFromArray(zExtPointArray& _vertexPositions, zExtIntArray& _polyCounts, zExtIntArray& _polyConnects, zExtMesh& out_mesh);

		/*! \brief Set colors of mesh vertices.
		 *  \param [in]		extMesh						-Reference to the zExtMesh object to be created.
		 *  \param [in]		vertexColors				-Array of colors for each vertex.
		 */
		ZSPACE_EXTERNAL int ext_meshUtil_setMeshVertexColors(zExtMesh& extMesh, zExtColorArray& vertexColors);



		/*! \brief Creates a new zExtMesh object from vertex and face data.
		 *  \param [in]		_vertexPositions			-File path
		 *  \param [in,out] out_mesh					-Reference to the zExtMesh object to be created.
		 */
		ZSPACE_EXTERNAL void ext_meshUtil_createMeshOBJFromFile(char* filePath, zExtMesh& out_mesh);

		/*! \brief Creates a new zExtMesh object from vertex and face data.
		*  \param [in]		_vertexPositions			-File path
		*  \param [in,out] out_mesh					-Reference to the zExtMesh object to be created.
		*/
		ZSPACE_EXTERNAL void ext_meshUtil_exportToJson(zExtMesh& mesh, char* filePath);

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
		ZSPACE_EXTERNAL int ext_meshUtil_getMeshFaceCount(zExtMesh& objMesh, int* outfCounts);

		/*! \brief Gets the position and color data for the vertices of a zExtMesh object.
		*
		 *  \param [in]		objMesh The			-zExtMesh object to retrieve vertex data from.
		 *  \param [out]	outVPostions		-Pointer to an array to store vertex positions.
		 *  \param [out]	outVColors			-Pointer to an array to store vertex colors.
		 *  \return 1 on success, 0 on failure.
		 *
		 */
		ZSPACE_EXTERNAL int ext_meshUtil_getMeshPositionRaw(zExtMesh& objMesh, float* outVPostions, float* outVColors);

		/*! \brief Gets the face connectivity data for a zExtMesh object.
		 *  \param [in]		objMesh				-The zExtMesh object to retrieve face connectivity data from.
		 *  \param [out]	outfConnects		-Pointer to an array to store face connectivity data.
		 *  \return 1 on success, 0 on failure.
		 */
		ZSPACE_EXTERNAL int ext_meshUtil_getMeshFaceConnect(zExtMesh& objMesh, int* outfConnects);

		/*! \brief Gets the center point of the mesh.
		 *  \param [in]		objMesh				-The zExtMesh object to retrieve face connectivity data from.
		 *  \param [out]	outCenter			-Pointer to an array to store centre position.
		 *  \return 1 on success, 0 on failure.
		 */
		ZSPACE_EXTERNAL int ext_meshUtil_getMeshCentre(zExtMesh& objMesh, float* outCentre);


		/*! \brief Gets an array of zExtMesh from zExtMeshArray object.
		*  \param [in]		inArray				-zExtMeshArray to get zExtMesh from.
		*  \param [out]		zExtMesh			-Out array of meshes.
		*  \return 1 on success, 0 on failure.
		*/
		ZSPACE_EXTERNAL int ext_meshUtil_getMeshsFromMeshArray(zExtMeshArray& inArray, zExtMesh* outMeshes);

		/*! \brief Gets an array of zExtMesh from zExtMeshPointerArray object.
		*  \param [in]		inArray				-zExtMeshPointerArray to get zExtMesh from.
		*  \param [out]		zExtMesh			-Out array of meshes.
		*  \return 1 on success, 0 on failure.
		*/
		ZSPACE_EXTERNAL int ext_meshUtil_getMeshsFromMeshPointerArray(zExtMeshPointerArray& inArray, zExtMesh* outMeshes);


		ZSPACE_EXTERNAL int ext_meshUtil_getMeshPosition(zExtMesh& objMesh, zExtPointArray& extPointArray);
		ZSPACE_EXTERNAL int ext_meshUtil_getMeshColors(zExtMesh& objMesh, zExtColorArray& extPointArray);
		ZSPACE_EXTERNAL int ext_meshUtil_getMeshPolygonDate(zExtMesh& objMesh, zExtIntArray& pCount, zExtIntArray& pConnect);

		ZSPACE_EXTERNAL int ext_meshUtil_catmullclark(zExtMesh& objMesh, int level, bool fixedCorner);



	}

}




#if defined(ZSPACE_EXTERNAL_STATIC_LIBRARY)  || defined(ZSPACE_EXTERNAL_DYNAMIC_LIBRARY)
// All defined OK so do nothing
#else
#include<source/zCore/zExtMesh.cpp>
#endif

#endif