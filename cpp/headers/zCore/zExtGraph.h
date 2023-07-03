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

//#include <headers/zToolsets/geometry/zTsSDFSlicer.h>

#include <headers/base/zSpace_External.h>
#include <headers/zCore/zExtPoint.h>
#include <headers/zCore/zExtColor.h>
#include <headers/zCore/zExtUtilsCore.h>

#include <headers/zCore/base/zExtern.h>
#include <headers/zInterface/functionsets/zFnMesh.h>
#include <headers/zInterface/functionsets/zFnGraph.h>

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>

#include<execution>

using namespace std;

namespace zSpace
{
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
	struct zExtGraph
	{
		zObjGraph* graph;
		int vCount;
		int eCount;
		zExtPointArray vPositions;
		zExtColorArray vColors;
		zExtIntArray ePair;
		zExtColorArray eColors;

		zExtGraph(zObjGraph* g);
		void updateAttributes();
		zIntArray getGraphSequence();
	};
	struct zExtGraphArray
	{
		zObjGraphArray* graphArray;
		int graphsCount;
		void updateAttributes();
	};
	struct zExtGraphPointerArray
	{
		zObjGraphPointerArray* graphPArray;
		int graphsCount;
		void updateAttributes();
	};
	
	ZSPACE_EXTERNAL_C
	{

		//ZSPACE_EXTERNAL void ext_graph_getGraphData(zExtGraph extGraph, zext vPositions, float* vColors, int* ePairs, float* eColors);

		ZSPACE_EXTERNAL void ext_graphUtil_getGraphData(zExtGraph extGraph, float* vPositions, float* vColors, int* ePairs, float* eColors);
		ZSPACE_EXTERNAL void ext_graphUtil_getGraphSequence(zExtGraph extGraph, int* outSequence);
		ZSPACE_EXTERNAL void ext_graphUtil_getGraphsFromGraphPointerArray(zExtGraphPointerArray graphSet, zExtGraph* outGraphArray);

		////Graph Data
		//ZSPACE_EXTERNAL void ext_graphUtil_getGraphsSetFromPointersVector2(zObjGraphPointerArray* graphs, zObjGraph** outGraphArray);
		//ZSPACE_EXTERNAL void ext_graphUtil_getGraphsSetFromVector2(zObjGraphArray* graphs, zObjGraph** outGraphArray);
		//ZSPACE_EXTERNAL void ext_graphUtil_getGraphCounts2(zObjGraph* graph, int& outvCount, int& outeCount);
		//ZSPACE_EXTERNAL void ext_graphUtil_getGraphData2(zObjGraph* graph, float* outVPostions, float* outvColors, int* outePair, float* outeColors);

		
	}

}




#if defined(ZSPACE_EXTERNAL_STATIC_LIBRARY)  || defined(ZSPACE_EXTERNAL_DYNAMIC_LIBRARY)
// All defined OK so do nothing
#else
#include<source/zCore/zExtGraph.cpp>
#endif

#endif