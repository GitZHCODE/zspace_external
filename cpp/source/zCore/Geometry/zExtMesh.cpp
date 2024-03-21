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


#include"headers/zCore/Geometry/zExtMesh.h"


namespace zSpace
{
	
	ZSPACE_EXTERNAL_INLINE zExtMesh::zExtMesh(zObjMesh* m)
	{
		pointer = m;
		updateAttributes();
	}

	ZSPACE_EXTERNAL_INLINE zExtMesh::zExtMesh(zObjMesh& m)
	{
		pointer = &m;
		updateAttributes();
	}


	ZSPACE_EXTERNAL_INLINE zExtMesh::zExtMesh()
	{
		pointer = new zObjMesh();
		updateAttributes();
	}
	

	ZSPACE_EXTERNAL_INLINE zExtMesh::~zExtMesh()
	{
		delete pointer;
		pointer = nullptr;
	}

	ZSPACE_EXTERNAL_INLINE zStatus zExtMesh::checkMemAlloc(bool allocateMemory)
	{
		try
		{
			if (!pointer || pointer == nullptr)
			{
				if (!allocateMemory) return zMemNotAllocError;
				pointer = new zObjMesh();
				return zStatus(zMemAllocSuccess);
			}
			else
			{
				return zStatus(zSkip);
			}

			
		}
		catch (const std::exception&)
		{
			return zStatus(zThrowError);
		}
	}

	ZSPACE_EXTERNAL_INLINE void zExtMesh::updateAttributes()
	{
		zFnMesh fn(*pointer);
		vCount = fn.numVertices();
		//printf("\n update numverts %i %i", vCount, fn.numVertices());
		fCount = fn.numPolygons();

		

		//fn.getVertexPositions(*verticesArray.pointer);
		//verticesArray.updateAttributes();

		//fn.getVertexColors(*colorsArray.pointer);
		//colorsArray.updateAttributes();


	}
	ZSPACE_EXTERNAL_INLINE bool zExtMesh::createMeshFromJson(json* jsonPointer) //Should be moved to core
	{

		pointer = new zObjMesh();

		/*for (auto& element : pointer->items())
		{
			const auto& key = element.key();
			string k = element.key();
			printf("\n MeshFromJSON() %s", k.c_str());

		}*/

		zUtilsJsonHE meshJSON;

		zFnMesh fnMesh(*pointer);



		// Vertices
		meshJSON.vertices.clear();
		meshJSON.halfedges.clear();
		meshJSON.halfedges.clear();

		try
		{
			meshJSON.vertices = ((*jsonPointer)["Vertices"].get<vector<int>>());
		}
		catch (const std::exception& ex)
		{
			printf("\n \n !!! ERROR:  NO 'Vertices' attribute in this JSON !!! \n \n");
			// return false;
			
			//throw std::runtime_error(" \n !!! ERROR: \n NO 'Vertices' attribute in this JSON \n !!! \n");
			throw std::invalid_argument(" \n !!! ERROR: \n NO 'Vertices' attribute in this JSON \n !!! \n");
		}

		//Edges
		try { meshJSON.halfedges = ((*jsonPointer)["Halfedges"].get<vector<vector<int>>>());  }
		catch (const std::exception&)
		{
			 printf("\n \n !!! ERROR:  NO 'Halfedges' attribute in this JSON !!! \n \n");
			return false;
			//throw std::invalid_argument(" \n !!! ERROR: \n NO 'Verticies' attribute in this JSON \n !!! \n"); ;
		}
		//Faces
		try { meshJSON.faces = ((*jsonPointer)["Faces"].get<vector<int>>()); }
		catch (const std::exception&)
		{
			 printf("\n \n !!! ERROR:  NO 'Faces' attribute in this JSON !!! \n \n");
			return false;
			//throw std::invalid_argument(" \n !!! ERROR: \n NO 'Verticies' attribute in this JSON \n !!! \n"); ;
		}



		// update  mesh
		pointer->mesh.clear();

		pointer->mesh.vertices.assign(meshJSON.vertices.size(), zVertex());
		pointer->mesh.halfEdges.assign(meshJSON.halfedges.size(), zHalfEdge());

		int numE = (int)floor(meshJSON.halfedges.size() * 0.5);
		pointer->mesh.edges.assign(numE, zEdge());
		pointer->mesh.faces.assign(meshJSON.faces.size(), zFace());

		pointer->mesh.vHandles.assign(meshJSON.vertices.size(), zVertexHandle());
		pointer->mesh.eHandles.assign(numE, zEdgeHandle());
		pointer->mesh.heHandles.assign(meshJSON.halfedges.size(), zHalfEdgeHandle());
		pointer->mesh.fHandles.assign(meshJSON.faces.size(), zFaceHandle());

		// set IDs
		for (int i = 0; i < meshJSON.vertices.size(); i++) pointer->mesh.vertices[i].setId(i);
		for (int i = 0; i < meshJSON.halfedges.size(); i++) pointer->mesh.halfEdges[i].setId(i);
		for (int i = 0; i < meshJSON.faces.size(); i++) pointer->mesh.faces[i].setId(i);



		// set Pointers
		int n_v = 0;
		for (zItMeshVertex v(*pointer); !v.end(); v++)
		{
			v.setId(n_v);

			if (meshJSON.vertices[n_v] != -1)
			{
				zItMeshHalfEdge he(*pointer, meshJSON.vertices[n_v]);;
				v.setHalfEdge(he);

				pointer->mesh.vHandles[n_v].id = n_v;
				pointer->mesh.vHandles[n_v].he = meshJSON.vertices[n_v];
			}

			n_v++;
		}
		pointer->mesh.setNumVertices(n_v);

		int n_he = 0;
		int n_e = 0;

		for (zItMeshHalfEdge he(*pointer); !he.end(); he++)
		{
			// Half Edge
			he.setId(n_he);
			pointer->mesh.heHandles[n_he].id = n_he;

			if (meshJSON.halfedges[n_he][0] != -1)
			{
				zItMeshHalfEdge hePrev(*pointer, meshJSON.halfedges[n_he][0]);
				he.setPrev(hePrev);

				pointer->mesh.heHandles[n_he].p = meshJSON.halfedges[n_he][0];
			}

			if (meshJSON.halfedges[n_he][1] != -1)
			{
				zItMeshHalfEdge heNext(*pointer, meshJSON.halfedges[n_he][1]);
				he.setNext(heNext);

				pointer->mesh.heHandles[n_he].n = meshJSON.halfedges[n_he][1];
			}

			if (meshJSON.halfedges[n_he][2] != -1)
			{
				zItMeshVertex v(*pointer, meshJSON.halfedges[n_he][2]);
				he.setVertex(v);

				pointer->mesh.heHandles[n_he].v = meshJSON.halfedges[n_he][2];
			}

			if (meshJSON.halfedges[n_he][3] != -1)
			{
				zItMeshFace f(*pointer, meshJSON.halfedges[n_he][3]);
				he.setFace(f);

				pointer->mesh.heHandles[n_he].f = meshJSON.halfedges[n_he][3];
			}

			// symmetry half edges && Edge
			if (n_he % 2 == 1)
			{
				zItMeshHalfEdge heSym(*pointer, n_he - 1);
				he.setSym(heSym);

				zItMeshEdge e(*pointer, n_e);
				e.setId(n_e);

				e.setHalfEdge(heSym, 0);
				e.setHalfEdge(he, 1);

				he.setEdge(e);
				heSym.setEdge(e);

				pointer->mesh.heHandles[n_he].e = n_e;
				pointer->mesh.heHandles[n_he - 1].e = n_e;

				pointer->mesh.eHandles[n_e].id = n_e;
				pointer->mesh.eHandles[n_e].he0 = n_he - 1;
				pointer->mesh.eHandles[n_e].he1 = n_he;

				n_e++;
			}

			n_he++;
		}

		pointer->mesh.setNumEdges(n_e);

		int n_f = 0;

		for (zItMeshFace f(*pointer); !f.end(); f++)
		{
			f.setId(n_f);

			if (meshJSON.vertices[n_f] != -1)
			{
				zItMeshHalfEdge he(*pointer, meshJSON.faces[n_f]);
				f.setHalfEdge(he);

				pointer->mesh.fHandles[n_f].id = n_f;
				pointer->mesh.fHandles[n_f].he = meshJSON.faces[n_f];
			}

			n_f++;
		}
		pointer->mesh.setNumPolygons(n_f);

		//// Vertex Attributes
		meshJSON.vertexAttributes = (*jsonPointer)["VertexAttributes"].get<vector<vector<double>>>();
		//printf("\n vertexAttributes: %zi %zi", vertexAttributes.size(), vertexAttributes[0].size());

		pointer->mesh.vertexPositions.clear();
		pointer->mesh.vertexNormals.clear();
		pointer->mesh.vertexColors.clear();
		pointer->mesh.vertexWeights.clear();
		for (int i = 0; i < meshJSON.vertexAttributes.size(); i++)
		{
			for (int k = 0; k < meshJSON.vertexAttributes[i].size(); k++)
			{
				// position, normal and color

				if (meshJSON.vertexAttributes[i].size() == 9)
				{
					zVector pos(meshJSON.vertexAttributes[i][k], meshJSON.vertexAttributes[i][k + 1], meshJSON.vertexAttributes[i][k + 2]);
					pointer->mesh.vertexPositions.push_back(pos);

					zVector normal(meshJSON.vertexAttributes[i][k + 3], meshJSON.vertexAttributes[i][k + 4], meshJSON.vertexAttributes[i][k + 5]);
					pointer->mesh.vertexNormals.push_back(normal);

					zColor col(meshJSON.vertexAttributes[i][k + 6], meshJSON.vertexAttributes[i][k + 7], meshJSON.vertexAttributes[i][k + 8], 1);
					pointer->mesh.vertexColors.push_back(col);

					pointer->mesh.vertexWeights.push_back(2.0);

					k += 8;
				}

				// position, normal
				if (meshJSON.vertexAttributes[i].size() == 6)
				{
					zVector pos(meshJSON.vertexAttributes[i][k], meshJSON.vertexAttributes[i][k + 1], meshJSON.vertexAttributes[i][k + 2]);
					pointer->mesh.vertexPositions.push_back(pos);

					zVector normal(meshJSON.vertexAttributes[i][k + 3], meshJSON.vertexAttributes[i][k + 4], meshJSON.vertexAttributes[i][k + 5]);
					pointer->mesh.vertexNormals.push_back(normal);

					pointer->mesh.vertexColors.push_back(zColor(1, 0, 0, 1));

					pointer->mesh.vertexWeights.push_back(2.0);

					k += 5;
				}

				// BRG position, normal and color, thickness
				if (meshJSON.vertexAttributes[i].size() == 15)
				{
					zVector pos(meshJSON.vertexAttributes[i][k], meshJSON.vertexAttributes[i][k + 1], meshJSON.vertexAttributes[i][k + 2]);
					pointer->mesh.vertexPositions.push_back(pos);

					zVector normal(meshJSON.vertexAttributes[i][k + 3], meshJSON.vertexAttributes[i][k + 4], meshJSON.vertexAttributes[i][k + 5]);
					pointer->mesh.vertexNormals.push_back(normal);

					zColor col(meshJSON.vertexAttributes[i][k + 6], meshJSON.vertexAttributes[i][k + 7], meshJSON.vertexAttributes[i][k + 8], 1);
					pointer->mesh.vertexColors.push_back(col);

					pointer->mesh.vertexWeights.push_back(2.0);

					k += 14;
				}


				// position, normal
				if (meshJSON.vertexAttributes[i].size() == 8)
				{
					zVector pos(meshJSON.vertexAttributes[i][k], meshJSON.vertexAttributes[i][k + 1], meshJSON.vertexAttributes[i][k + 2]);
					pointer->mesh.vertexPositions.push_back(pos);

					zVector normal(meshJSON.vertexAttributes[i][k + 3], meshJSON.vertexAttributes[i][k + 4], meshJSON.vertexAttributes[i][k + 5]);
					pointer->mesh.vertexNormals.push_back(normal);

					pointer->mesh.vertexColors.push_back(zColor(1, 0, 0, 1));

					pointer->mesh.vertexWeights.push_back(2.0);

					k += 7;
				}

			}
		}

		// Edge Attributes
		//meshJSON.halfedgeAttributes = j["HalfedgeAttributes"].get<vector<vector<double>>>();

		pointer->mesh.edgeColors.clear();
		pointer->mesh.edgeWeights.clear();
		if (meshJSON.halfedgeAttributes.size() == 0)
		{
			for (int i = 0; i < pointer->mesh.n_e; i++)
			{
				pointer->mesh.edgeColors.push_back(zColor());
				pointer->mesh.edgeWeights.push_back(1.0);
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

					pointer->mesh.edgeColors.push_back(col);
					pointer->mesh.edgeWeights.push_back(1.0);

				}
			}
		}

