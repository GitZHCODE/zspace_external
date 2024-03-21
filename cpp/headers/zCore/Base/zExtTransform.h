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

#ifndef ZSPACE_EXT_CORE_TRANSFORM_H
#define ZSPACE_EXT_CORE_TRANSFORM_H



#pragma once

#include <headers/zInterface/functionsets/zFnGraph.h>


#include "headers/base/zSpace_External.h"
#include "headers/base/zStatus.h"



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
	struct ZSPACE_EXTERNAL zExtTransform
	{
		zTransform* pointer = nullptr;
		float row0[4];
		float row1[4];
		float row2[4];
		float row3[4];
		//float matrix[4][4];

		zExtTransform();
		zExtTransform(zTransform* t, bool transpose = false);
		zExtTransform(zTransform t);
		~zExtTransform();
		zStatusCode checkMemAlloc(bool allocateMemory = true);
		int initPointer(zTransform t);

		void updateAttributes(zTransform* transform, bool transpose = false);
		void updateAttributes(bool transpose = false);
	};

	/** \addtogroup zExternal
	*	\brief Collection of external structs and methods for applications.
	*  @{
	*/

	/** \addtogroup zCore
	*	\brief external structs and methods for zCore.
	*  @{
	*/

	/*! \struct zExtGraphArray
	*	\brief An external struct for zObjGraphArray.
	*	\since version 0.0.1
	*/

	/** @}*/

	/** @}*/

	/** @}*/
	struct ZSPACE_EXTERNAL zExtTransformArray
	{
		vector<zTransform>* pointer = nullptr; /**< A pointer to the graph array object */
		int arrayCount; /**< The number of graphs in the array */


		zStatusCode checkMemAlloc(bool allocateMemory = true);
		~zExtTransformArray();
		/**
		 * \brief Updates the attributes of the zExtGraphArray object
		 */

		void updateAttributes();

		void getItems(zExtTransform* items);
		void setItems(zExtTransform* items, int count);
	};

	ZSPACE_EXTERNAL_C
	{
	ZSPACE_EXTERNAL void ext_transform_createNewFromArray(float* array, zExtTransform & outTransform);

	/*! \brief Creates a new zExtTransform with zero.
	 *  \param [in,out] outTransform					-Reference to the zExtTransform object to be created.
	 */
	ZSPACE_EXTERNAL void ext_transform_initPointer(zExtTransform& outTransform);

	/*! \brief Creates a new zExtTransform from a float array.
	 *  \param [in]		array							-float array of size 16 to create the zExTransform.
	 *  \param [in,out] outTransform					-Reference to the zExtTransform object to be created.
	 */
	ZSPACE_EXTERNAL void ext_transform_createNewFromArray(float* array, zExtTransform& outTransform);
	/*! \brief Update a zExtTransform.
	 *  \param [in,out] transform						-Reference to the zExtTransform object to update.
	 *  \param [in]		array							-float array of size 16 to update the zExTransform.
	 */
	ZSPACE_EXTERNAL void ext_transform_updateFromValues(zExtTransform& transform, float* array);
	/*! \brief Get array of transform from transformArray/vector<zTransform>
	 *  \param [in,out] transform						-Reference to the zExtTransformArray object to update.
	 *  \param [in]		array							-an array of zExtTranform.
	 */
	ZSPACE_EXTERNAL int ext_transform_array_getItems(zExtTransformArray inArray, zExtTransform* outTranfroms);

	ZSPACE_EXTERNAL int ext_transform_setItemsFromArray(zExtTransformArray inArray, zExtTransform* inTranfroms, int count);


	}



}




#if defined(ZSPACE_EXTERNAL_STATIC_LIBRARY)  || defined(ZSPACE_EXTERNAL_DYNAMIC_LIBRARY)
// All defined OK so do nothing
#else
#include<source/zCore/Base/zExtTransform.cpp>
#endif

#endif