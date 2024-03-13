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


#include<headers/zCore/Base/zExtTransform.h>


namespace zSpace
{
	ZSPACE_EXTERNAL_INLINE zExtTransform::zExtTransform(zTransform* t, bool transpose)
	{

		pointer = t;
		updateAttributes(t, transpose);
	}

	ZSPACE_EXTERNAL_INLINE zExtTransform::zExtTransform()
	{
		checkMemAlloc();
		pointer->setZero();
		updateAttributes();
	}

	ZSPACE_EXTERNAL_INLINE zExtTransform::zExtTransform(zTransform t)
	{
		checkMemAlloc();
		pointer = new zTransform(t);
		updateAttributes();

	}

	ZSPACE_EXTERNAL_INLINE zExtTransform::~zExtTransform()
	{
		delete pointer;
		pointer = nullptr;
	}

	ZSPACE_EXTERNAL_INLINE int zExtTransform::checkMemAlloc(bool allocateMemory)
	{
		try
		{
			if (pointer != nullptr) return 1;
			else
			{
				if (!allocateMemory) return 0;
				pointer = new zTransform();
				for (int i = 0; i < 4; i++)
				{
					(*pointer)(0, i) = row0[i];
					(*pointer)(1, i) = row1[i];
					(*pointer)(2, i) = row2[i];
					(*pointer)(3, i) = row3[i];
					//array[i] = (*pointer)(i / 4, i % 4);
				}
				return 2;

			}
		}
		catch (const std::exception&)
		{
			printf("\n Pointer initialization failed");
			return 404;
		}
		
	}
	ZSPACE_EXTERNAL_INLINE int zExtTransform::initPointer(zTransform t)
	{
		try
		{
			//check if the pointer is already initialized
			if (pointer != nullptr)
			{
				//printf("\n Pointer already initialized");
				updateAttributes(&t);
				return 1;
			}
			else
			{
				pointer = new zTransform(t);
				//printf("\n Pointer initialized successfully");
				return 1;
			}
		}
		catch (const std::exception&)
		{
			printf("\n Pointer initialization failed");
			return 0;
		}
	}

	ZSPACE_EXTERNAL_INLINE void zExtTransform::updateAttributes(zTransform* t, bool transpose)
	{
		pointer = t;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				pointer->asPermutation();
			}


		}
		updateAttributes(transpose);
	}

	ZSPACE_EXTERNAL_INLINE void zExtTransform::updateAttributes(bool transpose)
	{
		if (transpose)
		{
			pointer->transpose();
		}
		for (int i = 0; i < 4; i++)
		{
			row0[i] = (*pointer)(0, i);
			row1[i] = (*pointer)(1, i);
			row2[i] = (*pointer)(2, i);
			row3[i] = (*pointer)(3, i);

			//array[i] = (*pointer)(i / 4, i % 4);
		}
		/*for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				matrix[row][col] = (*pointer)(row, col);
			}
		}*/

	}

	ZSPACE_EXTERNAL_INLINE int zExtTransformArray::checkMemAlloc(bool allocateMemory)
	{
		try
		{
			if (pointer != nullptr) return 1;
			else
			{
				if (!allocateMemory) return 0;
				pointer = new vector<zTransform>();
				return 2;

			}
		}
		catch (const std::exception&)
		{
			printf("\n Pointer initialization failed");
			return 404;
		}
		
	}

	ZSPACE_EXTERNAL_INLINE zExtTransformArray::~zExtTransformArray()
	{
		delete pointer;
		pointer = nullptr;
	}

	ZSPACE_EXTERNAL_INLINE void zExtTransformArray::updateAttributes()
	{
		arrayCount = pointer->size();
	}

	ZSPACE_EXTERNAL_INLINE void zExtTransformArray::getItems(zExtTransform* items)
	{
		for (int i = 0; i < arrayCount; i++)
		{
			items[i] = zExtTransform(&pointer->at(i));
		}
	}

	ZSPACE_EXTERNAL_INLINE void ext_transform_initPointer(zExtTransform& outTransform)
	{
		outTransform.checkMemAlloc();
	}

	ZSPACE_EXTERNAL_INLINE void ext_transform_createNewFromArray(float* array, zExtTransform& outTransform)
	{
		outTransform = zExtTransform();
		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				(*outTransform.pointer)(row, col) = array[row * 4 + col];
			}
		}
		outTransform.updateAttributes();

	}

	ZSPACE_EXTERNAL_INLINE void ext_transform_updateFromValues(zExtTransform& transform, float* array)
	{
		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				(*transform.pointer)(row, col) = array[row * 4 + col];
			}
		}
		transform.updateAttributes();
	}

	ZSPACE_EXTERNAL_INLINE int ext_transform_array_getItems(zExtTransformArray inArray, zExtTransform* outTranfroms)
	{
		try
		{
			for (int i = 0; i < inArray.pointer->size(); i++)
			{
				outTranfroms[i] = zExtTransform(&inArray.pointer->at(i));
				outTranfroms[i].updateAttributes();
			}
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}

	}

	ZSPACE_EXTERNAL_INLINE int ext_transform_setItemsFromArray(zExtTransformArray inArray, zExtTransform* inTranfroms, int count)
	{
		return 0;
	}




}