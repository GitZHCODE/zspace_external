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


#include"headers/zCore/Field/zExtField.h"


namespace zSpace
{
	ZSPACE_EXTERNAL_INLINE zExtMeshScalarField::~zExtMeshScalarField()
	{
		delete pointer;
		pointer = nullptr;
	}
	ZSPACE_EXTERNAL_INLINE zStatusCode zExtMeshScalarField::checkMemAlloc(bool allocateMemory)
	{
		try
		{
			if (!pointer || pointer == nullptr)
			{
				if (!allocateMemory) return zMemNotAllocError;
				pointer = new zObjMeshScalarField();
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

	ZSPACE_EXTERNAL_INLINE void zExtMeshScalarField::updateAttributes()
	{
	}


	ZSPACE_EXTERNAL_INLINE int ext_meshField_initPointer(zExtMeshScalarField& field)
	{
		return field.checkMemAlloc();
	}


	ZSPACE_EXTERNAL_INLINE int ext_meshField_createMeshScalarField(zExtMeshScalarField& field, zExtPoint& minBB, zExtPoint& maxBB, int resX, int resY, int numNeighbors, bool setValuesperVertex, bool triMesh)
	{
		try
		{
			field.checkMemAlloc();
			zFnMeshScalarField fn(*field.pointer);
			fn.create(minBB, maxBB, resX, resY, numNeighbors, setValuesperVertex, triMesh);

			////zFnMeshScalarField fn2(*field.pointer);
			//zObjMeshScalarField oMeshField;
			//zFnMeshScalarField fnFields(oMeshField);

			//zPoint minBB(-10, -10, 0);
			//zPoint maxBB(10, 10, 0);
			//int resX = 128;
			//int resY = resX;



			//zScalarArray circle;
			//zPoint circleCenter(0, 0, 0);

			//float radius = 2.0;
			//fn.getScalars_Circle(circle, circleCenter, radius, 0.0, false);
			//fn.setFieldValues(circle);
			////fnFields.getIsocontour(oGraphs[0], 0);
			//zObjGraph oGraph;

			//fn.getIsocontour(oGraph, 0);
			//zFnGraph fnGraph(oGraph);
			//printf("\n createMeshScalarField graph numEdge %i", fnGraph.numEdges());



			return 1;
		}
		catch (const std::exception&)
		{
			printf("\n Mesh Scalar Field creation failed");
			return 0;
		}
	}

	ZSPACE_EXTERNAL_INLINE int ext_meshField_setFieldValues(zExtMeshScalarField& extField, zExtFloatArray& fValues)
	{
		try
		{


			if (fValues.arrayCount != extField.pointer->field.fieldValues.size())
			{
				printf("\n outExtScalars.arrayCount != extField.meshPointer->field.fieldValues.size()");
				return 0;
			}

			zFnMeshScalarField fn(*extField.pointer);
			printf("\n setFieldValues fValues.meshPointer->size() %i", fValues.pointer->size());



			fn.setFieldValues(*fValues.pointer);

			//zObjGraph oGraph;
			//fn.getIsocontour(oGraph, 0);
			//zFnGraph fnGraph(oGraph);
			//printf("\n setFieldValues graph numEdge %i", fnGraph.numEdges());

			extField.updateAttributes();
			return 1;
		}
		catch (const std::exception&)
		{
			printf("\n Mesh Scalar Field set values failed");
			return 0;
		}

	}

	ZSPACE_EXTERNAL_INLINE int ext_meshField_getFieldMesh(zExtMeshScalarField& extField, zExtMesh& outMesh)
	{
		try {
			outMesh.checkMemAlloc(true);
			outMesh.pointer = extField.pointer;
			outMesh.updateAttributes();
			//outMesh = zExtMesh(extField.pointer);
			return 1;
		}
		catch (const std::exception&)
		{
			printf("\n Mesh Scalar Field get mesh failed");
			return 0;
		}
		
	}

	ZSPACE_EXTERNAL_INLINE int ext_meshField_duplicate(zExtMeshScalarField& extField, zExtMeshScalarField& outExtField)
	{
		try
		{
			zFnMeshScalarField fn(*extField.pointer);
			outExtField.checkMemAlloc();
			*outExtField.pointer = zObjMeshScalarField(*extField.pointer);
			//fn.duplicate(*outExtField.pointer);
			outExtField.updateAttributes();
			printf("\n MeshScalarField duplicate success");

			return 1;
		}
		catch (const std::exception&)
		{
			printf("\n Mesh Scalar Field duplicate failed");
			return 0;
		}	
	}

	ZSPACE_EXTERNAL_INLINE int ext_meshField_getScalarsAsVertexDistance_1(zExtMeshScalarField& extField, zExtFloatArray& outExtScalars, zExtPointArray& inPositions, float offset, bool normalise)
	{
		try
		{
			zFnMeshScalarField fn(*extField.pointer);
			outExtScalars.checkMemAlloc();
			fn.getScalarsAsVertexDistance(*outExtScalars.pointer, *inPositions.pointer, offset, normalise);
			extField.updateAttributes();
			outExtScalars.updateAttributes();
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
	}

	ZSPACE_EXTERNAL_INLINE int ext_meshField_getScalarsAsVertexDistance_4(zExtMeshScalarField& extField, zExtFloatArray& outExtScalars, zExtMesh& inMeshObj, float offset, bool normalise)
	{
		try
		{
			zFnMeshScalarField fn(*extField.pointer);
			outExtScalars.checkMemAlloc();
			fn.getScalarsAsVertexDistance(*outExtScalars.pointer, *inMeshObj.pointer, offset, normalise);
			extField.updateAttributes();
			outExtScalars.updateAttributes();
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
	}

	ZSPACE_EXTERNAL_INLINE int ext_meshField_getScalarsAsVertexDistance_5(zExtMeshScalarField& extField, zExtFloatArray& outExtScalars, zExtGraph& inGraphObj, float offset, bool normalise)
	{
		try
		{
			zFnMeshScalarField fn(*extField.pointer);
			outExtScalars.checkMemAlloc();
			fn.getScalarsAsVertexDistance(*outExtScalars.pointer, *inGraphObj.pointer, offset, normalise);
			extField.updateAttributes();
			outExtScalars.updateAttributes();
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
	}

	ZSPACE_EXTERNAL_INLINE int ext_meshField_getScalarsAsEdgeDistance_0(zExtMeshScalarField& extField, zExtFloatArray& outExtScalars, zExtMesh& inMeshObj, float offset, bool normalise)
	{
		try
		{
			zFnMeshScalarField fn(*extField.pointer);
			outExtScalars.checkMemAlloc();
			fn.getScalarsAsEdgeDistance(*outExtScalars.pointer, *inMeshObj.pointer, offset, normalise);
			extField.updateAttributes();
			outExtScalars.updateAttributes();
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
	}

	ZSPACE_EXTERNAL_INLINE int ext_meshField_getScalarsAsEdgeDistance_1(zExtMeshScalarField& extField, zExtFloatArray& outExtScalars, zExtGraph& inGraphObj, float offset, bool normalise)
	{
		try
		{
			zFnMeshScalarField fn(*extField.pointer);
			outExtScalars.checkMemAlloc();
			fn.getScalarsAsEdgeDistance(*outExtScalars.pointer, *inGraphObj.pointer, offset, normalise);
			extField.updateAttributes();
			outExtScalars.updateAttributes();
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
	}




	ZSPACE_EXTERNAL_INLINE int ext_meshField_getScalars_Polygon(zExtMeshScalarField& extField, zExtFloatArray& outExtScalars, zExtGraph& inGraphObj, bool normalise)
	{
		try
		{
			zFnMeshScalarField fn(*extField.pointer);
			outExtScalars.checkMemAlloc();
			fn.getScalars_Polygon(*outExtScalars.pointer, *inGraphObj.pointer, normalise);
			extField.updateAttributes();
			outExtScalars.updateAttributes();
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
	}

	ZSPACE_EXTERNAL_INLINE int ext_meshField_getScalars_Circle(zExtMeshScalarField& extField, zExtFloatArray& outExtScalars, zVector& cen, float r, double annularVal, bool normalise)
	{
		try
		{
			zFnMeshScalarField fn(*extField.pointer);

			outExtScalars.checkMemAlloc();
			fn.getScalars_Circle(*outExtScalars.pointer, cen, r, annularVal, normalise);
			extField.updateAttributes();
			outExtScalars.updateAttributes();
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
	}

	ZSPACE_EXTERNAL_INLINE int ext_meshField_getScalars_Ellipse(zExtMeshScalarField& extField, zExtFloatArray& outExtScalars, zVector& cen, float a, float b, double annularVal, bool normalise)
	{
		try
		{
			zFnMeshScalarField fn(*extField.pointer);
			outExtScalars.checkMemAlloc();
			fn.getScalars_Ellipse(*outExtScalars.pointer, cen, a, b, annularVal, normalise);
			extField.updateAttributes();
			outExtScalars.updateAttributes();
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;

		}

	}

	ZSPACE_EXTERNAL_INLINE int ext_meshField_getScalars_Line(zExtMeshScalarField& extField, zExtFloatArray& outExtScalars, zVector& v0, zVector& v1, double annularVal, bool normalise)
	{
		try
		{
			zFnMeshScalarField fn(*extField.pointer);
			outExtScalars.checkMemAlloc();
			fn.getScalars_Line(*outExtScalars.pointer, v0, v1, annularVal, normalise);
			extField.updateAttributes();
			outExtScalars.updateAttributes();
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}

	}

	ZSPACE_EXTERNAL_INLINE int ext_meshField_getScalars_Triangle(zExtMeshScalarField& extField, zExtFloatArray& outExtScalars, zPoint& p0, zPoint& p1, zPoint& p2, double annularVal, bool normalise)
	{
		try
		{
			
			zFnMeshScalarField fn(*extField.pointer);
			outExtScalars.checkMemAlloc();
			fn.getScalars_Triangle(*outExtScalars.pointer, p0, p1, p2, annularVal, normalise);
			extField.updateAttributes();
			outExtScalars.updateAttributes();
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
	}

	ZSPACE_EXTERNAL_INLINE int ext_meshField_getScalars_Square(zExtMeshScalarField& extField, zExtFloatArray& outExtScalars, zVector& cen, zVector& dimensions, float annularVal, bool normalise)
	{
		try
		{
			zFnMeshScalarField fn(*extField.pointer);
			outExtScalars.checkMemAlloc();
			fn.getScalars_Square(*outExtScalars.pointer, cen, dimensions, annularVal, normalise);
			extField.updateAttributes();
			outExtScalars.updateAttributes();
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
	}

	ZSPACE_EXTERNAL_INLINE int ext_meshField_getScalars_Trapezoid(zExtMeshScalarField& extField, zExtFloatArray& outExtScalars, float r1, float r2, float he, float annularVal, bool normalise)
	{
		try
		{
			zFnMeshScalarField fn(*extField.pointer);
			outExtScalars.checkMemAlloc();
			fn.getScalars_Trapezoid(*outExtScalars.pointer, r1, r2, he, annularVal, normalise);
			extField.updateAttributes();
			outExtScalars.updateAttributes();
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
	}


	ZSPACE_EXTERNAL_INLINE int ext_meshField_smoothField(zExtMeshScalarField& extField, zExtFloatArray& outExtScalars, int numSmooth, double diffuseDamp, int type)
	{

		if (outExtScalars.arrayCount != extField.pointer->field.fieldValues.size())
		{
			printf("\n smoothField outExtScalars.arrayCount != extField.meshPointer->field.fieldValues.size()");
			return 0;
		}

		try
		{

			printf("\n smooth 1");
			zFnMeshScalarField fn(*extField.pointer);
			outExtScalars.checkMemAlloc();
			printf("\n smooth 2");

			zDiffusionType ztype;
			if (type == 0)
			{
				ztype = zDiffusionType::zAverage;
			}
			else if (type == 1)
			{
				ztype = zDiffusionType::zLaplacian;
			}
			else
			{
				ztype = zDiffusionType::zLaplacianAdjacent;
			}
			printf("\n smooth 3");

			fn.smoothField(*outExtScalars.pointer, numSmooth, diffuseDamp, ztype);
			printf("\n smooth 4");

			extField.updateAttributes();
			printf("\n smooth 5");

			outExtScalars.updateAttributes();
			printf("\n smooth 6");

			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
	}

	ZSPACE_EXTERNAL_INLINE int ext_meshField_computePositionsInFieldIndex(zExtMeshScalarField& extField, zExtPointArray& positions, zExtPointArray2D& extFieldIndexPositions)
	{
		try
		{
			zFnMeshScalarField fn(*extField.pointer);
			extFieldIndexPositions.checkMemAlloc();
			fn.computePositionsInFieldIndex(*positions.pointer, *extFieldIndexPositions.pointer);
			extField.updateAttributes();
			extFieldIndexPositions.updateAttributes();
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
	}

	ZSPACE_EXTERNAL_INLINE int ext_meshField_computePositionIndicesInFieldIndex(zExtMeshScalarField& extField, zExtPointArray& positions, zExtIntArray2D& extFieldIndexPositionIndicies)
	{
		try
		{
			zFnMeshScalarField fn(*extField.pointer);
			extFieldIndexPositionIndicies.checkMemAlloc();
			fn.computePositionIndicesInFieldIndex(*positions.pointer, *extFieldIndexPositionIndicies.pointer);
			extField.updateAttributes();
			extFieldIndexPositionIndicies.updateAttributes();
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
	}

	ZSPACE_EXTERNAL_INLINE int ext_meshField_boolean_union(zExtMeshScalarField& extField, zExtFloatArray& scalars0, zExtFloatArray& scalars1, zExtFloatArray& scalarsResult, bool normalise)
	{
		try
		{
			if (scalars0.arrayCount != extField.pointer->field.fieldValues.size())
			{
				printf("\n outExtScalars.arrayCount != extField.meshPointer->field.fieldValues.size()");
				return 0;
			}
			if (scalars1.arrayCount != extField.pointer->field.fieldValues.size())
			{
				printf("\n outExtScalars.arrayCount != extField.meshPointer->field.fieldValues.size()");
				return 0;
			}
			zFnMeshScalarField fn(*extField.pointer);
			scalarsResult.checkMemAlloc();
			fn.boolean_union(*scalars0.pointer, *scalars1.pointer, *scalarsResult.pointer, normalise);
			extField.updateAttributes();
			scalarsResult.updateAttributes();
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
	}

	ZSPACE_EXTERNAL_INLINE int ext_meshField_boolean_subtract(zExtMeshScalarField& extField, zExtFloatArray& fieldValues_A, zExtFloatArray& fieldValues_B, zExtFloatArray& fieldValues_Result, bool normalise)
	{
		try
		{
			if (fieldValues_A.arrayCount != extField.pointer->field.fieldValues.size())
			{
				printf("\n outExtScalars.arrayCount != extField.meshPointer->field.fieldValues.size()");
				return 0;
			}
			if (fieldValues_B.arrayCount != extField.pointer->field.fieldValues.size())
			{
				printf("\n outExtScalars.arrayCount != extField.meshPointer->field.fieldValues.size()");
				return 0;
			}
			zFnMeshScalarField fn(*extField.pointer);
			fieldValues_Result.checkMemAlloc();
			fn.boolean_subtract(*fieldValues_A.pointer, *fieldValues_B.pointer, *fieldValues_Result.pointer, normalise);
			extField.updateAttributes();
			fieldValues_Result.updateAttributes();
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
	}

	ZSPACE_EXTERNAL_INLINE int ext_meshField_boolean_intersect(zExtMeshScalarField& extField, zExtFloatArray& fieldValues_A, zExtFloatArray& fieldValues_B, zExtFloatArray& fieldValues_Result, bool normalise)
	{
		try
		{
			if (fieldValues_A.arrayCount != extField.pointer->field.fieldValues.size())
			{
				printf("\n outExtScalars.arrayCount != extField.meshPointer->field.fieldValues.size()");
				return 0;
			}
			if (fieldValues_B.arrayCount != extField.pointer->field.fieldValues.size())
			{
				printf("\n outExtScalars.arrayCount != extField.meshPointer->field.fieldValues.size()");
				return 0;
			}
			zFnMeshScalarField fn(*extField.pointer);
			fieldValues_Result.checkMemAlloc();
			fn.boolean_subtract(*fieldValues_A.pointer, *fieldValues_B.pointer, *fieldValues_Result.pointer, normalise);
			extField.updateAttributes();
			fieldValues_Result.updateAttributes();
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
	}

	ZSPACE_EXTERNAL_INLINE int ext_meshField_boolean_difference(zExtMeshScalarField& extField, zExtFloatArray& fieldValues_A, zExtFloatArray& fieldValues_B, zExtFloatArray& fieldValues_Result, bool normalise)
	{
		try
		{
			if (fieldValues_A.arrayCount != extField.pointer->field.fieldValues.size())
			{
				printf("\n outExtScalars.arrayCount != extField.meshPointer->field.fieldValues.size()");
				return 0;
			}
			if (fieldValues_B.arrayCount != extField.pointer->field.fieldValues.size())
			{
				printf("\n outExtScalars.arrayCount != extField.meshPointer->field.fieldValues.size()");
				return 0;
			}
			zFnMeshScalarField fn(*extField.pointer);
			fieldValues_Result.checkMemAlloc();
			fn.boolean_difference(*fieldValues_A.pointer, *fieldValues_B.pointer, *fieldValues_Result.pointer, normalise);
			extField.updateAttributes();
			fieldValues_Result.updateAttributes();
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
	}

	ZSPACE_EXTERNAL_INLINE int ext_meshField_boolean_clipwithPlane(zExtMeshScalarField& extField, zExtFloatArray& scalars, zExtTransform& clipPlane)
	{
		try
		{
			
			zFnMeshScalarField fn(*extField.pointer);
			fn.boolean_clipwithPlane(*scalars.pointer, *clipPlane.pointer);
			extField.updateAttributes();
			scalars.updateAttributes();
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
	}

	ZSPACE_EXTERNAL_INLINE int ext_meshField_boolean_clipwithPlaneCenterAndNormal(zExtMeshScalarField& extField, zExtFloatArray& fieldValues_A, zExtFloatArray& fieldValues_Result, zPoint& clipPlane_center, zVector& clipPlane_Norm)
	{
		try
		{
			zFnMeshScalarField fn(*extField.pointer);
			fieldValues_Result.checkMemAlloc();
			fn.boolean_clipwithPlane(*fieldValues_A.pointer, *fieldValues_Result.pointer, clipPlane_center, clipPlane_Norm);
			extField.updateAttributes();
			fieldValues_Result.updateAttributes();
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
	}

	ZSPACE_EXTERNAL_INLINE int ext_meshField_blend_linear(zExtMeshScalarField& extField, int currentFrame, int totalFrames, zExtFloatArray& fieldValues_A, zExtFloatArray& fieldValues_B, zExtFloatArray& fieldValues_Result)
	{
		try
		{
			zFnMeshScalarField fn(*extField.pointer);
			fieldValues_Result.checkMemAlloc();
			fn.blend_linear(currentFrame, totalFrames, *fieldValues_A.pointer, *fieldValues_B.pointer, *fieldValues_Result.pointer);
			extField.updateAttributes();
			fieldValues_Result.updateAttributes();
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
	}

	ZSPACE_EXTERNAL_INLINE int ext_meshField_getIsocontour(zExtMeshScalarField& extField, zExtGraph& outCoutourGraphObj, float inThreshold, int precision, float distTolerance)
	{
		try
		{
			zFnMeshScalarField fn(*extField.pointer);

			//zScalarArray circle;
			//zPoint circleCenter(0, 0, 0);

			//float radius = 2.0;
			//fn.getScalars_Circle(circle, circleCenter, radius, 0.0, false);
			//
			////fnFields.getIsocontour(oGraphs[0], 0);
			//zObjGraph oGraph;
			//fn.setFieldValues(circle);
			//fn.getIsocontour(oGraph, 0);
			//zFnGraph fnGraph(oGraph);
			//printf("\n getIsocontour graph numEdge %i", fnGraph.numEdges());


			


			//zFnMeshScalarField fn(*extField.pointer);
			printf("\n num numFieldValues %i", fn.numFieldValues());
			zFloatArray fValues;
			fn.getFieldValues(fValues);
			fn.setFieldValues(fValues);
			/*for (auto& f : fValues)
			{
				printf(" _ %f", f);
			}*/
			

			outCoutourGraphObj.checkMemAlloc();
			//zObjGraph graph;
			//fn.getIsocontour(graph, 0);
			fn.getIsocontour(*outCoutourGraphObj.pointer, inThreshold, precision, distTolerance);

			extField.updateAttributes();

			/*zFnGraph fng(graph);
			printf("\n num edges %i", fng.numEdges());
			fng = zFnGraph(*outCoutourGraphObj.pointer);

			printf("\n num edges %i", fng.numEdges());*/


			outCoutourGraphObj.updateAttributes();
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
	}

	ZSPACE_EXTERNAL_INLINE int ext_meshField_getIsolineMesh(zExtMeshScalarField& extField, zExtMesh& outCoutourMeshObj, float inThreshold, bool invertMesh)
	{
		try
		{
			zFnMeshScalarField fn(*extField.pointer);
			outCoutourMeshObj.checkMemAlloc();
			fn.getIsolineMesh(*outCoutourMeshObj.pointer, inThreshold, invertMesh);

			extField.updateAttributes();
			outCoutourMeshObj.updateAttributes();
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
	}

	ZSPACE_EXTERNAL_INLINE int ext_meshField_getIsobandMesh(zExtMeshScalarField& extField, zExtMesh& outCoutourMeshObj, float inThresholdLow, float inThresholdHigh)
	{
		try
		{
			zFnMeshScalarField fn(*extField.pointer);
			outCoutourMeshObj.checkMemAlloc();
			fn.getIsobandMesh(*outCoutourMeshObj.pointer, inThresholdLow, inThresholdHigh);

			extField.updateAttributes();
			outCoutourMeshObj.updateAttributes();
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}

	}






}