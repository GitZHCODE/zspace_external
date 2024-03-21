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



#include "headers/zCore/Interop/zExtOV.h"


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
	ZSPACE_EXTERNAL_INLINE zStatusCode zExtUSD::checkMemAlloc(bool allocateMemory)
	{
		try
		{
			if (!pointer || pointer == nullptr)
			{
				if (!allocateMemory) return zMemNotAllocError;
				pointer = new UsdPrim();
				return zMemAllocSuccess;
			}
			else
			{
				return zSkip;
			}
		}
		catch (const std::exception&)
		{
			return zThrowError;
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


	
	ZSPACE_EXTERNAL_INLINE zExtOmniClient::zExtOmniClient()
	{
	}

	ZSPACE_EXTERNAL_INLINE zExtOmniClient::zExtOmniClient(zOmniCore* omniCore)
	{
	}

	ZSPACE_EXTERNAL_INLINE zExtOmniClient::~zExtOmniClient()
	{
		delete pointer;
		pointer = nullptr;
	}

	ZSPACE_EXTERNAL_INLINE void zExtOmniClient::updateAttributes()
	{
	}

	ZSPACE_EXTERNAL_INLINE zStatusCode zExtOmniClient::checkMemAlloc(bool allocateMemory)
	{
		
		try
		{
			if (!pointer || pointer == nullptr)
			{
				if (!allocateMemory) return zMemNotAllocError;
				pointer = new zOmniCore();
				return zMemAllocSuccess;
			}
			else
			{
				return zSkip;
			}
		}
		catch (const std::exception&)
		{
			return zThrowError;
		}
	}

	ZSPACE_EXTERNAL_INLINE int ext_omni_startOmniverse(zExtOmniClient& extOmni, char* filePath)
	{
		try
		{
			extOmni.checkMemAlloc();
			string destinationPath(filePath);
			bool chk = extOmni.pointer->isValidOmniURL(destinationPath);

			// Startup Omniverse with the default login
			if (!extOmni.pointer->startOmniverse())
			{
				printf("\n omniClient did not start");
				return 2;
			}
			extOmni.pointer->printConnectedUsername(destinationPath);
			return chk ? 1 : 0;

		}
		catch (const std::exception&)
		{
			return 404;
			printf("\n ext_omni_startOmniverse failed");

		}
	}

	ZSPACE_EXTERNAL_INLINE int ext_omni_shutdownOmniverse(zExtOmniClient& extOmni)
	{
		try
		{
			extOmni.checkMemAlloc();


			
			extOmni.pointer->shutdownOmniverse();
			return 1;

		}
		catch (const std::exception&)
		{
			printf("\n ext_omni_startOmniverse failed");
			return 0;

		}
	}

#endif
	
}