		// face Attributes
		meshJSON.faceAttributes = (*jsonPointer)["FaceAttributes"].get<vector<vector<double>>>();

		pointer->mesh.faceColors.clear();
		pointer->mesh.faceNormals.clear();
		for (int i = 0; i < meshJSON.faceAttributes.size(); i++)
		{
			for (int k = 0; k < meshJSON.faceAttributes[i].size(); k++)
			{
				// normal and color
				if (meshJSON.faceAttributes[i].size() == 6)
				{
					zColor col(meshJSON.faceAttributes[i][k + 3], meshJSON.faceAttributes[i][k + 4], meshJSON.faceAttributes[i][k + 5], 1);
					pointer->mesh.faceColors.push_back(col);

					zVector normal(meshJSON.faceAttributes[i][k], meshJSON.faceAttributes[i][k + 1], meshJSON.faceAttributes[i][k + 2]);
					pointer->mesh.faceNormals.push_back(normal);

					k += 5;
				}

				if (meshJSON.faceAttributes[i].size() == 3)
				{
					zVector normal(meshJSON.faceAttributes[i][k], meshJSON.faceAttributes[i][k + 1], meshJSON.faceAttributes[i][k + 2]);
					pointer->mesh.faceNormals.push_back(normal);

					pointer->mesh.faceColors.push_back(zColor(0.5, 0.5, 0.5, 1));

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
		for (int i = 0; i < pointer->mesh.vertexPositions.size(); i++)
		{
			pointer->mesh.addToPositionMap(pointer->mesh.vertexPositions[i], i);
		}

		for (zItMeshEdge e(*pointer); !e.end(); e++)
		{
			int v1 = e.getHalfEdge(0).getVertex().getId();
			int v2 = e.getHalfEdge(1).getVertex().getId();

			pointer->mesh.addToHalfEdgesMap(v1, v2, e.getHalfEdge(0).getId());
		}

		printf("\n meshPointer: %i %i %i ", fnMesh.numVertices(), fnMesh.numEdges(), fnMesh.numPolygons());
	
		//set static container
		pointer->mesh.staticGeometry = true;

		vector<vector<int>> edgeVerts;

		for (zItMeshEdge e(*pointer); !e.end(); e++)
		{
			vector<int> verts;
			e.getVertices(verts);

			edgeVerts.push_back(verts);
		}

		pointer->mesh.setStaticEdgeVertices(edgeVerts);

		vector<vector<int>> faceVerts;

		for (zItMeshFace f(*pointer); !f.end(); f++)
		{
			vector<int> verts;
			f.getVertices(verts);

			faceVerts.push_back(verts);
		}

		pointer->mesh.setStaticFaceVertices(faceVerts);


		updateAttributes();

		return true;
	}
	ZSPACE_EXTERNAL_INLINE bool zExtMesh::createMeshFromJson(string infilename)
	{

		zFnMesh fnmesh(*pointer);


		json j;
		zUtilsJsonHE meshJSON;

		ifstream in_myfile;
		in_myfile.open(infilename.c_str());

		int lineCnt = 0;

		if (in_myfile.fail())
		{
			cout << " error in opening file  " << infilename.c_str() << endl;
			return false;
		}

		in_myfile >> j;
		in_myfile.close();

		// READ Data from JSON


		// Vertices
		meshJSON.vertices.clear();
		meshJSON.vertices = (j["Vertices"].get<vector<int>>());


		//Edges
		meshJSON.halfedges.clear();
		meshJSON.halfedges = (j["Halfedges"].get<vector<vector<int>>>());

		// Faces
		meshJSON.faces.clear();
		meshJSON.faces = (j["Faces"].get<vector<int>>());

		// update  mesh
		pointer->mesh.clear();

		pointer->mesh.vertices.assign(meshJSON.vertices.size(), zVertex());
		pointer->mesh.halfEdges.assign(meshJSON.halfedges.size(), zHalfEdge());

		int numE = (int)floor(meshJSON.halfedges.size() * 0.5);
		pointer->mesh.edges.assign(numE, zEdge());
		pointer->mesh.faces.assign(meshJSON.faces.size(), zFace());

		pointer->mesh.vHandles.assign(meshJSON.vertices.size(), zVertexHandle());
		pointer->mesh.eHandles.assign(numE, zEdgeHandle());
		pointer->mesh.heHandles.assign(meshJSON.halfedges.size(), zHalfEdgeHandle());
		pointer->mesh.fHandles.assign(meshJSON.faces.size(), zFaceHandle());

		// set IDs
		for (int i = 0; i < meshJSON.vertices.size(); i++) pointer->mesh.vertices[i].setId(i);
		for (int i = 0; i < meshJSON.halfedges.size(); i++) pointer->mesh.halfEdges[i].setId(i);
		for (int i = 0; i < meshJSON.faces.size(); i++) pointer->mesh.faces[i].setId(i);

		//printf("\n nV %i | nHE %i | nP %i ", meshJSON.vertices.size(), meshJSON.halfedges.size(), meshJSON.faces.size());

		// set Pointers
		int n_v = 0;
		for (zItMeshVertex v(*pointer); !v.end(); v++)
		{
			v.setId(n_v);

			if (meshJSON.vertices[n_v] != -1)
			{
				zItMeshHalfEdge he(*pointer, meshJSON.vertices[n_v]);;
				v.setHalfEdge(he);

				pointer->mesh.vHandles[n_v].id = n_v;
				pointer->mesh.vHandles[n_v].he = meshJSON.vertices[n_v];
			}

			n_v++;
		}
		pointer->mesh.setNumVertices(n_v);

		int n_he = 0;
		int n_e = 0;

		for (zItMeshHalfEdge he(*pointer); !he.end(); he++)
		{
			// Half Edge
			he.setId(n_he);
			pointer->mesh.heHandles[n_he].id = n_he;

			if (meshJSON.halfedges[n_he][0] != -1)
			{
				zItMeshHalfEdge hePrev(*pointer, meshJSON.halfedges[n_he][0]);
				he.setPrev(hePrev);

				pointer->mesh.heHandles[n_he].p = meshJSON.halfedges[n_he][0];
			}

			if (meshJSON.halfedges[n_he][1] != -1)
			{
				zItMeshHalfEdge heNext(*pointer, meshJSON.halfedges[n_he][1]);
				he.setNext(heNext);

				pointer->mesh.heHandles[n_he].n = meshJSON.halfedges[n_he][1];
			}

			if (meshJSON.halfedges[n_he][2] != -1)
			{
				zItMeshVertex v(*pointer, meshJSON.halfedges[n_he][2]);
				he.setVertex(v);

				pointer->mesh.heHandles[n_he].v = meshJSON.halfedges[n_he][2];
			}

			if (meshJSON.halfedges[n_he][3] != -1)
			{
				zItMeshFace f(*pointer, meshJSON.halfedges[n_he][3]);
				he.setFace(f);

				pointer->mesh.heHandles[n_he].f = meshJSON.halfedges[n_he][3];
			}

			// symmetry half edges && Edge
			if (n_he % 2 == 1)
			{
				zItMeshHalfEdge heSym(*pointer, n_he - 1);
				he.setSym(heSym);

				zItMeshEdge e(*pointer, n_e);
				e.setId(n_e);

				e.setHalfEdge(heSym, 0);
				e.setHalfEdge(he, 1);

				he.setEdge(e);
				heSym.setEdge(e);

				pointer->mesh.heHandles[n_he].e = n_e;
				pointer->mesh.heHandles[n_he - 1].e = n_e;

				pointer->mesh.eHandles[n_e].id = n_e;
				pointer->mesh.eHandles[n_e].he0 = n_he - 1;
				pointer->mesh.eHandles[n_e].he1 = n_he;

				n_e++;
			}

			n_he++;
		}

		pointer->mesh.setNumEdges(n_e);

		int n_f = 0;

		for (zItMeshFace f(*pointer); !f.end(); f++)
		{
			f.setId(n_f);

			if (meshJSON.vertices[n_f] != -1)
			{
				zItMeshHalfEdge he(*pointer, meshJSON.faces[n_f]);
				f.setHalfEdge(he);

				pointer->mesh.fHandles[n_f].id = n_f;
				pointer->mesh.fHandles[n_f].he = meshJSON.faces[n_f];
			}

			n_f++;
		}
		pointer->mesh.setNumPolygons(n_f);

		//// Vertex Attributes
		meshJSON.vertexAttributes = j["VertexAttributes"].get<vector<vector<double>>>();
		//printf("\n vertexAttributes: %zi %zi", vertexAttributes.size(), vertexAttributes[0].size());

		pointer->mesh.vertexPositions.clear();
		pointer->mesh.vertexNormals.clear();
		pointer->mesh.vertexColors.clear();
		pointer->mesh.vertexWeights.clear();
		for (int i = 0; i < meshJSON.vertexAttributes.size(); i++)
		{
			for (int k = 0; k < meshJSON.vertexAttributes[i].size(); k++)
			{
				// position, normal and color

				if (meshJSON.vertexAttributes[i].size() == 9)
				{
					zVector pos(meshJSON.vertexAttributes[i][k], meshJSON.vertexAttributes[i][k + 1], meshJSON.vertexAttributes[i][k + 2]);
					pointer->mesh.vertexPositions.push_back(pos);

					zVector normal(meshJSON.vertexAttributes[i][k + 3], meshJSON.vertexAttributes[i][k + 4], meshJSON.vertexAttributes[i][k + 5]);
					pointer->mesh.vertexNormals.push_back(normal);

					zColor col(meshJSON.vertexAttributes[i][k + 6], meshJSON.vertexAttributes[i][k + 7], meshJSON.vertexAttributes[i][k + 8], 1);
					pointer->mesh.vertexColors.push_back(col);

					pointer->mesh.vertexWeights.push_back(2.0);

					k += 8;
				}

				// position, normal
				if (meshJSON.vertexAttributes[i].size() == 6)
				{
					zVector pos(meshJSON.vertexAttributes[i][k], meshJSON.vertexAttributes[i][k + 1], meshJSON.vertexAttributes[i][k + 2]);
					pointer->mesh.vertexPositions.push_back(pos);

					zVector normal(meshJSON.vertexAttributes[i][k + 3], meshJSON.vertexAttributes[i][k + 4], meshJSON.vertexAttributes[i][k + 5]);
					pointer->mesh.vertexNormals.push_back(normal);

					pointer->mesh.vertexColors.push_back(zColor(1, 0, 0, 1));

					pointer->mesh.vertexWeights.push_back(2.0);

					k += 5;
				}

				// BRG position, normal and color, thickness
				if (meshJSON.vertexAttributes[i].size() == 15)
				{
					zVector pos(meshJSON.vertexAttributes[i][k], meshJSON.vertexAttributes[i][k + 1], meshJSON.vertexAttributes[i][k + 2]);
					pointer->mesh.vertexPositions.push_back(pos);

					zVector normal(meshJSON.vertexAttributes[i][k + 3], meshJSON.vertexAttributes[i][k + 4], meshJSON.vertexAttributes[i][k + 5]);
					pointer->mesh.vertexNormals.push_back(normal);

					zColor col(meshJSON.vertexAttributes[i][k + 6], meshJSON.vertexAttributes[i][k + 7], meshJSON.vertexAttributes[i][k + 8], 1);
					pointer->mesh.vertexColors.push_back(col);

					pointer->mesh.vertexWeights.push_back(2.0);

					k += 14;
				}


				// position, normal
				if (meshJSON.vertexAttributes[i].size() == 8)
				{
					zVector pos(meshJSON.vertexAttributes[i][k], meshJSON.vertexAttributes[i][k + 1], meshJSON.vertexAttributes[i][k + 2]);
					pointer->mesh.vertexPositions.push_back(pos);

					zVector normal(meshJSON.vertexAttributes[i][k + 3], meshJSON.vertexAttributes[i][k + 4], meshJSON.vertexAttributes[i][k + 5]);
					pointer->mesh.vertexNormals.push_back(normal);

					pointer->mesh.vertexColors.push_back(zColor(1, 0, 0, 1));

					pointer->mesh.vertexWeights.push_back(2.0);

					k += 7;
				}

			}
		}

		// Edge Attributes
		//meshJSON.halfedgeAttributes = j["HalfedgeAttributes"].get<vector<vector<double>>>();

		pointer->mesh.edgeColors.clear();
		pointer->mesh.edgeWeights.clear();
		if (meshJSON.halfedgeAttributes.size() == 0)
		{
			for (int i = 0; i < pointer->mesh.n_e; i++)
			{
				pointer->mesh.edgeColors.push_back(zColor());
				pointer->mesh.edgeWeights.push_back(1.0);
			}
		}
		else
		{

			/*for (int i = 0; i < pointer->mesh.n_e; i++)
			{
				pointer->mesh.edgeColors.push_back(zColor());
				pointer->mesh.edgeWeights.push_back(1.0);
			}*/

			for (int i = 0; i < meshJSON.halfedgeAttributes.size(); i += 2)
			{
				// color
				if (meshJSON.halfedgeAttributes[i].size() == 3)
				{
					zColor col(meshJSON.halfedgeAttributes[i][0], meshJSON.halfedgeAttributes[i][1], meshJSON.halfedgeAttributes[i][2], 1);

					pointer->mesh.edgeColors.push_back(col);
					pointer->mesh.edgeWeights.push_back(1.0);

				}
			}
		}

		// face Attributes
		meshJSON.faceAttributes = j["FaceAttributes"].get<vector<vector<double>>>();

		pointer->mesh.faceColors.clear();
		pointer->mesh.faceNormals.clear();
		for (int i = 0; i < meshJSON.faceAttributes.size(); i++)
		{
			for (int k = 0; k < meshJSON.faceAttributes[i].size(); k++)
			{
				// normal and color
				if (meshJSON.faceAttributes[i].size() == 6)
				{
					zColor col(meshJSON.faceAttributes[i][k + 3], meshJSON.faceAttributes[i][k + 4], meshJSON.faceAttributes[i][k + 5], 1);
					pointer->mesh.faceColors.push_back(col);

					zVector normal(meshJSON.faceAttributes[i][k], meshJSON.faceAttributes[i][k + 1], meshJSON.faceAttributes[i][k + 2]);
					pointer->mesh.faceNormals.push_back(normal);

					k += 5;
				}

				if (meshJSON.faceAttributes[i].size() == 3)
				{
					zVector normal(meshJSON.faceAttributes[i][k], meshJSON.faceAttributes[i][k + 1], meshJSON.faceAttributes[i][k + 2]);
					pointer->mesh.faceNormals.push_back(normal);

					pointer->mesh.faceColors.push_back(zColor(0.5, 0.5, 0.5, 1));

					k += 2;
				}
			}
		}

		if (meshJSON.faceAttributes.size() == 0)
		{
			fnmesh.computeMeshNormals();
			fnmesh.setFaceColor(zColor(0.5, 0.5, 0.5, 1));
		}

		// add to maps 
		for (int i = 0; i < pointer->mesh.vertexPositions.size(); i++)
		{
			pointer->mesh.addToPositionMap(pointer->mesh.vertexPositions[i], i);
		}

		for (zItMeshEdge e(*pointer); !e.end(); e++)
		{
			int v1 = e.getHalfEdge(0).getVertex().getId();
			int v2 = e.getHalfEdge(1).getVertex().getId();

			pointer->mesh.addToHalfEdgesMap(v1, v2, e.getHalfEdge(0).getId());
		}

		printf("\n mesh: nV %i - nE %i - nF %i ", fnmesh.numVertices(), fnmesh.numEdges(), fnmesh.numPolygons());

		return true;




	}

	ZSPACE_EXTERNAL_INLINE void zExtMesh::graphFromMeshHEArray(zItMeshHalfEdgeArray& meshItHE, zObjGraph& outGraph)
	{
		zFnGraph fnGraph(outGraph);

		zIntArray econnects;
		zPointArray positions;
		int counter = 0;
		zUtilsCore core;
		for (auto& he : meshItHE)
		{
			zPoint p0 = he.getStartVertex().getPosition();
			int v0 = -1;
			he.getEdge().setColor(zBLUE);

			bool exist = core.checkRepeatElement(p0, positions, v0);
			if (!exist)
			{
				v0 = positions.size();
				positions.push_back(p0);
			}
			zPoint p1 = he.getVertex().getPosition();
			int v1 = -1;
			exist = core.checkRepeatElement(p1, positions, v1);
			if (!exist)
			{
				v1 = positions.size();
				positions.push_back(p1);
			}
			econnects.push_back(v0);
			econnects.push_back(v1);
			counter++;
		}
		fnGraph.create(positions, econnects);
	}

	ZSPACE_EXTERNAL_INLINE void zExtMesh::graphFromMeshHEArray(vector<zItMeshHalfEdgeArray>& meshItHE, zObjGraph& outGraph)
	{
		zFnGraph fnGraph(outGraph);

		zIntArray econnects;
		zPointArray positions;
		zUtilsCore core;

		int counter = 0;
		for (int i = 0; i < meshItHE.size(); i++)
		{
			//printf("\n graphIds reset");

			zIntArray graphIds;
			for (auto& he : meshItHE[i])
			{
				zPoint p0 = he.getStartVertex().getPosition();
				int v0 = -1;
				he.getEdge().setColor(zBLUE);

				bool exist = core.checkRepeatElement(p0, positions, v0);
				if (!exist)
				{
					v0 = positions.size();
					positions.push_back(p0);
				}


				zPoint p1 = he.getVertex().getPosition();
				int v1 = -1;

				exist = core.checkRepeatElement(p1, positions, v1);
				if (!exist)
				{
					v1 = positions.size();
					positions.push_back(p1);
				}

				econnects.push_back(v0);
				econnects.push_back(v1);

				graphIds.push_back(counter);
				counter++;
			}
		}


		fnGraph.create(positions, econnects);
	}

	ZSPACE_EXTERNAL_INLINE void zExtMesh::getEdgeLoop(zObjMesh& mesh, vector<zItMeshHalfEdgeArray>& outUDirection, vector<zItMeshHalfEdgeArray>& outVDirection)
	{
		printf("\n getEdgeLoop 0");

		outUDirection.clear();
		outVDirection.clear();
		//get first edge loops (u and v) starting from a corner


		zItMeshHalfEdgeArray firstU;
		zItMeshHalfEdgeArray firstV;

		for (zItMeshVertex v(mesh); !v.end(); v++)
		{
			//printf("\n getEdgeLoop 1 - %i", v.checkValency(2));

			if (v.checkValency(2))//<vCorner
			{

				zItMeshHalfEdgeArray cornerEdges;
				v.getConnectedHalfEdges(cornerEdges);

				printf("\n getEdgeLoop 2 cornerEdges %i", cornerEdges.size());

				zItMeshHalfEdge eV = cornerEdges[0];// .getSym();
				zItMeshHalfEdge eU = cornerEdges[1];


				firstV.push_back(eV);


				while (!eV.getVertex().checkValency(2))
				{
					printf("\n eV.onBoundary()? %i", eV.onBoundary());
					eV = eV.onBoundary() ? eV.getNext() : eV.getNext().getSym().getNext();
					firstV.push_back(eV);
				}

				firstU.push_back(eU);
				while (!eU.getVertex().checkValency(2))
				{
					//printf("\n getEdgeLoop 5");
					printf("\n eU.onBoundary()? %i", eU.onBoundary());

					eU = eU.onBoundary() ? eU.getNext() : eU.getNext().getSym().getNext();
					firstU.push_back(eU);
				}

				printf("\n getEdgeLoop 6 %i : %i", firstU.size(), firstV.size());
				break;
			}
		}
		//outVDirection.push_back(firstV);
		//outUDirection.push_back(firstU);

		int counter = -1;
		bool goPrev = false;
		for (auto e : firstU)
		{
			/*counter++;
			if (counter == 0) continue;*/

			zItMeshHalfEdgeArray otherDir;

			zItMeshHalfEdge e1 = e.onBoundary() ? e.getSym().getPrev().getSym() : e.getNext();
			printf("\n V e.onBoundary() %i ", e.onBoundary());

			bool exit = false;
			while (!exit)
			{
				otherDir.push_back(e1);
				e1 = e1.onBoundary() ? e1.getNext() : e1.getNext().getSym().getNext();
				exit = e1.getVertex().getValence() != e1.getStartVertex().getValence();
			}
			otherDir.push_back(e1);

			outVDirection.push_back(otherDir);
		}
		for (auto e : firstV)
		{
			zItMeshHalfEdgeArray otherDir;

			zItMeshHalfEdge e1 = e.onBoundary() ? e.getSym().getNext() : e.getNext();
			printf("\n U e.onBoundary() %i ", e.onBoundary());

			bool exit = false;
			while (!exit)
			{
				//printf("\n in adding U");
				otherDir.push_back(e1);
				e1 = e1.onBoundary() ? e1.getNext() : e1.getNext().getSym().getNext();
				exit = e1.getVertex().getValence() != e1.getStartVertex().getValence();
			}
			otherDir.push_back(e1);

			outUDirection.push_back(otherDir);
		}




	}

	ZSPACE_EXTERNAL_INLINE void zExtMesh::smoothMesh(int numDivisions, bool smoothCorner, zIntArray fixedIndex, bool smoothFixedEdges)
	{
		printf("\n smooth mesh c++");

		zFnMesh fnmesh(*pointer); //<to be deleted when moved to core and update accordingly

		vector<zVector> fCenters;
		vector<zVector> tempECenters;
		vector<zVector> eCenters;

		for (int j = 0; j < numDivisions; j++)
		{
			// get face centers
			fCenters.clear();
			fnmesh.getCenters(zFaceData, fCenters);

			// get edge centers

			tempECenters.clear();

			eCenters.clear();
			fnmesh.getCenters(zEdgeData, eCenters);

			tempECenters = eCenters;

			zVector* vPositions = fnmesh.getRawVertexPositions();

			int numOriginalVertices = fnmesh.numVertices();
			int numOriginalEdges = fnmesh.numEdges();

			// compute new smooth positions of the edge centers
			
			//for (int i = 0; i < numOriginalEdges; i++)
			//{
			//	zItMeshEdge e(*pointer, i);
			//	if (e.onBoundary()) continue;
			//	zVector newPos;
			//	vector<int> eVerts;
			//	e.getVertices(eVerts);
			//	for (auto& vId : eVerts) newPos += vPositions[vId];
			//	vector<int> eFaces;
			//	e.getFaces(eFaces);
			//	for (auto& fId : eFaces) newPos += fCenters[fId];
			//	newPos /= (eFaces.size() + eVerts.size());
			//	eCenters[i] = newPos;
			//}

			vector<zVector> faceNormals, vertexNormals;
			fnmesh.getFaceNormals(faceNormals);
			fnmesh.getVertexNormals(vertexNormals);
			for (int i = 0; i < numOriginalEdges; i++)
			{
				zItMeshEdge e(*pointer, i);
				if (e.onBoundary())
				{
					//if (!fixedIndex.size() > 0)
					{
						continue;
					}
					
				}

				zVector newPos;
				vector<int> eVerts;
				e.getVertices(eVerts);
				// Check if both vertices of the edge are fixed
				bool isFixedEdge = find(begin(fixedIndex), end(fixedIndex), eVerts[0]) != end(fixedIndex) &&
					find(begin(fixedIndex), end(fixedIndex), eVerts[1]) != end(fixedIndex);

				//printf("\n edge vertecies %i - %i", eVerts[0], eVerts[1]);

				if (isFixedEdge)
				{
					//continue;
					if (!smoothFixedEdges)
					{
						printf("\n smooth mesh and don't smooth fixed verticies");

						// For a fixed edge, set newPos as the midpoint of the edge
						newPos = (vPositions[eVerts[0]] + vPositions[eVerts[1]]) / 2.0;
					}
					else
					{
						printf("\n smooth mesh and smooth fixed verticies");
						// Assume we have functions to calculate or get vertex normals
						zVector normalStart = vertexNormals[eVerts[0]]; // Vertex normal at start
						zVector normalEnd = vertexNormals[eVerts[1]];   // Vertex normal at end

						// Calculate the midpoint
						zVector midpoint = (vPositions[eVerts[0]] + vPositions[eVerts[1]]) / 2.0;

						// Adjust midpoint based on normals to respect edge flow
						zVector edgeDirection = (vPositions[eVerts[1]] - vPositions[eVerts[0]]);
						edgeDirection.normalize();
						zVector bisectorNormal = (normalStart + normalEnd);
						bisectorNormal.normalize(); // Simple way to get an intermediate normal

						// This step simulates the "edge flow" adjustment by moving the midpoint along the bisector of the vertex normals
						// The amount of adjustment might need tweaking based on your mesh's scale and specific requirements
						float adjustmentFactor = 0.5; // This factor controls the influence of the curvature on the new position
						zVector midpointProjection = midpoint + edgeDirection;
						newPos = midpoint + bisectorNormal * adjustmentFactor * midpoint.distanceTo(midpointProjection);
						// Ensure newPos is within the edge's segment defined by its two vertices
						// This is a simple projection and may need refinement
					}
					
				}
				else
				{
					// Existing logic for computing newPos
					for (auto& vId : eVerts) newPos += vPositions[vId];
					vector<int> eFaces;
					e.getFaces(eFaces);
					for (auto& fId : eFaces) newPos += fCenters[fId];
					newPos /= (eFaces.size() + eVerts.size());
				}
				eCenters[i] = newPos;
			}

			


			// compute new smooth positions for the original vertices
			for (int i = 0; i < numOriginalVertices; i++)
			{
				zItMeshVertex v(*pointer, i);
				vector<zItMeshEdge> cEdges;
				v.getConnectedEdges(cEdges);

				bool vFixedChk = find(begin(fixedIndex), end(fixedIndex), v.getId()) != end(fixedIndex);
				if (vFixedChk)
				{
					continue;

					

					zVector P = vPositions[i];
					//int n = 1; // rosetta , not matching with maya
					int n = 0;

					zVector R(0, 0, 0);
					for (auto& e : cEdges)
					{
						vector<int> eVerts;
						e.getVertices(eVerts);
						bool eFixedChk = find(begin(fixedIndex), end(fixedIndex), eVerts[0]) != end(fixedIndex) &&
							find(begin(fixedIndex), end(fixedIndex), eVerts[1]) != end(fixedIndex);
						if (eFixedChk)
						{
							R += tempECenters[e.getId()];
							n++;
						}
					}

					// rosetta , not matching with maya
					//vPositions[i] = (P + R) / n; 

					vPositions[i] = (P / n) + (R / (n * n));

				}
				else if (v.onBoundary())
				{

					if (!smoothCorner && cEdges.size() == 2) continue;					

					zVector P = vPositions[i];
					//int n = 1; // rosetta , not matching with maya
					int n = 0;

					zVector R(0, 0, 0);
					for (auto& e : cEdges)
					{
						vector<int> eVerts;
						e.getVertices(eVerts);
						bool eFixedChk = find(begin(fixedIndex), end(fixedIndex), eVerts[0]) != end(fixedIndex) &&
							find(begin(fixedIndex), end(fixedIndex), eVerts[1]) != end(fixedIndex);
						if (e.onBoundary())
						{
							R += tempECenters[e.getId()];
							n++;
						}
					}

					// rosetta , not matching with maya
					//vPositions[i] = (P + R) / n; 

					vPositions[i] = (P / n) + (R / (n * n));
				}
				
				else
				{
					//if (chkFixed) continue;
					zVector R;

					//vector<int> cEdges;
					//v.getConnectedEdges(cEdges);

					for (auto& e : cEdges) R += tempECenters[ e.getId()];
					R /= cEdges.size();

					zVector F;
					vector<int> cFaces;
					v.getConnectedFaces(cFaces);
					for (auto& fId : cFaces) F += fCenters[fId];
					F /= cFaces.size();

					zVector P = vPositions[i];
					int n = cFaces.size();

					vPositions[i] = (F + (R * 2) + (P * (n - 3))) / n;
				}
			}

			// split edges at center			
			for (int i = 0; i < numOriginalEdges; i++)
			{
				zItMeshEdge e(*pointer, i);
				if (e.isActive())
				{
					zItMeshVertex newVert = fnmesh.splitEdge(e);
					newVert.setPosition(eCenters[i]);
				}
			}

			// add faces
			int numOriginalFaces = fnmesh.numPolygons();

			for (int i = 0; i < numOriginalFaces; i++)
			{
				zItMeshFace f(*pointer, i);

				if (!f.isActive()) continue;

				vector<zItMeshHalfEdge> fEdges;
				f.getHalfEdges(fEdges);

				// disable current face
				f.deactivate();

				// check if vertex exists if not add new vertex
				zItMeshVertex vertexCen;
				fnmesh.addVertex(fCenters[i], true, vertexCen);

				// add new faces				
				int startId = 0;
				if (fEdges[0].getVertex().getId() < numOriginalVertices) startId = 1;

				for (int k = startId; k < fEdges.size() + startId; k += 2)
				{
					vector<int> newFVerts;

					newFVerts.push_back(fEdges[k].getVertex().getId());

					newFVerts.push_back(vertexCen.getId());

					newFVerts.push_back(fEdges[k].getPrev().getStartVertex().getId());

					newFVerts.push_back(fEdges[k].getPrev().getVertex().getId());

					zItMeshFace newF;
					fnmesh.addPolygon(newFVerts, newF);
				}
			}

			// update half edge handles. 
			for (int i = 0; i < pointer->mesh.heHandles.size(); i++)
			{
				if (pointer->mesh.heHandles[i].f != -1) pointer->mesh.heHandles[i].f -= numOriginalFaces;
			}

			// remove inactive faces
			fnmesh.garbageCollection(zFaceData);

			fnmesh.computeMeshNormals();
		}
	}

	ZSPACE_EXTERNAL_INLINE void zExtMesh::smoothMesh1D(int numDivisions, bool flip, bool smoothCorner, zIntArray fixedIndex)
	{
		zFnMesh fnmesh(*pointer);

		int n_v_lowPoly = fnmesh.numVertices();

		for (int ss = 0; ss < numDivisions; ss++)
		{

			zPointArray lowpolyPosition;
			zPointArray highpolyPosition;
			zPointArray newPositions;
			zIntArray newPolyConnects;
			zIntArray newPolyCounts;

			fnmesh.getVertexPositions(lowpolyPosition);


			vector<zItMeshHalfEdgeArray> edgeLoopU, edgeLoopV;
			smoothMesh(1, smoothCorner, fixedIndex);
			fnmesh.getVertexPositions(highpolyPosition);

			getEdgeLoop(*pointer, edgeLoopU, edgeLoopV);

			vector<zItMeshHalfEdgeArray> edgeLoop = flip ? edgeLoopV : edgeLoopU;
			//for each edge loop, get the id of vertex on that edge loop and check if any id included in the original before smoothing
			zBoolArray checkEdges;
			checkEdges.assign(edgeLoop.size(), true);

			for (int i = 0; i < edgeLoop.size(); i++)
			{
				if (edgeLoop[i][0].getStartVertex().getId() < lowpolyPosition.size())
				{
					checkEdges[i] = false;
					continue;
				}
				for (auto& e : edgeLoop[i])
				{
					if (e.getVertex().getId() < lowpolyPosition.size())
					{
						checkEdges[i] = false;
						break;
					}
				}
			}


			zIntArray indexMap;
			indexMap.assign(highpolyPosition.size(), -1);

			for (int k = 0; k < lowpolyPosition.size(); k++)
			{
				newPositions.push_back(highpolyPosition[k]);
				indexMap[k] = k;
			}

			for (int i = 0; i < edgeLoop.size(); i++)
			{
				if (checkEdges[i])
				{
					for (auto& e : edgeLoop[i])
					{
						zItMeshVertexArray newPts;

						auto e1 = e.getNext().getNext();

						newPts.push_back(e1.getStartVertex());
						newPts.push_back(e1.getVertex());

						e1 = e1.getNext().getNext().getSym().getNext().getNext();

						newPts.push_back(e1.getStartVertex());
						newPts.push_back(e1.getVertex());

						for (auto& p : newPts)
						{
							if (indexMap[p.getId()] == -1)
							{
								newPositions.push_back(p.getPosition());
								indexMap[p.getId()] = newPositions.size() - 1;
							}
							newPolyConnects.push_back(indexMap[p.getId()]);

						}
						newPolyCounts.push_back(4);
					}
				}
			}

			fnmesh.create(newPositions, newPolyCounts, newPolyConnects);
		}

	}


	ZSPACE_EXTERNAL_INLINE zExtMeshArray::zExtMeshArray(zObjMeshArray* m)
	{
		pointer = m;
		updateAttributes();
	}

	ZSPACE_EXTERNAL_INLINE zExtMeshArray::~zExtMeshArray()
	{
		delete pointer;
		pointer = nullptr;
	}

	ZSPACE_EXTERNAL_INLINE zStatus zExtMeshArray::checkMemAlloc(bool allocateMemory)
	{
		try
		{
			if (pointer != nullptr) return zStatus(zSkip);
			else
			{
				if (!allocateMemory) return zStatus(zMemNotAllocError);
				pointer = new zObjMeshArray();
				return zMemAllocSuccess;

			}
		}
		catch (const std::exception&)
		{
			printf("\n Pointer initialization failed");
			return zStatus(zMemNotAllocError);
		}
	}

	ZSPACE_EXTERNAL_INLINE void zExtMeshArray::updateAttributes()
	{
		arrayCount = pointer->size();
	}

	ZSPACE_EXTERNAL_INLINE void zExtMeshArray::setItems(zObjMesh* items, int count)
	{
		checkMemAlloc();
		pointer->clear();
		for (int i = 0; i < count; i++)
		{
			pointer->push_back(items[i]);
		}
		updateAttributes();
	}

	ZSPACE_EXTERNAL_INLINE zExtMeshPointerArray::zExtMeshPointerArray(zObjMeshPointerArray* m)
	{
		pointer = m;
		updateAttributes();
	}

	ZSPACE_EXTERNAL_INLINE zExtMeshPointerArray::~zExtMeshPointerArray()
	{
		delete pointer;
		pointer = nullptr;
	}

	ZSPACE_EXTERNAL_INLINE zStatus zExtMeshPointerArray::checkMemAlloc(bool allocateMemory)
	{
		try
		{
			if (!pointer || pointer == nullptr)
			{
				if (!allocateMemory) return zMemNotAllocError;
				pointer = new zObjMeshPointerArray();
					return zStatus(zMemAllocSuccess);
			}
			else
			{
				return zStatus(zSkip);
			}


		}
		catch (const std::exception&)
		{
			return zStatus(zThrowError);
		}
	}

	ZSPACE_EXTERNAL_INLINE void zExtMeshPointerArray::updateAttributes()
	{
		arrayCount = pointer->size();
	}
	

	//--------------------------
	//----CREATE METHODS
	//--------------------------
	ZSPACE_EXTERNAL_INLINE void ext_mesh_createFromRawArrays(double* _vertexPositions, int* _polyCounts, int* _polyConnects, int numVerts, int numFaces, zExtMesh& out_mesh)
	{
		if (!_vertexPositions || !_polyCounts || !_polyConnects) throw std::invalid_argument(" error: meshPointer container is empty.");

		zPointArray vPos;
		zIntArray pConnects;
		zIntArray pCounts;

		for (int i = 0; i < numVerts; i++)
		{
			zVector v;
			v = zVector(_vertexPositions[i * 3 + 0], _vertexPositions[i * 3 + 1], _vertexPositions[i * 3 + 2]);
			vPos.push_back(v);
		}
		int polyconnectsCurrentIndex = 0;
		for (int i = 0; i < numFaces; i++)
		{
			int num_faceVerts = _polyCounts[i];
			pCounts.push_back(_polyCounts[i]);

			for (int j = 0; j < num_faceVerts; j++)
			{
				pConnects.push_back(_polyConnects[polyconnectsCurrentIndex + j]);
			}

			polyconnectsCurrentIndex += num_faceVerts;
		}
		zFnMesh fnMesh(*out_mesh.pointer);
		fnMesh.create(vPos, pCounts, pConnects);
	}

	ZSPACE_EXTERNAL_INLINE zStatusCode ext_mesh_createFromArrays(zExtPointArray& _vertexPositions, zExtIntArray& _polyCounts, zExtIntArray& _polyConnects, zExtMesh& out_mesh)
	{
		try
		{
			out_mesh.checkMemAlloc();
			//out_mesh.pointer = new zObjMesh();
			zFnMesh fnMesh(*out_mesh.pointer);
			fnMesh.create(*_vertexPositions.pointer, *_polyCounts.pointer, *_polyConnects.pointer);
			out_mesh.updateAttributes();
			//printf("\n creatMesh %i %i \n", fnMesh.numVertices(), out_mesh.vCount);

			
		}
		catch (const std::exception&)
		{
			printf("\n Error Creating Mesh!!!");
			return zThrowError;
		}
		return zSuccess;
		
	}

	ZSPACE_EXTERNAL_INLINE zStatusCode ext_mesh_setMeshVertexColors(zExtMesh& extMesh, zExtColorArray& vertexColors)
	{
		try
		{
			zStatus memoryChk = extMesh.checkMemAlloc(false);
			if (memoryChk == zMemNotAllocError) return zMemNotAllocError;
			zFnMesh fnMesh(*extMesh.pointer);
			if (vertexColors.arrayCount != fnMesh.numVertices())
			{
				printf("\n Error Adding colors Mesh! not equal colors and vertices: colors %i | vertex %i", vertexColors.arrayCount, fnMesh.numVertices());
				//std::format("\n Error Adding colors Mesh! not equal colors and vertices: colors {} | vertex {}", vertexColors.arrayCount, fnMesh.numVertices());
				return zFail;
			}
			fnMesh.setVertexColors(*vertexColors.pointer, true);
			zColorArray c;
			fnMesh.getVertexColors(c);

			/*for (int i = 0; i < c.size(); i++)
			{
				printf(" \n mesh set colors input	r %f g %f b %f", vertexColors.pointer->at(i).r, vertexColors.pointer->at(i).g, vertexColors.pointer->at(i).b);
				printf(" \n mesh set colors output	r %f g %f b %f", c.at(i).r, c.at(i).g, c.at(i).b);

			}*/
			extMesh.updateAttributes();
		}
		catch (const std::exception&)
		{
			printf("\n Error Adding colors Mesh!!!");
			return zThrowError;
		}
		return zSuccess;
	}

	ZSPACE_EXTERNAL_INLINE zStatusCode ext_mesh_duplicate(zExtMesh& inObject, zExtMesh& outObject)
	{
		try
		{
			
			zStatus memoryChk = inObject.checkMemAlloc(false);
			if (memoryChk == zMemNotAllocError) return zMemNotAllocError;
			zFnMesh fn(*inObject.pointer);
			outObject.checkMemAlloc();
			*outObject.pointer = zObjMesh(*inObject.pointer);
			outObject.updateAttributes();

			return zSuccess;
		}
		catch (const std::exception&)
		{
			return zThrowError;
		}
	}

	//--------------------------
	//----EXCHANGE METHODS
	//--------------------------

	ZSPACE_EXTERNAL_INLINE zStatusCode ext_mesh_from(char* filePath, zExtMesh& outMesh)
	{
		printf("\n from 0");
		try
		{
			printf("\n from 1");

			outMesh.checkMemAlloc(true);
			zFnMesh fn(*outMesh.pointer);
			std::string str(filePath);
			std::string ext = str.substr(str.find_last_of(".") + 1);
			std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
			cout << endl << ext;
			if (ext == "json") fn.from(filePath, zJSON);
			else if (ext == "obj") fn.from(filePath, zOBJ);
#if defined ZSPACE_USD_INTEROP
			else if (ext == "usd" || ext == "usda") fn.from(filePath, zUSD);
#endif
			//else return zStatus(zInvalidParameter);
			else return zInvalidParameter;
			outMesh.updateAttributes();
			//return zSuccess;

			return zSuccess;
		}
		catch (const std::exception&)
		{
			//return zThrowError;
			return zThrowError;
		}
		
	}

	ZSPACE_EXTERNAL_INLINE zStatusCode ext_mesh_to(zExtMesh& extMesh, char* filePath)
	{
		try
		{
			zStatus memoryChk = extMesh.checkMemAlloc(false);
			if (memoryChk == zMemNotAllocError) return zMemNotAllocError;

			zFnMesh fn(*extMesh.pointer);
			std::string str(filePath);
			std::string ext = str.substr(str.find_last_of(".") + 1);
			std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

			if (ext == "json") fn.to(filePath, zJSON);
			else if (ext == "obj") fn.to(filePath, zOBJ);
#if defined ZSPACE_USD_INTEROP
			else if (ext == "usd" || ext == "usda") fn.to(filePath, zUSD);
#endif
			else return zInvalidParameter;
			return zSuccess;
		}
		catch (const std::exception&)
		{
			return zThrowError;
		}
		
	}

	ZSPACE_EXTERNAL_INLINE zStatusCode ext_mesh_fromJSON(zExtJSON& extJson, zExtMesh& outMesh)
	{
		try
		{
			int memoryChk = extJson.checkMemAlloc(false);
			if (memoryChk != 1 || memoryChk != 2) return zMemNotAllocError;
			outMesh.checkMemAlloc();
			zFnMesh fn(*outMesh.pointer);
			fn.from(*extJson.pointer);
			outMesh.updateAttributes();
			return zSuccess;
		}
		catch (const std::exception&)
		{
			return zThrowError;
		}
	}

	ZSPACE_EXTERNAL_INLINE zStatusCode ext_mesh_toJSON(zExtMesh& extMesh, zExtJSON& outJson)
	{
		try
		{
			zStatus memoryChk = extMesh.checkMemAlloc(false);
			if (memoryChk == zMemNotAllocError) return zMemNotAllocError;
			outJson.checkMemAlloc();
			zFnMesh fn(*extMesh.pointer);
			fn.to(*outJson.pointer);
			outJson.updateAttributes();
			return zSuccess;
		}
		catch (const std::exception&)
		{
			return zThrowError;
		}
	}

#if defined(ZSPACE_USD_INTEROP)  

	ZSPACE_EXTERNAL_INLINE zStatusCode ext_mesh_fromUSD(zExtUSD& extUsd, zExtMesh& outMesh)
	{
		try
		{
			/*zStatus memoryChk = extUsd.checkMemAlloc(false);
			if (memoryChk == zMemNotAllocError) return zMemNotAllocError;*/
			
			int memoryChk = extUsd.checkMemAlloc(false);
			if (memoryChk != 1 || memoryChk != 2) return zMemNotAllocError;
			outMesh.checkMemAlloc();
			zFnMesh fn(*outMesh.pointer);
			fn.from(*extUsd.pointer);
			outMesh.updateAttributes();
			return zSuccess;
		}
		catch (const std::exception&)
		{
			return zThrowError;
		}

	}

	ZSPACE_EXTERNAL_INLINE zStatusCode ext_mesh_toUSD(zExtMesh& extMesh, zExtUSD& extUsd)
	{
		try
		{
			printf("\n tousd 0");
			zStatus memoryChk = extMesh.checkMemAlloc(false);
			printf("\n tousd 1");

			if (memoryChk == zMemNotAllocError) return zMemNotAllocError;
			printf("\n tousd 2");

			extUsd.checkMemAlloc();
			printf("\n tousd 3");

			zFnMesh fn(*extMesh.pointer);
			printf("\n tousd 4");

			fn.to(*extUsd.pointer);
			printf("\n tousd 5");

			//extUsd.updateAttributes();
			printf("\n tousd 6");

			return zSuccess;
		}
		catch (const std::exception&)
		{
			return zThrowError;;
		}
	}

#endif
	
	
	ZSPACE_EXTERNAL_INLINE zStatusCode ext_mesh_getMeshsFromMeshArray(zExtMeshArray& inArray, zExtMesh* outMeshes)
	{
		for (int i = 0; i < inArray.pointer->size(); i++)
		{
			outMeshes[i] = zExtMesh(&inArray.pointer->at(i));
			outMeshes[i].updateAttributes();
		}
	}

	ZSPACE_EXTERNAL_INLINE zStatusCode ext_mesh_getMeshsFromMeshPointerArray(zExtMeshPointerArray& inArray, zExtMesh* outMeshes)
	{
		try
		{
			zStatus memoryChk = inArray.checkMemAlloc(false);
			if (memoryChk == zMemNotAllocError) return zMemNotAllocError;
			for (int i = 0; i < inArray.pointer->size(); i++)
			{
				outMeshes[i] = zExtMesh(inArray.pointer->at(i));
				outMeshes[i].updateAttributes();
			}
		}
		catch (const std::exception&)
		{
			return zThrowError;
		}
		
	}

	ZSPACE_EXTERNAL_INLINE zStatusCode ext_mesh_getVertexPositions(zExtMesh& objMesh, zExtPointArray& extArray)
	{
		try
		{
			zStatus memoryChk = objMesh.checkMemAlloc(false);
			if (memoryChk == zMemNotAllocError) return zMemNotAllocError;
			extArray.checkMemAlloc();
			zFnMesh fn(*objMesh.pointer);
			fn.getVertexPositions(*extArray.pointer);
			extArray.updateAttributes();

			return zSuccess;
		}
		catch (const std::exception&)
		{
			printf("\n ext_mesh_getVertexPositions failed!");
			return zThrowError;
		}
		
	}

	ZSPACE_EXTERNAL_INLINE zStatusCode ext_mesh_getMeshColors(zExtMesh& objMesh, zExtColorArray& extArray)
	{
		try
		{
			zStatus memoryChk = objMesh.checkMemAlloc(false);
			if (memoryChk == zMemNotAllocError) return zMemNotAllocError;
			extArray.checkMemAlloc();

			zFnMesh fn(*objMesh.pointer);
			fn.getVertexColors(*extArray.pointer);
			extArray.updateAttributes();
			return zSuccess;
		}
		catch (const std::exception&)
		{
			printf("\n ext_mesh_getMeshColors failed!");
			return zThrowError;
		}
			
	}

	ZSPACE_EXTERNAL_INLINE zStatusCode ext_mesh_getMeshPolygonDate(zExtMesh& objMesh, zExtIntArray& pCount, zExtIntArray& pConnect)
	{
		pCount.pointer = new zIntArray();
		pConnect.pointer = new zIntArray();

		zFnMesh fn(*objMesh.pointer);
		fn.getPolygonData(*pConnect.pointer, *pCount.pointer);
		pCount.updateAttributes();
		pConnect.updateAttributes();
		return zSuccess;
	}

	ZSPACE_EXTERNAL_INLINE int ext_mesh_smoothMesh(zExtMesh& objMesh, int level, bool smoothCorner, zExtIntArray& fixedVerts, bool smoothFixedEdges)
	{
		printf("\n smooth 0");

		try
		{
			printf("\n smooth 1");

			zStatus memoryChk = objMesh.checkMemAlloc(false);
			if (memoryChk == zMemNotAllocError)
			{
				printf("\n smooth failed");

				//return zMemNotAllocError;
				return (int) (zMemNotAllocError);
			}
			printf("\n smooth 2");

			auto chkArray = fixedVerts.checkMemAlloc(true);
			printf("\n smooth 3");

			objMesh.smoothMesh(level, smoothCorner, *fixedVerts.pointer, smoothFixedEdges);
			printf("\n smooth 4");

			objMesh.updateAttributes();
			printf("\n smooth success");

			//return zSuccess;
			return  (int)(zSuccess);
		}
		catch (const std::exception&)
		{
			printf("\n Catmullclark failed!");
			//return zThrowError;
			return  (int)(zThrowError);
		}
	}

	ZSPACE_EXTERNAL_INLINE zStatusCode ext_mesh_smoothMesh1D(zExtMesh& objMesh, int level, bool smoothCorner, bool flip, zExtIntArray& fixedVerts)
	{
		try
		{
			zStatus memoryChk = objMesh.checkMemAlloc(false);
			if (memoryChk == zMemNotAllocError) return zMemNotAllocError;
			int chkArray = fixedVerts.checkMemAlloc(true);


			objMesh.smoothMesh1D(level, flip, smoothCorner, *fixedVerts.pointer);

			objMesh.updateAttributes();
			printf("\n smooth1d success");

			return zSuccess;
		}
		catch (const std::exception&)
		{
			printf("\n Smooth1D failed!");
			return zThrowError;
		}
	}

	ZSPACE_EXTERNAL_INLINE zStatusCode ext_mesh_getEdgeLoops(zExtMesh& objMesh, zExtGraphArray& graphArrayU, zExtGraphArray& graphArrayV)
	{
		try
		{
			zStatus memoryChk = objMesh.checkMemAlloc(false);
			if (memoryChk == zMemNotAllocError) return zMemNotAllocError;
			/*vector<zItMeshHalfEdgeArray> edgeLoopU, edgeLoopV;
			objMesh.getEdgeLoop(*objMesh.pointer, edgeLoopU, edgeLoopV);

			graphArrayU

			objMesh.updateAttributes();
			printf("\n smooth1d success");*/

			return zSuccess;
		}
		catch (const std::exception&)
		{
			printf("\n ext_mesh_getEdgeLoops failed!");
			return zThrowError;
		}
	}

	ZSPACE_EXTERNAL_INLINE zStatusCode ext_mesh_getEdgeLoopsGraph(zExtMesh& objMesh, zExtGraph& graphU, zExtGraph& graphV)
	{
		try
		{
			zStatus memoryChk = objMesh.checkMemAlloc(false);
			if (memoryChk == zMemNotAllocError) return zMemNotAllocError;

			vector<zItMeshHalfEdgeArray> edgeLoopU, edgeLoopV;
			objMesh.getEdgeLoop(*objMesh.pointer, edgeLoopU, edgeLoopV);
			graphU.checkMemAlloc();
			graphV.checkMemAlloc();
			objMesh.graphFromMeshHEArray(edgeLoopU, *graphU.pointer);
			objMesh.graphFromMeshHEArray(edgeLoopV, *graphV.pointer);

			printf("\n getEdgeLoopsGraph success");

			return zSuccess;
		}
		catch (const std::exception&)
		{
			printf("\n getEdgeLoopsGraph failed!");
			return zThrowError;
		}
	}

	ZSPACE_EXTERNAL_INLINE zStatusCode ext_mesh_checkPlanarity(zExtMesh& objMesh, float tolerance, int planarityType, bool colorFaces, zExtDoubleArray& outDeviations)
	{
		try
		{
			zStatus memoryChk = objMesh.checkMemAlloc(false);
			if (memoryChk == zMemNotAllocError) return zMemNotAllocError;
			outDeviations.checkMemAlloc();

			zFnMesh fn(*objMesh.pointer);
			fn.getPlanarityDeviationPerFace(*outDeviations.pointer, planarityType == 0 ? zPlanarSolverType::zQuadPlanar : zPlanarSolverType::zVolumePlanar, colorFaces, tolerance);
			outDeviations.updateAttributes();
			objMesh.updateAttributes();
			return zSuccess;
		}
		catch (const std::exception&)
		{
			printf("\n planarity failed!");
			return zThrowError;
		}
	}

	ZSPACE_EXTERNAL_INLINE zStatusCode ext_mesh_getFaceColor(zExtMesh& objMesh, zExtColorArray& extPointArray)
	{
		try
		{
			zStatus memoryChk = objMesh.checkMemAlloc(false);
			if (memoryChk == zMemNotAllocError) return zMemNotAllocError;
			extPointArray.checkMemAlloc();
			zFnMesh fn(*objMesh.pointer);
			fn.getFaceColors(*extPointArray.pointer);
			extPointArray.updateAttributes();
			return zSuccess;
		}
		catch (const std::exception&)
		{
			printf("\n getFaceColor failed!");
			return zThrowError;
		}
	}



	ZSPACE_EXTERNAL_INLINE zStatusCode ext_mesh_getVertexPositionsRaw(zExtMesh& objMesh, float* outVPostions, float* outVColors)
	{
		zStatus memoryChk = objMesh.checkMemAlloc(false);
		if (memoryChk == zMemNotAllocError) return zMemNotAllocError;
		zFnMesh fn(*objMesh.pointer);
		zPoint* pts = fn.getRawVertexPositions();
		zColor* colors = fn.getRawVertexColors();
		for (int i = 0; i < fn.numVertices(); i++)
		{
			outVPostions[i * 3 + 0] = pts[i].x;
			outVPostions[i * 3 + 1] = pts[i].y;
			outVPostions[i * 3 + 2] = pts[i].z;

			outVColors[i * 4 + 0] = colors[i].r;
			outVColors[i * 4 + 1] = colors[i].g;
			outVColors[i * 4 + 2] = colors[i].b;
			outVColors[i * 4 + 3] = colors[i].a;
		}
		return zSuccess;
	}
	ZSPACE_EXTERNAL_INLINE zStatusCode ext_mesh_getMeshFaceCounts(zExtMesh& objMesh, int* outfCounts)
	{
		try
		{
			zStatus memoryChk = objMesh.checkMemAlloc(false);
			if (memoryChk == zMemNotAllocError) return zMemNotAllocError;

			zFnMesh fn(*objMesh.pointer);
			zIntArray pCounts;
			zIntArray pConnects;
			fn.getPolygonData(pConnects, pCounts);
			for (int i = 0; i < pCounts.size(); i++)
			{
				outfCounts[i] = pCounts[i];
			}
			return zSuccess;
		}
		catch (const std::exception&)
		{
			printf("\n getMeshFaceCounts failed!");
			return zThrowError;
		}
		
	}
	ZSPACE_EXTERNAL_INLINE zStatusCode ext_mesh_getMeshFaceConnect(zExtMesh& objMesh, int* outfConnects)
	{
		try
		{
			zStatus memoryChk = objMesh.checkMemAlloc(false);
			if (memoryChk == zMemNotAllocError) return zMemNotAllocError;

			zFnMesh fn(*objMesh.pointer);
			zIntArray pCounts;
			zIntArray pConnects;
			fn.getPolygonData(pConnects, pCounts);
			for (int i = 0; i < pConnects.size(); i++)
			{
				outfConnects[i] = pConnects[i];
			}
			return zSuccess;
		}
		catch (const std::exception&)
		{
			printf("\n getFaceColor failed!");
			return zThrowError;
		}
		
	}

	ZSPACE_EXTERNAL_INLINE zStatusCode ext_mesh_getMeshCentre(zExtMesh& objMesh, float* outCentre)
	{
		try
		{
			zStatus memoryChk = objMesh.checkMemAlloc(false);
			if (memoryChk == zMemNotAllocError) return zMemNotAllocError;

			zFnMesh fn(*objMesh.pointer);
			zPoint pt = fn.getCenter();
			outCentre[0] = pt.x;
			outCentre[1] = pt.y;
			outCentre[2] = pt.z;

			return zSuccess;
		}
		catch (const std::exception&)
		{
			printf("\n getFaceCentre failed!");
			return zThrowError;
		}
		
	}
	ZSPACE_EXTERNAL_INLINE zStatusCode ext_mesh_getPlanarityDeviationPerFace(zExtMesh& objMesh, zExtDoubleArray& outPlanarityDevs, int type, bool colorFaces , double tolerance )
	{
		try
		{
			zDoubleArray devs;
			zFnMesh fn(*objMesh.pointer);
			zPlanarSolverType solverType;
			if (type == 0)
			{
				solverType = zPlanarSolverType::zQuadPlanar;
			}
			else
			{
				solverType = zPlanarSolverType::zVolumePlanar;
			}
			fn.getPlanarityDeviationPerFace(devs, solverType, colorFaces, tolerance);
			outPlanarityDevs = zExtDoubleArray(devs);
		}
		catch (const std::exception&)
		{
			printf("\n Planarity Deviation Check Failed!");
			return zThrowError;
		}
	}

	ZSPACE_EXTERNAL_INLINE zStatusCode ext_mesh_getGaussianCurvature(zExtMesh& objMesh, zExtDoubleArray& outGaussianCurvature )
	{
		try
		{
			zStatus memoryChk = objMesh.checkMemAlloc(false);
			if (memoryChk == zMemNotAllocError) return zMemNotAllocError;
			zDoubleArray gaussiancurv;
			zFnMesh fn(*objMesh.pointer);
			fn.getGaussianCurvature(gaussiancurv);
			outGaussianCurvature = zDoubleArray(gaussiancurv);
		}

		catch (const std::exception&)
		{
			printf("\n Check GaussianCurvature Failed!");
			return zThrowError;
		}
	}

	ZSPACE_EXTERNAL_INLINE zPoint ext_mesh_meshTest(int num)
	{
		printf("\n TEST C++ %i", num);
		//return zStatus((zStatusCode)num);
		return zPoint(0,0,10);

	}
	ZSPACE_EXTERNAL_INLINE int ext_mesh_meshTest2(zStatus2& num)
	{
		printf("\n TEST2 C++ %i", num.statusCode);
		//return zStatus((zStatusCode)num);
		return (int) num.statusCode;

	}

}