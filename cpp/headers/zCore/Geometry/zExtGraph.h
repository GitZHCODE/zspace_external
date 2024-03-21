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

#ifndef ZSPACE_EXT_CORE_GRAPH_H
#define ZSPACE_EXT_CORE_GRAPH_H



#pragma once

#include "headers/base/zSpace_External.h"
#include "headers/base/zStatus.h"
#include "headers/zCore/Base/zExtPoint.h"
#include "headers/zCore/Base/zExtColor.h"
#include "headers/zCore/Utils/zExtUtilsCore.h"
#include "headers/zCore/Utils/zExtJSON.h"
#include "headers/zCore/Interop/zExtOV.h"

#include <headers/zCore/base/zExtern.h>
#include <headers/zInterface/functionsets/zFnGraph.h>



#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>

#include<execution>

using namespace std;

namespace zSpace
{
	struct zExtJSON;
	struct zExtMesh;


	/** \addtogroup zExternal
	*	\brief Collection of external structs and methods for applications.
	*  @{
	*/

	/** \addtogroup zToolsets
	*	\brief external structs and methods for zToolsets.
	*  @{
	*/

	/** \addtogroup DigiFab
	*	\brief external structs and methods for digital fabrication related utilities.
	*  @{
	*/

	/*! \class zTsRobot
	*	\brief A class for inverse kinematics chain of a 6 Axis Robot.
	*	\since version 0.0.2
	*/

	/** @}*/

	/** @}*/

	/** @}*/
	struct ZSPACE_EXTERNAL zExtGraph
	{

		zObjGraph* pointer = nullptr;  /**< A pointer to the graph array object */
		int vCount; /**< The number of vertices in the graph */
		int eCount; /**< The number of edges in the graph */
		zExtPointArray vPositions; /**< The array of vertex positions */
		zExtColorArray vColors; /**< The array of vertex colors */
		zExtIntArray ePair;		/**< The array of edge pairs */
		zExtColorArray eColors; /**< The array of edge colors */
		~zExtGraph();
		zExtGraph();
		zExtGraph(zObjGraph* g);
		zStatusCode checkMemAlloc(bool allocateMemory = true);
		/*! \brief update the attributes of the ExtGraph object.
		* \return void
		*/
		void updateAttributes();
		zIntArray getGraphSequence();
	};
	struct ZSPACE_EXTERNAL zExtGraphArray
	{
		zObjGraphArray* pointer = nullptr;
		~zExtGraphArray();
		int arrayCount;
		zStatusCode checkMemAlloc(bool allocateMemory = true);
		void updateAttributes();
	};
	struct ZSPACE_EXTERNAL zExtGraphPointerArray
	{
		zObjGraphPointerArray* pointer = nullptr;
		~zExtGraphPointerArray();
		int arrayCount;
		int checkMemAlloc(bool allocateMemory = true);
		void updateAttributes();
	};

