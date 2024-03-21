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

#ifndef ZSPACE_EXT_CORE_COLOR_H
#define ZSPACE_EXT_CORE_COLOR_H



#pragma once



#include <headers/zCore/base/zExtern.h>
#include "headers/base/zStatus.h"

#include <headers/zInterface/functionsets/zFnMesh.h>
#include <headers/zInterface/functionsets/zFnGraph.h>

#include "headers/base/zSpace_External.h"

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

/*! \struct zExtColor
*	\brief An external struct for zColor .
*	\since version 0.0.1
*/

/** @}*/

/** @}*/

/** @}*/
	//struct zExtColor
	//{
	//	//zColor* pointer = nullptr;
	//	float r; ///< red component
	//	float g; ///< green component
	//	float b; ///< blue component
	//	float a; ///< alpha component


	//	zExtColor();
	//	zExtColor(zColor* t);
	//	zExtColor(zColor t);
	//	zExtColor(float R, float G, float B, float A);

	//	void updateAttributes(zColor* t);
	//	void updateAttributes(zColor t);
	//	void updateAttributes(float R, float G, float B, float A );
	//};

	typedef zColor zExtColor;

	struct ZSPACE_EXTERNAL zExtColorArray
	{
		zColorArray* pointer = nullptr; /**< A pointer to the array object */
		int arrayCount; /**< The number of items in the array */
		zExtColorArray();
		zExtColorArray(zColorArray* a);
		~zExtColorArray();

		zStatusCode checkMemAlloc(bool allocateMemory = true);
		/**
		 * \brief Updates the attributes of the external object
		 */
		void updateAttributes();
		/**
		 * \brief get items from array
		 */
		void getItems(zExtColor* items);
		void setItems(zExtColor* items, int count);
	};



	ZSPACE_EXTERNAL_C
	{
		ZSPACE_EXTERNAL void ext_color_createRGB(float r, float g, float b, float a, zExtColor& refPoint);
		ZSPACE_EXTERNAL void ext_color_array_getItems(zExtColorArray& extArray, zExtColor* outArray);
		ZSPACE_EXTERNAL void ext_color_setItemsFromArray(zExtColorArray& extArray, zExtColor* inArray, int count);
		ZSPACE_EXTERNAL int ext_color_computeHSV(zExtColor& extColor);
		ZSPACE_EXTERNAL int ext_color_computeRGB(zExtColor& extColor);
	}

}




#if defined(ZSPACE_EXTERNAL_STATIC_LIBRARY)  || defined(ZSPACE_EXTERNAL_DYNAMIC_LIBRARY)
// All defined OK so do nothing
#else
#include<source/zCore/Base/zExtColor.cpp>
#endif

#endif