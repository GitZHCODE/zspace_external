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


#include "..\..\headers\zCore\zExtColor.h"


namespace zSpace
{
	ZSPACE_EXTERNAL_INLINE zExtColor::zExtColor(zColor* t)
	{
		//pointer = t;
		updateAttributes(t);
	}ZSPACE_EXTERNAL_INLINE zExtColor::zExtColor(zColor t)
	{
		//pointer = t;
		updateAttributes(t);
	}
	ZSPACE_EXTERNAL_INLINE zExtColor::zExtColor()
	{
		//delete pointer; 
		//pointer = new zColor();
		updateAttributes(0, 0, 0, 1);
	}
	ZSPACE_EXTERNAL_INLINE void zExtColor::updateAttributes(zColor* t)
	{
		r = t->r;
		g = t->g;
		b = t->b;
		a = t->a;
		
	}
	ZSPACE_EXTERNAL_INLINE void zExtColor::updateAttributes(zColor t)
	{
		r = t.r;
		g = t.g;
		b = t.b;
		a = t.a;
	}
	ZSPACE_EXTERNAL_INLINE void zExtColor::updateAttributes(float R, float G, float B, float A)
	{
		r = R;
		g = G;
		b = B;
		a = A;
	}
	
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
	ZSPACE_EXTERNAL_INLINE void zExtColorArray::updateAttributes()
	{
		arrayCount = pointer->size();
	}
	ZSPACE_EXTERNAL_INLINE void zExtColorArray::getItems(zExtColor* items)
	{
		for (int i = 0; i < pointer->size(); i++)
		{
			items[i].updateAttributes(pointer->at(i));
		}
	}
	
	ZSPACE_EXTERNAL_INLINE void ext_color_getItemsFromArray(zExtColorArray& extArray, zExtColor* outArray)
	{
		extArray.getItems(outArray);
	}
	ZSPACE_EXTERNAL_INLINE void ext_color_createRGB(float r, float g, float b, float a, zExtColor& refPoint)
	{
		//refPoint = new zColor(r, g, b, a);
		refPoint.updateAttributes(r, g, b, a);
	}

}