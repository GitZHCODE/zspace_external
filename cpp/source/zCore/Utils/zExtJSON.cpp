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
#include "headers/zCore/Utils/zExtJSON.h"
//#include"headers/zCore/zExtMesh.h"
namespace zSpace
{
	ZSPACE_EXTERNAL_INLINE zExtJSON::zExtJSON()
	{
		////delete pointer; 
		pointer = new json();
		updateAttributes();
	}
	ZSPACE_EXTERNAL_INLINE zExtJSON::zExtJSON(json j)
	{
		pointer = &j;
		updateAttributes();
	}

	ZSPACE_EXTERNAL_INLINE zExtJSON::zExtJSON(json* j)
	{
		pointer = j;
		updateAttributes();
	}
	ZSPACE_EXTERNAL_INLINE zExtJSON::zExtJSON(const string& filePath)
	{
		//delete pointer;
		pointer = new json();

		//zUtilsCore coreUtils;
		//bool fileChk = coreUtils.readJSON(filePath, *pointer);

		pointer->clear();
		ifstream in_myfile;
		in_myfile.open(filePath.c_str());

		int lineCnt = 0;

		if (in_myfile.fail())
		{
			cout << " error in opening file  " << filePath.c_str() << endl;
			//return false;
		}

		in_myfile >> *pointer;
		in_myfile.close();

		updateAttributes();
	}
	ZSPACE_EXTERNAL_INLINE zExtJSON::~zExtJSON()
	{
		delete pointer;
		pointer = nullptr;
	}
	ZSPACE_EXTERNAL_INLINE zStatusCode zExtJSON::checkMemAlloc(bool allocateMemory)
	{
		try
		{
			if (!pointer || pointer == nullptr)
			{
				if (!allocateMemory) return zMemNotAllocError;
				pointer = new json();
				return zMemAllocSuccess;
			}
			else
			{
				return zSkip;
			}
		}
		catch (const std::exception&)
		{
			return zMemNotAllocError;
		}
	}
	ZSPACE_EXTERNAL_INLINE void zExtJSON::updateAttributes()
	{

		numOfAttributes = pointer->size();
		//pointer->array(); //in case of multiple levels
		//attributesNames = zExtStringArray(GetAllAttributeNames());
		attributesNames.pointer = new zStringArray(GetAllAttributeNames());

		attributesNames.updateAttributes();
		// = zExtStringArray(GetAllAttributeNames());

		attributesTypes.pointer = new zStringArray(GetAllAttributeTypes());// = zExtStringArray(GetAllAttributeNames());
		attributesTypes.updateAttributes();
		//attributesTypes = zExtStringArray(GetAllAttributeTypes());
		/*for (int i = 0; i < attributesNames.arrayCount; i++)
		{
			printf("\n name %s ", attributesNames.pointer->at(i).c_str());
			printf("\n key %s ", attributesTypes.pointer->at(i).c_str());
		}*/
	}
	ZSPACE_EXTERNAL_INLINE zStringArray zExtJSON::GetAllAttributeNames()
	{
		zStringArray names;
		names.clear();
		//names.assign()
		for (auto& element : pointer->items())
		{
			const auto& key = element.key();
			string k = element.key();
			//names.push_back(element.key().c_str());
			names.push_back(k);
			//printf("\n name %s ", element.key().c_str());

			//const auto& value = element.value();

			//std::cout << "Attribute: " << key << ", Value: " << value << std::endl;
		}

		/*for (auto it = pointer->begin(); it != pointer->end(); ++it)
		{
			names.push_back(it.key());
			printf("\n name %s ", it.key());
		}*/
		return names;
	}

