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

#ifndef ZSPACE_EXT_CORE_XXXXX //<<update
#define ZSPACE_EXT_CORE_XXXXX



#pragma once

//#include <headers/zToolsets/geometry/zTsSDFSlicer.h>

#include <headers/base/zSpace_External.h>
#include <headers/zCore/base/zExtern.h>

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>

#include<execution>

using namespace std;

namespace zSpace
{


	struct zExtXXX //<update
	{
		zIntArray* pointer; /**< A pointer to object */
		int arrayCount; /**< Attribute */
		zExtXXX();
		zExtXXX(zIntArray* a);

		int initPointer();
		/**
		 * \brief Updates the attributes of the external object
		 */
		void updateAttributes();
	};



	ZSPACE_EXTERNAL_C
	{
		ZSPACE_EXTERNAL void ext_zExtXXX_create(zExtXXX& extObject);
		
	}

}




#if defined(ZSPACE_EXTERNAL_STATIC_LIBRARY)  || defined(ZSPACE_EXTERNAL_DYNAMIC_LIBRARY)
// All defined OK so do nothing
#else
#include<source/zCore/zExtXXX.cpp> //< update
#endif

#endif