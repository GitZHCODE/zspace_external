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


#include "headers/zCore/Base/zExtPoint.h"


namespace zSpace
{
	///*ZSPACE_EXTERNAL_INLINE zExtPoint::zExtPoint(zPoint* t)
	//{
	//	pointer = t;
	//	updateAttributes(t);
	//}*/
	//ZSPACE_EXTERNAL_INLINE zExtPoint::zExtPoint()
	//{
	//	//delete pointer; 
	//	//pointer = new zPoint();
	//	x = 0;
	//	y = 0;
	//	z = 0;
	//	//updateAttributes();
	//}

	///*ZSPACE_EXTERNAL_INLINE void zExtPoint::updateAttributes(zPoint* t)
	//{
	//	pointer = t;
	//	updateAttributes();	
	//}*/
	///*ZSPACE_EXTERNAL_INLINE void zExtPoint::updateAttributes()
	//{
	//	x = pointer->x;
	//	y = pointer->y;
	//	z = pointer->z;
	//}*/

	


	/*ZSPACE_EXTERNAL void ext_point_create(float x, float y, float z, zExtPoint& refPoint)
	{
		refPoint = new zPoint(x, y, z);
		refPoint.updateAttributes();
	}*/


	ZSPACE_EXTERNAL_INLINE zExtPointArray::zExtPointArray(zPointArray* a)
	{
		pointer = a;
		updateAttributes();
	}
	ZSPACE_EXTERNAL_INLINE zExtPointArray::zExtPointArray()
	{
		//delete pointer; 
 pointer = new zPointArray;
	}
	ZSPACE_EXTERNAL_INLINE zExtPointArray::~zExtPointArray()
	{
		delete pointer;
		pointer = nullptr;
	}
	ZSPACE_EXTERNAL_INLINE int zExtPointArray::checkMemAlloc(bool allocateMemory)
	{
		try
		{
			if (pointer != nullptr) return 1;
			else
			{
				if (!allocateMemory) return 0;
				pointer = new zPointArray();
				return 2;

			}
		}
		catch (const std::exception&)
		{
			printf("\n Pointer initialization failed");
			return 404;
		}
	}
	ZSPACE_EXTERNAL_INLINE void zExtPointArray::updateAttributes()
	{
		arrayCount = pointer->size();
	}
	ZSPACE_EXTERNAL_INLINE void zExtPointArray::getItems(zExtPoint* items)
	{
		for (int i = 0; i < pointer->size(); i++)
		{
			//items[i].updateAttributes(pointer->at(i));
			items[i] = zExtPoint((pointer->at(i)));
		}
	}
	ZSPACE_EXTERNAL_INLINE void zExtPointArray::setItems(zExtPoint* items, int count)
	{
		checkMemAlloc();
		pointer->clear();
		for (int i = 0; i < count; i++)
		{
			zPoint p(items[i].x, items[i].y, items[i].z);
			pointer->push_back(p);
		}
		updateAttributes();
		printf("\n zExtPointArray setItems %i %i", count, arrayCount);
	}
	//ZSPACE_EXTERNAL_INLINE int ext_point_create(float x, float y, float z, zExtPoint& refPoint)
	//{
	//	try
	//	{
	//		//refPoint
	//		return 1;

	//	}
	//	catch (const std::exception&)
	//	{
	//		return 0;
	//	}
	//}
	ZSPACE_EXTERNAL_INLINE void ext_point_array_getItems(zExtPointArray& extArray, zExtPoint* outArray)
	{
		extArray.getItems(outArray);
	}


	//ZSPACE_EXTERNAL_INLINE zExtPoint::zExtPoint(float X, float Y, float Z)
	//{
	//	x = X;
	//	y = Y;
	//	z = Z;
	//}

	//ZSPACE_EXTERNAL_INLINE zExtPoint::zExtPoint(zPoint t)
	//{
	//	x = t.x;
	//	y = t.y;
	//	z = t.z;
	//}

	//ZSPACE_EXTERNAL_INLINE void zExtPoint::updateAttributes(float X, float Y, float Z)
	//{
	//	x = X;
	//	y = Y;
	//	z = Z;
	//}

	//ZSPACE_EXTERNAL_INLINE void zExtPoint::updateAttributes(zPoint t)
	//{
	//	x = t.x;
	//	y = t.y;
	//	z = t.z;
	//}
	ZSPACE_EXTERNAL_INLINE int ext_point_setItemsFromArray(zExtPointArray& extArray, zExtPoint* inArray, int count)
	{
		try
		{
			extArray.setItems(inArray, count);
			return 1;
		}
		catch (const std::exception&)
		{
			printf("\n ERROR set zExtPointArray");
			return 0;
		}
	}
	ZSPACE_EXTERNAL_INLINE void ext_point_testAdd(zPoint& point1, zPoint& point2)
	{
		printf("\n point.x = %f", point1.x);
		printf("\n point.x = %f", point2.x);

		zPoint point = point1 + point2;
		printf("\n point.x = %f", point.x);
	}
	ZSPACE_EXTERNAL_INLINE zExtPointArray2D::zExtPointArray2D(vector<zPointArray> a)
	{
		
		pointer = new vector<zPointArray>(a);
		updateAttributes();
	}
	ZSPACE_EXTERNAL_INLINE zExtPointArray2D::zExtPointArray2D(vector<zPointArray>* a)
	{
		pointer = a;
		updateAttributes();
	}
	ZSPACE_EXTERNAL_INLINE zExtPointArray2D::~zExtPointArray2D()
	{
		delete pointer;
		pointer = nullptr;
	}
	ZSPACE_EXTERNAL_INLINE void zExtPointArray2D::updateAttributes()
	{
		arrayCount = pointer->size();

	}

	ZSPACE_EXTERNAL_INLINE int zExtPointArray2D::checkMemAlloc(bool allocateMemory)
	{
		try
		{
			if (pointer != nullptr) return 1;
			else
			{
				if (!allocateMemory) return 0;
				pointer = new vector<zPointArray>();
				return 2;

			}
		}
		catch (const std::exception&)
		{
			printf("\n Pointer initialization failed");
			return 404;
		}
	}

	ZSPACE_EXTERNAL_INLINE void zExtPointArray2D::getItems(zExtPointArray* items)
	{
		for (int i = 0; i < pointer->size(); i++)
		{
			items[i].pointer = &pointer->at(i);
			items[i].updateAttributes();
		}
	}
	ZSPACE_EXTERNAL_INLINE void zExtPointArray2D::setItems(zExtPointArray* items, int count)
	{	
		checkMemAlloc();
		for (int i = 0; i < count; i++)
		{
			pointer->push_back(*(items[i].pointer));
		}
		updateAttributes();
	}
}