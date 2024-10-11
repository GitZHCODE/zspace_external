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

#ifndef ZSPACE_EXT_UTILS_CORE_H
#define ZSPACE_EXT_UTILS_CORE_H



#pragma once


#include <headers/zCore/zCore.h>
#include <headers/zCore/utilities/zUtilsCore.h>



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
	struct ZSPACE_EXTERNAL zExtIntArray
	{
		zIntArray* pointer = nullptr; /**< A pointer to the array object */
		int arrayCount; /**< The number of items in the array */
		zExtIntArray();
		zExtIntArray(zIntArray a);
		zExtIntArray(zIntArray* a);
		~zExtIntArray();
		/**
		 * \brief Updates the attributes of the external object
		 */
		zStatusCode checkMemAlloc(bool allocateMemory = true);
		void updateAttributes();
		/**
		 * \brief get items from array
		 */
		void getItems(int* items);
		void setItems(int* items, int count);
	};

	struct ZSPACE_EXTERNAL zExtIntArray2D
	{
		zInt2DArray* pointer = nullptr; /**< A pointer to the array object */
		int arrayCount; /**< The number of items in the array */
		zExtIntArray2D();
		zExtIntArray2D(zInt2DArray a);
		zExtIntArray2D(zInt2DArray* a);
		~zExtIntArray2D();

		zStatusCode checkMemAlloc(bool allocateMemory = true);

		/**
		 * \brief Updates the attributes of the external object
		 */
		void updateAttributes();
		/**
		 * \brief get items from array
		 */
		void getItems(zExtIntArray* items);
		void setItems(zExtIntArray* items, int count);
	};
	struct ZSPACE_EXTERNAL zExtFloatArray
	{
		zFloatArray* pointer = nullptr; /**< A pointer to the array object */
		int arrayCount; /**< The number of items in the array */
		zExtFloatArray();
		zExtFloatArray(zFloatArray a);
		zExtFloatArray(zFloatArray* a);
		~zExtFloatArray();
		/**
		 * \brief Updates the attributes of the external object
		 */
		zStatusCode checkMemAlloc(bool allocateMemory = true);
		void updateAttributes();
		/**
		 * \brief get items from array
		 */
		void getItems(float* items);
		void setItems(float* items, int count);
	};

	struct ZSPACE_EXTERNAL zExtFloatArray2D
	{
		vector<zFloatArray>* pointer = nullptr; /**< A pointer to the array object */
		int arrayCount; /**< The number of items in the array */
		zExtFloatArray2D();
		zExtFloatArray2D(vector<zFloatArray> a);
		zExtFloatArray2D(vector<zFloatArray>* a);
		~zExtFloatArray2D();


		/**
		 * \brief Updates the attributes of the external object
		 */
		void updateAttributes();
		zStatusCode checkMemAlloc(bool allocateMemory = true);
		/**
		 * \brief get items from array
		 */
		void getItems(zExtFloatArray* items);
		void setItems(zExtFloatArray* items, int count);
	};

	struct ZSPACE_EXTERNAL zExtDoubleArray
	{
		zDoubleArray* pointer = nullptr; /**< A pointer to the array object */
		int arrayCount; /**< The number of items in the array */
		zExtDoubleArray();
		//zExtDoubleArray(const zExtDoubleArray& a);
		//zExtDoubleArray( zExtDoubleArray&& a);
		zExtDoubleArray(zDoubleArray& a);
		zExtDoubleArray(zDoubleArray* a);
		~zExtDoubleArray();
		/**
		 * \brief Updates the attributes of the external object
		 */
		void updateAttributes();
		zStatusCode checkMemAlloc(bool allocateMemory = true);
		/**
		 * \brief get items from array
		 */
		void getItems(double* items);
		void setItems(double* items, int count);
		void setItems(zDoubleArray& a);
	};

	struct ZSPACE_EXTERNAL zExtDoubleArray2D
	{
		vector<zDoubleArray>* pointer = nullptr; /**< A pointer to the array object */
		int arrayCount; /**< The number of items in the array */
		zExtDoubleArray2D();
		zExtDoubleArray2D(vector<zDoubleArray> a);
		zExtDoubleArray2D(vector<zDoubleArray>* a);
		~zExtDoubleArray2D();

		/**
		 * \brief Updates the attributes of the external object
		 */
		void updateAttributes();
		zStatusCode checkMemAlloc(bool allocateMemory = true);
		/**
		 * \brief get items from array
		 */
		void getItems(zExtDoubleArray* items);
		void setItems(zExtDoubleArray* items, int count);
	};
	struct ZSPACE_EXTERNAL zExtString
	{
		string* pointer = nullptr; /**< A pointer to the array object */
		int stringLength; /**< The number of items in the array */
		~zExtString();
		/**
		 * \brief Updates the attributes of the external object
		 */
		void updateAttributes();
		zStatusCode checkMemAlloc(bool allocateMemory = true);

		///**
		// * \brief Gets items from the array
		// */
		void getCharecters(char* outString);
		void setItems(char* items, int count);
	};

	struct ZSPACE_EXTERNAL zExtStringArray
	{
		//zStringArray* pointer = nullptr; /**< A pointer to the array object */
		vector<string>* pointer = nullptr; /**< A pointer to the array object */
		int arrayCount; /**< The number of items in the array */

		zExtStringArray();
		//zExtStringArray(zStringArray a);
		zExtStringArray(vector<string> a);
		zExtStringArray(vector<string>* a);
		~zExtStringArray();

		/**
		 * \brief Updates the attributes of the external object
		 */
		void updateAttributes();
		zStatusCode checkMemAlloc(bool allocateMemory = true);

		/**
		 * \brief Gets items from the array
		 */
		void getItems(string* items);
		void setItems(string* items, int count);
	};

	struct ZSPACE_EXTERNAL zExtStringArray2D
	{
		vector<zStringArray>* pointer = nullptr; /**< A pointer to the array object */
		int arrayCount; /**< The number of items in the array */

		zExtStringArray2D();
		zExtStringArray2D(vector<zStringArray> a);
		zExtStringArray2D(vector<zStringArray>* a);
		~zExtStringArray2D();

		/**
		 * \brief Updates the attributes of the external object
		 */
		void updateAttributes();
		zStatusCode checkMemAlloc(bool allocateMemory = true);

		/**
		 * \brief Gets items from the array
		 */
		void getItems(zExtStringArray* items);
		void setItems(zExtStringArray* items, int count);
	};	
	
	struct ZSPACE_EXTERNAL zExtBoolArray
	{
		zBoolArray* pointer = nullptr; /**< A pointer to the array object */
		int arrayCount; /**< The number of items in the array */

		zExtBoolArray();
		zExtBoolArray(zBoolArray a);
		zExtBoolArray(zBoolArray* a);
		~zExtBoolArray();

		/**
		 * \brief Updates the attributes of the external object
		 */
		void updateAttributes();
		zStatusCode checkMemAlloc(bool allocateMemory = true);

		/**
		 * \brief Gets items from the array
		 */
		void getItems(bool* items);
		void setItems(bool* items, int count);
	};

	struct ZSPACE_EXTERNAL zExtBoolArray2D
	{
		vector<zBoolArray>* pointer = nullptr; /**< A pointer to the array object */
		int arrayCount; /**< The number of items in the array */

		zExtBoolArray2D();
		zExtBoolArray2D(vector<zBoolArray> a);
		zExtBoolArray2D(vector<zBoolArray>* a);
		~zExtBoolArray2D();

		/**
		 * \brief Updates the attributes of the external object
		 */
		void updateAttributes();
		zStatusCode checkMemAlloc(bool allocateMemory = true);

		/**
		 * \brief Gets items from the array
		 */
		void getItems(zExtBoolArray* items);
		void setItems(zExtBoolArray* items, int count);
	};

	ZSPACE_EXTERNAL_C
	{

		ZSPACE_EXTERNAL void ext_int_array_getItems(zExtIntArray & extArray, int* outArray);
		ZSPACE_EXTERNAL void ext_int_array_setItems(zExtIntArray& extArray, int* inArray, int count);
		ZSPACE_EXTERNAL void ext_int_array2D_getItems(zExtIntArray2D& extArray, zExtIntArray* outArray);
		ZSPACE_EXTERNAL void ext_int_array2D_setItems(zExtIntArray2D& extArray, zExtIntArray* inArray, int count);
		ZSPACE_EXTERNAL void ext_float_array_getItems(zExtFloatArray& extArray, float* outArray);
		ZSPACE_EXTERNAL void ext_float_setItemsFromArray(zExtFloatArray& extArray, float* inArray, int count);
		ZSPACE_EXTERNAL void ext_float_array2D_getItems(zExtFloatArray2D& extArray, zExtFloatArray* outArray);
		ZSPACE_EXTERNAL void ext_float_array2D_setItems(zExtFloatArray2D& extArray, zExtFloatArray* inArray, int count);
		ZSPACE_EXTERNAL void ext_double_array_getItems(zExtDoubleArray& extArray, double* outArray);
		ZSPACE_EXTERNAL void ext_double_setItemsFromArray(zExtDoubleArray& extArray, double* inArray, int count);
		ZSPACE_EXTERNAL void ext_double_array2D_getItems(zExtDoubleArray2D& extArray, zExtDoubleArray* outArray);
		ZSPACE_EXTERNAL void ext_double_array2D_setItems(zExtDoubleArray2D& extArray, zExtDoubleArray* inArray, int count);
		ZSPACE_EXTERNAL int ext_string_getCharArrayFromExtString(zExtString& extString, char* outString);
		ZSPACE_EXTERNAL int ext_string_setExtStringFromCharArray(zExtString& extString, char* inString, int count);
		ZSPACE_EXTERNAL void ext_string_array_getItems(zExtStringArray& extArray, zExtString* outArray);
		ZSPACE_EXTERNAL void ext_string_array_setItems(zExtStringArray& extArray, zExtString* inArray, int count);
		ZSPACE_EXTERNAL void ext_string_array2D_getItems(zExtStringArray2D& extArray, zExtStringArray* outArray);
		ZSPACE_EXTERNAL void ext_string_array2D_setItems(zExtStringArray2D& extArray, zExtStringArray* inArray, int count);
		ZSPACE_EXTERNAL void ext_bool_array_getItems(zExtBoolArray& extArray, bool* outArray);
		ZSPACE_EXTERNAL void ext_bool_setItemsFromArray(zExtBoolArray& extArray, bool* inArray, int count);
		ZSPACE_EXTERNAL void ext_bool_array2D_getItems(zExtBoolArray2D& extArray, zExtBoolArray* outArray);
		ZSPACE_EXTERNAL void ext_bool_array2D_setItems(zExtBoolArray2D& extArray, zExtBoolArray* inArray, int count);



	}



}




#if defined(ZSPACE_EXTERNAL_STATIC_LIBRARY)  || defined(ZSPACE_EXTERNAL_DYNAMIC_LIBRARY)
// All defined OK so do nothing
#else
#include<source/zCore/Utils/zExtUtilsCore.cpp>
#endif

#endif