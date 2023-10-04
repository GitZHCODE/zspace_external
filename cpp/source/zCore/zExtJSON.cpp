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
#include<headers/zCore/zExtJSON.h>
namespace zSpace
{
	ZSPACE_EXTERNAL_INLINE zExtJSON::zExtJSON()
	{
		////delete pointer; 
		pointer = new json();
		updateAttributes();
	}
	ZSPACE_EXTERNAL_INLINE zExtJSON::~zExtJSON() { 
		//delete pointer;
	};
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
		zUtilsCore coreUtils;
		bool fileChk = coreUtils.readJSON(filePath, *pointer);
		updateAttributes();
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
					//int
					if (it.value().is_number_integer()) 
						type = "int";
					else if (it.value().is_array() && it.value().size() > 0 && it.value()[0].is_number_integer())
						type = "int[]";
					else if (it.value().is_array() && it.value().size() > 0 && it.value()[0].is_array() && it.value()[0].size() > 0 && it.value()[0][0].is_number_integer())
						type = "int[][]";
					//float
					else if (it.value().is_number_float())
						type = "float";
					else if (it.value().is_array() && it.value().size() > 0 && it.value()[0].is_number_float())
						type = "float[]";
					else if (it.value().is_array() && it.value().size() > 0 && it.value()[0].is_array() && it.value()[0].size() > 0 && it.value()[0][0].is_number_float())
						type = "float[][]";
					else if (it.value().is_array() && it.value().size() > 0 && it.value()[0].is_array() && it.value()[0].size() > 0 && it.value()[0][0].is_array(), it.value()[0][0][0].is_number_float())
						type = "zExtJSON";
					//bool
					else if (it.value().is_boolean())
						type = "bool";
					else if (it.value().is_array() && it.value().size() > 0 && it.value()[0].is_boolean())
						type = "bool[]";
					else if (it.value().is_array() && it.value().size() > 0 && it.value()[0].is_array() && it.value()[0].size() > 0 && it.value()[0][0].is_boolean())
						type = "bool[][]";
					//string
					else if (it.value().is_string())
						type = "string";
					else if (it.value().is_array())
						type = "string[]";
					else if (it.value().is_array() && it.value().size() > 0 && it.value()[0].is_array())
						type = "string[][]";
				}
			}
			catch (const json::exception&)
			{
				//type = "TYPE UNIDENTIFIED";
				type = "string";

			}

			printf("\n item key and type %s - %s", it.key().c_str(), type);
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

		(*pointer)[attributeName] = attributeValue;
		
		
	}
	ZSPACE_EXTERNAL_INLINE bool zExtJSON::ExportJsonFile(const string& filePath)
	{
		try
		{
			// Write the JSON object to the file
			ofstream file(filePath);
			file << pointer->dump(4); // Write formatted JSON with indentation of 4 spaces
			file.close();
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
		bool fileChk = coreUtils.readJSON(filePath, *pointer);
		//printf("\n read json 1");

		if(fileChk) updateAttributes();
		//printf("\n read json 2");

		return fileChk;
	}
	ZSPACE_EXTERNAL_INLINE zObjMesh zExtJSON::readMeshFromJson()
	{
		printf("\n readMeshFromJson 0");

		for (auto& element : pointer->items())
		{
			const auto& key = element.key();
			string k = element.key();
			//printf("\n s");
			printf("\n readMeshFromJson() %s", k.c_str());

		}
		//printf("\n readMeshFromJson 0");
		//printf("\n count %i", pointer->array().size());
		zObjMesh m;
		bool chk = MeshFromJSON(m);
		//updateAttributes();
		return zObjMesh();
	}

	ZSPACE_EXTERNAL_INLINE bool zExtJSON::readMeshFromJson(zObjMesh& outMesh)
	{
		printf("\n readMeshFromJson 0");

		for (auto& element : pointer->items())
		{
			const auto& key = element.key();
			string k = element.key();
			printf("\n %s", k.c_str());

		}
		printf("\n readMeshFromJson 0");
		//printf("\n count %i", pointer->array().size());

		bool chk = MeshFromJSON(outMesh);
		updateAttributes();
		return chk;
	}

	ZSPACE_EXTERNAL_INLINE bool zExtJSON::writeMeshToJson(zObjMesh& inMesh)
	{
		bool chk = MeshtoJSON(inMesh, *pointer);
		updateAttributes();
		return chk;
	}
	
	ZSPACE_EXTERNAL_INLINE bool zExtJSON::MeshtoJSON(zObjMesh& inMesh, json& jsonObj) // to be moved to core
	{
		try
		{
			zFnMesh fnMesh(inMesh);
			// remove inactive elements
			if (fnMesh.numVertices() != inMesh.mesh.vertices.size()) fnMesh.garbageCollection(zVertexData);
			if (fnMesh.numEdges() != inMesh.mesh.edges.size()) fnMesh.garbageCollection(zEdgeData);
			if (fnMesh.numPolygons() != inMesh.mesh.faces.size())fnMesh.garbageCollection(zFaceData);

			// CREATE JSON FILE
			zUtilsJsonHE meshJSON;

			// Vertices
			for (zItMeshVertex v(inMesh); !v.end(); v++)
			{
				if (v.getHalfEdge().isActive()) meshJSON.vertices.push_back(v.getHalfEdge().getId());
				else meshJSON.vertices.push_back(-1);
			}

			//Edges
			for (zItMeshHalfEdge he(inMesh); !he.end(); he++)
			{
				vector<int> HE_edges;

				if (he.getPrev().isActive()) HE_edges.push_back(he.getPrev().getId());
				else HE_edges.push_back(-1);

				if (he.getNext().isActive()) HE_edges.push_back(he.getNext().getId());
				else HE_edges.push_back(-1);

				if (he.getVertex().isActive()) HE_edges.push_back(he.getVertex().getId());
				else HE_edges.push_back(-1);

				if (!he.onBoundary()) HE_edges.push_back(he.getFace().getId());
				else HE_edges.push_back(-1);

				meshJSON.halfedges.push_back(HE_edges);
			}

			// Faces
			for (zItMeshFace f(inMesh); !f.end(); f++)
			{
				if (f.getHalfEdge().isActive()) meshJSON.faces.push_back(f.getHalfEdge().getId());
				else meshJSON.faces.push_back(-1);
			}

			// vertex Attributes
			for (int i = 0; i < inMesh.mesh.vertexPositions.size(); i++)
			{
				vector<double> v_attrib;

				v_attrib.push_back(inMesh.mesh.vertexPositions[i].x);
				v_attrib.push_back(inMesh.mesh.vertexPositions[i].y);
				v_attrib.push_back(inMesh.mesh.vertexPositions[i].z);

				v_attrib.push_back(inMesh.mesh.vertexNormals[i].x);
				v_attrib.push_back(inMesh.mesh.vertexNormals[i].y);
				v_attrib.push_back(inMesh.mesh.vertexNormals[i].z);


				v_attrib.push_back(inMesh.mesh.vertexColors[i].r);
				v_attrib.push_back(inMesh.mesh.vertexColors[i].g);
				v_attrib.push_back(inMesh.mesh.vertexColors[i].b);

				meshJSON.vertexAttributes.push_back(v_attrib);
			}

			// face Attributes
			for (int i = 0; i < fnMesh.numPolygons(); i++)
			{
				vector<double> f_attrib;

				f_attrib.push_back(inMesh.mesh.faceNormals[i].x);
				f_attrib.push_back(inMesh.mesh.faceNormals[i].y);
				f_attrib.push_back(inMesh.mesh.faceNormals[i].z);

				f_attrib.push_back(inMesh.mesh.faceColors[i].r);
				f_attrib.push_back(inMesh.mesh.faceColors[i].g);
				f_attrib.push_back(inMesh.mesh.faceColors[i].b);

				meshJSON.faceAttributes.push_back(f_attrib);
			}

			// he Attributes
			for (int i = 0; i < fnMesh.numEdges(); i++)
			{
				vector<double> he_attrib;

				he_attrib.push_back(inMesh.mesh.edgeColors[i].r);
				he_attrib.push_back(inMesh.mesh.edgeColors[i].g);
				he_attrib.push_back(inMesh.mesh.edgeColors[i].b);

				meshJSON.halfedgeAttributes.push_back(he_attrib);

				meshJSON.halfedgeAttributes.push_back(he_attrib);
			}

			// Json file 
			jsonObj["Vertices"] = meshJSON.vertices;
			jsonObj["Halfedges"] = meshJSON.halfedges;
			jsonObj["Faces"] = meshJSON.faces;
			jsonObj["VertexAttributes"] = meshJSON.vertexAttributes;
			jsonObj["HalfedgeAttributes"] = meshJSON.halfedgeAttributes;
			jsonObj["FaceAttributes"] = meshJSON.faceAttributes;

			return true;
		}
		catch (const std::exception&)
		{
			return false;
		}
		
	}

	ZSPACE_EXTERNAL_INLINE bool zExtJSON::MeshFromJSON(zObjMesh& outMesh)
	{
		try
		{
			printf("\n MeshFromJSONxx 0");

			zStringArray names;
			names.clear();
			//names.assign()
			printf("\n count %i", pointer->array().size());

			for (auto& element : pointer->items())
			{
				const auto& key = element.key();
				string k = element.key();
				names.push_back(k);
				printf("\n MeshFromJSON() %s", k.c_str());

			}

			zUtilsJsonHE meshJSON;
			printf("\n MeshFromJSON 00");

			zFnMesh fnMesh(outMesh);

			printf("\n MeshFromJSON 000");


			// Vertices
			meshJSON.vertices.clear();
			printf("\n MeshFromJSON 0000");
			zIntArray vs = (*pointer)["Vertices"].get<zIntArray>();// = zExtIntArray(j[attributeKeySt].get<zIntArray>());
			printf("\n MeshFromJSON 0000 0");

			meshJSON.vertices = ((*pointer)["Vertices"].get<zIntArray>());
			printf("\n MeshFromJSON 0-1");


			//Edges
			meshJSON.halfedges.clear();
			meshJSON.halfedges = ((*pointer)["Halfedges"].get<vector<vector<int>>>());
			printf("\n MeshFromJSON 0-2");

			// Faces
			meshJSON.faces.clear();
			meshJSON.faces = ((*pointer)["Faces"].get<vector<int>>());
			printf("\n MeshFromJSON 0-3");

			// update  mesh
			outMesh.mesh.clear();

			outMesh.mesh.vertices.assign(meshJSON.vertices.size(), zVertex());
			outMesh.mesh.halfEdges.assign(meshJSON.halfedges.size(), zHalfEdge());
			printf("\n MeshFromJSON 0-4");

			int numE = (int)floor(meshJSON.halfedges.size() * 0.5);
			outMesh.mesh.edges.assign(numE, zEdge());
			outMesh.mesh.faces.assign(meshJSON.faces.size(), zFace());

			outMesh.mesh.vHandles.assign(meshJSON.vertices.size(), zVertexHandle());
			outMesh.mesh.eHandles.assign(numE, zEdgeHandle());
			outMesh.mesh.heHandles.assign(meshJSON.halfedges.size(), zHalfEdgeHandle());
			outMesh.mesh.fHandles.assign(meshJSON.faces.size(), zFaceHandle());
			printf("\n MeshFromJSON 0-5");

			// set IDs
			for (int i = 0; i < meshJSON.vertices.size(); i++) outMesh.mesh.vertices[i].setId(i);
			for (int i = 0; i < meshJSON.halfedges.size(); i++) outMesh.mesh.halfEdges[i].setId(i);
			for (int i = 0; i < meshJSON.faces.size(); i++) outMesh.mesh.faces[i].setId(i);

			printf("\n MeshFromJSON 1");

			// set Pointers
			int n_v = 0;
			for (zItMeshVertex v(outMesh); !v.end(); v++)
			{
				v.setId(n_v);

				if (meshJSON.vertices[n_v] != -1)
				{
					zItMeshHalfEdge he(outMesh, meshJSON.vertices[n_v]);;
					v.setHalfEdge(he);

					outMesh.mesh.vHandles[n_v].id = n_v;
					outMesh.mesh.vHandles[n_v].he = meshJSON.vertices[n_v];
				}

				n_v++;
			}
			outMesh.mesh.setNumVertices(n_v);

			int n_he = 0;
			int n_e = 0;

			for (zItMeshHalfEdge he(outMesh); !he.end(); he++)
			{
				// Half Edge
				he.setId(n_he);
				outMesh.mesh.heHandles[n_he].id = n_he;

				if (meshJSON.halfedges[n_he][0] != -1)
				{
					zItMeshHalfEdge hePrev(outMesh, meshJSON.halfedges[n_he][0]);
					he.setPrev(hePrev);

					outMesh.mesh.heHandles[n_he].p = meshJSON.halfedges[n_he][0];
				}

				if (meshJSON.halfedges[n_he][1] != -1)
				{
					zItMeshHalfEdge heNext(outMesh, meshJSON.halfedges[n_he][1]);
					he.setNext(heNext);

					outMesh.mesh.heHandles[n_he].n = meshJSON.halfedges[n_he][1];
				}

				if (meshJSON.halfedges[n_he][2] != -1)
				{
					zItMeshVertex v(outMesh, meshJSON.halfedges[n_he][2]);
					he.setVertex(v);

					outMesh.mesh.heHandles[n_he].v = meshJSON.halfedges[n_he][2];
				}

				if (meshJSON.halfedges[n_he][3] != -1)
				{
					zItMeshFace f(outMesh, meshJSON.halfedges[n_he][3]);
					he.setFace(f);

					outMesh.mesh.heHandles[n_he].f = meshJSON.halfedges[n_he][3];
				}

				// symmetry half edges && Edge
				if (n_he % 2 == 1)
				{
					zItMeshHalfEdge heSym(outMesh, n_he - 1);
					he.setSym(heSym);

					zItMeshEdge e(outMesh, n_e);
					e.setId(n_e);

					e.setHalfEdge(heSym, 0);
					e.setHalfEdge(he, 1);

					he.setEdge(e);
					heSym.setEdge(e);

					outMesh.mesh.heHandles[n_he].e = n_e;
					outMesh.mesh.heHandles[n_he - 1].e = n_e;

					outMesh.mesh.eHandles[n_e].id = n_e;
					outMesh.mesh.eHandles[n_e].he0 = n_he - 1;
					outMesh.mesh.eHandles[n_e].he1 = n_he;

					n_e++;
				}

				n_he++;
			}
			printf("\n MeshFromJSON 2");

			outMesh.mesh.setNumEdges(n_e);

			int n_f = 0;

			for (zItMeshFace f(outMesh); !f.end(); f++)
			{
				f.setId(n_f);

				if (meshJSON.vertices[n_f] != -1)
				{
					zItMeshHalfEdge he(outMesh, meshJSON.faces[n_f]);
					f.setHalfEdge(he);

					outMesh.mesh.fHandles[n_f].id = n_f;
					outMesh.mesh.fHandles[n_f].he = meshJSON.faces[n_f];
				}

				n_f++;
			}
			outMesh.mesh.setNumPolygons(n_f);

			//// Vertex Attributes
			meshJSON.vertexAttributes = (*pointer)["VertexAttributes"].get<vector<vector<double>>>();
			//printf("\n vertexAttributes: %zi %zi", vertexAttributes.size(), vertexAttributes[0].size());

			outMesh.mesh.vertexPositions.clear();
			outMesh.mesh.vertexNormals.clear();
			outMesh.mesh.vertexColors.clear();
			outMesh.mesh.vertexWeights.clear();
			for (int i = 0; i < meshJSON.vertexAttributes.size(); i++)
			{
				for (int k = 0; k < meshJSON.vertexAttributes[i].size(); k++)
				{
					// position, normal and color

					if (meshJSON.vertexAttributes[i].size() == 9)
					{
						zVector pos(meshJSON.vertexAttributes[i][k], meshJSON.vertexAttributes[i][k + 1], meshJSON.vertexAttributes[i][k + 2]);
						outMesh.mesh.vertexPositions.push_back(pos);

						zVector normal(meshJSON.vertexAttributes[i][k + 3], meshJSON.vertexAttributes[i][k + 4], meshJSON.vertexAttributes[i][k + 5]);
						outMesh.mesh.vertexNormals.push_back(normal);

						zColor col(meshJSON.vertexAttributes[i][k + 6], meshJSON.vertexAttributes[i][k + 7], meshJSON.vertexAttributes[i][k + 8], 1);
						outMesh.mesh.vertexColors.push_back(col);

						outMesh.mesh.vertexWeights.push_back(2.0);

						k += 8;
					}

					// position, normal
					if (meshJSON.vertexAttributes[i].size() == 6)
					{
						zVector pos(meshJSON.vertexAttributes[i][k], meshJSON.vertexAttributes[i][k + 1], meshJSON.vertexAttributes[i][k + 2]);
						outMesh.mesh.vertexPositions.push_back(pos);

						zVector normal(meshJSON.vertexAttributes[i][k + 3], meshJSON.vertexAttributes[i][k + 4], meshJSON.vertexAttributes[i][k + 5]);
						outMesh.mesh.vertexNormals.push_back(normal);

						outMesh.mesh.vertexColors.push_back(zColor(1, 0, 0, 1));

						outMesh.mesh.vertexWeights.push_back(2.0);

						k += 5;
					}

					// BRG position, normal and color, thickness
					if (meshJSON.vertexAttributes[i].size() == 15)
					{
						zVector pos(meshJSON.vertexAttributes[i][k], meshJSON.vertexAttributes[i][k + 1], meshJSON.vertexAttributes[i][k + 2]);
						outMesh.mesh.vertexPositions.push_back(pos);

						zVector normal(meshJSON.vertexAttributes[i][k + 3], meshJSON.vertexAttributes[i][k + 4], meshJSON.vertexAttributes[i][k + 5]);
						outMesh.mesh.vertexNormals.push_back(normal);

						zColor col(meshJSON.vertexAttributes[i][k + 6], meshJSON.vertexAttributes[i][k + 7], meshJSON.vertexAttributes[i][k + 8], 1);
						outMesh.mesh.vertexColors.push_back(col);

						outMesh.mesh.vertexWeights.push_back(2.0);

						k += 14;
					}


					// position, normal
					if (meshJSON.vertexAttributes[i].size() == 8)
					{
						zVector pos(meshJSON.vertexAttributes[i][k], meshJSON.vertexAttributes[i][k + 1], meshJSON.vertexAttributes[i][k + 2]);
						outMesh.mesh.vertexPositions.push_back(pos);

						zVector normal(meshJSON.vertexAttributes[i][k + 3], meshJSON.vertexAttributes[i][k + 4], meshJSON.vertexAttributes[i][k + 5]);
						outMesh.mesh.vertexNormals.push_back(normal);

						outMesh.mesh.vertexColors.push_back(zColor(1, 0, 0, 1));

						outMesh.mesh.vertexWeights.push_back(2.0);

						k += 7;
					}

				}
			}

			// Edge Attributes
			//meshJSON.halfedgeAttributes = j["HalfedgeAttributes"].get<vector<vector<double>>>();
			printf("\n MeshFromJSON 3");

			outMesh.mesh.edgeColors.clear();
			outMesh.mesh.edgeWeights.clear();
			if (meshJSON.halfedgeAttributes.size() == 0)
			{
				for (int i = 0; i < outMesh.mesh.n_e; i++)
				{
					outMesh.mesh.edgeColors.push_back(zColor());
					outMesh.mesh.edgeWeights.push_back(1.0);
				}
			}
			else
			{

				/*for (int i = 0; i < meshObj.mesh.n_e; i++)
				{
					meshObj.mesh.edgeColors.push_back(zColor());
					meshObj.mesh.edgeWeights.push_back(1.0);
				}*/

				for (int i = 0; i < meshJSON.halfedgeAttributes.size(); i += 2)
				{
					// color
					if (meshJSON.halfedgeAttributes[i].size() == 3)
					{
						zColor col(meshJSON.halfedgeAttributes[i][0], meshJSON.halfedgeAttributes[i][1], meshJSON.halfedgeAttributes[i][2], 1);

						outMesh.mesh.edgeColors.push_back(col);
						outMesh.mesh.edgeWeights.push_back(1.0);

					}
				}
			}

			// face Attributes
			meshJSON.faceAttributes = (*pointer)["FaceAttributes"].get<vector<vector<double>>>();
			printf("\n MeshFromJSON 4");

			outMesh.mesh.faceColors.clear();
			outMesh.mesh.faceNormals.clear();
			for (int i = 0; i < meshJSON.faceAttributes.size(); i++)
			{
				for (int k = 0; k < meshJSON.faceAttributes[i].size(); k++)
				{
					// normal and color
					if (meshJSON.faceAttributes[i].size() == 6)
					{
						zColor col(meshJSON.faceAttributes[i][k + 3], meshJSON.faceAttributes[i][k + 4], meshJSON.faceAttributes[i][k + 5], 1);
						outMesh.mesh.faceColors.push_back(col);

						zVector normal(meshJSON.faceAttributes[i][k], meshJSON.faceAttributes[i][k + 1], meshJSON.faceAttributes[i][k + 2]);
						outMesh.mesh.faceNormals.push_back(normal);

						k += 5;
					}

					if (meshJSON.faceAttributes[i].size() == 3)
					{
						zVector normal(meshJSON.faceAttributes[i][k], meshJSON.faceAttributes[i][k + 1], meshJSON.faceAttributes[i][k + 2]);
						outMesh.mesh.faceNormals.push_back(normal);

						outMesh.mesh.faceColors.push_back(zColor(0.5, 0.5, 0.5, 1));

						k += 2;
					}
				}
			}

			if (meshJSON.faceAttributes.size() == 0)
			{
				fnMesh.computeMeshNormals();
				fnMesh.setFaceColor(zColor(0.5, 0.5, 0.5, 1));
			}

			// add to maps 
			for (int i = 0; i < outMesh.mesh.vertexPositions.size(); i++)
			{
				outMesh.mesh.addToPositionMap(outMesh.mesh.vertexPositions[i], i);
			}

			for (zItMeshEdge e(outMesh); !e.end(); e++)
			{
				int v1 = e.getHalfEdge(0).getVertex().getId();
				int v2 = e.getHalfEdge(1).getVertex().getId();

				outMesh.mesh.addToHalfEdgesMap(v1, v2, e.getHalfEdge(0).getId());
			}

			printf("\n extPointer: %i %i %i ", fnMesh.numVertices(), fnMesh.numEdges(), fnMesh.numPolygons());
			return true;
		}
		catch (const std::exception&)
		{
			return false;
		}
	}





	// JSON - Read Attributes
	ZSPACE_EXTERNAL_INLINE int ext_json_readJSONAttributeInt			(zExtJSON& extJSON, char* attributeKey, int& outAttributeValue)
	{
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
		string attributeKeySt(attributeKey);
		zUtilsCore core;
		json j = *extJSON.pointer;
			try
			{
				outAttributeValue = zExtIntArray(j[attributeKeySt].get<zIntArray>());
				//outAttributeValue.pointer = &j[attributeKeySt].get<zIntArray>();
				outAttributeValue.updateAttributes();
				return 1;
			}
			catch (const exception&) { return 0; }
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_readJSONAttributeIntArray2D		(zExtJSON& extJSON, char* attributeKey, zExtIntArray2D& outAttributeValue)
	{
		string attributeKeySt(attributeKey);
		zUtilsCore core;
		json j = *extJSON.pointer;
		try
		{
			outAttributeValue = zExtIntArray2D(j[attributeKeySt].get<zInt2DArray>());
			outAttributeValue.updateAttributes();
			return 1;
		}
		catch (const exception&) { return 0; };
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_readJSONAttributeFloat			(zExtJSON& extJSON, char* attributeKey, float& outAttributeValue)
	{
		string attributeKeySt(attributeKey);
		zUtilsCore core;
		json j = *extJSON.pointer;
			try
			{
				outAttributeValue = j[attributeKeySt].get<float>();
				return 1;
			}
			catch (const exception&) { return 0; };
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_readJSONAttributeFloatArray		(zExtJSON& extJSON, char* attributeKey, zExtFloatArray& outAttributeValue)
	{
		printf("\n ext_json_readJSONAttributeFloatArray 0");
		string attributeKeySt(attributeKey);
		zUtilsCore core;
		json j = *extJSON.pointer;
			try
			{
				printf("\n ext_json_readJSONAttributeFloatArray 1");

				outAttributeValue = zExtFloatArray(j[attributeKeySt].get<zFloatArray>());
				printf("\n ext_json_readJSONAttributeFloatArray 2");

				outAttributeValue.updateAttributes();
				printf("\n ext_json_readJSONAttributeFloatArray 3");

				return 1;
			}
			catch (const exception&) { return 0; };
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_readJSONAttributeFloatArray2D	(zExtJSON& extJSON, char* attributeKey, zExtFloatArray2D& outAttributeValue)
	{
		string attributeKeySt(attributeKey);
		zUtilsCore core;
		json j = *extJSON.pointer;
			try
			{
				outAttributeValue = zExtFloatArray2D(j[attributeKeySt].get<vector<zFloatArray>>());
				outAttributeValue.updateAttributes();
				return 1;
			}
			catch (const exception&) { return 0; };
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_readJSONAttributeDouble			(zExtJSON& extJSON, char* attributeKey, double& outAttributeValue)
	{
		string attributeKeySt(attributeKey);
		zUtilsCore core;
		json j = *extJSON.pointer;
		try
		{
			outAttributeValue = j[attributeKeySt].get<double>();
			return 1;
		}
		catch (const exception&) { return 0; };
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_readJSONAttributeDoubleArray	(zExtJSON& extJSON, char* attributeKey, zExtDoubleArray& outAttributeValue)
	{
		string attributeKeySt(attributeKey);
		zUtilsCore core;
		json j = *extJSON.pointer;
		try
		{
			outAttributeValue = zExtDoubleArray(j[attributeKeySt].get<zDoubleArray>());
			outAttributeValue.updateAttributes();
			return 1;
		}
		catch (const exception&) { return 0; };
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_readJSONAttributeDoubleArray2D	(zExtJSON& extJSON, char* attributeKey, zExtDoubleArray2D& outAttributeValue)
	{
		string attributeKeySt(attributeKey);
		zUtilsCore core;
		json j = *extJSON.pointer;
		try
		{
			outAttributeValue = zExtDoubleArray2D(j[attributeKeySt].get<vector<zDoubleArray>>());
			outAttributeValue.updateAttributes();
			return 1;
		}
		catch (const exception&) { return 0; };
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_readJSONAttributeString			(zExtJSON& extJSON, char* attributeKey, zExtString& outAttributeValue)
	{
		string attributeKeySt(attributeKey);
		zUtilsCore core;
		json j = *extJSON.pointer;
			try
			{
				outAttributeValue = zExtString();
				//string st = j[attributeKeySt].get<string>();
				outAttributeValue.pointer = new string(j[attributeKeySt].get<string>());
				//outAttributeValue.pointer = new string(st);
				//*outAttributeValue.pointer = j[attributeKeySt].get<string>();
				outAttributeValue.updateAttributes();
				/*for (int i = 0; i < st.empty(); i++)
				{
					outAttributeValue[i] = st[i];
				}*/
				//outAttributeValue = j[attributeKeySt].get<string>().c_str();
				return 1;
			}
			catch (const exception& ){ return 0; }
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_readJSONAttributeStringArray	(zExtJSON& extJSON, char* attributeKey, zExtStringArray& outAttributeValue)
	{
		string attributeKeySt(attributeKey);
		zUtilsCore core;
		json j = *extJSON.pointer;
			try
			{
				outAttributeValue = zExtStringArray(j[attributeKeySt].get<zStringArray>());
				outAttributeValue.updateAttributes();
				return 1;
			}
			catch (const exception&) { return 0; };
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_readJSONAttributeStringArray2D	(zExtJSON& extJSON, char* attributeKey, zExtStringArray2D& outAttributeValue)
	{
		string attributeKeySt(attributeKey);
		zUtilsCore core;
		json j = *extJSON.pointer;
		try
		{
			outAttributeValue = zExtStringArray2D(j[attributeKeySt].get<vector<zStringArray>>());
			outAttributeValue.updateAttributes();
			return 1;
		}
		catch (const exception&) { return 0; };
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_readJSONAttributeBool			(zExtJSON& extJSON, char* attributeKey, bool& outAttributeValue)
	{
		string attributeKeySt(attributeKey);
		zUtilsCore core;
		json j = *extJSON.pointer;
		try
		{
			outAttributeValue = j[attributeKeySt].get<bool>();

			//outAttributeValue = j[attributeKeySt];

			return 1;
		}
		catch (const exception&) { return 0; }
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_readJSONAttributeBoolArray		(zExtJSON& extJSON, char* attributeKey, zExtBoolArray& outAttributeValue)
	{
		string attributeKeySt(attributeKey);
		zUtilsCore core;
		json j = *extJSON.pointer;
		try
		{
			outAttributeValue = zExtBoolArray(j[attributeKeySt].get<zBoolArray>());
			outAttributeValue.updateAttributes();
			return 1;
		}
		catch (const exception&) { return 0; };
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_readJSONAttributeBoolArray2D	(zExtJSON& extJSON, char* attributeKey, zExtBoolArray2D& outAttributeValue)
	{
		string attributeKeySt(attributeKey);
		zUtilsCore core;
		json j = *extJSON.pointer;
		try
		{
			outAttributeValue = zExtBoolArray2D(j[attributeKeySt].get<vector<zBoolArray>>());
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
			extJSON.AddAttribute(attributeKey, inAttributeValue);
			if (updateExtAttributes) extJSON.updateAttributes();
			return 1;
		}
		catch (const exception&) { return 0; };
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_writeJSONAttributeStringArray	(zExtJSON& extJSON, char* attributeKey, zExtStringArray& inAttributeValue,		bool updateExtAttributes)
	{
		try
		{
			extJSON.AddAttribute(attributeKey, *inAttributeValue.pointer);
			if (updateExtAttributes) extJSON.updateAttributes();
			return 1;
		}
		catch (const exception&) { return 0; };
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_writeJSONAttributeStringArray2D	(zExtJSON& extJSON, char* attributeKey, zExtStringArray2D& inAttributeValue,	bool updateExtAttributes)
	{
		try
		{
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
			zUtilsCore util;
			util.writeJSONAttribute(*extJSON.pointer, attributeKey, *inAttributeValue.pointer);
			//extJSON.AddAttribute(attributeKey, inAttributeValue.pointer);
			if (updateExtAttributes) extJSON.updateAttributes();
			return 1;
		}
		catch (const exception&) { return 0; };
	}

	// JSON - Write Attributes Generic - TRIAL

	
	ZSPACE_EXTERNAL_INLINE void ext_json_createJson(zExtJSON& extJSON)
	{
		extJSON.pointer = new json();// = zExtJSON();

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
			string pathSt(inputPath);
			extJSON.ReadJsonFile(pathSt); 	

			for (auto& element : extJSON.pointer->items())
			{
				const auto& key = element.key();
				string k = element.key();
				//printf("\n %s", k.c_str());

			}
			return 1;
		}
	catch (const exception&) { return 0; }
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_getMeshFromJson(zExtJSON& extJSON, zExtMesh& outMesh)
	{
		//outMesh = zExtMesh();
		//zObjMesh m = (extJSON.readMeshFromJson());
		printf("\n ext_json_getMeshFromJson 0");
		outMesh.createMeshFromJson(extJSON.pointer);
		//*outMesh.mesh = (extJSON.readMeshFromJson());
		printf("\n ext_json_getMeshFromJson 1");
		//outMesh.updateAttributes();
		printf("\n ext_json_getMeshFromJson 2");
		//try
		//{
		//	printf("\n ext_json_getMeshFromJson 0");
		//	for (auto& element : extJSON.pointer->items())
		//	{
		//		const auto& key = element.key();
		//		string k = element.key();
		//		printf("\n %s", k.c_str());

		//	}
		//	outMesh = zExtMesh();
		//	printf("\n ext_json_getMeshFromJson 1");

		//	//bool chk = extJSON.readMeshFromJson(*outMesh.mesh);
		//	zObjMesh m = (extJSON.readMeshFromJson());
		//	//bool chk = extJSON.readMeshFromJson(*outMesh.mesh);
		//	printf("\n ext_json_getMeshFromJson 2");

		//	outMesh.updateAttributes();
		//	printf("\n ext_json_getMeshFromJson 3");

		//	return 1;
		//}
		//catch (const std::exception&)
		//{
		//	return 0;
		//}
		return 1;
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_getMeshFromJsonPath(char* path, zExtMesh& outMesh)
	{
		try
		{
			printf("\n ext_json_getMeshFromJsonPath 0");
			outMesh.extPointer = new zObjMesh();
			printf("\n ext_json_getMeshFromJsonPath 1");

			string pathst(path);
			printf("\n ext_json_getMeshFromJsonPath 2");

			outMesh.createMeshFromJson(pathst);


			outMesh.updateAttributes();


			//printf("\n ext_json_getMeshFromJsonPath 3");

			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_setMeshToJson(zExtJSON& extJSON, zExtMesh& inMesh)
	{
		try
		{
			bool chk = extJSON.writeMeshToJson(*inMesh.extPointer);
			return chk;
		}
		catch (const std::exception&)
		{
			return 0;
		}
	}
	ZSPACE_EXTERNAL_INLINE int ext_json_exportFile(zExtJSON& extJSON, char* filePath)
	{
		string filePathSt(filePath);
		try
		{
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