	ZSPACE_EXTERNAL_INLINE zStringArray zExtJSON::GetAllAttributeTypes()
	{
		zStringArray types;
		types.clear();

		for (auto& it : pointer->items())
		{
			string type = "";
			try
			{
				if (!it.value().is_null())
				{
					
					if (!it.value().is_array())
					{
						auto v = it.value();
						if (v.is_number_integer()) type = "int";
						else if (v.is_number_float()) type = "float";
						else if (v.is_boolean()) type = "bool";
						else if (v.is_string()) type = "string";
					}
					else if (it.value().is_array() && it.value().size() > 0)
					{
						auto v = it.value()[0];
						if (v.is_number_integer()) type = "int[]";
						else if (v.is_number_float()) type = "float[]";
						else if (v.is_boolean()) type = "bool[]";
						else if (v.is_string()) type = "string[]";
					}
					else if (it.value().is_array() && it.value().size() > 0 && it.value()[0].is_array() && it.value()[0].size() > 0)
					{
						auto v = it.value()[0][0];
						if (v.is_number_integer()) type = "int[][]";
						else if (v.is_number_float()) type = "float[][]";
						else if (v.is_boolean()) type = "bool[][]";
						else if (v.is_string()) type = "string[][]";
					}
					


					////int
					//if (it.value().is_number_integer())
					//	type = "int";
					//else if (it.value().is_array() && it.value().size() > 0 && it.value()[0].is_number_integer())
					//	type = "int[]";
					//else if (it.value().is_array() && it.value().size() > 0 && it.value()[0].is_array() && it.value()[0].size() > 0 && it.value()[0][0].is_number_integer())
					//	type = "int[][]";
					////float
					//else if (it.value().is_number_float())
					//	type = "float";
					//else if (it.value().is_array() && it.value().size() > 0 && it.value()[0].is_number_float())
					//	type = "float[]";
					//else if (it.value().is_array() && it.value().size() > 0 && it.value()[0].is_array() && it.value()[0].size() > 0 && it.value()[0][0].is_number_float())
					//	type = "float[][]";
					//else if (it.value().is_array() && it.value().size() > 0 && it.value()[0].is_array() && it.value()[0].size() > 0 && it.value()[0][0].is_array(), it.value()[0][0][0].is_number_float())
					//	type = "zExtJSON";
					////bool
					//else if (it.value().is_boolean())
					//	type = "bool";
					//else if (it.value().is_array() && it.value().size() > 0 && it.value()[0].is_boolean())
					//{
					//	printf("\n \n IT is is_boolean %d ", it.value()[0].is_boolean());

					//	type = "bool[]";
					//}
					//else if (it.value().is_array() && it.value().size() > 0 && it.value()[0].is_array() && it.value()[0].size() > 0 && it.value()[0][0].is_boolean())
					//	type = "bool[][]";
					////string
					//else if (it.value().is_string())
					//	type = "string";
					//else if (it.value().is_array(), it.value()[0].is_string())
					//	type = "string[]";
					//else if (it.value().is_array() && it.value().size() > 0 && it.value()[0].is_array())
					//	type = "string[][]";
				}
			}
			catch (const json::exception&)
			{
				//type = "TYPE UNIDENTIFIED";
				type = "string";

			}

			//printf("\n item key and type %s - %s", it.key().c_str(), type);
			types.push_back(type);
		}


		//for (auto it = pointer->begin(); it != pointer->end(); ++it)
		//{
		//	try
		//	{
		//		if (!it.value().is_null())
		//		{
		//			//int
		//			if (it.value().is_number_integer())
		//				types.push_back("int");
		//			else if (it.value().is_array() && it.value().size() > 0 && it.value()[0].is_number_integer())
		//				types.push_back("int[]");
		//			else if (it.value().is_array() && it.value().size() > 0 && it.value()[0].is_array() && it.value()[0].size() > 0 && it.value()[0][0].is_number_integer())
		//				types.push_back("int[][]");
		//			//float
		//			else if (it.value().is_number_float())
		//				types.push_back("float");
		//			else if (it.value().is_array() && it.value().size() > 0 && it.value()[0].is_number_float())
		//				types.push_back("float[]");
		//			else if (it.value().is_array() && it.value().size() > 0 && it.value()[0].is_array() && it.value()[0].size() > 0 && it.value()[0][0].is_number_float())
		//				types.push_back("float[][]");
		//			//bool
		//			else if (it.value().is_boolean())
		//				types.push_back("bool");
		//			else if (it.value().is_array() && it.value().size() > 0 && it.value()[0].is_boolean())
		//				types.push_back("bool[]");
		//			else if (it.value().is_array() && it.value().size() > 0 && it.value()[0].is_array() && it.value()[0].size() > 0 && it.value()[0][0].is_boolean())
		//				types.push_back("bool[][]");
		//			//string
		//			else if (it.value().is_string())
		//				types.push_back("string");
		//			else if (it.value().is_array())
		//				types.push_back("string[]");
		//			else if (it.value().is_array() && it.value().size() > 0 && it.value()[0].is_array())
		//				types.push_back("string[][]");
		//		}
		//	}
		//	catch (const json::exception&)
		//	{
		//		types.push_back("TYPE UNIDENTIFIED");
		//	}
		//}
		

		
		return types;
	}
	ZSPACE_EXTERNAL_INLINE void zExtJSON::AddAttribute(const string& attributeName, const json& attributeValue)
	{
		//printf("\n cpp add atribute");
		zUtilsCore core;
		//json j = *pointer;
		//try
		//{
		//	/*outAttributeValue.checkMemAlloc(true);
		//	core.json_readAttribute(j, attributeKeySt, *outAttributeValue.pointer);
		//	outAttributeValue.updateAttributes();*/
		//	return 1;
		//}

		core.json_writeAttribute(*pointer, attributeName, attributeValue);

		//(*pointer)[attributeName] = attributeValue;
		
		
	}
	ZSPACE_EXTERNAL_INLINE bool zExtJSON::ExportJsonFile(const string& filePath)
	{
		try
		{
			// Write the JSON object to the file
			ofstream file(filePath);
			file << pointer->dump(4); // Write formatted JSON with indentation of 4 spaces
			file.close();
			printf("\n json file exported successfully");
			return true;
		}
		catch (const std::exception&) { return false; }
		
	}
	ZSPACE_EXTERNAL_INLINE bool zExtJSON::UpdateJsonFile(const string& filePath, const string& attributeName, const json& attributeValue)
	{
		// Check if the file exists
		ifstream file(filePath);
		if (!file)
		{
			cerr << "JSON file does not exist: " << filePath << endl;
			return false; 
		}
		file.close();
		// Read the existing JSON file
		json data;
		try
		{
			ifstream inputFile(filePath);
			inputFile >> data;
			inputFile.close();
		}
		catch (const json::parse_error& e)
		{
			cerr << "Failed to parse JSON file: " << filePath << "\n";
			cerr << "Parse error: " << e.what() << endl;
			return false; 
		}
		// Add attributes to the JSON object
		data[attributeName] = attributeValue;
		// Write the updated JSON object back to the file
		ofstream outFile(filePath);
		if (!outFile)
		{
			cerr << "Failed to write to JSON file: " << filePath << endl;
			return false; 
		}
		outFile << setw(4) << data;
		outFile.close();
		return true; 
	}

