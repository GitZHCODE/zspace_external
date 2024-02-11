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
	bool zStatus::checkError()
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
		
		default: return false;
		}
		
	}
	void zStatus::clearError()
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


	
	ZSPACE_EXTERNAL_INLINE bool ext_status_operator_equal(zStatus& item, zStatus& item2)
	{
		return item == item2;
	}	


	ZSPACE_EXTERNAL_INLINE bool ext_status_operator_equalCode(zStatus& item, zStatusCode& code)
	{
		return item == code;
	}	





}