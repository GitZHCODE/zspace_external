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


#include"headers/zCore/Utils/zExtUtilsCore.h"


namespace zSpace
{
	//	------------------------------	//
	//	-----	Int Array 1D	------	//
	//	------------------------------	//
	// Constructor
	ZSPACE_EXTERNAL_INLINE zExtIntArray::zExtIntArray(zIntArray* a)
	{
		//delete pointer;
		pointer = a;
		updateAttributes();
	}
	ZSPACE_EXTERNAL_INLINE zExtIntArray::zExtIntArray()
	{
		//delete pointer;
		checkMemAlloc(true);

		updateAttributes();
	}
	ZSPACE_EXTERNAL_INLINE zExtIntArray::zExtIntArray(zIntArray a)
	{
		if (!pointer) pointer = new zIntArray(a);
		else *pointer = a;
		
		updateAttributes();
	}
	ZSPACE_EXTERNAL_INLINE zExtIntArray::~zExtIntArray()
	{
		delete pointer;
		pointer = nullptr;
	}
	ZSPACE_EXTERNAL_INLINE zStatusCode zExtIntArray::checkMemAlloc(bool allocateMemory)
	{
	
		try
		{
			if (!pointer || pointer == nullptr)
			{
				if (!allocateMemory) return zMemNotAllocError;
				pointer = new vector<int>();
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
	// Methods
	ZSPACE_EXTERNAL_INLINE void zExtIntArray::updateAttributes()
	{
		arrayCount = pointer->size();
	}
	ZSPACE_EXTERNAL_INLINE void zExtIntArray::getItems(int* items)
	{
		for (int i = 0; i < pointer->size(); i++)
		{
			items[i] = pointer->at(i);
		}
	}
	ZSPACE_EXTERNAL_INLINE void zExtIntArray::setItems(int* items, int count)
	{
		//delete pointer;
		checkMemAlloc();
		pointer->clear();
		for (int i = 0; i < count; i++)
		{
			pointer->push_back(items[i]);
		}
		updateAttributes();
	}
	// External Methods
	ZSPACE_EXTERNAL_INLINE void ext_int_array_getItems(zExtIntArray& extArray, int* outArray)
	{
		extArray.getItems(outArray);
	}
	ZSPACE_EXTERNAL_INLINE void ext_int_array_setItems(zExtIntArray& extArray, int* inArray, int count)
	{
		extArray.setItems(inArray, count);
	}
	//-----* Int Array 2D*------//
	// Constructor
	ZSPACE_EXTERNAL_INLINE zExtIntArray2D::zExtIntArray2D()
	{
		//delete pointer;
		pointer = new zInt2DArray();
		updateAttributes();
	}
	ZSPACE_EXTERNAL_INLINE zExtIntArray2D::zExtIntArray2D(zInt2DArray a)
	{
		//delete pointer;
		pointer = new zInt2DArray(a);
		updateAttributes();
	}
	ZSPACE_EXTERNAL_INLINE zExtIntArray2D::zExtIntArray2D(zInt2DArray* a)
	{
		//delete pointer;
		pointer = a;
		updateAttributes();
	}
	ZSPACE_EXTERNAL_INLINE zExtIntArray2D::~zExtIntArray2D()
	{
		delete pointer;
		pointer = nullptr;
	}
	ZSPACE_EXTERNAL_INLINE zStatusCode zExtIntArray2D::checkMemAlloc(bool allocateMemory)
	{
		
		try
		{
			if (!pointer || pointer == nullptr)
			{
				if (!allocateMemory) return zMemNotAllocError;
				pointer = new vector<zIntArray>();
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
	// Methods
	ZSPACE_EXTERNAL_INLINE void zExtIntArray2D::updateAttributes()
	{
		arrayCount = pointer->size();
	}
	ZSPACE_EXTERNAL_INLINE void zExtIntArray2D::getItems(zExtIntArray* items)
	{
		for (int i = 0; i < pointer->size(); i++)
		{
			items[i].pointer = &pointer->at(i);
			items[i].updateAttributes();
		}
	}
	ZSPACE_EXTERNAL_INLINE void zExtIntArray2D::setItems(zExtIntArray* items, int count)
	{
		//delete pointer;
		pointer = new zInt2DArray;
		for (int i = 0; i < count; i++)
		{
			pointer->push_back(*(items[i].pointer));
		}
		updateAttributes();
	}
	// External Methods
	ZSPACE_EXTERNAL_INLINE void ext_int_array2D_getItems(zExtIntArray2D& extArray, zExtIntArray* outArray)
	{
		//int memoryChk = extArray.checkMemAlloc(false);
		//if (memoryChk != 1) return;// memoryChk;
		extArray.checkMemAlloc();

		extArray.getItems(outArray);
	}
	ZSPACE_EXTERNAL_INLINE void ext_int_array2D_setItems(zExtIntArray2D& extArray, zExtIntArray* inArray, int count)
	{
		extArray.setItems(inArray, count);
	}

	//	------------------------------	//
	//	-----	Float Array 2D	------	//
	//	------------------------------	//
	// Constructor
	ZSPACE_EXTERNAL_INLINE zExtFloatArray::zExtFloatArray()
	{
		//delete pointer;
		//pointer = new zFloatArray();
		checkMemAlloc();
		updateAttributes();
	}
	ZSPACE_EXTERNAL_INLINE zExtFloatArray::zExtFloatArray(zFloatArray a)
	{
		delete pointer;
		pointer = new zFloatArray(a);
		//checkMemAlloc();

		updateAttributes();
	}
	ZSPACE_EXTERNAL_INLINE zExtFloatArray::zExtFloatArray(zFloatArray* a)
	{
		//delete pointer;
		pointer = a;
		updateAttributes();
	}
	ZSPACE_EXTERNAL_INLINE zExtFloatArray::~zExtFloatArray()
	{
		delete pointer;
		pointer = nullptr;
	}
	ZSPACE_EXTERNAL_INLINE zStatusCode zExtFloatArray::checkMemAlloc(bool allocateMemory)
	{
		try
		{
			if (!pointer || pointer == nullptr)
			{
				if (!allocateMemory) return zMemNotAllocError;
				pointer  = new vector<float>();
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
	// Methods
	ZSPACE_EXTERNAL_INLINE void zExtFloatArray::updateAttributes()
	{
		arrayCount = pointer->size();
	}
	ZSPACE_EXTERNAL_INLINE void zExtFloatArray::getItems(float* items)
	{
		for (int i = 0; i < pointer->size(); i++)
		{
			items[i] = pointer->at(i);
		}
	}
	ZSPACE_EXTERNAL_INLINE void zExtFloatArray::setItems(float* items, int count)
	{
		//delete pointer;
		checkMemAlloc();
		pointer->clear();
		for (int i = 0; i < count; i++)
		{
			pointer->push_back(items[i]);
		}
		updateAttributes();
	}
	// External Methods
	ZSPACE_EXTERNAL_INLINE void ext_float_array_getItems(zExtFloatArray& extArray, float* outArray)
	{
		extArray.getItems(outArray);
	}
	ZSPACE_EXTERNAL_INLINE void ext_float_setItemsFromArray(zExtFloatArray& extArray, float* inArray, int count)
	{
		extArray.setItems(inArray, count);
	}
	//	------------------------------	//
	//	-----	Float Array 1D	------	//
	//	------------------------------	//
	// Constructor
	ZSPACE_EXTERNAL_INLINE zExtFloatArray2D::zExtFloatArray2D()
	{
		//delete pointer;
		pointer = new vector<zFloatArray>();
		updateAttributes();
	}
	ZSPACE_EXTERNAL_INLINE zExtFloatArray2D::zExtFloatArray2D(vector<zFloatArray> a)
	{
		//delete pointer;
		pointer = new vector<zFloatArray>(a);
		updateAttributes();
	}
	ZSPACE_EXTERNAL_INLINE zExtFloatArray2D::zExtFloatArray2D(vector<zFloatArray>* a)
	{
		pointer = a;
		updateAttributes();
	}
	ZSPACE_EXTERNAL_INLINE zExtFloatArray2D::~zExtFloatArray2D()
	{
		delete pointer;
		pointer = nullptr;
	}
	// Methods
	ZSPACE_EXTERNAL_INLINE void zExtFloatArray2D::updateAttributes()
	{
		arrayCount = pointer->size();
	}
	ZSPACE_EXTERNAL_INLINE zStatusCode zExtFloatArray2D::checkMemAlloc(bool allocateMemory)
	{
		
		try
		{
			if (!pointer || pointer == nullptr)
			{
				if (!allocateMemory) return zMemNotAllocError;
				pointer =new vector<zFloatArray>(); 
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

	ZSPACE_EXTERNAL_INLINE void zExtFloatArray2D::getItems(zExtFloatArray* items)
	{
		for (int i = 0; i < pointer->size(); i++)
		{
			items[i].pointer = &pointer->at(i);
			items[i].updateAttributes();
		}
	}
	ZSPACE_EXTERNAL_INLINE void zExtFloatArray2D::setItems(zExtFloatArray* items, int count)
	{
		//delete pointer;
		pointer = new vector<zFloatArray>;
	
		for (int i = 0; i < count; i++)
		{
			pointer->push_back(*(items[i].pointer));
		}
		updateAttributes();
	}
	// External Methods
	ZSPACE_EXTERNAL_INLINE void ext_float_array2D_getItems(zExtFloatArray2D& extArray, zExtFloatArray* outArray)
	{
		extArray.getItems(outArray);
	}
	ZSPACE_EXTERNAL_INLINE void ext_float_array2D_setItems(zExtFloatArray2D& extArray, zExtFloatArray* inArray, int count)
	{
		extArray.setItems(inArray, count);
	}


	//	------------------------------	//
	//	-----	Double Array 1D	------	//
	//	------------------------------	//
	// Constructor
	ZSPACE_EXTERNAL_INLINE zExtDoubleArray::zExtDoubleArray()
	{
		//delete pointer;
		pointer = new zDoubleArray();
		updateAttributes();
	}
	ZSPACE_EXTERNAL_INLINE zExtDoubleArray::zExtDoubleArray(zDoubleArray a)
	{
		//delete pointer;

		pointer = new zDoubleArray(a);
		updateAttributes();
	}
	ZSPACE_EXTERNAL_INLINE zExtDoubleArray::zExtDoubleArray(zDoubleArray* a)
	{
		pointer = a;
		updateAttributes();
	}
	ZSPACE_EXTERNAL_INLINE zExtDoubleArray::~zExtDoubleArray()
	{
		delete pointer;
		pointer = nullptr;
	}
	// Methods
	ZSPACE_EXTERNAL_INLINE void zExtDoubleArray::updateAttributes()
	{
		arrayCount = pointer->size();
	}
	ZSPACE_EXTERNAL_INLINE zStatusCode zExtDoubleArray::checkMemAlloc(bool allocateMemory)
	{
		
		try
		{
			if (!pointer || pointer == nullptr)
			{
				if (!allocateMemory) return zMemNotAllocError;
				pointer = new vector<double>();
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
	ZSPACE_EXTERNAL_INLINE void zExtDoubleArray::getItems(double* items)
	{
		for (int i = 0; i < pointer->size(); i++)
		{
			items[i] = pointer->at(i);
		}
	}
	ZSPACE_EXTERNAL_INLINE void zExtDoubleArray::setItems(double* items, int count)
	{
		//delete pointer;
		pointer = new zDoubleArray;
		for (int i = 0; i < count; i++)
		{
			pointer->push_back(items[i]);
		}
		updateAttributes();
	}
	// External Methods
	ZSPACE_EXTERNAL_INLINE void ext_double_array_getItems(zExtDoubleArray& extArray, double* outArray)
	{
		extArray.getItems(outArray);
	}
	ZSPACE_EXTERNAL_INLINE void ext_double_setItemsFromArray(zExtDoubleArray& extArray, double* inArray, int count)
	{
		extArray.setItems(inArray, count);
	}


	//	------------------------------	//
	//	-----	Double Array 2D	------	//
	//	------------------------------	//
	// Constructor
	ZSPACE_EXTERNAL_INLINE zExtDoubleArray2D::zExtDoubleArray2D()
	{
		//delete pointer;
		checkMemAlloc(true);
		//pointer = new vector<zDoubleArray>();
		updateAttributes();
	}
	ZSPACE_EXTERNAL_INLINE zExtDoubleArray2D::zExtDoubleArray2D(vector<zDoubleArray> a)
	{
		//delete pointer;
		pointer = new vector<zDoubleArray>();
		updateAttributes();
	}
	ZSPACE_EXTERNAL_INLINE zExtDoubleArray2D::zExtDoubleArray2D(vector<zDoubleArray>* a)
	{
		//delete pointer;
		pointer = a;
		updateAttributes();
	}
	ZSPACE_EXTERNAL_INLINE zExtDoubleArray2D::~zExtDoubleArray2D()
	{
		delete pointer;
		pointer = nullptr;
	}
	// Methods
	ZSPACE_EXTERNAL_INLINE void zExtDoubleArray2D::updateAttributes()
	{
		arrayCount = pointer->size();
	}
	ZSPACE_EXTERNAL_INLINE zStatusCode zExtDoubleArray2D::checkMemAlloc(bool allocateMemory)
	{
		
		try
		{
			if (!pointer || pointer == nullptr)
			{
				if (!allocateMemory) return zMemNotAllocError;
				pointer = new vector<zDoubleArray>();
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
	ZSPACE_EXTERNAL_INLINE void zExtDoubleArray2D::getItems(zExtDoubleArray* items)
	{
		for (int i = 0; i < pointer->size(); i++)
		{
			items[i].pointer = &pointer->at(i);
			items[i].updateAttributes();
		}
	}
	ZSPACE_EXTERNAL_INLINE void zExtDoubleArray2D::setItems(zExtDoubleArray* items, int count)
	{
		//delete pointer;
		//delete pointer;
		pointer = new vector<zDoubleArray>;
		for (int i = 0; i < count; i++)
		{
			pointer->push_back(*(items[i].pointer));
		}
		updateAttributes();
	}
	// External Methods
	ZSPACE_EXTERNAL_INLINE void ext_double_array2D_getItems(zExtDoubleArray2D& extArray, zExtDoubleArray* outArray)
	{
		extArray.getItems(outArray);
	}
	ZSPACE_EXTERNAL_INLINE void ext_double_array2D_setItems(zExtDoubleArray2D& extArray, zExtDoubleArray* inArray, int count)
	{
		extArray.setItems(inArray, count);
	}

	ZSPACE_EXTERNAL_INLINE zExtString::~zExtString()
	{
		delete pointer;
		pointer = nullptr;
	}

	//	------------------------------	//
	//	------------ String --------	//
	//	------------------------------	//
	// Methods
	ZSPACE_EXTERNAL_INLINE void zExtString::updateAttributes()
	{
		stringLength = pointer->size();
	}
	ZSPACE_EXTERNAL_INLINE zStatusCode zExtString::checkMemAlloc(bool allocateMemory)
	{
		
		try
		{
			if (!pointer || pointer == nullptr)
			{
				if (!allocateMemory) return zMemNotAllocError;
				pointer = new string();
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
	ZSPACE_EXTERNAL_INLINE void zExtString::getCharecters(char* outString)
	{
		for (int i = 0; i < pointer->size(); i++)
		{
			outString[i] = pointer->at(i);
		}
	}
	ZSPACE_EXTERNAL_INLINE void zExtString::setItems(char* items, int count)
	{
		//checkMemAlloc(true);
		pointer = new string(items, count);
		//cout << endl << "extstring " << items;
		//printf("\n zExtString %s", pointer->c_str());
		/*pointer = new string;
		for (int i = 0; i < count; i++)
		{
			pointer->push_back(items[i]);
		}*/

		//cout << string(items, count);
		updateAttributes();
	}
	// External Methods
	ZSPACE_EXTERNAL_INLINE int ext_string_getCharArrayFromExtString(zExtString& extString, char* outString)
	{
		try
		{
			extString.getCharecters(outString);
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
	}
	ZSPACE_EXTERNAL_INLINE int ext_string_setExtStringFromCharArray(zExtString& extString, char* inString, int count)
	{
		try
		{
			extString.setItems(inString, count);

			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
	}
	//	------------------------------	//
	//	-----	String Array 1D	------	//
	//	------------------------------	//
	// Constructor
	ZSPACE_EXTERNAL_INLINE zExtStringArray::zExtStringArray()
	{
		//delete pointer;
		pointer = new zStringArray();
		updateAttributes();
	}
	ZSPACE_EXTERNAL_INLINE zExtStringArray::zExtStringArray(zStringArray a)
	{
		//printf("\n string 0");
		try
		{
			//printf("\n string meshPointer before deleted");
			//printf("\n Ptr i% ", pointer);
			if (pointer != nullptr)
			{
				printf("\n ptr init");

				////delete pointer;

			}
		}
		catch (const std::exception&)
		{
			printf("\n string  not deleted");

		}
		
		//printf("\n string 1");

		pointer = new zStringArray(a);
		//printf("\n string 2");

		updateAttributes();
		//printf("\n string 3");

	}
	ZSPACE_EXTERNAL_INLINE zExtStringArray::zExtStringArray(zStringArray* a)
	{
		//delete pointer;
		pointer = a;
		updateAttributes();
	}
	ZSPACE_EXTERNAL_INLINE zExtStringArray::~zExtStringArray()
	{
		delete pointer;
		pointer = nullptr;
	}
	// Methods
	ZSPACE_EXTERNAL_INLINE void zExtStringArray::updateAttributes()
	{
		arrayCount = pointer->size();
	}
	ZSPACE_EXTERNAL_INLINE zStatusCode zExtStringArray::checkMemAlloc(bool allocateMemory)
	{
		try
		{
			if (!pointer || pointer == nullptr)
			{
				if (!allocateMemory) return zMemNotAllocError;
				pointer = new vector<string>();
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
	ZSPACE_EXTERNAL_INLINE void zExtStringArray::getItems(string* items)
	{
		//printf("count %i ", arrayCount);
		//printf("count %i ", pointer->size());
		for (int i = 0; i < pointer->size(); i++)
		{
			items[i] = pointer->at(i);
		}
	}
	ZSPACE_EXTERNAL_INLINE void zExtStringArray::setItems(string* items, int count)
	{
		printf("\n zExtStringArray::setItems");
		//delete pointer;
		//pointer = new zStringArray();
		pointer = new vector<string>();
		vector<string> st;

		for (int i = 0; i < count; i++)
		{
			bool chk = items[i].c_str() != nullptr;
			// Use %s format specifier for strings
			printf("\n %i zExtString %d - %i", i, chk, items[i]);

			// Use cout for printing the content
			//cout << endl << items[i] << endl;
		
			pointer->push_back(items[i]);
		}
		updateAttributes();
	}
	// External Methods
	ZSPACE_EXTERNAL_INLINE void ext_string_array_getItems(zExtStringArray& extArray, zExtString* outArray)
	{
		//extArray.getItems(outArray);
		//printf(" \n outArray size %i ", outArray->size());
		//printf(" \n extArray.pointer size %i ", extArray.pointer->size());
		//outArray->clear();
		//outArray->assign(extArray.pointer->size(), ' ' );
		//printf(" \n outArray size %i ", outArray->size());

		for (int i = 0; i < extArray.pointer->size(); i++)
		{
			//printf(" \n extArray.pointer->at(i) %s ", extArray.pointer->at(i));
			//printf(" \n outArray[i] %s ", outArray[i]);

			outArray[i].pointer = &extArray.pointer->at(i);
			outArray[i].updateAttributes();
			//printf(" \n outArray[i] %s ", outArray[i]);

		}
	}
	ZSPACE_EXTERNAL_INLINE void ext_string_array_setItems(zExtStringArray& extArray, zExtString* inArray, int count)
	{
		////printf("\n ext_string_array_setItems  count %i", count);
		//vector<string> st;
		//string* items;
		////items->assign("", count);
		//for (int i = 0; i < count; i++)
		//{
		//	//bool chk = inArray[i].pointer->c_str() != nullptr;
		//	//printf("\n %i zExtString %d - %i", i, chk, inArray[i].stringLength);

		//	//cout << endl << *inArray[i].pointer << endl;
		//	st.push_back(*inArray[i].pointer);
		//	items[i] = *inArray[i].pointer;
		//}
		//extArray = zExtStringArray(st);
		//extArray.checkMemAlloc(true);
		////extArray.setItems(items, count);
		//extArray.updateAttributes();
		////extArray.setItems(inArray->pointer, count);

		//zExtStringArray.pointer = new vector<zDoubleArray>;
		extArray.checkMemAlloc(true);
		for (int i = 0; i < count; i++)
		{
			//extArray.pointer->push_back(*(items[i].pointer));
			extArray.pointer->push_back(*(inArray[i].pointer));
		}
		extArray.updateAttributes();



	}
	//	------------------------------	//
	//	-----	String Array 2D	------	//
	//	------------------------------	//
	// Constructor
	ZSPACE_EXTERNAL_INLINE zExtStringArray2D::zExtStringArray2D()
	{
		//delete pointer;
		pointer = new vector<zStringArray>();
		updateAttributes();
	}
	ZSPACE_EXTERNAL_INLINE zExtStringArray2D::zExtStringArray2D(vector<zStringArray> a)
	{
		//delete pointer;
		pointer = new vector<zStringArray>(a);
		updateAttributes();
	}
	ZSPACE_EXTERNAL_INLINE zExtStringArray2D::zExtStringArray2D(vector<zStringArray>* a)
	{
		//delete pointer;
		pointer = a;
		updateAttributes();
	}
	ZSPACE_EXTERNAL_INLINE zExtStringArray2D::~zExtStringArray2D()
	{
		delete pointer;
		pointer = nullptr;
	}
	// Methods
	ZSPACE_EXTERNAL_INLINE void zExtStringArray2D::updateAttributes()
	{
		arrayCount = pointer->size();
	}
	ZSPACE_EXTERNAL_INLINE zStatusCode zExtStringArray2D::checkMemAlloc(bool allocateMemory)
	{
		
		try
		{
			if (!pointer || pointer == nullptr)
			{
				if (!allocateMemory) return zMemNotAllocError;
				pointer = new vector<zStringArray>();
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
	ZSPACE_EXTERNAL_INLINE void zExtStringArray2D::getItems(zExtStringArray* items)
	{
		for (int i = 0; i < pointer->size(); i++)
		{
			items[i].pointer = &pointer->at(i);
			items[i].updateAttributes();
		}
	}
	ZSPACE_EXTERNAL_INLINE void zExtStringArray2D::setItems(zExtStringArray* items, int count)
	{
		//delete pointer;
		//delete pointer;
		pointer = new vector<zStringArray>();
		for (int i = 0; i < count; i++)
		{
			pointer->push_back(*(items[i].pointer));
		}
		updateAttributes();
	}
	// External Methods
	ZSPACE_EXTERNAL_INLINE void ext_string_array2D_getItems(zExtStringArray2D& extArray, zExtStringArray* outArray)
	{
		extArray.getItems(outArray);
	}
	ZSPACE_EXTERNAL_INLINE void ext_string_array2D_setItems(zExtStringArray2D& extArray, zExtStringArray* inArray, int count)
	{
		extArray.setItems(inArray, count);
	}
	//	------------------------------	//
	//	-----	Bool Array 1D	------	//
	//	------------------------------	//
	// Constructor
	ZSPACE_EXTERNAL_INLINE zExtBoolArray::zExtBoolArray()
	{
		//delete pointer;
		pointer = new zBoolArray();
		updateAttributes();
	}
	ZSPACE_EXTERNAL_INLINE zExtBoolArray::zExtBoolArray(zBoolArray a)
	{
		//delete pointer;
		pointer = new zBoolArray(a);
		updateAttributes();
	}
	ZSPACE_EXTERNAL_INLINE zExtBoolArray::zExtBoolArray(zBoolArray* a)
	{
		//delete pointer;
		pointer = a;
		updateAttributes();
	}
	ZSPACE_EXTERNAL_INLINE zExtBoolArray::~zExtBoolArray()
	{
		delete pointer;
		pointer = nullptr;
	}
	// Methods
	ZSPACE_EXTERNAL_INLINE void zExtBoolArray::updateAttributes()
	{
		arrayCount = pointer->size();
	}
	ZSPACE_EXTERNAL_INLINE zStatusCode zExtBoolArray::checkMemAlloc(bool allocateMemory)
	{
		
		try
		{
			if (!pointer || pointer == nullptr)
			{
				if (!allocateMemory) return zMemNotAllocError;
				pointer = new vector<bool>();
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
	ZSPACE_EXTERNAL_INLINE void zExtBoolArray::getItems(bool* items)
	{
		for (int i = 0; i < pointer->size(); i++)
		{
			items[i] = pointer->at(i);
		}
	}
	ZSPACE_EXTERNAL_INLINE void zExtBoolArray::setItems(bool* items, int count)
	{
		//delete pointer;
		pointer = new zBoolArray();
		for (int i = 0; i < count; i++)
		{
			pointer->push_back(items[i]);
		}
		updateAttributes();
	}
	// External Methods
	ZSPACE_EXTERNAL_INLINE void ext_bool_array_getItems(zExtBoolArray& extArray, bool* outArray)
	{
		extArray.getItems(outArray);
	}
	ZSPACE_EXTERNAL_INLINE void ext_bool_setItemsFromArray(zExtBoolArray& extArray, bool* inArray, int count)
	{
		extArray.setItems(inArray, count);
	}

	//	------------------------------	//
	//	-----	Bool Array 2D	------	//
	//	------------------------------	//
	// Constructor
	ZSPACE_EXTERNAL_INLINE zExtBoolArray2D::zExtBoolArray2D()
	{
		//delete pointer;
		pointer = new vector<zBoolArray>();
		updateAttributes();
	}
	ZSPACE_EXTERNAL_INLINE zExtBoolArray2D::zExtBoolArray2D(vector<zBoolArray> a)
	{
		//delete pointer;
		pointer = new vector<zBoolArray>(a);
		updateAttributes();
	}
	ZSPACE_EXTERNAL_INLINE zExtBoolArray2D::zExtBoolArray2D(vector<zBoolArray>* a)
	{
		//delete pointer;
		pointer = a;
		updateAttributes();
	}
	ZSPACE_EXTERNAL_INLINE zExtBoolArray2D::~zExtBoolArray2D()
	{
		delete pointer;
		pointer = nullptr;
	}
	// Methods
	ZSPACE_EXTERNAL_INLINE void zExtBoolArray2D::updateAttributes()
	{
		arrayCount = pointer->size();
	}
	ZSPACE_EXTERNAL_INLINE zStatusCode zExtBoolArray2D::checkMemAlloc(bool allocateMemory)
	{
		
		try
		{
			if (!pointer || pointer == nullptr)
			{
				if (!allocateMemory) return zMemNotAllocError;
				pointer = new vector<zBoolArray>();
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
	ZSPACE_EXTERNAL_INLINE void zExtBoolArray2D::getItems(zExtBoolArray* items)
	{
		for (int i = 0; i < pointer->size(); i++)
		{
			items[i].pointer = &pointer->at(i);
			items[i].updateAttributes();
		}
	}
	ZSPACE_EXTERNAL_INLINE void zExtBoolArray2D::setItems(zExtBoolArray* items, int count)
	{
		//delete pointer;
		pointer = new vector<zBoolArray>();
		for (int i = 0; i < count; i++)
		{
			pointer->push_back(*(items[i].pointer));
		}
		updateAttributes();
	}
	// External Methods
	ZSPACE_EXTERNAL_INLINE void ext_bool_array2D_getItems(zExtBoolArray2D& extArray, zExtBoolArray* outArray)
	{
		extArray.getItems(outArray);
	}
	ZSPACE_EXTERNAL_INLINE void ext_bool_array2D_setItems(zExtBoolArray2D& extArray, zExtBoolArray* inArray, int count)
	{
		extArray.setItems(inArray, count);
	}




	ZSPACE_EXTERNAL_INLINE string ext_string_getItemFromArray(zExtStringArray& extArray, int index)
	{
		return extArray.pointer->at(index);
	}

	ZSPACE_EXTERNAL_INLINE int ext_string_getItemFromArrayCharLength(zExtStringArray& extArray, int index)
	{
		return extArray.pointer->at(index).size();
	}

	ZSPACE_EXTERNAL_INLINE void ext_string_getItemFromArrayChar(zExtStringArray& extArray, int index, char* outString)
	{
		//printf("\n ext_string_getItemFromArrayChar \n");

		for (int i = 0; i < extArray.pointer->at(index).size(); i++)
		{
			//printf("%c", extArray.pointer->at(index).at(i));
			outString[i] = extArray.pointer->at(index).at(i);
		}
	}



}