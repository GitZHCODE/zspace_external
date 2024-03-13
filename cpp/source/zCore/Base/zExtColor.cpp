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


#include "headers\zCore\Base\zExtColor.h"


namespace zSpace
{
	//ZSPACE_EXTERNAL_INLINE zExtColor::zExtColor(zColor* t)
	//{
	//	//pointer = t;
	//	updateAttributes(t);
	//}ZSPACE_EXTERNAL_INLINE zExtColor::zExtColor(zColor t)
	//{
	//	//pointer = t;
	//	updateAttributes(t);
	//}
	//ZSPACE_EXTERNAL_INLINE zExtColor::zExtColor()
	//{
	//	//delete pointer; 
	//	//pointer = new zColor();
	//	updateAttributes(0, 0, 0, 1);
	//}
	//ZSPACE_EXTERNAL_INLINE void zExtColor::updateAttributes(zColor* t)
	//{
	//	r = t->r;
	//	g = t->g;
	//	b = t->b;
	//	a = t->a;
	//	
	//}
	//ZSPACE_EXTERNAL_INLINE void zExtColor::updateAttributes(zColor t)
	//{
	//	r = t.r;
	//	g = t.g;
	//	b = t.b;
	//	a = t.a;
	//}
	//ZSPACE_EXTERNAL_INLINE void zExtColor::updateAttributes(float R, float G, float B, float A)
	//{
	//	r = R;
	//	g = G;
	//	b = B;
	//	a = A;
	//}
	
	ZSPACE_EXTERNAL_INLINE zExtColorArray::zExtColorArray(zColorArray* a)
	{
		pointer = a;
		updateAttributes();
	}
	ZSPACE_EXTERNAL_INLINE zExtColorArray::zExtColorArray()
	{
		//delete pointer; 
		pointer = new zColorArray();
	}
	ZSPACE_EXTERNAL_INLINE zExtColorArray::~zExtColorArray()
	{
		delete pointer;
		pointer = nullptr;
	}
	ZSPACE_EXTERNAL_INLINE int zExtColorArray::checkMemAlloc(bool allocateMemory)
	{
		try
		{
			if (pointer != nullptr) return 1;
			else
			{
				if (!allocateMemory) return 0;
				pointer = new zColorArray();
				return 2;
			}
		}
		catch (const std::exception&)
		{
			printf("\n Pointer initialization failed");
			return 404;
		}
	}
	ZSPACE_EXTERNAL_INLINE void zExtColorArray::updateAttributes()
	{
		arrayCount = pointer->size();
	}
	ZSPACE_EXTERNAL_INLINE void zExtColorArray::getItems(zExtColor* items)
	{
		//printf("\n c++ get colors %i", pointer->size());
		//printf("\n c++ get colors %f - %f - %f", pointer->at(0).r, pointer->at(0).g, pointer->at(0).b);
		for (int i = 0; i < pointer->size(); i++)
		{

			items[i] = pointer->at(i);
			//items[i].updateAttributes(pointer->at(i));
		}
	}

	ZSPACE_EXTERNAL_INLINE void zExtColorArray::setItems(zExtColor* items, int count)
	{
		//pointer = new zColorArray;
		checkMemAlloc();
		pointer -> clear();
		for (int i = 0; i < count; i++)
		{
			//pointer->push_back(zColor(items[i].r, items[i].g, items[i].b, items[i].a));
			pointer->push_back(items[i]);
		}
		/*for (int i = 0; i < count; i++)
		{
			printf(" \n set colors %f %f %f %f", pointer->at(i) .r, pointer->at(i).g, pointer->at(i).b);

		}*/
		updateAttributes();
	}
	
	ZSPACE_EXTERNAL_INLINE void ext_color_array_getItems(zExtColorArray& extArray, zExtColor* outArray)
	{
		extArray.getItems(outArray);
	}
	ZSPACE_EXTERNAL_INLINE void ext_color_setItemsFromArray(zExtColorArray& extArray, zExtColor* inArray, int count)
	{
		extArray.setItems(inArray, count);

	}
	ZSPACE_EXTERNAL_INLINE int ext_color_computeHSV(zExtColor& extColor)
	{
		try
		{
			extColor.toHSV();
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
	}
	ZSPACE_EXTERNAL_INLINE int ext_color_computeRGB(zExtColor& extColor)
	{
		try
		{
			extColor.toRGB();
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
	}
	ZSPACE_EXTERNAL_INLINE void ext_color_createRGB(float r, float g, float b, float a, zExtColor& refPoint)
	{
		refPoint = zColor(r, g, b, a);
		refPoint.toHSV();
		//refPoint.updateAttributes(r, g, b, a);
	}

}