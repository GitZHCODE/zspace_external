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

#ifndef ZSPACE_EXT_CORE_USD_H
#define ZSPACE_EXT_CORE_USD_H



#pragma once




#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>

#include <headers/zApp/include/zInterOp.h>

#include <headers/zInterface/functionsets/zFn.h>

#include "headers/base/zSpace_External.h"
#include "headers/zCore/Utils/zExtUtilsCore.h"

#if defined(ZSPACE_USD_INTEROP) 
#include <headers/zInterOp/core/zOmniCore.h>
#endif



#include<execution>


using namespace std;

namespace zSpace
{
#if defined(ZSPACE_USD_INTEROP)  
	//zOmniCore omniCore;

	struct ZSPACE_EXTERNAL zExtUSD
	{
		UsdPrim* pointer = nullptr;
		zExtUSD();
		zExtUSD(UsdPrim* usd);
		~zExtUSD();
		void updateAttributes();
		int checkMemAlloc(bool allocateMemory = true);
	};
	ZSPACE_EXTERNAL_C
	{
		
	}

	struct ZSPACE_EXTERNAL zExtOmniClient
	{
		zOmniCore* pointer = nullptr;
		zExtOmniClient();
		zExtOmniClient(zOmniCore* omniCore);
		~zExtOmniClient();
		void updateAttributes();
		int checkMemAlloc(bool allocateMemory = true);
	};

	ZSPACE_EXTERNAL_C
	{
		ZSPACE_EXTERNAL int ext_omni_startOmniverse(zExtOmniClient& pointer, char* filePath);
		ZSPACE_EXTERNAL int ext_omni_shutdownOmniverse(zExtOmniClient& pointer);
	}



	
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		struct zExtUSDStage
	{
		UsdStageRefPtr* pointer = nullptr;
		zExtUSDStage();
		zExtUSDStage(UsdStageRefPtr* usd);
		void updateAttributes();
		int checkMemAlloc(bool allocateMemory = true);
	};

	ZSPACE_EXTERNAL_C
	{
		ZSPACE_EXTERNAL int ext_usd_openStage(const string& filePath, zExtUSDStage& extUSD);
		ZSPACE_EXTERNAL int ext_usd_createStage(const string& filePath, zExtUSDStage& extUSD);



	}
#endif


}




#if defined(ZSPACE_EXTERNAL_STATIC_LIBRARY)  || defined(ZSPACE_EXTERNAL_DYNAMIC_LIBRARY)
// All defined OK so do nothing
#else
#include<source/zCore/zExtOV.cpp>
#endif

#endif