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

#ifndef ZSPACE_EXT_CORE_POINT_H
#define ZSPACE_EXT_CORE_POINT_H



#pragma once

//#include <headers/zToolsets/geometry/zTsSDFSlicer.h>

#include <headers/base/zSpace_External.h>

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

/** \addtogroup zCore
*	\brief external structs and methods for zCore.
*  @{
*/

/*! \struct zExtTransform
*	\brief An external struct for zTransform .
*	\since version 0.0.1
*/

/** @}*/

/** @}*/

/** @}*/
	struct zExtPoint
	{
		//zPoint* pointer;
		float x;
		float y;
		float z;

		zExtPoint();
		zExtPoint(float X, float Y, float Z);
		zExtPoint(zPoint t);
		//zExtPoint(zPoint* t);

		//void updateAttributes(zPoint* t);
		//void updateAttributes();
		void updateAttributes(float X, float Y, float Z);
		void updateAttributes(zPoint t);
	};

	struct zExtPointArray
	{
		zPointArray* pointer; /**< A pointer to the array object */
		int arrayCount; /**< The number of items in the array */
		zExtPointArray();
		zExtPointArray(zPointArray* a);

		/**
		 * \brief Updates the attributes of the external object
		 */
		void updateAttributes();
		/**
		 * \brief get items from array
		 */
		void getItems(zExtPoint* items);
	};



	ZSPACE_EXTERNAL_C
	{
		//ZSPACE_EXTERNAL void ext_point_create(float x, float y, float z, zExtPoint& refPoint);
		ZSPACE_EXTERNAL void ext_point_getItemsFromArray(zExtPointArray & extArray, zExtPoint * outArray);
	}

}




#if defined(ZSPACE_EXTERNAL_STATIC_LIBRARY)  || defined(ZSPACE_EXTERNAL_DYNAMIC_LIBRARY)
// All defined OK so do nothing
#else
#include<source/zCore/zExtPoint.cpp>
#endif

#endif