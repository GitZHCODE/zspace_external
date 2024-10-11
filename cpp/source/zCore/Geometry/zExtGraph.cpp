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


#include"headers/zCore/Geometry/zExtGraph.h"
//forward declaration
#include "headers/zCore/Geometry/zExtMesh.h"
#include "headers/zCore/Utils/zExtJSON.h"


namespace zSpace
{

	ZSPACE_EXTERNAL_INLINE zExtGraph::zExtGraph(zObjGraph* g)
	{
		pointer = g;
		updateAttributes();
	}
	ZSPACE_EXTERNAL_INLINE zExtGraph::zExtGraph()
	{
		checkMemAlloc();
		//pointer = new zObjGraph();
		//updateAttributes();

	}
	ZSPACE_EXTERNAL_INLINE zExtGraph::~zExtGraph()
	{
		delete pointer;
		pointer = nullptr;
	}
	ZSPACE_EXTERNAL_INLINE zStatusCode zExtGraph::checkMemAlloc(bool allocateMemory)
	{
		try
		{
			if (!pointer || pointer == nullptr)
			{
				if (!allocateMemory) return zMemNotAllocError;
				pointer = new zObjGraph();
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
	ZSPACE_EXTERNAL_INLINE void zExtGraph::updateAttributes()
	{
		zFnGraph g(*pointer);
		
		try
		{
			g.numEdges();
			//printf("\n updateAttributes 1");

			eCount = g.numEdges();
			//printf("\n updateAttributes 1");

			vCount = g.numVertices();
			//printf("\n updateAttributes 2");

			vPositions.checkMemAlloc();
			//printf("\n updateAttributes 3");

			g.getVertexPositions(*vPositions.pointer);
			//printf("\n updateAttributes 4");

			vPositions.updateAttributes();
			//printf("\n updateAttributes 5");


			vColors.checkMemAlloc();
			//printf("\n updateAttributes 6");
			g.getVertexColors(*vColors.pointer);
			//printf("\n updateAttributes 7");
			vColors.updateAttributes();
			//printf("\n updateAttributes 8");

			ePair.checkMemAlloc();
			//printf("\n updateAttributes 9");
			g.getEdgeData(*ePair.pointer);
			//printf("\n updateAttributes 10");
			ePair.updateAttributes();
			//printf("\n updateAttributes 11");

			eColors.checkMemAlloc();
			//printf("\n updateAttributes 12");
			g.getEdgeColors(*eColors.pointer);
			//printf("\n updateAttributes 13");
			eColors.updateAttributes();
			//printf("\n updateAttributes 14");
		}
		catch (const std::exception&)
		{
			printf("\n updateAttributes failed");
		}
		
	}
	ZSPACE_EXTERNAL_INLINE zIntArray zExtGraph::getGraphSequence()
	{
		zIntArray sequence;
		zItGraphVertexArray vArray;

		zFnGraph fnGraph(*pointer);
		if (fnGraph.numVertices() == 0) return sequence;

		for (zItGraphVertex v(*pointer); !v.end(); v++)
		{
			if (!v.checkValency(2))
			{
				vArray.push_back(v);
			}
		}

		if (vArray.size() == 2)
		{
			zItGraphHalfEdge he = vArray[0].getHalfEdge();
			sequence.push_back(vArray[0].getId());
			do
			{
				sequence.push_back(he.getVertex().getId());
				he = he.getNext();
			} while (he.getVertex() != vArray[1]);

			sequence.push_back(vArray[1].getId());
			sequence.push_back(vArray[0].getId());
		}
		if (vArray.size() == 0)
		{

			zItGraphHalfEdge he(*pointer, 0);

			zItGraphVertex startV = he.getStartVertex();

			zItGraphHalfEdge startHe = he;

			sequence.push_back(he.getStartVertex().getId());

			do
			{

				if (he.getVertex() == startV)
				{

					sequence.push_back(he.getVertex().getId());
				}
				else
				{

					sequence.push_back(he.getVertex().getId());
				}

				he = he.getNext();

			} while (he != startHe);
		}

		//printf("\n num of vertices : num of sequence ---- %i : %i \n ", fnGraph.numVertices(), sequence.size());

		return sequence;
	}

	ZSPACE_EXTERNAL_INLINE zExtGraphArray::~zExtGraphArray()
	{
		delete pointer;
		pointer = nullptr;
	}

	ZSPACE_EXTERNAL_INLINE zStatusCode zExtGraphArray::checkMemAlloc(bool allocateMemory)
	{
		try
		{
			if (!pointer || pointer == nullptr)
			{
				if (!allocateMemory) return zMemNotAllocError;
				pointer = new zObjGraphArray();
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

	ZSPACE_EXTERNAL_INLINE zExtGraphPointerArray::~zExtGraphPointerArray()
	{
		delete pointer;
		pointer = nullptr;
	}

	ZSPACE_EXTERNAL_INLINE void zExtGraphPointerArray::updateAttributes()
	{
		arrayCount = pointer->size();
	}


	ZSPACE_EXTERNAL_INLINE void ext_graph_getGraphData(zExtGraph extGraph, float* vPositions, float* vColors, int* ePairs, float* eColors)
	{
		zObjGraph* graph;
		graph = extGraph.pointer;
		zFnGraph g(*graph);
		int vCount = g.numVertices();
		int eCount = g.numEdges();


		zPointArray inVerticies;
		g.getVertexPositions(inVerticies);

		zColorArray inVColors;
		g.getVertexColors(inVColors);

		zColorArray ineColors;
		g.getEdgeColors(ineColors);

		zIntArray inEdges;
		g.getEdgeData(inEdges);
		for (int i = 0; i < vCount; i++)
		{
			vPositions[i * 3 + 0] = inVerticies[i].x;
			vPositions[i * 3 + 1] = inVerticies[i].y;
			vPositions[i * 3 + 2] = inVerticies[i].z;

			vColors[i * 4 + 0] = inVColors[i].r;
			vColors[i * 4 + 1] = inVColors[i].g;
			vColors[i * 4 + 2] = inVColors[i].b;
			vColors[i * 4 + 3] = inVColors[i].a;
		}
		for (int64_t i = 0; i < eCount; i++)
		{

			ePairs[i * 2 + 0] = inEdges[i * 2 + 0];
			ePairs[i * 2 + 1] = inEdges[i * 2 + 1];

			eColors[i * 4 + 0] = ineColors[i].r;
			eColors[i * 4 + 1] = ineColors[i].g;
			eColors[i * 4 + 2] = ineColors[i].b;
			eColors[i * 4 + 3] = ineColors[i].a;

		}
	}
	ZSPACE_EXTERNAL_INLINE void ext_graph_getGraphSequence(zExtGraph extGraph, int* outSequence)//the size of the area = the number of vertices + 1
	{
		zIntArray seq;
		seq = extGraph.getGraphSequence();
		for (int i = 0; i < seq.size(); i++)
		{
			outSequence[i] = seq[i];
		}
	}
	ZSPACE_EXTERNAL_INLINE void ext_graph_getGraphsFromGraphPointerArray(zExtGraphPointerArray graphSet, zExtGraph* outGraphArray)
	{

		for (int i = 0; i < graphSet.arrayCount; i++)
		{
			outGraphArray[i].pointer = graphSet.pointer->at(i);
			outGraphArray[i].updateAttributes();
		}
		/*zObjGraphArray* graphs;
		graphs = graphSet.graphSet;
		for (int i = 0; i < graphs->size(); i++)
		{
			outGraphArray[i] = graphSet.graphSet->at(i);
		}*/
	}

	ZSPACE_EXTERNAL_INLINE int ext_graph_from(char* filePath, zExtGraph& outGraph)
	{
		try
		{
			outGraph.checkMemAlloc(true);
			zFnGraph fn(*outGraph.pointer);
			std::string str(filePath);
			std::string ext = str.substr(str.find_last_of(".") + 1);
			std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

			if (ext == "json")
			{
				fn.from(filePath, zJSON);

			}
			else if (ext == "obj") fn.from(filePath, zOBJ);
#if defined ZSPACE_USD_INTEROP
			else if (ext == "usd" || ext == "usda") fn.from(filePath, zUSD);
#endif
			else return 0;
			outGraph.updateAttributes();
			return 1;
		}
		catch (const std::exception&)
		{
			return 404;
		}
	}
	ZSPACE_EXTERNAL_INLINE int ext_graph_to(zExtGraph& extGraph, char* filePath)
	{
		try
		{
			zStatusCode memoryChk = extGraph.checkMemAlloc(false);
			if (memoryChk == zMemNotAllocError) return zMemNotAllocError;

			zFnGraph fn(*extGraph.pointer);
			std::string str(filePath);
			std::string ext = str.substr(str.find_last_of(".") + 1);
			std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

			if (ext == "json") fn.to(filePath, zJSON);
			else if (ext == "obj") fn.to(filePath, zOBJ);
#if defined ZSPACE_USD_INTEROP
			else if (ext == "usd" || ext == "usda") fn.to(filePath, zUSD);
#endif
			else return 0;
			return 1;
		}
		catch (const std::exception&)
		{
			return 404;
		}
	}

	ZSPACE_EXTERNAL_INLINE zStatusCode ext_graph_fromJSON(zExtJSON& extJson, zExtGraph& outGraph)
	{
		try
		{
			zStatusCode memoryChk = extJson.checkMemAlloc(false);
			if (memoryChk == zMemNotAllocError) return zMemNotAllocError;
			outGraph.checkMemAlloc();
			zFnGraph fn(*outGraph.pointer);
			fn.from(*extJson.pointer);
			outGraph.updateAttributes();
			return zStatusCode::zSuccess;

		}
		catch (const std::exception&)
		{
			return zStatusCode::zThrowError;
		}
	}


	ZSPACE_EXTERNAL_INLINE zStatusCode ext_graph_toJSON(zExtGraph& extGraph, zExtJSON& outJson)
	{
		try
		{
			zStatusCode memoryChk = extGraph.checkMemAlloc(false);
			if (memoryChk == zMemNotAllocError) return zMemNotAllocError;
			outJson.checkMemAlloc();
			zFnGraph fn(*extGraph.pointer);
			fn.to(*outJson.pointer);
			outJson.updateAttributes();
			return zStatusCode::zSuccess;
		}
		catch (const std::exception&)
		{
			return zStatusCode::zThrowError;
		}
	}

#if defined(ZSPACE_USD_INTEROP)  

	ZSPACE_EXTERNAL_INLINE int ext_graph_fromUSD(zExtUSD& extUsd, zExtGraph& outGraph)
	{
		try
		{
			zStatusCode memoryChk = extUsd.checkMemAlloc(false);
			if (memoryChk == zMemNotAllocError) return zMemNotAllocError;
			outGraph.checkMemAlloc();
			zFnGraph fn(*outGraph.pointer);
			fn.from(*extUsd.pointer);
			outGraph.updateAttributes();
			return 1;
		}
		catch (const std::exception&)
		{
			return 404;
		}

	}

	ZSPACE_EXTERNAL_INLINE int ext_graph_toUSD(zExtGraph& extGraph, zExtUSD& extUsd)
	{
		try
		{
			zStatusCode memoryChk = extGraph.checkMemAlloc(false);
			if (memoryChk == zMemNotAllocError) return zMemNotAllocError;
			extUsd.checkMemAlloc();
			zFnGraph fn(*extGraph.pointer);
			fn.to(*extUsd.pointer);
			extUsd.updateAttributes();
			return 1;
		}
		catch (const std::exception&)
		{
			return 404;
		}
	}

#endif


	ZSPACE_EXTERNAL_INLINE int ext_graph_updateGraph(zExtGraph& extGraph)
	{
		try
		{
			extGraph.checkMemAlloc();
			if (extGraph.vPositions.pointer->size() == 0 || extGraph.ePair.pointer->size() == 0)
			{
				printf("\n graph update failed %i _ %i", extGraph.vPositions.pointer->size(), extGraph.ePair.pointer->size());
				return 0;
			}
			zFnGraph fnGraph(*extGraph.pointer);

			fnGraph.create(*extGraph.vPositions.pointer, *extGraph.ePair.pointer);

			
			

			//if (extGraph.eColors.arrayCount == extGraph.ePair.arrayCount/2)
			//printf("\n \n edge color %i %i", extGraph.eColors.arrayCount, fnGraph.numEdges());
			//printf("\n \n vector color %i %i", extGraph.vColors.arrayCount, fnGraph.numVertices());

			if (extGraph.eColors.arrayCount == fnGraph.numEdges())
			{
				//printf("\n set edge color " + extGraph.eColors.arrayCount);
				//fnGraph.setEdgeColors(*extGraph.eColors.pointer, extGraph.vColors.arrayCount == 0);
				fnGraph.setEdgeColors(*extGraph.eColors.pointer, false);
			}
			if (extGraph.vColors.arrayCount == fnGraph.numVertices() && extGraph.vColors.arrayCount != 0)
			{
				//printf("\n set vertex color");

				//fnGraph.setVertexColors(*extGraph.vColors.pointer, extGraph.eColors.arrayCount == 0);
				fnGraph.setVertexColors(*extGraph.vColors.pointer, false);
			}
			//printf("\n graph update %i %i \n", extGraph.vPositions.pointer->size(), extGraph.ePair.pointer->size());

			extGraph.updateAttributes();
			//zColorArray c;
			//fnGraph.getEdgeColors(c);
			//cout << c[0].r << c[0].g << c[0].b << c[0].a << endl;
			//printf("edgeColor %f %f %f %f", c[4].r, c[4].g, c[4].b, c[4].a);
			//printf("\n %i %i \n", c[0]);

			return 1;
		}
		catch (const std::exception&)
		{
			printf("\n graph update failed");
			return 0;
		}


		////Graph Data
		//ZSPACE_EXTERNAL_INLINE void ext_graph_getGraphsSetFromPointersVector2(zObjGraphPointerArray* graphs, zObjGraph** outGraphArray)
		//{
		//	for (int i = 0; i < graphs->size(); i++)
		//	{
		//		outGraphArray[i] = graphs->at(i);
		//	}
		//}
		//ZSPACE_EXTERNAL_INLINE void ext_graph_getGraphsSetFromVector2(zObjGraphArray* graphs, zObjGraph** outGraphArray)
		//{
		//	for (int i = 0; i < graphs->size(); i++)
		//	{
		//		outGraphArray[i] = &graphs->at(i);
		//	}
		//}
		//ZSPACE_EXTERNAL_INLINE void ext_graph_getGraphCounts2(zObjGraph* graph, int& outvCount, int& outeCount)
		//{
		//	zFnGraph g(*graph);
		//	outeCount = g.numEdges();
		//	outvCount = g.numVertices();
		//}
		//ZSPACE_EXTERNAL_INLINE void ext_graph_getGraphData2(zObjGraph* graph, float* vPositions, float* vColors, int* ePairs, float* eColors)
		//{
		//	zFnGraph g(*graph);
		//	int vCount = g.numVertices();
		//	int eCount = g.numEdges();


		//	zPointArray inVerticies;
		//	g.getVertexPositions(inVerticies);

		//	zColorArray inVColors;
		//	g.getVertexColors(inVColors);

		//	zColorArray ineColors;
		//	g.getEdgeColors(ineColors);

		//	zIntArray inEdges;
		//	g.getEdgeData(inEdges);
		//	for (int i = 0; i < vCount; i++)
		//	{
		//		vPositions[i * 3 + 0] = inVerticies[i].x;
		//		vPositions[i * 3 + 1] = inVerticies[i].y;
		//		vPositions[i * 3 + 2] = inVerticies[i].z;

		//		vColors[i * 4 + 0] = inVColors[i].r;
		//		vColors[i * 4 + 1] = inVColors[i].g;
		//		vColors[i * 4 + 2] = inVColors[i].b;
		//		vColors[i * 4 + 3] = inVColors[i].a;
		//	}
		//	for (int64_t i = 0; i < eCount; i++)
		//	{

		//		ePairs[i * 2 + 0] = inEdges[i * 2 + 0];
		//		ePairs[i * 2 + 1] = inEdges[i * 2 + 1];

		//		eColors[i * 4 + 0] = ineColors[i].r;
		//		eColors[i * 4 + 1] = ineColors[i].g;
		//		eColors[i * 4 + 2] = ineColors[i].b;
		//		eColors[i * 4 + 3] = ineColors[i].a;

		//	}
		//}
		//
	}

	ZSPACE_EXTERNAL_INLINE zStatusCode ext_graph_duplicate(zExtGraph& inObject, zExtGraph& outObject)
	{
		try
		{

			zStatus memoryChk = inObject.checkMemAlloc(false);
			if (memoryChk == zMemNotAllocError) return zMemNotAllocError;
			zFnGraph fn(*inObject.pointer);
			outObject.checkMemAlloc();
			*outObject.pointer = zObjGraph(*inObject.pointer);
			outObject.updateAttributes();

			return zSuccess;
		}
		catch (const std::exception&)
		{
			return zThrowError;
		}
	}
	
}