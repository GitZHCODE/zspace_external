// This file is part of zspace, a simple C++ collection of geometry data-structures & algorithms, 
// data analysis & visualization framework.
//
// Copyright (C) 2022 ZSPACE 
// 
// This Source Code Form is subject to the terms of the MIT License 
// If a copy of the MIT License was not distributed with this file, You can 
// obtain one at https://opensource.org/licenses/MIT.
//
// Author : Heba Eiz <heba.eiz@zaha-hadid.com>
//

//WIP

#ifndef ZSPACE_STATUS
#define ZSPACE_STATUS

#pragma once

#include "headers/base/zSpace_External.h"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>

#include<execution>

#include<Windows.h>

using namespace std;

namespace zSpace
{
	/*! \enum	zStatus
	*	\brief	Data types for error handling and returns.
	*/
	enum ZSPACE_EXTERNAL zStatusCode {
		zFail,				///<The operation failed
		zSuccess, 			///<The operation was successful.
		zMemAllocSuccess,	///<Memory allocation successful. 
		zMemNotAllocError,	///<The operation failed due to memory not allocated.
		zThrowError,		///<The operation failed due to a THROW error
		zInvalidParameter,	///<The operation failed due to IVALID input
		zPathNotFound,		///<The operation failed due to NOT FOUND PATH
		zRunning,			///<The operation is RUNNING
		zSkip				///<The operation is skipped due to internal condition
	};

	class zStatusCodeUtil
	{
	public:
		static bool getErrorCheck(zStatusCode code);
		static string getCodeString(zStatusCode code);
	};

	struct ZSPACE_EXTERNAL zStatus
	{
	//public:
		zStatusCode statusCode;
		char* errorMessage;
		zStatus(zStatusCode code);
		zStatus(zStatusCode code, string error);
		~zStatus();

		bool getErrorCheck();
		void clearError();
		bool operator==(const zStatus& item);
		bool operator==(const zStatusCode& code);

	};

	ZSPACE_EXTERNAL_C
	{
		ZSPACE_EXTERNAL bool ext_status_operator_equal(zStatus& item, zStatus& item2);
		ZSPACE_EXTERNAL bool ext_status_operator_equalCode(zStatus& item, zStatusCode& code);
		ZSPACE_EXTERNAL bool ext_status_getErrorCheck(zStatus& item);

	}



}

#if defined(ZSPACE_EXTERNAL_STATIC_LIBRARY)  || defined(ZSPACE_EXTERNAL_DYNAMIC_LIBRARY)
// All defined OK so do nothing
#else
#include<source/base/zStatus.cpp>
#endif

#endif