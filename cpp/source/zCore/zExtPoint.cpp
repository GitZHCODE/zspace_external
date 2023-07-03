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


#include<headers/zCore/zExtPoint.h>


namespace zSpace
{
	/*ZSPACE_EXTERNAL_INLINE zExtPoint::zExtPoint(zPoint* t)
	{
		pointer = t;
		updateAttributes(t);
	}*/
	ZSPACE_EXTERNAL_INLINE zExtPoint::zExtPoint()
	{
		//delete pointer; 
		//pointer = new zPoint();
		x = 0;
		y = 0;
		z = 0;
		//updateAttributes();
	}

	/*ZSPACE_EXTERNAL_INLINE void zExtPoint::updateAttributes(zPoint* t)
	{
		pointer = t;
		updateAttributes();	
	}*/
	/*ZSPACE_EXTERNAL_INLINE void zExtPoint::updateAttributes()
	{
		x = pointer->x;
		y = pointer->y;
		z = pointer->z;
	}*/

	


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
	ZSPACE_EXTERNAL_INLINE void ext_point_getItemsFromArray(zExtPointArray& extArray, zExtPoint* outArray)
	{
		extArray.getItems(outArray);
	}


	ZSPACE_EXTERNAL_INLINE zExtPoint::zExtPoint(float X, float Y, float Z)
	{
		x = X;
		y = Y;
		z = Z;
	}

	ZSPACE_EXTERNAL_INLINE zExtPoint::zExtPoint(zPoint t)
	{
		x = t.x;
		y = t.y;
		z = t.z;
	}

	ZSPACE_EXTERNAL_INLINE void zExtPoint::updateAttributes(float X, float Y, float Z)
	{
		x = X;
		y = Y;
		z = Z;
	}

	ZSPACE_EXTERNAL_INLINE void zExtPoint::updateAttributes(zPoint t)
	{
		x = t.x;
		y = t.y;
		z = t.z;
	}
}