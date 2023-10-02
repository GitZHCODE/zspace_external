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


#include<headers/zCore/zExtMesh.h>


namespace zSpace
{
	

	ZSPACE_EXTERNAL_INLINE zExtMesh::zExtMesh(zObjMesh* m)
	{
		extPointer = m;
		updateAttributes();
	}

	ZSPACE_EXTERNAL_INLINE zExtMesh::zExtMesh()
	{
		//extPointer = new zObjMesh();
	}

	ZSPACE_EXTERNAL_INLINE void zExtMesh::updateAttributes()
	{
		zFnMesh fn(*extPointer);
		vCount = fn.numVertices();
		fCount = fn.numPolygons();

		//fn.getVertexPositions(*verticesArray.pointer);
		//verticesArray.updateAttributes();

		//fn.getVertexColors(*colorsArray.pointer);
		//colorsArray.updateAttributes();


	}
	ZSPACE_EXTERNAL_INLINE bool zExtMesh::createMeshFromJson(json* jsonPointer) //Should be moved to core
	{

		extPointer = new zObjMesh();

		/*for (auto& element : pointer->items())
		{
			const auto& key = element.key();
			string k = element.key();
			printf("\n MeshFromJSON() %s", k.c_str());

		}*/

		zUtilsJsonHE meshJSON;

		zFnMesh fnMesh(*extPointer);



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
		extPointer->mesh.clear();

		extPointer->mesh.vertices.assign(meshJSON.vertices.size(), zVertex());
		extPointer->mesh.halfEdges.assign(meshJSON.halfedges.size(), zHalfEdge());

		int numE = (int)floor(meshJSON.halfedges.size() * 0.5);
		extPointer->mesh.edges.assign(numE, zEdge());
		extPointer->mesh.faces.assign(meshJSON.faces.size(), zFace());

		extPointer->mesh.vHandles.assign(meshJSON.vertices.size(), zVertexHandle());
		extPointer->mesh.eHandles.assign(numE, zEdgeHandle());
		extPointer->mesh.heHandles.assign(meshJSON.halfedges.size(), zHalfEdgeHandle());
		extPointer->mesh.fHandles.assign(meshJSON.faces.size(), zFaceHandle());

		// set IDs
		for (int i = 0; i < meshJSON.vertices.size(); i++) extPointer->mesh.vertices[i].setId(i);
		for (int i = 0; i < meshJSON.halfedges.size(); i++) extPointer->mesh.halfEdges[i].setId(i);
		for (int i = 0; i < meshJSON.faces.size(); i++) extPointer->mesh.faces[i].setId(i);



		// set Pointers
		int n_v = 0;
		for (zItMeshVertex v(*extPointer); !v.end(); v++)
		{
			v.setId(n_v);

			if (meshJSON.vertices[n_v] != -1)
			{
				zItMeshHalfEdge he(*extPointer, meshJSON.vertices[n_v]);;
				v.setHalfEdge(he);

				extPointer->mesh.vHandles[n_v].id = n_v;
				extPointer->mesh.vHandles[n_v].he = meshJSON.vertices[n_v];
			}

			n_v++;
		}
		extPointer->mesh.setNumVertices(n_v);

		int n_he = 0;
		int n_e = 0;

		for (zItMeshHalfEdge he(*extPointer); !he.end(); he++)
		{
			// Half Edge
			he.setId(n_he);
			extPointer->mesh.heHandles[n_he].id = n_he;

			if (meshJSON.halfedges[n_he][0] != -1)
			{
				zItMeshHalfEdge hePrev(*extPointer, meshJSON.halfedges[n_he][0]);
				he.setPrev(hePrev);

				extPointer->mesh.heHandles[n_he].p = meshJSON.halfedges[n_he][0];
			}

			if (meshJSON.halfedges[n_he][1] != -1)
			{
				zItMeshHalfEdge heNext(*extPointer, meshJSON.halfedges[n_he][1]);
				he.setNext(heNext);

				extPointer->mesh.heHandles[n_he].n = meshJSON.halfedges[n_he][1];
			}

			if (meshJSON.halfedges[n_he][2] != -1)
			{
				zItMeshVertex v(*extPointer, meshJSON.halfedges[n_he][2]);
				he.setVertex(v);

				extPointer->mesh.heHandles[n_he].v = meshJSON.halfedges[n_he][2];
			}

			if (meshJSON.halfedges[n_he][3] != -1)
			{
				zItMeshFace f(*extPointer, meshJSON.halfedges[n_he][3]);
				he.setFace(f);

				extPointer->mesh.heHandles[n_he].f = meshJSON.halfedges[n_he][3];
			}

			// symmetry half edges && Edge
			if (n_he % 2 == 1)
			{
				zItMeshHalfEdge heSym(*extPointer, n_he - 1);
				he.setSym(heSym);

				zItMeshEdge e(*extPointer, n_e);
				e.setId(n_e);

				e.setHalfEdge(heSym, 0);
				e.setHalfEdge(he, 1);

				he.setEdge(e);
				heSym.setEdge(e);

				extPointer->mesh.heHandles[n_he].e = n_e;
				extPointer->mesh.heHandles[n_he - 1].e = n_e;

				extPointer->mesh.eHandles[n_e].id = n_e;
				extPointer->mesh.eHandles[n_e].he0 = n_he - 1;
				extPointer->mesh.eHandles[n_e].he1 = n_he;

				n_e++;
			}

			n_he++;
		}

		extPointer->mesh.setNumEdges(n_e);

		int n_f = 0;

		for (zItMeshFace f(*extPointer); !f.end(); f++)
		{
			f.setId(n_f);

			if (meshJSON.vertices[n_f] != -1)
			{
				zItMeshHalfEdge he(*extPointer, meshJSON.faces[n_f]);
				f.setHalfEdge(he);

				extPointer->mesh.fHandles[n_f].id = n_f;
				extPointer->mesh.fHandles[n_f].he = meshJSON.faces[n_f];
			}

			n_f++;
		}
		extPointer->mesh.setNumPolygons(n_f);

		//// Vertex Attributes
		meshJSON.vertexAttributes = (*jsonPointer)["VertexAttributes"].get<vector<vector<double>>>();
		//printf("\n vertexAttributes: %zi %zi", vertexAttributes.size(), vertexAttributes[0].size());

		extPointer->mesh.vertexPositions.clear();
		extPointer->mesh.vertexNormals.clear();
		extPointer->mesh.vertexColors.clear();
		extPointer->mesh.vertexWeights.clear();
		for (int i = 0; i < meshJSON.vertexAttributes.size(); i++)
		{
			for (int k = 0; k < meshJSON.vertexAttributes[i].size(); k++)
			{
				// position, normal and color

				if (meshJSON.vertexAttributes[i].size() == 9)
				{
					zVector pos(meshJSON.vertexAttributes[i][k], meshJSON.vertexAttributes[i][k + 1], meshJSON.vertexAttributes[i][k + 2]);
					extPointer->mesh.vertexPositions.push_back(pos);

					zVector normal(meshJSON.vertexAttributes[i][k + 3], meshJSON.vertexAttributes[i][k + 4], meshJSON.vertexAttributes[i][k + 5]);
					extPointer->mesh.vertexNormals.push_back(normal);

					zColor col(meshJSON.vertexAttributes[i][k + 6], meshJSON.vertexAttributes[i][k + 7], meshJSON.vertexAttributes[i][k + 8], 1);
					extPointer->mesh.vertexColors.push_back(col);

					extPointer->mesh.vertexWeights.push_back(2.0);

					k += 8;
				}

				// position, normal
				if (meshJSON.vertexAttributes[i].size() == 6)
				{
					zVector pos(meshJSON.vertexAttributes[i][k], meshJSON.vertexAttributes[i][k + 1], meshJSON.vertexAttributes[i][k + 2]);
					extPointer->mesh.vertexPositions.push_back(pos);

					zVector normal(meshJSON.vertexAttributes[i][k + 3], meshJSON.vertexAttributes[i][k + 4], meshJSON.vertexAttributes[i][k + 5]);
					extPointer->mesh.vertexNormals.push_back(normal);

					extPointer->mesh.vertexColors.push_back(zColor(1, 0, 0, 1));

					extPointer->mesh.vertexWeights.push_back(2.0);

					k += 5;
				}

				// BRG position, normal and color, thickness
				if (meshJSON.vertexAttributes[i].size() == 15)
				{
					zVector pos(meshJSON.vertexAttributes[i][k], meshJSON.vertexAttributes[i][k + 1], meshJSON.vertexAttributes[i][k + 2]);
					extPointer->mesh.vertexPositions.push_back(pos);

					zVector normal(meshJSON.vertexAttributes[i][k + 3], meshJSON.vertexAttributes[i][k + 4], meshJSON.vertexAttributes[i][k + 5]);
					extPointer->mesh.vertexNormals.push_back(normal);

					zColor col(meshJSON.vertexAttributes[i][k + 6], meshJSON.vertexAttributes[i][k + 7], meshJSON.vertexAttributes[i][k + 8], 1);
					extPointer->mesh.vertexColors.push_back(col);

					extPointer->mesh.vertexWeights.push_back(2.0);

					k += 14;
				}


				// position, normal
				if (meshJSON.vertexAttributes[i].size() == 8)
				{
					zVector pos(meshJSON.vertexAttributes[i][k], meshJSON.vertexAttributes[i][k + 1], meshJSON.vertexAttributes[i][k + 2]);
					extPointer->mesh.vertexPositions.push_back(pos);

					zVector normal(meshJSON.vertexAttributes[i][k + 3], meshJSON.vertexAttributes[i][k + 4], meshJSON.vertexAttributes[i][k + 5]);
					extPointer->mesh.vertexNormals.push_back(normal);

					extPointer->mesh.vertexColors.push_back(zColor(1, 0, 0, 1));

					extPointer->mesh.vertexWeights.push_back(2.0);

					k += 7;
				}

			}
		}

		// Edge Attributes
		//meshJSON.halfedgeAttributes = j["HalfedgeAttributes"].get<vector<vector<double>>>();

		extPointer->mesh.edgeColors.clear();
		extPointer->mesh.edgeWeights.clear();
		if (meshJSON.halfedgeAttributes.size() == 0)
		{
			for (int i = 0; i < extPointer->mesh.n_e; i++)
			{
				extPointer->mesh.edgeColors.push_back(zColor());
				extPointer->mesh.edgeWeights.push_back(1.0);
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

					extPointer->mesh.edgeColors.push_back(col);
					extPointer->mesh.edgeWeights.push_back(1.0);

				}
			}
		}

