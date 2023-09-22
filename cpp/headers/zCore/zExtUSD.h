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


#include <headers/base/zSpace_External.h>

#include <headers/zInterface/functionsets/zFnGraph.h>

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>

#include <headers/zApp/include/zInterOp.h>
#include<headers/zInterOp/core/zOmniCore.h>

#include<execution>

using namespace std;

namespace zSpace
{

	zOmniCore omniCore;


	ZSPACE_EXTERNAL_C
	{
		

	}



}




#if defined(ZSPACE_EXTERNAL_STATIC_LIBRARY)  || defined(ZSPACE_EXTERNAL_DYNAMIC_LIBRARY)
// All defined OK so do nothing
#else
#include<source/zCore/zExtUSD.cpp>
#endif

#endif