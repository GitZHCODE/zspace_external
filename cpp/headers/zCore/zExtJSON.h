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

#ifndef ZSPACE_EXT_CORE_JSON_H
#define ZSPACE_EXT_CORE_JSON_H



#pragma once


#include <headers/base/zSpace_External.h>
#include<headers/zCore/zExtUtilsCore.h>
#include<headers/zCore/zExtMesh.h>
#include <headers/zCore/zCore.h>
#include <headers/zCore/utilities/zUtilsCore.h>



#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>

#include<execution>

using namespace std;

namespace zSpace
{
	struct zExtJSON
	{
		json* pointer;
		int numOfAttributes;
		zExtStringArray attributesNames;
		zExtStringArray attributesTypes;

		zExtJSON();
		zExtJSON(json j);
		zExtJSON(json* j);
		zExtJSON(const string& filePath);

		~zExtJSON();

		void updateAttributes();
		zStringArray GetAllAttributeTypes();
		zStringArray GetAllAttributeNames();
		void AddAttribute(const string& attributeName, const json& attributeValue);
		bool ExportJsonFile(const string& filePath);
		bool UpdateJsonFile(const string& filePath, const string& attributeName, const json& attributeValue);
		bool ReadJsonFile(const string& filePath);
		zObjMesh readMeshFromJson();
		bool readMeshFromJson(zObjMesh& outMesh);
		bool writeMeshToJson(zObjMesh& inMesh);
		static bool MeshtoJSON(zObjMesh& inMesh, json& jsonObj);
		 bool MeshFromJSON(zObjMesh& outMesh);
	};

