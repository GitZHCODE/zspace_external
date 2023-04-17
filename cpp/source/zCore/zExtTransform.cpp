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


#include<headers/zCore/zExtTransform.h>


namespace zSpace
{
	ZSPACE_EXTERNAL_INLINE zExtTransform::zExtTransform(zTransform* t, bool transpose)
	{
		_transform = t;
		updateAttributes(t, transpose);
	}

	ZSPACE_EXTERNAL_INLINE zExtTransform::zExtTransform()
	{
		_transform = new zTransform();
		_transform->setZero();
		updateAttributes();
	}

	ZSPACE_EXTERNAL_INLINE void zExtTransform::updateAttributes(zTransform* t, bool transpose)
	{
		_transform = t;
		updateAttributes(transpose);	
	}
	ZSPACE_EXTERNAL_INLINE void zExtTransform::updateAttributes(bool transpose)
	{
		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				matrix[row][col] = (*_transform)(row, col);
			}
		}

	}

	void zExtTransformArray::updateAttributes()
	{
		arrayCount = pointer->size();
	}
	
	ZSPACE_EXTERNAL_INLINE void ext_zTransform_createNew(zExtTransform& outTransform)
	{
		outTransform = zExtTransform();
	}

	ZSPACE_EXTERNAL_INLINE void ext_zTransform_createNewFromArray(float* array, zExtTransform& outTransform)
	{
		outTransform = zExtTransform();
		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				(*outTransform._transform)(row, col) = array[row * 4 + col];
			}
		}
		outTransform.updateAttributes();

	}

	ZSPACE_EXTERNAL_INLINE void ext_zTransform_updateFromValues(zExtTransform& transform, float* array)
	{
		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				(*transform._transform)(row, col) = array[row * 4 + col];
			}
		}
		transform.updateAttributes();
	}

	ZSPACE_EXTERNAL_INLINE void ext_zTransform_getGraphsFromTransformArray(zExtTransformArray inArray, zExtTransform* outTranfroms)
	{
		for (int i = 0; i < inArray.pointer->size(); i++)
		{
			outTranfroms[i] = zExtTransform(&inArray.pointer->at(i));
			outTranfroms[i].updateAttributes();
		}
	}




}