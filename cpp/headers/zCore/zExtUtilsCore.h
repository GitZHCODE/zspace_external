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


#include <headers/base/zSpace_External.h>

#include <headers/zCore/zCore.h>
#include <headers/zCore/utilities/zUtilsCore.h>


#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>

#include<execution>

using namespace std;

namespace zSpace
{
	struct zExtIntArray
	{
		zIntArray* pointer; /**< A pointer to the array object */
		int arrayCount; /**< The number of items in the array */
		zExtIntArray();
		zExtIntArray(zIntArray a);
		zExtIntArray(zIntArray* a);
		/**
		 * \brief Updates the attributes of the external object
		 */
		void updateAttributes();
		/**
		 * \brief get items from array
		 */
		void getItems(int* items);
		void setItems(int* items, int count);
	};

	struct zExtIntArray2D
	{
		zInt2DArray* pointer; /**< A pointer to the array object */
		int arrayCount; /**< The number of items in the array */
		zExtIntArray2D();
		zExtIntArray2D(zInt2DArray a);
		zExtIntArray2D(zInt2DArray* a);

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
	struct zExtFloatArray
	{
		zFloatArray* pointer; /**< A pointer to the array object */
		int arrayCount; /**< The number of items in the array */
		zExtFloatArray();
		zExtFloatArray(zFloatArray a);
		zExtFloatArray(zFloatArray* a);
		/**
		 * \brief Updates the attributes of the external object
		 */
		void updateAttributes();
		/**
		 * \brief get items from array
		 */
		void getItems(float* items);
		void setItems(float* items, int count);
	};

	struct zExtFloatArray2D
	{
		vector<zFloatArray>* pointer; /**< A pointer to the array object */
		int arrayCount; /**< The number of items in the array */
		zExtFloatArray2D();
		zExtFloatArray2D(vector<zFloatArray> a);
		zExtFloatArray2D(vector<zFloatArray>* a);

		/**
		 * \brief Updates the attributes of the external object
		 */
		void updateAttributes();
		/**
		 * \brief get items from array
		 */
		void getItems(zExtFloatArray* items);
		void setItems(zExtFloatArray* items, int count);
	};

	struct zExtDoubleArray
	{
		zDoubleArray* pointer; /**< A pointer to the array object */
		int arrayCount; /**< The number of items in the array */
		zExtDoubleArray();
		zExtDoubleArray(zDoubleArray a);
		zExtDoubleArray(zDoubleArray* a);
		/**
		 * \brief Updates the attributes of the external object
		 */
		void updateAttributes();
		/**
		 * \brief get items from array
		 */
		void getItems(double* items);
		void setItems(double* items, int count);
	};

	struct zExtDoubleArray2D
	{
		vector<zDoubleArray>* pointer; /**< A pointer to the array object */
		int arrayCount; /**< The number of items in the array */
		zExtDoubleArray2D();
		zExtDoubleArray2D(vector<zDoubleArray> a);
		zExtDoubleArray2D(vector<zDoubleArray>* a);

		/**
		 * \brief Updates the attributes of the external object
		 */
		void updateAttributes();
		/**
		 * \brief get items from array
		 */
		void getItems(zExtDoubleArray* items);
		void setItems(zExtDoubleArray* items, int count);
	};
	struct zExtString
	{
		string* pointer; /**< A pointer to the array object */
		int stringLength; /**< The number of items in the array */
		//zExtString(string s);
		/**
		 * \brief Updates the attributes of the external object
		 */
		void updateAttributes();

		///**
		// * \brief Gets items from the array
		// */
		void getCharecters(char* outString);
		void setItems(char* items, int count);
	};

	struct zExtStringArray
	{
		zStringArray* pointer; /**< A pointer to the array object */
		int arrayCount; /**< The number of items in the array */

		zExtStringArray();
		zExtStringArray(zStringArray a);
		zExtStringArray(zStringArray* a);

		/**
		 * \brief Updates the attributes of the external object
		 */
		void updateAttributes();

		/**
		 * \brief Gets items from the array
		 */
		void getItems(string* items);
		void setItems(string* items, int count);
	};

	struct zExtStringArray2D
	{
		vector<zStringArray>* pointer; /**< A pointer to the array object */
		int arrayCount; /**< The number of items in the array */

		zExtStringArray2D();
		zExtStringArray2D(vector<zStringArray> a);
		zExtStringArray2D(vector<zStringArray>* a);

		/**
		 * \brief Updates the attributes of the external object
		 */
		void updateAttributes();

		/**
		 * \brief Gets items from the array
		 */
		void getItems(zExtStringArray* items);
		void setItems(zExtStringArray* items, int count);
	};	
	