	ZSPACE_EXTERNAL_C
	{
		//--------------------------
		//---- JSON methods
		//--------------------------



		ZSPACE_EXTERNAL int ext_json_readJSONAttributeJSON			(zExtJSON& extJSON, char* attributeKey, zExtJSON& outAttributeValue);
		ZSPACE_EXTERNAL int ext_json_readJSONAttributeInt			(zExtJSON& extJSON, char* attributeKey, int& outAttributeValue);
		ZSPACE_EXTERNAL int ext_json_readJSONAttributeIntArray		(zExtJSON& extJSON, char* attributeKey, zExtIntArray& outAttributeValue);
		ZSPACE_EXTERNAL int ext_json_readJSONAttributeIntArray2D	(zExtJSON& extJSON, char* attributeKey, zExtIntArray2D& outAttributeValue);
		ZSPACE_EXTERNAL int ext_json_readJSONAttributeFloat			(zExtJSON& extJSON, char* attributeKey, float& outAttributeValue);
		ZSPACE_EXTERNAL int ext_json_readJSONAttributeFloatArray	(zExtJSON& extJSON, char* attributeKey, zExtFloatArray& outAttributeValue);
		ZSPACE_EXTERNAL int ext_json_readJSONAttributeFloatArray2D	(zExtJSON& extJSON, char* attributeKey, zExtFloatArray2D& outAttributeValue);
		ZSPACE_EXTERNAL int ext_json_readJSONAttributeDouble		(zExtJSON& extJSON, char* attributeKey, double& outAttributeValue);
		ZSPACE_EXTERNAL int ext_json_readJSONAttributeDoubleArray	(zExtJSON& extJSON, char* attributeKey, zExtDoubleArray& outAttributeValue);
		ZSPACE_EXTERNAL int ext_json_readJSONAttributeDoubleArray2D	(zExtJSON& extJSON, char* attributeKey, zExtDoubleArray2D& outAttributeValue);
		ZSPACE_EXTERNAL int ext_json_readJSONAttributeString		(zExtJSON& extJSON, char* attributeKey, zExtString& outAttributeValue);
		ZSPACE_EXTERNAL int ext_json_readJSONAttributeStringArray	(zExtJSON& extJSON, char* attributeKey, zExtStringArray& outAttributeValue);
		ZSPACE_EXTERNAL int ext_json_readJSONAttributeStringArray2D	(zExtJSON& extJSON, char* attributeKey, zExtStringArray2D& outAttributeValue);
		ZSPACE_EXTERNAL int ext_json_readJSONAttributeBool			(zExtJSON& extJSON, char* attributeKey, bool& outAttributeValue);
		ZSPACE_EXTERNAL int ext_json_readJSONAttributeBoolArray		(zExtJSON& extJSON, char* attributeKey, zExtBoolArray& outAttributeValue);
		ZSPACE_EXTERNAL int ext_json_readJSONAttributeBoolArray2D	(zExtJSON& extJSON, char* attributeKey, zExtBoolArray2D& outAttributeValue);
		
		ZSPACE_EXTERNAL int ext_json_writeJSONAttributeInt			(zExtJSON& extJSON, char* attributeKey, int inAttributeValue,					bool updateExtAttributes = true);
		ZSPACE_EXTERNAL int ext_json_writeJSONAttributeIntArray		(zExtJSON& extJSON, char* attributeKey, zExtIntArray& inAttributeValue,			bool updateExtAttributes = true);
		ZSPACE_EXTERNAL int ext_json_writeJSONAttributeIntArray2D	(zExtJSON& extJSON, char* attributeKey, zExtIntArray2D& inAttributeValue,		bool updateExtAttributes = true);
		ZSPACE_EXTERNAL int ext_json_writeJSONAttributeFloat		(zExtJSON& extJSON, char* attributeKey, float inAttributeValue,					bool updateExtAttributes = true);
		ZSPACE_EXTERNAL int ext_json_writeJSONAttributeFloatArray	(zExtJSON& extJSON, char* attributeKey, zExtFloatArray& inAttributeValue,		bool updateExtAttributes = true);
		ZSPACE_EXTERNAL int ext_json_writeJSONAttributeFloatArray2D	(zExtJSON& extJSON, char* attributeKey, zExtFloatArray2D& inAttributeValue,		bool updateExtAttributes = true);
		ZSPACE_EXTERNAL int ext_json_writeJSONAttributeDouble		(zExtJSON& extJSON, char* attributeKey, double inAttributeValue,				bool updateExtAttributes = true);
		ZSPACE_EXTERNAL int ext_json_writeJSONAttributeDoubleArray	(zExtJSON& extJSON, char* attributeKey, zExtDoubleArray& inAttributeValue,		bool updateExtAttributes = true);
		ZSPACE_EXTERNAL int ext_json_writeJSONAttributeDoubleArray2D(zExtJSON& extJSON, char* attributeKey, zExtDoubleArray2D& inAttributeValue,	bool updateExtAttributes = true);
		ZSPACE_EXTERNAL int ext_json_writeJSONAttributeString		(zExtJSON& extJSON, char* attributeKey, char* inAttributeValue,					bool updateExtAttributes = true);
		ZSPACE_EXTERNAL int ext_json_writeJSONAttributeStringArray	(zExtJSON& extJSON, char* attributeKey, zExtStringArray& inAttributeValue,		bool updateExtAttributes = true);
		ZSPACE_EXTERNAL int ext_json_writeJSONAttributeStringArray2D(zExtJSON& extJSON, char* attributeKey, zExtStringArray2D& inAttributeValue,	bool updateExtAttributes = true);
		ZSPACE_EXTERNAL int ext_json_writeJSONAttributeBool			(zExtJSON& extJSON, char* attributeKey, bool inAttributeValue,					bool updateExtAttributes = true);
		ZSPACE_EXTERNAL int ext_json_writeJSONAttributeBoolArray	(zExtJSON& extJSON, char* attributeKey, zExtBoolArray& inAttributeValue,		bool updateExtAttributes = true);
		ZSPACE_EXTERNAL int ext_json_writeJSONAttributeBoolArray2D	(zExtJSON& extJSON, char* attributeKey, zExtBoolArray2D& inAttributeValue,		bool updateExtAttributes = true);
		ZSPACE_EXTERNAL int ext_json_writeJSONAttributeJSON(zExtJSON& extJSON, char* attributeKey, zExtJSON& inAttributeValue, bool updateExtAttributes = true);

	
		ZSPACE_EXTERNAL void ext_json_createJson		(zExtJSON& extJSON);
		ZSPACE_EXTERNAL void ext_json_createJsonDeepCopy(zExtJSON& inJSON, zExtJSON& outJSON);
		ZSPACE_EXTERNAL int ext_json_readJsonFile		(zExtJSON& extJSON, char* inputPath);
		ZSPACE_EXTERNAL int ext_json_getMeshFromJson	(zExtJSON& extJSON, zExtMesh& outMesh);
		ZSPACE_EXTERNAL int ext_json_getMeshFromJsonPath(char* path, zExtMesh& outMesh);
		ZSPACE_EXTERNAL int ext_json_setMeshToJson		(zExtJSON& extJSON, zExtMesh& inMesh);
		ZSPACE_EXTERNAL int ext_json_exportFile			(zExtJSON& extJSON, char* outputPath);





	}



}




#if defined(ZSPACE_EXTERNAL_STATIC_LIBRARY)  || defined(ZSPACE_EXTERNAL_DYNAMIC_LIBRARY)
// All defined OK so do nothing
#else
#include<source/zCore/zExtJSON.cpp>
#endif

#endif