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
		mesh = m;
		updateAttributes();
	}

	ZSPACE_EXTERNAL_INLINE void zExtMesh::updateAttributes()
	{
		zFnMesh fn(*mesh);
		vCount = fn.numVertices();
		fCount = fn.numPolygons();
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
	ZSPACE_EXTERNAL_INLINE void ext_meshUtil_createMeshOBJFromArray(double* _vertexPositions, int* _polyCounts, int* _polyConnects, int numVerts, int numFaces, zExtMesh& out_mesh)
	{
		if (!_vertexPositions || !_polyCounts || !_polyConnects) throw std::invalid_argument(" error: mesh container is empty.");

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
		zFnMesh fnMesh(*out_mesh.mesh);
		fnMesh.create(vPos, pCounts, pConnects);
	}

	ZSPACE_EXTERNAL_INLINE void ext_meshUtil_createMeshOBJFromFile(char* filePath, zExtMesh& out_mesh)
	{
		string pathSt(filePath);
		filesystem::path file_path(pathSt);
		string fileExtension = file_path.extension().string();
		transform(fileExtension.begin(), fileExtension.end(), fileExtension.begin(), [](unsigned char c) { return std::tolower(c); });

		zFnMesh fnMesh(*out_mesh.mesh);

		if (fileExtension == ".pointer")
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
		zFnMesh fn(*mesh.mesh);
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



	ZSPACE_EXTERNAL_INLINE void ext_meshUtil_meshTest(int outfCounts)
	{
		printf("\n C++ %i", outfCounts);

	}
	ZSPACE_EXTERNAL_INLINE int ext_meshUtil_getMeshPosition(zExtMesh& objMesh, float* outVPostions, float* outVColors)
	{
		if (!objMesh.mesh)
		{
			"/n meshPointer is null";
			return 0;
		}
		zFnMesh fn(*objMesh.mesh);
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
		if (!objMesh.mesh)
		{
			"/n meshPointer is null";
			return 0;
		}
		zFnMesh fn(*objMesh.mesh);
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
		if (!objMesh.mesh)
		{
			"/n meshPointer is null";
			return 0;
		}
		zFnMesh fn(*objMesh.mesh);
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
		if (!objMesh.mesh)
		{
			"/n meshPointer is null";
			return 0;
		}
		zFnMesh fn(*objMesh.mesh);
		zPoint pt =  fn.getCenter();
		outCentre[0] = pt.x;
		outCentre[1] = pt.y;
		outCentre[2] = pt.z;

		return 1;
	}


}