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

#include "headers/base/zStatus.h"

namespace zSpace
{
	
	ZSPACE_EXTERNAL_INLINE zStatus::zStatus(zStatusCode code)
	{
		statusCode = code;
		cout << endl << "zSatus code " << statusCode <<" " << zStatusCodeUtil::getCodeString(statusCode);

		//string error = zStatusCodeUtil::getCodeString(code);
		//statusMessage = new char[error.length() + 1];
		//strcpy(statusMessage, error.c_str());
	}
	ZSPACE_EXTERNAL_INLINE zStatus::zStatus(zStatusCode code, string error)
	{
		statusCode = code;
		//statusMessage = new char[error.length() + 1];
		//strcpy(statusMessage, error.c_str());
	}
	ZSPACE_EXTERNAL_INLINE zStatus::~zStatus()
	{
		//delete[] statusMessage;
	}
	
	ZSPACE_EXTERNAL_INLINE zStatus::zStatus()
	{
		statusCode = zStatusCode::zFail;
	}

	ZSPACE_EXTERNAL_INLINE bool zStatus::getErrorCheck()
	{
		switch (statusCode)
		{
		case zFail: return true;
		case zSuccess: return false;
		case zMemAllocSuccess: return false;
		case zMemNotAllocError: return true;
		case zThrowError: return true;
		case zInvalidParameter: return true;
		case zPathNotFound: return true;
		case zRunning: return false;
		case zSkip: return false;
		
		default: return false;
		}
		
	}
	ZSPACE_EXTERNAL_INLINE void zStatus::clearError()
	{
		statusCode = zSuccess;
		//errorString->clear();
	}
	ZSPACE_EXTERNAL_INLINE bool zStatus::operator==(const zStatus& item)
	{
		return this->statusCode == item.statusCode;
	}


	ZSPACE_EXTERNAL_INLINE bool zStatus::operator==(const zStatusCode& code)
	{
		return this->statusCode == code;
	}


	ZSPACE_EXTERNAL_INLINE bool zStatusCodeUtil::getErrorCheck(zStatusCode code)
	{
		switch (code)
		{
		case zFail: return true;
		case zSuccess: return false;
		case zMemAllocSuccess: return false;
		case zMemNotAllocError: return true;
		case zThrowError: return true;
		case zInvalidParameter: return true;
		case zPathNotFound: return true;
		case zRunning: return false;

		default: return false;
		}
	}

	ZSPACE_EXTERNAL_INLINE string zStatusCodeUtil::getCodeString(zStatusCode code)
	{
		switch (code)
		{
		case zFail: return "Process failed";
		case zSuccess: return "Process success";
		case zMemAllocSuccess: return "Process success: Memory allocation success";
		case zMemNotAllocError: return "Process failed: Memory allocation error";
		case zThrowError: return "Process failed: Unknown error";
		case zInvalidParameter: return "Process failed: Invalid input parameter";
		case zPathNotFound: return "Process failed: Path/Directory is not found";
		case zRunning: return "Process is running";
		case zSkip: return "Process is skipped";

		default: return "code value is invalid/not set";
		}
	}

	
	ZSPACE_EXTERNAL_INLINE bool ext_status_operator_equal(zStatus& item, zStatus& item2)
	{
		return item == item2;
	}	


	ZSPACE_EXTERNAL_INLINE bool ext_status_operator_equalCode(zStatus& item, zStatusCode& code)
	{
		return item == code;
	}
	ZSPACE_EXTERNAL_INLINE bool ext_status_getErrorCheck(zStatus& item)
	{
		return item.getErrorCheck();
	}






	

	ZSPACE_EXTERNAL_INLINE zStatus2::zStatus2()
	{
		statusCode = 10;
	}

	ZSPACE_EXTERNAL_INLINE zStatus2::~zStatus2()
	{
	}

}