		// face Attributes
		meshJSON.faceAttributes = (*jsonPointer)["FaceAttributes"].get<vector<vector<double>>>();

		extPointer->mesh.faceColors.clear();
		extPointer->mesh.faceNormals.clear();
		for (int i = 0; i < meshJSON.faceAttributes.size(); i++)
		{
			for (int k = 0; k < meshJSON.faceAttributes[i].size(); k++)
			{
				// normal and color
				if (meshJSON.faceAttributes[i].size() == 6)
				{
					zColor col(meshJSON.faceAttributes[i][k + 3], meshJSON.faceAttributes[i][k + 4], meshJSON.faceAttributes[i][k + 5], 1);
					extPointer->mesh.faceColors.push_back(col);

					zVector normal(meshJSON.faceAttributes[i][k], meshJSON.faceAttributes[i][k + 1], meshJSON.faceAttributes[i][k + 2]);
					extPointer->mesh.faceNormals.push_back(normal);

					k += 5;
				}

				if (meshJSON.faceAttributes[i].size() == 3)
				{
					zVector normal(meshJSON.faceAttributes[i][k], meshJSON.faceAttributes[i][k + 1], meshJSON.faceAttributes[i][k + 2]);
					extPointer->mesh.faceNormals.push_back(normal);

					extPointer->mesh.faceColors.push_back(zColor(0.5, 0.5, 0.5, 1));

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
		for (int i = 0; i < extPointer->mesh.vertexPositions.size(); i++)
		{
			extPointer->mesh.addToPositionMap(extPointer->mesh.vertexPositions[i], i);
		}

		for (zItMeshEdge e(*extPointer); !e.end(); e++)
		{
			int v1 = e.getHalfEdge(0).getVertex().getId();
			int v2 = e.getHalfEdge(1).getVertex().getId();

			extPointer->mesh.addToHalfEdgesMap(v1, v2, e.getHalfEdge(0).getId());
		}

		printf("\n extPointer: %i %i %i ", fnMesh.numVertices(), fnMesh.numEdges(), fnMesh.numPolygons());
	
		//set static container
		extPointer->mesh.staticGeometry = true;

		vector<vector<int>> edgeVerts;

		for (zItMeshEdge e(*extPointer); !e.end(); e++)
		{
			vector<int> verts;
			e.getVertices(verts);

			edgeVerts.push_back(verts);
		}

		extPointer->mesh.setStaticEdgeVertices(edgeVerts);

		vector<vector<int>> faceVerts;

		for (zItMeshFace f(*extPointer); !f.end(); f++)
		{
			vector<int> verts;
			f.getVertices(verts);

			faceVerts.push_back(verts);
		}

		extPointer->mesh.setStaticFaceVertices(faceVerts);


		updateAttributes();

		return true;
	}
	ZSPACE_EXTERNAL_INLINE bool zExtMesh::createMeshFromJson(string infilename)
	{

		zFnMesh fnmesh(*extPointer);


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
		extPointer->mesh.clear();

		extPointer->mesh.vertices.assign(meshJSON.vertices.size(), zVertex());
		extPointer->mesh.halfEdges.assign(meshJSON.halfedges.size(), zHalfEdge());

		int numE = (int)floor(meshJSON.halfedges.size() * 0.5);
		extPointer->mesh.edges.assign(numE, zEdge());
		extPointer->mesh.faces.assign(meshJSON.faces.size(), zFace());

		extPointer->mesh.vHandles.assign(meshJSON.vertices.size(), zVertexHandle());
		extPointer->mesh.eHandles.assign(numE, zEdgeHandle());
		extPointer->mesh.heHandles.assign(meshJSON.halfedges.size(), zHalfEdgeHandle());
		extPointer->mesh.fHandles.assign(meshJSON.faces.size(), zFaceHandle());

		// set IDs
		for (int i = 0; i < meshJSON.vertices.size(); i++) extPointer->mesh.vertices[i].setId(i);
		for (int i = 0; i < meshJSON.halfedges.size(); i++) extPointer->mesh.halfEdges[i].setId(i);
		for (int i = 0; i < meshJSON.faces.size(); i++) extPointer->mesh.faces[i].setId(i);

		//printf("\n nV %i | nHE %i | nP %i ", meshJSON.vertices.size(), meshJSON.halfedges.size(), meshJSON.faces.size());

		// set Pointers
		int n_v = 0;
		for (zItMeshVertex v(*extPointer); !v.end(); v++)
		{
			v.setId(n_v);

			if (meshJSON.vertices[n_v] != -1)
			{
				zItMeshHalfEdge he(*extPointer, meshJSON.vertices[n_v]);;
				v.setHalfEdge(he);

				extPointer->mesh.vHandles[n_v].id = n_v;
				extPointer->mesh.vHandles[n_v].he = meshJSON.vertices[n_v];
			}

			n_v++;
		}
		extPointer->mesh.setNumVertices(n_v);

		int n_he = 0;
		int n_e = 0;

		for (zItMeshHalfEdge he(*extPointer); !he.end(); he++)
		{
			// Half Edge
			he.setId(n_he);
			extPointer->mesh.heHandles[n_he].id = n_he;

			if (meshJSON.halfedges[n_he][0] != -1)
			{
				zItMeshHalfEdge hePrev(*extPointer, meshJSON.halfedges[n_he][0]);
				he.setPrev(hePrev);

				extPointer->mesh.heHandles[n_he].p = meshJSON.halfedges[n_he][0];
			}

			if (meshJSON.halfedges[n_he][1] != -1)
			{
				zItMeshHalfEdge heNext(*extPointer, meshJSON.halfedges[n_he][1]);
				he.setNext(heNext);

				extPointer->mesh.heHandles[n_he].n = meshJSON.halfedges[n_he][1];
			}

			if (meshJSON.halfedges[n_he][2] != -1)
			{
				zItMeshVertex v(*extPointer, meshJSON.halfedges[n_he][2]);
				he.setVertex(v);

				extPointer->mesh.heHandles[n_he].v = meshJSON.halfedges[n_he][2];
			}

			if (meshJSON.halfedges[n_he][3] != -1)
			{
				zItMeshFace f(*extPointer, meshJSON.halfedges[n_he][3]);
				he.setFace(f);

				extPointer->mesh.heHandles[n_he].f = meshJSON.halfedges[n_he][3];
			}

			// symmetry half edges && Edge
			if (n_he % 2 == 1)
			{
				zItMeshHalfEdge heSym(*extPointer, n_he - 1);
				he.setSym(heSym);

				zItMeshEdge e(*extPointer, n_e);
				e.setId(n_e);

				e.setHalfEdge(heSym, 0);
				e.setHalfEdge(he, 1);

				he.setEdge(e);
				heSym.setEdge(e);

				extPointer->mesh.heHandles[n_he].e = n_e;
				extPointer->mesh.heHandles[n_he - 1].e = n_e;

				extPointer->mesh.eHandles[n_e].id = n_e;
				extPointer->mesh.eHandles[n_e].he0 = n_he - 1;
				extPointer->mesh.eHandles[n_e].he1 = n_he;

				n_e++;
			}

			n_he++;
		}

		extPointer->mesh.setNumEdges(n_e);

		int n_f = 0;

		for (zItMeshFace f(*extPointer); !f.end(); f++)
		{
			f.setId(n_f);

			if (meshJSON.vertices[n_f] != -1)
			{
				zItMeshHalfEdge he(*extPointer, meshJSON.faces[n_f]);
				f.setHalfEdge(he);

				extPointer->mesh.fHandles[n_f].id = n_f;
				extPointer->mesh.fHandles[n_f].he = meshJSON.faces[n_f];
			}

			n_f++;
		}
		extPointer->mesh.setNumPolygons(n_f);

		//// Vertex Attributes
		meshJSON.vertexAttributes = j["VertexAttributes"].get<vector<vector<double>>>();
		//printf("\n vertexAttributes: %zi %zi", vertexAttributes.size(), vertexAttributes[0].size());

		extPointer->mesh.vertexPositions.clear();
		extPointer->mesh.vertexNormals.clear();
		extPointer->mesh.vertexColors.clear();
		extPointer->mesh.vertexWeights.clear();
		for (int i = 0; i < meshJSON.vertexAttributes.size(); i++)
		{
			for (int k = 0; k < meshJSON.vertexAttributes[i].size(); k++)
			{
				// position, normal and color

				if (meshJSON.vertexAttributes[i].size() == 9)
				{
					zVector pos(meshJSON.vertexAttributes[i][k], meshJSON.vertexAttributes[i][k + 1], meshJSON.vertexAttributes[i][k + 2]);
					extPointer->mesh.vertexPositions.push_back(pos);

					zVector normal(meshJSON.vertexAttributes[i][k + 3], meshJSON.vertexAttributes[i][k + 4], meshJSON.vertexAttributes[i][k + 5]);
					extPointer->mesh.vertexNormals.push_back(normal);

					zColor col(meshJSON.vertexAttributes[i][k + 6], meshJSON.vertexAttributes[i][k + 7], meshJSON.vertexAttributes[i][k + 8], 1);
					extPointer->mesh.vertexColors.push_back(col);

					extPointer->mesh.vertexWeights.push_back(2.0);

					k += 8;
				}

				// position, normal
				if (meshJSON.vertexAttributes[i].size() == 6)
				{
					zVector pos(meshJSON.vertexAttributes[i][k], meshJSON.vertexAttributes[i][k + 1], meshJSON.vertexAttributes[i][k + 2]);
					extPointer->mesh.vertexPositions.push_back(pos);

					zVector normal(meshJSON.vertexAttributes[i][k + 3], meshJSON.vertexAttributes[i][k + 4], meshJSON.vertexAttributes[i][k + 5]);
					extPointer->mesh.vertexNormals.push_back(normal);

					extPointer->mesh.vertexColors.push_back(zColor(1, 0, 0, 1));

					extPointer->mesh.vertexWeights.push_back(2.0);

					k += 5;
				}

				// BRG position, normal and color, thickness
				if (meshJSON.vertexAttributes[i].size() == 15)
				{
					zVector pos(meshJSON.vertexAttributes[i][k], meshJSON.vertexAttributes[i][k + 1], meshJSON.vertexAttributes[i][k + 2]);
					extPointer->mesh.vertexPositions.push_back(pos);

					zVector normal(meshJSON.vertexAttributes[i][k + 3], meshJSON.vertexAttributes[i][k + 4], meshJSON.vertexAttributes[i][k + 5]);
					extPointer->mesh.vertexNormals.push_back(normal);

					zColor col(meshJSON.vertexAttributes[i][k + 6], meshJSON.vertexAttributes[i][k + 7], meshJSON.vertexAttributes[i][k + 8], 1);
					extPointer->mesh.vertexColors.push_back(col);

					extPointer->mesh.vertexWeights.push_back(2.0);

					k += 14;
				}


				// position, normal
				if (meshJSON.vertexAttributes[i].size() == 8)
				{
					zVector pos(meshJSON.vertexAttributes[i][k], meshJSON.vertexAttributes[i][k + 1], meshJSON.vertexAttributes[i][k + 2]);
					extPointer->mesh.vertexPositions.push_back(pos);

					zVector normal(meshJSON.vertexAttributes[i][k + 3], meshJSON.vertexAttributes[i][k + 4], meshJSON.vertexAttributes[i][k + 5]);
					extPointer->mesh.vertexNormals.push_back(normal);

					extPointer->mesh.vertexColors.push_back(zColor(1, 0, 0, 1));

					extPointer->mesh.vertexWeights.push_back(2.0);

					k += 7;
				}

			}
		}

		// Edge Attributes
		//meshJSON.halfedgeAttributes = j["HalfedgeAttributes"].get<vector<vector<double>>>();

		extPointer->mesh.edgeColors.clear();
		extPointer->mesh.edgeWeights.clear();
		if (meshJSON.halfedgeAttributes.size() == 0)
		{
			for (int i = 0; i < extPointer->mesh.n_e; i++)
			{
				extPointer->mesh.edgeColors.push_back(zColor());
				extPointer->mesh.edgeWeights.push_back(1.0);
			}
		}
		else
		{

			/*for (int i = 0; i < extPointer->mesh.n_e; i++)
			{
				extPointer->mesh.edgeColors.push_back(zColor());
				extPointer->mesh.edgeWeights.push_back(1.0);
			}*/

			for (int i = 0; i < meshJSON.halfedgeAttributes.size(); i += 2)
			{
				// color
				if (meshJSON.halfedgeAttributes[i].size() == 3)
				{
					zColor col(meshJSON.halfedgeAttributes[i][0], meshJSON.halfedgeAttributes[i][1], meshJSON.halfedgeAttributes[i][2], 1);

					extPointer->mesh.edgeColors.push_back(col);
					extPointer->mesh.edgeWeights.push_back(1.0);

				}
			}
		}

		// face Attributes
		meshJSON.faceAttributes = j["FaceAttributes"].get<vector<vector<double>>>();

		extPointer->mesh.faceColors.clear();
		extPointer->mesh.faceNormals.clear();
		for (int i = 0; i < meshJSON.faceAttributes.size(); i++)
		{
			for (int k = 0; k < meshJSON.faceAttributes[i].size(); k++)
			{
				// normal and color
				if (meshJSON.faceAttributes[i].size() == 6)
				{
					zColor col(meshJSON.faceAttributes[i][k + 3], meshJSON.faceAttributes[i][k + 4], meshJSON.faceAttributes[i][k + 5], 1);
					extPointer->mesh.faceColors.push_back(col);

					zVector normal(meshJSON.faceAttributes[i][k], meshJSON.faceAttributes[i][k + 1], meshJSON.faceAttributes[i][k + 2]);
					extPointer->mesh.faceNormals.push_back(normal);

					k += 5;
				}

				if (meshJSON.faceAttributes[i].size() == 3)
				{
					zVector normal(meshJSON.faceAttributes[i][k], meshJSON.faceAttributes[i][k + 1], meshJSON.faceAttributes[i][k + 2]);
					extPointer->mesh.faceNormals.push_back(normal);

					extPointer->mesh.faceColors.push_back(zColor(0.5, 0.5, 0.5, 1));

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
		for (int i = 0; i < extPointer->mesh.vertexPositions.size(); i++)
		{
			extPointer->mesh.addToPositionMap(extPointer->mesh.vertexPositions[i], i);
		}

		for (zItMeshEdge e(*extPointer); !e.end(); e++)
		{
			int v1 = e.getHalfEdge(0).getVertex().getId();
			int v2 = e.getHalfEdge(1).getVertex().getId();

			extPointer->mesh.addToHalfEdgesMap(v1, v2, e.getHalfEdge(0).getId());
		}

		printf("\n mesh: nV %i - nE %i - nF %i ", fnmesh.numVertices(), fnmesh.numEdges(), fnmesh.numPolygons());

		return true;




	}

	ZSPACE_EXTERNAL_INLINE zExtMeshArray::zExtMeshArray(zObjMeshArray* m)
	{
		pointer = m;
		updateAttributes();
	}

	ZSPACE_EXTERNAL_INLINE void zExtMeshArray::updateAttributes()
	{
		arrayCount = pointer->size();
	}

	ZSPACE_EXTERNAL_INLINE zExtMeshPointerArray::zExtMeshPointerArray(zObjMeshPointerArray* m)
	{
		pointer = m;
		updateAttributes();
	}

	ZSPACE_EXTERNAL_INLINE void zExtMeshPointerArray::updateAttributes()
	{
		arrayCount = pointer->size();
	}
	
	ZSPACE_EXTERNAL_INLINE void ext_meshUtil_createMeshOBJFromRawArray(double* _vertexPositions, int* _polyCounts, int* _polyConnects, int numVerts, int numFaces, zExtMesh& out_mesh)
	{
		if (!_vertexPositions || !_polyCounts || !_polyConnects) throw std::invalid_argument(" error: extPointer container is empty.");

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
		zFnMesh fnMesh(*out_mesh.extPointer);
		fnMesh.create(vPos, pCounts, pConnects);
	}

	ZSPACE_EXTERNAL_INLINE int ext_meshUtil_createMeshOBJFromArray(zExtPointArray& _vertexPositions, zExtIntArray& _polyCounts, zExtIntArray& _polyConnects, zExtMesh& out_mesh)
	{
		try
		{
			out_mesh.extPointer = new zObjMesh();
			zFnMesh fnMesh(*out_mesh.extPointer);
			fnMesh.create(*_vertexPositions.pointer, *_polyCounts.pointer, *_polyConnects.pointer);
			out_mesh.updateAttributes();
			
		}
		catch (const std::exception&)
		{
			printf("\n Error Creating Mesh!!!");
			return 0;
		}
		return 1;
		
	}

	ZSPACE_EXTERNAL_INLINE int ext_meshUtil_setMeshVertexColors(zExtMesh& extMesh, zExtColorArray& vertexColors)
	{
		try
		{
			zFnMesh fnMesh(*extMesh.extPointer);
			if (vertexColors.arrayCount != fnMesh.numVertices())
			{
				printf("\n Error Adding colors Mesh! not equal colors and vertices: colors %i | vertex %i", vertexColors.arrayCount, fnMesh.numVertices());
				return 0;
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
			return 0;
		}
		return 1;
	}

	ZSPACE_EXTERNAL_INLINE void ext_meshUtil_createMeshOBJFromFile(char* filePath, zExtMesh& out_mesh)
	{
		string pathSt(filePath);
		filesystem::path file_path(pathSt);
		string fileExtension = file_path.extension().string();
		transform(fileExtension.begin(), fileExtension.end(), fileExtension.begin(), [](unsigned char c) { return std::tolower(c); });

		zFnMesh fnMesh(*out_mesh.extPointer);

		if (fileExtension == ".jsonPointer")
		{
			fnMesh.from(pathSt, zOBJ);
		}
		else if (fileExtension == ".json")
		{
			fnMesh.from(pathSt, zJSON);
		}
	}

	ZSPACE_EXTERNAL_INLINE void ext_meshUtil_exportToJson(zExtMesh& mesh, char* filePath)
	{
		zFnMesh fn(*mesh.extPointer);
		fn.to(filePath, zSpace::zFileTpye::zJSON);
	}

	ZSPACE_EXTERNAL_INLINE int ext_meshUtil_getMeshsFromMeshArray(zExtMeshArray& inArray, zExtMesh* outMeshes)
	{
		for (int i = 0; i < inArray.pointer->size(); i++)
		{
			outMeshes[i] = zExtMesh(&inArray.pointer->at(i));
			outMeshes[i].updateAttributes();
		}
	}

	ZSPACE_EXTERNAL_INLINE int ext_meshUtil_getMeshsFromMeshPointerArray(zExtMeshPointerArray& inArray, zExtMesh* outMeshes)
	{
		for (int i = 0; i < inArray.pointer->size(); i++)
		{
			outMeshes[i] = zExtMesh(inArray.pointer->at(i));
			outMeshes[i].updateAttributes();
		}
	}

	ZSPACE_EXTERNAL_INLINE int ext_meshUtil_getMeshPosition(zExtMesh& objMesh, zExtPointArray& extArray)
	{
		extArray.pointer = new zPointArray();

		zFnMesh fn(*objMesh.extPointer);
		fn.getVertexPositions(*extArray.pointer);
		extArray.updateAttributes();

		return 1;
	}

	ZSPACE_EXTERNAL_INLINE int ext_meshUtil_getMeshColors(zExtMesh& objMesh, zExtColorArray& extArray)
	{
		extArray.pointer = new zColorArray();
		zFnMesh fn(*objMesh.extPointer);
		fn.getVertexColors(*extArray.pointer);
		zColorArray c;
		fn.getVertexColors(c);
		for (int i = 0; i < extArray.pointer->size(); i++)
		{
			//printf(" \n mesh get colors extArray	r %f g %f b %f", extArray.pointer->at(i).r, extArray.pointer->at(i).g, extArray.pointer->at(i).b);
			//printf(" \n mesh get colors zColorArray	r %f g %f b %f", c.at(i).r, c.at(i).g, c.at(i).b);

		}
		extArray.updateAttributes();
		return 1;
	}

	ZSPACE_EXTERNAL_INLINE int ext_meshUtil_getMeshPolygonDate(zExtMesh& objMesh, zExtIntArray& pCount, zExtIntArray& pConnect)
	{
		pCount.pointer = new zIntArray();
		pConnect.pointer = new zIntArray();

		zFnMesh fn(*objMesh.extPointer);
		fn.getPolygonData(*pConnect.pointer, *pCount.pointer);
		pCount.updateAttributes();
		pConnect.updateAttributes();
		return 1;
	}

	ZSPACE_EXTERNAL_INLINE int ext_meshUtil_catmullclark(zExtMesh& objMesh, int level, bool fixedCorner)
	{
		try
		{

			zFnMesh fn(*objMesh.extPointer);
			fn.smoothMesh(level, !fixedCorner);
			objMesh.updateAttributes();
			return 1;
		}
		catch (const std::exception&)
		{
			printf("\n Catmullclark failed!");
			return 0;
		}
	}

	ZSPACE_EXTERNAL int ext_meshUtil_checkPlanarity(zExtMesh& objMesh, float tolerance, int planarityType, bool colorFaces, zExtDoubleArray& outDeviations)
	{
		try
		{
			zFnMesh fn(*objMesh.extPointer);
			outDeviations.pointer = new zDoubleArray();
			fn.getPlanarityDeviationPerFace(*outDeviations.pointer, planarityType == 0 ? zPlanarSolverType::zQuadPlanar : zPlanarSolverType::zVolumePlanar, colorFaces, tolerance);
			outDeviations.updateAttributes();
			objMesh.updateAttributes();
			return 1;
		}
		catch (const std::exception&)
		{
			printf("\n planarity failed!");
			return 0;
		}
	}



	ZSPACE_EXTERNAL_INLINE void ext_meshUtil_meshTest(int outfCounts)
	{
		printf("\n C++ %i", outfCounts);

	}
	ZSPACE_EXTERNAL_INLINE int ext_meshUtil_getMeshPositionRaw(zExtMesh& objMesh, float* outVPostions, float* outVColors)
	{
		if (!objMesh.extPointer)
		{
			"/n meshPointer is null";
			return 0;
		}
		zFnMesh fn(*objMesh.extPointer);
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
		return 1;
	}
	ZSPACE_EXTERNAL_INLINE int ext_meshUtil_getMeshFaceCount(zExtMesh& objMesh, int* outfCounts)
	{
		if (!objMesh.extPointer)
		{
			"/n meshPointer is null";
			return 0;
		}
		zFnMesh fn(*objMesh.extPointer);
		zIntArray pCounts;
		zIntArray pConnects;
		fn.getPolygonData(pConnects, pCounts);
		for (int i = 0; i < pCounts.size(); i++)
		{
			outfCounts[i] = pCounts[i];
		}
		return 1;
	}
	ZSPACE_EXTERNAL_INLINE int ext_meshUtil_getMeshFaceConnect(zExtMesh& objMesh, int* outfConnects)
	{
		if (!objMesh.extPointer)
		{
			"/n meshPointer is null";
			return 0;
		}
		zFnMesh fn(*objMesh.extPointer);
		zIntArray pCounts;
		zIntArray pConnects;
		fn.getPolygonData(pConnects, pCounts);
		for (int i = 0; i < pConnects.size(); i++)
		{
			outfConnects[i] = pConnects[i];
		}
		return 1;
	}

	ZSPACE_EXTERNAL_INLINE int ext_meshUtil_getMeshCentre(zExtMesh& objMesh, float* outCentre)
	{
		if (!objMesh.extPointer)
		{
			"/n meshPointer is null";
			return 0;
		}
		zFnMesh fn(*objMesh.extPointer);
		zPoint pt =  fn.getCenter();
		outCentre[0] = pt.x;
		outCentre[1] = pt.y;
		outCentre[2] = pt.z;

		return 1;
	}


}