	struct zExtBoolArray
	{
		zBoolArray* pointer; /**< A pointer to the array object */
		int arrayCount; /**< The number of items in the array */

		zExtBoolArray();
		zExtBoolArray(zBoolArray a);
		zExtBoolArray(zBoolArray* a);

		/**
		 * \brief Updates the attributes of the external object
		 */
		void updateAttributes();

		/**
		 * \brief Gets items from the array
		 */
		void getItems(bool* items);
		void setItems(bool* items, int count);
	};

	struct zExtBoolArray2D
	{
		vector<zBoolArray>* pointer; /**< A pointer to the array object */
		int arrayCount; /**< The number of items in the array */

		zExtBoolArray2D();
		zExtBoolArray2D(vector<zBoolArray> a);
		zExtBoolArray2D(vector<zBoolArray>* a);

		/**
		 * \brief Updates the attributes of the external object
		 */
		void updateAttributes();

		/**
		 * \brief Gets items from the array
		 */
		void getItems(zExtBoolArray* items);
		void setItems(zExtBoolArray* items, int count);
	};

	ZSPACE_EXTERNAL_C
	{

		ZSPACE_EXTERNAL void ext_int_getItemsFromArray(zExtIntArray & extArray, int* outArray);
		ZSPACE_EXTERNAL void ext_int_setItemsFromArray(zExtIntArray& extArray, int* inArray, int count);
		ZSPACE_EXTERNAL void ext_int_getItemsFromArray2D(zExtIntArray2D& extArray, zExtIntArray* outArray);
		ZSPACE_EXTERNAL void ext_int_setItemsFromArray2D(zExtIntArray2D& extArray, zExtIntArray* inArray, int count);
		ZSPACE_EXTERNAL void ext_float_getItemsFromArray(zExtFloatArray& extArray, float* outArray);
		ZSPACE_EXTERNAL void ext_float_setItemsFromArray(zExtFloatArray& extArray, float* inArray, int count);
		ZSPACE_EXTERNAL void ext_float_getItemsFromArray2D(zExtFloatArray2D& extArray, zExtFloatArray* outArray);
		ZSPACE_EXTERNAL void ext_float_setItemsFromArray2D(zExtFloatArray2D& extArray, zExtFloatArray* inArray, int count);
		ZSPACE_EXTERNAL void ext_double_getItemsFromArray(zExtDoubleArray& extArray, double* outArray);
		ZSPACE_EXTERNAL void ext_double_setItemsFromArray(zExtDoubleArray& extArray, double* inArray, int count);
		ZSPACE_EXTERNAL void ext_double_getItemsFromArray2D(zExtDoubleArray2D& extArray, zExtDoubleArray* outArray);
		ZSPACE_EXTERNAL void ext_double_setItemsFromArray2D(zExtDoubleArray2D& extArray, zExtDoubleArray* inArray, int count);
		ZSPACE_EXTERNAL int ext_string_getCharArrayFromExtString(zExtString& extString, char* outString);
		ZSPACE_EXTERNAL int ext_string_setExtStringFromCharArray(zExtString& extString, char* inString, int count);
		ZSPACE_EXTERNAL void ext_string_getItemsFromArray(zExtStringArray& extArray, zExtString* outArray);
		ZSPACE_EXTERNAL void ext_string_setItemsFromArray(zExtStringArray& extArray, zExtString* inArray, int count);
		ZSPACE_EXTERNAL void ext_string_getItemsFromArray2D(zExtStringArray2D& extArray, zExtStringArray* outArray);
		ZSPACE_EXTERNAL void ext_string_setItemsFromArray2D(zExtStringArray2D& extArray, zExtStringArray* inArray, int count);
		ZSPACE_EXTERNAL void ext_bool_getItemsFromArray(zExtBoolArray& extArray, bool* outArray);
		ZSPACE_EXTERNAL void ext_bool_setItemsFromArray(zExtBoolArray& extArray, bool* inArray, int count);
		ZSPACE_EXTERNAL void ext_bool_getItemsFromArray2D(zExtBoolArray2D& extArray, zExtBoolArray* outArray);
		ZSPACE_EXTERNAL void ext_bool_setItemsFromArray2D(zExtBoolArray2D& extArray, zExtBoolArray* inArray, int count);



	}



}




#if defined(ZSPACE_EXTERNAL_STATIC_LIBRARY)  || defined(ZSPACE_EXTERNAL_DYNAMIC_LIBRARY)
// All defined OK so do nothing
#else
#include<source/zCore/zExtUtilsCore.cpp>
#endif

#endif