	ZSPACE_EXTERNAL_C
	{

		//ZSPACE_EXTERNAL void ext_graph_getGraphData(zExtGraph extGraph, zext vPositions, float* vColors, int* ePairs, float* eColors);

		/*! \brief get the graph data from an ExtGraph object.
		* \param[in, out] extGraph The input zExtGraph object.
		* \param[in] vPositions The output array of vertex positions.
		* \param[in] vColors The output array of vertex colors.
		* \param[in] ePairs The output array of edge pairs.
		* \param[in] eColors The output array of edge colors.
		* \return void
		*/

		ZSPACE_EXTERNAL void ext_graph_getGraphData(zExtGraph extGraph, float* vPositions, float* vColors, int* ePairs, float* eColors);

		ZSPACE_EXTERNAL void ext_graph_getGraphSequence(zExtGraph extGraph, int* outSequence);

		/*! brief get array of ExtGraph objects from zextGraphPointerArray object.
		* \param[in] graphSet The input zExtGraphPointerArray object.
		* \param[in, out] outGraphArray The output array of zExtGraph objects.
		* \return void
		*/
		ZSPACE_EXTERNAL void ext_graph_getGraphsFromGraphPointerArray(zExtGraphPointerArray graphSet, zExtGraph* outGraphArray);


		/*! \brief Creates a new ExtGraph object from a file path.
		* \param[in]		filePath		- The path of the file to be read.
		* \param[in, out]	outGraph		- The output zExtGraph object.
		* \return 1 if the file was read successfully, 0 if the file was not read successfully.
		*/

		ZSPACE_EXTERNAL int ext_graph_from(char* filePath, zExtGraph& outGraph);

		/*! \brief Creates a new ExtGraph object from a JSON object.
		* \param[in] json The input zExtJSON object.
		* \param[in, out] outGraph The output zExtGraph object.
		* \return 1 if the file was read successfully, 0 if the file was not read successfully.
		*/

		ZSPACE_EXTERNAL int ext_graph_fromJSON(zExtJSON& json, zExtGraph& outGraph);

		/*! \brief Export zExtGraph
		* \param[in] extGraph The input zExtGraph object.
		* \param[in] filePath The path of the file to be written.
		* \return 1 if the file was written successfully, 0 if the file was not written successfully.
		*/
		ZSPACE_EXTERNAL int ext_graph_to(zExtGraph& extGraph, char* filePath);


		/*! \brief Export zExtGraph to JSON format
				* \param[in] extGraph The input zExtGraph object.
				* \param[in] json The output zExtJSON object.
				* \return 1 if the file was written successfully, 0 if the file was not written successfully.
				*/
		ZSPACE_EXTERNAL int ext_graph_toJSON(zExtGraph& extGraph, zExtJSON& json);

#if defined(ZSPACE_USD_INTEROP)  
		/*! \brief Creates a new zExtMesh object from a JSON object.
		* \param[in] json The input zExtJSON object.
		* \param[in, out] outMesh The output zExtMesh object.
		* \return 1 if the file was read successfully, 0 if the file was not read successfully.
		*/
		ZSPACE_EXTERNAL int ext_graph_fromUSD(zExtUSD& extUsd, zExtGraph& outGraph);

		/*! \brief Export zExtMesh to JSON format
				* \param[in] extGraph The input zExtMesh object.
				* \param[in] json The output zExtJSON object.
				* \return 1 if the file was written successfully, 0 if the file was not written successfully.
				*/
		ZSPACE_EXTERNAL int ext_graph_toUSD(zExtGraph& extGraph, zExtUSD& extUsd);
#endif


		ZSPACE_EXTERNAL int ext_graph_createOBJFromArray(zExtPointArray& _vertexPositions, zExtIntArray& _polyCounts, zExtIntArray& _polyConnects, zExtGraph& out_mesh);

		/*! \brief Export zExtGraph to JSON format
		* \param[in] extGraph The input zExtGraph object.
		* \param[in] json The output zExtJSON object.
		* \return 1 if the file was written successfully, 0 if the file was not written successfully.
		*/

		ZSPACE_EXTERNAL int ext_graph_updateGraph(zExtGraph& extGraph);


				////Graph Data
						//ZSPACE_EXTERNAL void ext_graph_getGraphsSetFromPointersVector2(zObjGraphPointerArray* graphs, zObjGraph** outGraphArray);
						//ZSPACE_EXTERNAL void ext_graph_getGraphsSetFromVector2(zObjGraphArray* graphs, zObjGraph** outGraphArray);
						//ZSPACE_EXTERNAL void ext_graph_getGraphCounts2(zObjGraph* graph, int& outvCount, int& outeCount);
						//ZSPACE_EXTERNAL void ext_graph_getGraphData2(zObjGraph* graph, float* outVPostions, float* outvColors, int* outePair, float* outeColors);


		/*! \brief Set colors of mesh vertices.
		 *  \param [in]		inObject						-Mesh to duplicate
		 *  \param [out]	outObject						-Duplicated mesh
		 */
		ZSPACE_EXTERNAL zStatusCode ext_graph_duplicate(zExtGraph& inObject, zExtGraph& outObject);

	}

}




#if defined(ZSPACE_EXTERNAL_STATIC_LIBRARY)  || defined(ZSPACE_EXTERNAL_DYNAMIC_LIBRARY)
// All defined OK so do nothing
#else
#include<source/zCore/zExtGraph.cpp>
#endif

#endif