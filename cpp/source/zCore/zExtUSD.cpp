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



#include<headers/zCore/zExtUSD.h>


namespace zSpace
{
#if defined(ZSPACE_USD_INTEROP)  
	ZSPACE_EXTERNAL_INLINE zExtUSD::zExtUSD()
	{
	}
	ZSPACE_EXTERNAL_INLINE zExtUSD::zExtUSD(UsdPrim* usd)
	{
	}
	ZSPACE_EXTERNAL_INLINE zExtUSD::~zExtUSD()
	{
		delete pointer;
		pointer = nullptr;
	}
	ZSPACE_EXTERNAL_INLINE void zExtUSD::updateAttributes()
	{
	}
	ZSPACE_EXTERNAL_INLINE int zExtUSD::checkMemAlloc(bool allocateMemory)
	{
		try
		{
			if (pointer != nullptr) return 1;
			else
			{
				if (!allocateMemory) return 0;
				pointer = new UsdPrim();
				return 2;

			}
		}
		catch (const std::exception&)
		{
			printf("\n Pointer initialization failed");
			return 404;
		}
	}

	/*
	ZSPACE_EXTERNAL_INLINE zExtUSDStage::zExtUSDStage()
	{
		pointer = new UsdStageRefPtr();
		updateAttributes();
	}
	ZSPACE_EXTERNAL_INLINE zExtUSDStage::zExtUSDStage(UsdStageRefPtr* usd)
	{
		pointer = usd;
	}
	ZSPACE_EXTERNAL_INLINE void zExtUSDStage::updateAttributes()
	{
	}
	ZSPACE_EXTERNAL_INLINE int zExtUSDStage::checkMemAlloc(bool allocateMemory)
	{
		try
		{
			//check if the pointer is already initialized
			if (pointer != nullptr)
			{
				return 1;
			}
			else
			{
				pointer = new UsdStageRefPtr();
				return 1;
			}
		}
		catch (const std::exception&)
		{
			printf("\n Pointer initialization failed");
			return 0;
		}
	}

	ZSPACE_EXTERNAL_INLINE int ext_usd_openStage(const string& filePath, zExtUSDStage& extUSD)
	{
		extUSD.checkMemAlloc();
		try
		{
			//zOmniCore omniCore;
			
			
			
		}
		catch (const std::exception&)
		{

		}
		return 0;
	}
	ZSPACE_EXTERNAL_INLINE int ext_usd_createStage(const string& filePath, zExtUSDStage& extUSD)
	{
		return 0;
	}

	*/

#endif
	
}