	ZSPACE_EXTERNAL_INLINE bool zExtJSON::ReadJsonFile(const string& filePath)
	{
		//printf("\n read json 0");
		zUtilsCore coreUtils;
		bool fileChk = coreUtils.json_read(filePath, *pointer);
		//printf("\n read json 1");

		if(fileChk) updateAttributes();
		//printf("\n read json 2");

		return fileChk;
	}



	// JSON - Read Attributes
	ZSPACE_EXTERNAL_INLINE int ext_json_readJSONAttributeInt			(zExtJSON& extJSON, char* attributeKey, int& outAttributeValue)
	{
		zStatusCode memoryChk = extJSON.checkMemAlloc(false);
		if (memoryChk == zMemNotAllocError) return zMemNotAllocError;

		string attributeKeySt(attributeKey);
		zUtilsCore core;
		json j = *extJSON.pointer;
		try
		{
			outAttributeValue = j[attributeKeySt].get<int>();
			return 1;
		}
		catch (const exception&) { return 0; }
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_readJSONAttributeIntArray		(zExtJSON& extJSON, char* attributeKey, zExtIntArray& outAttributeValue)
	{
		zStatusCode memoryChk = extJSON.checkMemAlloc(false);
		printf("\n memChk JSON ");
		if (memoryChk == zMemNotAllocError) return zMemNotAllocError;
		printf("\n memChk JSON 2 ");

		string attributeKeySt(attributeKey);
		zUtilsCore core;
		json j = *extJSON.pointer;

		try
		{
			outAttributeValue.checkMemAlloc(true);
			core.json_readAttribute(j, attributeKeySt, *outAttributeValue.pointer);
			outAttributeValue.updateAttributes();

			return 1;
		}
		catch (const exception&) { return 0; }
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_readJSONAttributeIntArray2D		(zExtJSON& extJSON, char* attributeKey, zExtIntArray2D& outAttributeValue)
	{
		zStatusCode memoryChk = extJSON.checkMemAlloc(false);
		if (memoryChk == zMemNotAllocError) return zMemNotAllocError;

		string attributeKeySt(attributeKey);
		zUtilsCore core;
		json j = *extJSON.pointer;
		try
		{
			outAttributeValue.checkMemAlloc(true);
			core.json_readAttribute(j, attributeKeySt, *outAttributeValue.pointer);
			outAttributeValue.updateAttributes();
			return 1;
		}
		catch (const exception&) { return 0; };
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_readJSONAttributeFloat			(zExtJSON& extJSON, char* attributeKey, float& outAttributeValue)
	{
		zStatusCode memoryChk = extJSON.checkMemAlloc(false);
		if (memoryChk == zMemNotAllocError) return zMemNotAllocError;

		string attributeKeySt(attributeKey);
		zUtilsCore core;
		json j = *extJSON.pointer;
			try
			{
				core.json_readAttribute(j, attributeKeySt, outAttributeValue);
				return 1;
			}
			catch (const exception&) { return 0; };
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_readJSONAttributeFloatArray		(zExtJSON& extJSON, char* attributeKey, zExtFloatArray& outAttributeValue)
	{
		zStatusCode memoryChk = extJSON.checkMemAlloc(false);
		if (memoryChk == zMemNotAllocError) return zMemNotAllocError;

		printf("\n ext_json_readJSONAttributeFloatArray 0");
		string attributeKeySt(attributeKey);
		zUtilsCore core;
		json j = *extJSON.pointer;
			try
			{
				//zFloatArray arr;
				//outAttributeValue = zExtFloatArray();
				outAttributeValue.checkMemAlloc(true);

				core.json_readAttribute(j, attributeKeySt, *outAttributeValue.pointer);
				//core.json_readAttribute(j, attributeKeySt, arr);

				outAttributeValue.updateAttributes();

				printf("\n float[] %i %i %f", outAttributeValue.pointer->size(), outAttributeValue.arrayCount, outAttributeValue.pointer->at(0));
				//printf("\n 2float[] %i %f", arr.size(), arr[0]);

				return 1;
			}
			catch (const exception&) { return 0; };
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_readJSONAttributeFloatArray2D	(zExtJSON& extJSON, char* attributeKey, zExtFloatArray2D& outAttributeValue)
	{
		zStatusCode memoryChk = extJSON.checkMemAlloc(false);
		if (memoryChk == zMemNotAllocError) return zMemNotAllocError;

		string attributeKeySt(attributeKey);
		zUtilsCore core;
		json j = *extJSON.pointer;
			try
			{
				outAttributeValue.checkMemAlloc(true);
				core.json_readAttribute(j, attributeKeySt, *outAttributeValue.pointer);
				outAttributeValue.updateAttributes();
				return 1;
			}
			catch (const exception&) { return 0; };
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_readJSONAttributeDouble			(zExtJSON& extJSON, char* attributeKey, double& outAttributeValue)
	{
		zStatusCode memoryChk = extJSON.checkMemAlloc(false);
		if (memoryChk == zMemNotAllocError) return zMemNotAllocError;

		string attributeKeySt(attributeKey);
		zUtilsCore core;
		json j = *extJSON.pointer;
		try
		{
			core.json_readAttribute(j, attributeKeySt, outAttributeValue);
			return 1;
		}
		catch (const exception&) { return 0; };
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_readJSONAttributeDoubleArray	(zExtJSON& extJSON, char* attributeKey, zExtDoubleArray& outAttributeValue)
	{
		zStatusCode memoryChk = extJSON.checkMemAlloc(false);
		if (memoryChk == zMemNotAllocError) return zMemNotAllocError;

		string attributeKeySt(attributeKey);
		zUtilsCore core;
		json j = *extJSON.pointer;
		try
		{
			outAttributeValue.checkMemAlloc(true);
			core.json_readAttribute(j, attributeKeySt, *outAttributeValue.pointer);
			outAttributeValue.updateAttributes();
			return 1;
		}
		catch (const exception&) { return 0; };
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_readJSONAttributeDoubleArray2D	(zExtJSON& extJSON, char* attributeKey, zExtDoubleArray2D& outAttributeValue)
	{
		zStatusCode memoryChk = extJSON.checkMemAlloc(false);
		if (memoryChk == zMemNotAllocError) return zMemNotAllocError;

		string attributeKeySt(attributeKey);
		zUtilsCore core;
		json j = *extJSON.pointer;
		try
		{
			outAttributeValue.checkMemAlloc(true);
			core.json_readAttribute(j, attributeKeySt, *outAttributeValue.pointer);
			outAttributeValue.updateAttributes();
			return 1;
		}
		catch (const exception&) { return 0; };
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_readJSONAttributeString			(zExtJSON& extJSON, char* attributeKey, zExtString& outAttributeValue)
	{
		zStatusCode memoryChk = extJSON.checkMemAlloc(false);
		if (memoryChk == zMemNotAllocError) return zMemNotAllocError;

		string attributeKeySt(attributeKey);
		zUtilsCore core;
		json j = *extJSON.pointer;
			try
			{
				outAttributeValue.checkMemAlloc(true);
				core.json_readAttribute(j, attributeKeySt, *outAttributeValue.pointer);
				outAttributeValue.updateAttributes();
				//outAttributeValue = zExtString();
				////string st = j[attributeKeySt].get<string>();
				//outAttributeValue.pointer = new string(j[attributeKeySt].get<string>());
				////outAttributeValue.pointer = new string(st);
				////*outAttributeValue.pointer = j[attributeKeySt].get<string>();
				//outAttributeValue.updateAttributes();
				///*for (int i = 0; i < st.empty(); i++)
				//{
				//	outAttributeValue[i] = st[i];
				//}*/
				////outAttributeValue = j[attributeKeySt].get<string>().c_str();
				return 1;
			}
			catch (const exception& ){ return 0; }
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_readJSONAttributeStringArray	(zExtJSON& extJSON, char* attributeKey, zExtStringArray& outAttributeValue)
	{
		zStatusCode memoryChk = extJSON.checkMemAlloc(false);
		if (memoryChk == zMemNotAllocError) return zMemNotAllocError;
		string attributeKeySt(attributeKey);
		zUtilsCore core;
		json j = *extJSON.pointer;
			try
			{
				outAttributeValue.checkMemAlloc(true);
				core.json_readAttribute(j, attributeKeySt, *outAttributeValue.pointer);
				outAttributeValue.updateAttributes();
				return 1;
			}
			catch (const exception&) { return 0; };
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_readJSONAttributeStringArray2D	(zExtJSON& extJSON, char* attributeKey, zExtStringArray2D& outAttributeValue)
	{
		zStatusCode memoryChk = extJSON.checkMemAlloc(false);
		if (memoryChk == zMemNotAllocError) return zMemNotAllocError;
		string attributeKeySt(attributeKey);
		zUtilsCore core;
		json j = *extJSON.pointer;
		try
		{
			outAttributeValue.checkMemAlloc(true);
			core.json_readAttribute(j, attributeKeySt, *outAttributeValue.pointer);
			outAttributeValue.updateAttributes();
			return 1;
		}
		catch (const exception&) { return 0; };
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_readJSONAttributeBool			(zExtJSON& extJSON, char* attributeKey, bool& outAttributeValue)
	{
		zStatusCode memoryChk = extJSON.checkMemAlloc(false);
		if (memoryChk == zMemNotAllocError) return zMemNotAllocError;
		string attributeKeySt(attributeKey);
		zUtilsCore core;
		json j = *extJSON.pointer;
		try
		{
			//outAttributeValue = j[attributeKeySt].get<bool>();

			core.json_readAttribute(j, attributeKeySt, outAttributeValue);

			return 1;
		}
		catch (const exception&) { return 0; }
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_readJSONAttributeBoolArray		(zExtJSON& extJSON, char* attributeKey, zExtBoolArray& outAttributeValue)
	{
		zStatusCode memoryChk = extJSON.checkMemAlloc(false);
		if (memoryChk == zMemNotAllocError) return zMemNotAllocError;
		string attributeKeySt(attributeKey);
		zUtilsCore core;
		json j = *extJSON.pointer;
		try
		{
			outAttributeValue.checkMemAlloc(true);
			core.json_readAttribute(j, attributeKeySt, *outAttributeValue.pointer);
			outAttributeValue.updateAttributes();
			return 1;
		}
		catch (const exception&) { return 0; };
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_readJSONAttributeBoolArray2D	(zExtJSON& extJSON, char* attributeKey, zExtBoolArray2D& outAttributeValue)
	{
		zStatusCode memoryChk = extJSON.checkMemAlloc(false);
		if (memoryChk == zMemNotAllocError) return zMemNotAllocError;
		string attributeKeySt(attributeKey);
		zUtilsCore core;
		json j = *extJSON.pointer;
		try
		{
			outAttributeValue.checkMemAlloc(true);
			core.json_readAttribute(j, attributeKeySt, *outAttributeValue.pointer);
			outAttributeValue.updateAttributes();
			return 1;
		}
		catch (const exception&) { return 0; };
	}
	// JSON - Write Attributes
	ZSPACE_EXTERNAL_INLINE int ext_json_writeJSONAttributeInt			(zExtJSON& extJSON, char* attributeKey, int inAttributeValue,					bool updateExtAttributes)
	{
		printf("\n cpp json write int");
		try
		{
			extJSON.checkMemAlloc(true);

			extJSON.AddAttribute(attributeKey, inAttributeValue);
			if(updateExtAttributes) extJSON.updateAttributes();
			return 1;
		}
		catch (const exception&) { return 0; };
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_writeJSONAttributeIntArray		(zExtJSON& extJSON, char* attributeKey, zExtIntArray& inAttributeValue,			bool updateExtAttributes)
	{

		try
		{
			extJSON.checkMemAlloc(true);

			extJSON.AddAttribute(attributeKey, *inAttributeValue.pointer);
			if (updateExtAttributes) extJSON.updateAttributes();
			return 1;
		}
		catch (const exception&) { return 0; };
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_writeJSONAttributeIntArray2D	(zExtJSON& extJSON, char* attributeKey, zExtIntArray2D& inAttributeValue,		bool updateExtAttributes)
	{
		try
		{
			extJSON.checkMemAlloc(true);

			extJSON.AddAttribute(attributeKey, *inAttributeValue.pointer);
			if (updateExtAttributes) extJSON.updateAttributes();
			return 1;
		}
		catch (const exception&) { return 0; };
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_writeJSONAttributeFloat			(zExtJSON& extJSON, char* attributeKey, float inAttributeValue,					bool updateExtAttributes)
	{
		try
		{
			extJSON.checkMemAlloc(true);

			extJSON.AddAttribute(attributeKey, inAttributeValue);
			if (updateExtAttributes) extJSON.updateAttributes();
			return 1;
		}
		catch (const exception&) { return 0; };
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_writeJSONAttributeFloatArray	(zExtJSON& extJSON, char* attributeKey, zExtFloatArray& inAttributeValue,		bool updateExtAttributes)
	{
		try
		{
			extJSON.checkMemAlloc(true);

			extJSON.AddAttribute(attributeKey, *inAttributeValue.pointer);
			if (updateExtAttributes) extJSON.updateAttributes();
			return 1;
		}
		catch (const exception&) { return 0; };
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_writeJSONAttributeFloatArray2D	(zExtJSON& extJSON, char* attributeKey, zExtFloatArray2D& inAttributeValue,		bool updateExtAttributes)
	{
		try
		{
			extJSON.checkMemAlloc(true);

			extJSON.AddAttribute(attributeKey, *inAttributeValue.pointer);
			if (updateExtAttributes) extJSON.updateAttributes();
			return 1;
		}
		catch (const exception&) { return 0; };
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_writeJSONAttributeDouble		(zExtJSON& extJSON, char* attributeKey, double inAttributeValue,				bool updateExtAttributes)
	{
		try
		{
			extJSON.checkMemAlloc(true);

			extJSON.AddAttribute(attributeKey, inAttributeValue);
			if (updateExtAttributes) extJSON.updateAttributes();
			return 1;
		}
		catch (const exception&) { return 0; };
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_writeJSONAttributeDoubleArray	(zExtJSON& extJSON, char* attributeKey, zExtDoubleArray& inAttributeValue,		bool updateExtAttributes)
	{
		try
		{
			extJSON.checkMemAlloc(true);

			extJSON.AddAttribute(attributeKey, *inAttributeValue.pointer);
			if (updateExtAttributes) extJSON.updateAttributes();
			return 1;
		}
		catch (const exception&) { return 0; };
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_writeJSONAttributeDoubleArray2D	(zExtJSON& extJSON, char* attributeKey, zExtDoubleArray2D& inAttributeValue,	bool updateExtAttributes)
	{
		try
		{
			extJSON.checkMemAlloc(true);

			extJSON.AddAttribute(attributeKey, *inAttributeValue.pointer);
			if (updateExtAttributes) extJSON.updateAttributes();
			return 1;
		}
		catch (const exception&) { return 0; };
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_writeJSONAttributeString		(zExtJSON& extJSON, char* attributeKey, char* inAttributeValue,					bool updateExtAttributes)
	{
		try
		{
			string val(inAttributeValue);
			string key(attributeKey);
			extJSON.checkMemAlloc(true);
			//extJSON.AddAttribute(attributeKey, inAttributeValue);
			//extJSON.AddAttribute(attributeKey, val);
			//(*extJSON.pointer)[key] = val;
			//printf("\n write string %s", val);
			(*extJSON.pointer)[attributeKey] = inAttributeValue;
			//(*extJSON.pointer)[key] = val;
			//(*extJSON.pointer)["ttt"] = "vvv";
			
			if (updateExtAttributes) extJSON.updateAttributes();
			return 1;
		}
		catch (const exception&) { return 0; };
	}
	//ZSPACE_EXTERNAL_INLINE int ext_json_writeJSONAttributeString		(zExtJSON& extJSON, char* attributeKey, zExtString inAttributeValue,			bool updateExtAttributes)
	//{
	//	try
	//	{
	//		//string val(inAttributeValue);
	//		extJSON.checkMemAlloc(true);
	//		//extJSON.AddAttribute(attributeKey, inAttributeValue);
	//		printf("\n c++ write string");
	//		cout << *inAttributeValue.pointer;
	//		extJSON.AddAttribute(attributeKey, *inAttributeValue.pointer);
	//		if (updateExtAttributes) extJSON.updateAttributes();
	//		return 1;
	//	}
	//	catch (const exception&) { return 0; };
	//}
	ZSPACE_EXTERNAL_INLINE int ext_json_writeJSONAttributeStringArray	(zExtJSON& extJSON, char* attributeKey, zExtStringArray& inAttributeValue,		bool updateExtAttributes)
	{
		try
		{
			//printf("\n stringArray 0");
			zStatus memoryChk = inAttributeValue.checkMemAlloc(false);
			if (memoryChk == zMemNotAllocError) return zMemNotAllocError;
			//printf("\n stringArray 1");


			extJSON.checkMemAlloc(true);
			//printf("\n stringArray 2 %i", inAttributeValue.arrayCount);

			extJSON.AddAttribute(attributeKey, *inAttributeValue.pointer);
			//printf("\n stringArray 3");

			if (updateExtAttributes) extJSON.updateAttributes();
			return 1;
		}
		catch (const exception&) { return 0; };
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_writeJSONAttributeStringArray2D	(zExtJSON& extJSON, char* attributeKey, zExtStringArray2D& inAttributeValue,	bool updateExtAttributes)
	{
		try
		{
			extJSON.checkMemAlloc(true);

			extJSON.AddAttribute(attributeKey, *inAttributeValue.pointer);
			if (updateExtAttributes) extJSON.updateAttributes();
			return 1;
		}
		catch (const exception&) { return 0; };
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_writeJSONAttributeBool			(zExtJSON& extJSON, char* attributeKey, bool inAttributeValue,					bool updateExtAttributes)
	{
		try
		{
			extJSON.checkMemAlloc(true);

			extJSON.AddAttribute(attributeKey, inAttributeValue);
			if (updateExtAttributes) extJSON.updateAttributes();
			return 1;
		}
		catch (const exception&) { return 0; };
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_writeJSONAttributeBoolArray		(zExtJSON& extJSON, char* attributeKey, zExtBoolArray& inAttributeValue,		bool updateExtAttributes)
	{
		try
		{
			extJSON.checkMemAlloc(true);

			extJSON.AddAttribute(attributeKey, *inAttributeValue.pointer);
			if (updateExtAttributes) extJSON.updateAttributes();
			return 1;
		}
		catch (const exception&) { return 0; };
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_writeJSONAttributeBoolArray2D	(zExtJSON& extJSON, char* attributeKey, zExtBoolArray2D& inAttributeValue,		bool updateExtAttributes)
	{
		try
		{
			extJSON.checkMemAlloc(true);

			extJSON.AddAttribute(attributeKey, *inAttributeValue.pointer);
			if (updateExtAttributes) extJSON.updateAttributes();
			return 1;
		}
		catch (const exception&) { return 0; };
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_writeJSONAttributeJSON			(zExtJSON& extJSON, char* attributeKey, zExtJSON& inAttributeValue, bool updateExtAttributes)
	{
		try
		{
			extJSON.checkMemAlloc(true);

			extJSON.AddAttribute(attributeKey, *inAttributeValue.pointer);
			//zUtilsCore util;
			//util.writeJSONAttribute(*extJSON.pointer, attributeKey, *inAttributeValue.pointer);
			//extJSON.AddAttribute(attributeKey, inAttributeValue.pointer);
			if (updateExtAttributes) extJSON.updateAttributes();
			return 1;
		}
		catch (const exception&) { return 0; };
	}

	ZSPACE_EXTERNAL int ext_json_AppendJSONAttributeJSON(zExtJSON& extJSON, char* attributeKey, zExtJSON& inAttributeValue, bool includeSubKeys, bool updateExtAttributes)
	{
		try	{
			extJSON.checkMemAlloc(true);
			zStatus memChk = inAttributeValue.checkMemAlloc(false);
			if (memChk == zMemNotAllocError) return 0;

			string attributeName(attributeKey);
			//(*extJSON.pointer)[attributeName].insert((*inAttributeValue.pointer).end(), *inAttributeValue.pointer);
			if (includeSubKeys)
			{
				(*extJSON.pointer)[attributeName].push_back(*inAttributeValue.pointer);
			}
			else
			{
				zStringArray attNames = inAttributeValue.GetAllAttributeNames();
				for (int i = 0; i < attNames.size(); i++)
				{
					(*extJSON.pointer)[attributeName].push_back((*inAttributeValue.pointer)[attNames[i]]);
				}
			}

			if (updateExtAttributes) extJSON.updateAttributes();
			return 1;
		}
		catch (const exception&) { return 0; };
	}

	// JSON - Write Attributes Generic - TRIAL

	
	ZSPACE_EXTERNAL_INLINE void ext_json_createJson(zExtJSON& extJSON)
	{
		//extJSON.pointer = new json();// = zExtJSON();
		extJSON.checkMemAlloc(true);
		extJSON.updateAttributes();

	}
	ZSPACE_EXTERNAL_INLINE void ext_json_createJsonDeepCopy(zExtJSON& inJSON, zExtJSON& outJSON)
	{
		outJSON.pointer = new json(static_cast<const json&>(*inJSON.pointer));
		inJSON.updateAttributes();
		outJSON.updateAttributes();
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_readJsonFile(zExtJSON& extJSON, char* inputPath)
	{
		try
		{
			extJSON.checkMemAlloc(true);
			string pathSt(inputPath);
			extJSON.ReadJsonFile(pathSt); 	
			extJSON.updateAttributes();
			//for (auto& element : extJSON.pointer->items())
			//{
			//	const auto& key = element.key();
			//	string k = element.key();
			//	//printf("\n %s", k.c_str());

			//}
			return 1;
		}
	catch (const exception&) { return 0; }
	}
	//ZSPACE_EXTERNAL_INLINE int ext_json_getMeshFromJson(zExtJSON& extJSON, zExtMesh& outMesh)
	//{
	//	//outMesh = zExtMesh();
	//	//zObjMesh m = (extJSON.readMeshFromJson());
	//	printf("\n ext_json_getMeshFromJson 0");
	//	zFnMesh fn(*outMesh.pointer);
	//	fn.from(*extJSON.pointer);
	//	outMesh.updateAttributes();
	//	//outMesh.createMeshFromJson(extJSON.pointer);
	//	//*outMesh.mesh = (extJSON.readMeshFromJson());
	//	printf("\n ext_json_getMeshFromJson 1");
	//	//outMesh.updateAttributes();
	//	printf("\n ext_json_getMeshFromJson 2");
	//	//try
	//	//{
	//	//	printf("\n ext_json_getMeshFromJson 0");
	//	//	for (auto& element : extJSON.pointer->items())
	//	//	{
	//	//		const auto& key = element.key();
	//	//		string k = element.key();
	//	//		printf("\n %s", k.c_str());

	//	//	}
	//	//	outMesh = zExtMesh();
	//	//	printf("\n ext_json_getMeshFromJson 1");

	//	//	//bool chk = extJSON.readMeshFromJson(*outMesh.mesh);
	//	//	zObjMesh m = (extJSON.readMeshFromJson());
	//	//	//bool chk = extJSON.readMeshFromJson(*outMesh.mesh);
	//	//	printf("\n ext_json_getMeshFromJson 2");

	//	//	outMesh.updateAttributes();
	//	//	printf("\n ext_json_getMeshFromJson 3");

	//	//	return 1;
	//	//}
	//	//catch (const std::exception&)
	//	//{
	//	//	return 0;
	//	//}
	//	return 1;
	//}
	//ZSPACE_EXTERNAL_INLINE int ext_json_getMeshFromJsonPath(char* path, zExtMesh& outMesh)
	//{
	//	try
	//	{
	//		printf("\n ext_json_getMeshFromJsonPath 0");
	//		outMesh.pointer = new zObjMesh();
	//		printf("\n ext_json_getMeshFromJsonPath 1");

	//		string pathst(path);
	//		printf("\n ext_json_getMeshFromJsonPath 2");

	//		//outMesh.createMeshFromJson(pathst);
	//		zFnMesh fn(*outMesh.pointer);
	//		fn.from(pathst, zJSON);

	//		outMesh.updateAttributes();


	//		//printf("\n ext_json_getMeshFromJsonPath 3");

	//		return 1;
	//	}
	//	catch (const std::exception&)
	//	{
	//		return 0;
	//	}
	//}
	//ZSPACE_EXTERNAL_INLINE int ext_json_setMeshToJson(zExtJSON& extJSON, zExtMesh& inMesh)
	//{
	//	try
	//	{
	//		bool chk = extJSON.writeMeshToJson(*inMesh.pointer);
	//		extJSON.updateAttributes();
	//		return chk;
	//	}
	//	catch (const std::exception&)
	//	{
	//		return 0;
	//	}
	//}
	ZSPACE_EXTERNAL_INLINE int ext_json_exportFile(zExtJSON& extJSON, char* filePath)
	{
		string filePathSt(filePath);
		try
		{
			zStatusCode memoryChk = extJSON.checkMemAlloc(false);
			if (memoryChk == zMemNotAllocError) return zMemNotAllocError;

			extJSON.ExportJsonFile(filePathSt);
			return 1;
		}
		catch (const exception&) { return 0; }
	}

	/*ZSPACE_EXTERNAL_INLINE int ext_json_readFile(char* filePath, zExtJSON& outExtJSON)
	{
		string filePathSt(filePath);
		try
		{
			std::ifstream file(filePath);
			json data;
			file >> data;
			file.close();

			outExtJSON = zExtJSON(data);
		}
		catch (const exception&) { return 0; }
	}*/

}
