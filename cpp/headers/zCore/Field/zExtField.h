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

#ifndef ZSPACE_EXT_CORE_FIELD_MESH_SCALAR_H
#define ZSPACE_EXT_CORE_FIELD_MESH_SCALAR_H



#pragma once


#include <headers/zInterface/functionsets/zFnMeshField.h>
#include <headers/zInterface/functionsets/zFnGraph.h>


#include "headers/base/zSpace_External.h"
#include "headers/base/zStatus.h"


#include "headers/zCore/Base/zExtPoint.h"
#include "headers/zCore/Base/zExtTransform.h"
#include "headers/zCore/Utils/zExtUtilsCore.h"
#include "headers/zCore/Geometry/zExtMesh.h"
#include "headers/zCore/Geometry/zExtGraph.h"



#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>

#include<execution>

using namespace std;

namespace zSpace
{


	/** \addtogroup zExternal
*	\brief Collection of external structs and methods for applications.
*  @{
*/

/** \addtogroup zCore
*	\brief external structs and methods for zCore.
*  @{
*/

/*! \struct zExtField
*	\brief An external struct for zObjMeshField .
*	\since version 0.0.1
*/

/** @}*/

/** @}*/

/** @}*/
	struct ZSPACE_EXTERNAL zExtMeshScalarField
	{
		zObjMeshScalarField* pointer = nullptr;


		zExtMeshScalarField();
		
		zExtMeshScalarField(zObjMeshScalarField* extField);
		~zExtMeshScalarField();

		zStatusCode checkMemAlloc(bool allocateMemory = true);

		void updateAttributes();
	};




	ZSPACE_EXTERNAL_C
	{
		ZSPACE_EXTERNAL int ext_meshField_initPointer(zExtMeshScalarField & extField);

		ZSPACE_EXTERNAL int ext_meshField_createMeshScalarField(zExtMeshScalarField& extField, zExtPoint& minBB, zExtPoint& maxBB, int resX, int resY, int numNeighbors, bool setValuesperVertex, bool triMesh);

		/*! \brief This method sets the values of the field to the input container values.
		*
		*	\param		[in]	fValues		- input container of field value.
		*	\since version 0.0.2
		*/
		ZSPACE_EXTERNAL int ext_meshField_setFieldValues(zExtMeshScalarField& extField, zExtFloatArray& fValues, zFieldColorType type, float sdfWidth);



		ZSPACE_EXTERNAL int ext_meshField_getFieldMesh(zExtMeshScalarField& extField, zExtMesh& outMesh);

		ZSPACE_EXTERNAL int ext_meshField_duplicate(zExtMeshScalarField& extField, zExtMeshScalarField& outExtField);


		/*! \brief This method creates a vertex distance Field from the input point cloud.
		*	\param	[in, out]	extField	- zExtField object.
		*	\param	[out]	outExtScalars	- container for storing scalar values.
		*	\param	[in]	inPositions			- input container of postions for distance calculations.
		*	\param	[in]	offset				- input distance variable.
		*	\param	[in]	normalise			- true if the scalars need to mapped between -1 and 1. generally used for contouring.
		*	\since version 0.0.2
		*/
		ZSPACE_EXTERNAL int ext_meshField_getScalarsAsVertexDistance_1(zExtMeshScalarField& extField, zExtFloatArray& outExtScalars, zExtPointArray& inPositions, float offset, bool normalise = true);

		///*! \brief This method creates a vertex distance Field from the input  point cloud.
		//*
		//*	\param	[out]	scalars				- container for storing scalar values.
		//*	\param	[in]	inPointsObj			- input point cloud object for distance calculations.
		//*	\param	[in]	normalise			- true if the scalars need to mapped between -1 and 1. generally used for contouring.
		//*	\since version 0.0.2
		//*/
		//ZSPACE_EXTERNAL int ext_meshField_getScalarsAsVertexDistance_2(zExtMeshScalarField& extField, zExtFloatArray& outExtScalars, zObjPointCloud& inPointsObj, bool normalise = true);

		///*! \brief This method creates a vertex distance Field from the input point cloud.
		//*
		//*	\param	[out]	scalars				- container for storing scalar values.
		//*	\param	[in]	inPointsObj			- input point cloud object for distance calculations.
		//*	\param	[in]	offset				- input distance variable.
		//*	\param	[in]	normalise			- true if the scalars need to mapped between -1 and 1. generally used for contouring.
		//*	\since version 0.0.2
		//*/
		//ZSPACE_EXTERNAL int ext_meshField_getScalarsAsVertexDistance_3(zExtMeshScalarField& extField, zExtFloatArray& outExtScalars, zObjPointCloud& inPointsObj, float offset, bool normalise = true);

		/*! \brief This method creates a vertex distance Field from the input mesh vertex positions.
		*	\param	[in, out]	extField	- zExtField object.
		*	\param	[out]	outExtScalars	- container for storing scalar values.
		*	\param	[in]	inMeshObj			- input mesh object for distance calculations.
		*	\param	[in]	offset				- input distance variable.
		*	\param	[in]	normalise			- true if the scalars need to mapped between -1 and 1. generally used for contouring.
		*	\since version 0.0.2
		*/
		ZSPACE_EXTERNAL int ext_meshField_getScalarsAsVertexDistance_4(zExtMeshScalarField& extField, zExtFloatArray& outExtScalars, zExtMesh& inMeshObj, float offset, bool normalise = true);

		/*! \brief This method creates a vertex distance Field from the input graph vertex positions.
		*	\param	[in, out]	extField	- zExtField object.
		*	\param	[out]	outExtScalars	- container for storing scalar values.
		*	\param	[in]	inGraphObj		- input graph object for distance calculations.
		*	\param	[in]	offset			- input distance variable.
		*	\param	[in]	normalise		- true if the scalars need to mapped between -1 and 1. generally used for contouring.
		*	\since version 0.0.2
		*/
		ZSPACE_EXTERNAL int ext_meshField_getScalarsAsVertexDistance_5(zExtMeshScalarField& extField, zExtFloatArray& outExtScalars, zExtGraph& inGraphObj, float offset, bool normalise = true);

		/*! \brief This method creates a edge distance Field from the input mesh.
		*	\param	[in, out]	extField	- zExtField object.
		*	\param	[out]	outExtScalars	- container for storing scalar values.
		*	\param	[in]	inMeshObj		- input mesh object for distance calculations.
		*	\param	[in]	offset			- input distance variable.
		*	\param	[in]	normalise		- true if the scalars need to mapped between -1 and 1. generally used for contouring.
		*	\return 1 if the method is executed successfully, 0 otherwise.
		*	\since version 0.0.2
		*/
		ZSPACE_EXTERNAL int ext_meshField_getScalarsAsEdgeDistance_0(zExtMeshScalarField& extField, zExtFloatArray& outExtScalars, zExtMesh& inMeshObj, float offset, bool normalise = true);

		/*! \brief This method creates a edge distance Field from the input graph.
		*	\param	[in, out]	extField	- zExtField object.
		*	\param	[out]	outExtScalars	- container for storing scalar values.
		*	\param	[in]	inGraphObj		- input graph object for distance calculations.
		*	\param	[in]	offset			- input distance variable.
		*	\param	[in]	normalise		- true if the scalars need to mapped between -1 and 1. generally used for contouring.
		*	\since version 0.0.2
		*/
		ZSPACE_EXTERNAL int ext_meshField_getScalarsAsEdgeDistance_1(zExtMeshScalarField& extField, zExtFloatArray& outExtScalars, zExtGraph& inGraphObj, float offset, bool normalise = true);






		/* \brief This method gets the scalars for a polygon.
		* \param	[in, out]	extField	- zExtField object.
		* \param	[out]	outExtScalars	- container for storing scalar values.
		* \param	[in]	inGraphObj		- input graph object.
		* \param	[in]	normalise		- true if the scalars need to mapped between -1 and 1. generally used for contouring.
		* \return 1 if the method is executed successfully, 0 otherwise.
		*/
		ZSPACE_EXTERNAL int ext_meshField_getScalars_Polygon(zExtMeshScalarField& extField, zExtFloatArray& outExtScalars, zExtGraph& inGraphObj, bool normalise = true);

		/* \brief This method gets the scalars for a circle.
		*	\param	[in, out]	extField	- zExtField object.
		*	\param	[out]	outExtScalars	- container for storing scalar values.
		*	\param	[in]	cen				- centre of the circle.
		*	\param	[in]	p				- input field point.
		*	\param	[in]	r				- radius value.
		*	\param	[in]	annularVal		- input annular / offset value.
		*	\param	[in]	normalise		- true if the scalars need to mapped between -1 and 1. generally used for contouring.
		* \return 1 if the method is executed successfully, 0 otherwise.
		*/
		ZSPACE_EXTERNAL int ext_meshField_getScalars_Circle(zExtMeshScalarField& extField, zExtFloatArray& outExtScalars, zVector& cen, float r, double annularVal = 0, bool normalise = true);

		/* \brief This method gets the scalars for an ellipse.
		*	\param	[in, out]	extField	- zExtField object.
		*	\param	[out]	outExtScalars	- container for storing scalar values.
		*	\param	[in]	cen				- centre of the ellipse.
		*	\param	[in]	a				- major axis value.
		*	\param	[in]	b				- minor axis value.
		*	\param	[in]	annularVal		- input annular / offset value.
		*	\param	[in]	normalise		- true if the scalars need to mapped between -1 and 1. generally used for contouring.
		*	\return 1 if the method is executed successfully, 0 otherwise.
		*/
		ZSPACE_EXTERNAL int ext_meshField_getScalars_Ellipse(zExtMeshScalarField& extField, zExtFloatArray& outExtScalars, zVector& cen, float a, float b, double annularVal = 0, bool normalise = true);

		/* \brief This method gets the scalars for a line.
		* \param	[in, out]	extField	- zExtField object.
		* \param	[out]	outExtScalars	- container for storing scalar values.
		* \param	[in]	v0				- start point of the line.
		* \param	[in]	v1				- end point of the line.
		* \param	[in]	annularVal		- input annular / offset value.
		* \param	[in]	normalise		- true if the scalars need to mapped between -1 and 1. generally used for contouring.
		* \return 1 if the method is executed successfully, 0 otherwise.
		*/
		ZSPACE_EXTERNAL int ext_meshField_getScalars_Line(zExtMeshScalarField& extField, zExtFloatArray& outExtScalars, zVector& v0, zVector& v1, double annularVal = 0, bool normalise = true);

		/* \brief This method gets the scalars for a triangle.
		* \param	[in, out]	extField	- zExtField object.
		* \param	[out]	outExtScalars	- container for storing scalar values.
		* \param	[in]	p0				- first point of the triangle.
		* \param	[in]	p1				- second point of the triangle.
		* \param	[in]	p2				- third point of the triangle.
		* \param	[in]	annularVal		- input annular / offset value.
		* \param	[in]	normalise		- true if the scalars need to mapped between -1 and 1. generally used for contouring.
		* \return 1 if the method is executed successfully, 0 otherwise.
		*/
		ZSPACE_EXTERNAL int ext_meshField_getScalars_Triangle(zExtMeshScalarField& extField, zExtFloatArray& outExtScalars, zPoint& p0, zPoint& p1, zPoint& p2, double annularVal = 0, bool normalise = true);

		/*	 \brief This method gets the scalars for a rectangle.
		*	\param	[in, out]	extField	- zExtField object.
		*	\param	[out]	outExtScalars	- container for storing scalar values.
		*	\param	[in]	cen				- centre of the rectangle.
		*	\param	[in]	dimensions		- dimensions of the rectangle.
		*	\param	[in]	annularVal		- input annular / offset value.
		*	\param	[in]	normalise		- true if the scalars need to mapped between -1 and 1. generally used for contouring.
		*	\return 1 if the method is executed successfully, 0 otherwise.
		*/
		ZSPACE_EXTERNAL int ext_meshField_getScalars_Square(zExtMeshScalarField& extField, zExtFloatArray& outExtScalars, zVector& cen, zVector& dimensions, float annularVal = 0, bool normalise = true);

		/* \brief This method gets the scalars for a trapezoid.
		* \param	[in, out]	extField	- zExtField object.
		* \param	[out]	outExtScalars	- container for storing scalar values.
		* \param	[in]	r1				- input distance 1 value.
		* \param	[in]	r2				- input distance 2 value.
		* \param	[in]	he				- input height value.
		* \param	[in]	annularVal		- input annular / offset value.
		* \param	[in]	normalise		- true if the scalars need to mapped between -1 and 1. generally used for contouring.
		* \return 1 if the method is executed successfully, 0 otherwise.
		*/
		ZSPACE_EXTERNAL int ext_meshField_getScalars_Trapezoid(zExtMeshScalarField& extField, zExtFloatArray& outExtScalars, float r1, float r2, float he, float annularVal = 0, bool normalise = true);

		/* \brief This method gets the scalars for a polygon.
		* \param	[in, out]	extField	- zExtField object.
		* \param	[out]	outExtScalars	- container for storing scalar values.
		* \param	[in]	inGraphObj		- input graph object.
		* \param	[in]	pNorm			- normal vector.
		* \param	[in]	pCen			- centre point.
		* \param	[in]	scale			- input scale value.
		* \return 1 if the method is executed successfully, 0 otherwise.
		*/
		ZSPACE_EXTERNAL int ext_meshField_getScalars_SinBands(zExtMeshScalarField& extField, zExtFloatArray& outExtScalars, zExtGraph& inGraphObj, zVector& pNorm, zPoint& pCen, float scale);

		/* \brief This method avarages / smoothens the field values.
		* \param	[in, out]	extField	- zExtField object.
		* \param	[out]	outExtScalars	- container for storing scalar values.
		* \param [in]	numSmooth			- number of times the smoothing needs to be applied.
		* \param [in]	diffuseDamp			- diffusion damping value.
		* \param [in]	type				- diffusion type. 0 for zAverage, 1 for zGaussian.
		*/
		ZSPACE_EXTERNAL int ext_meshField_smoothField(zExtMeshScalarField& extField, zExtFloatArray& outExtScalars, int numSmooth, double diffuseDamp = 1.0, int type = 0);
		ZSPACE_EXTERNAL int ext_meshField_computePositionsInFieldIndex(zExtMeshScalarField& extField, zExtPointArray& positions, zExtPointArray2D& extFieldIndexPositions);
		ZSPACE_EXTERNAL int ext_meshField_computePositionIndicesInFieldIndex(zExtMeshScalarField& extField, zExtPointArray& positions, zExtIntArray2D& extFieldIndexPositionIndicies);


		//--------------------------
		//----  BOOLEAN METHODS
		//--------------------------		

		/*! \brief This method creates a union of the fields at the input buffers and stores them in the result buffer.
		*
		*	\param	[in, out]	extField		- zExtField object.
		*	\param	[in]		scalars0		- value of buffer.
		*	\param	[in]		scalars1		- value of buffer.
		*	\param	[out]		scalarsResult	- value of buffer to store the results.
		*	\param	[in]		normalise		- true if the scalars need to mapped between -1 and 1. generally used for contouring.
		*	\since version 0.0.4
		*/
		ZSPACE_EXTERNAL int ext_meshField_boolean_union(zExtMeshScalarField& extField, zExtFloatArray& scalars0, zExtFloatArray& scalars1, zExtFloatArray& scalarsResult, bool normalise = true);

		/*! \brief This method creates a subtraction of the fields at the input buffers and stores them in the result buffer.
		*	\param	[in, out]	extField			- zExtField object.
		*	\param	[in]		fieldValues_A		- field Values A.
		*	\param	[in]		fieldValues_B		- field Values B.
		*	\param	[in]		fieldValues_Result	- resultant field value.
		*	\param	[in]		normalise			- true if the scalars need to mapped between -1 and 1. generally used for contouring.
		*	\since version 0.0.4
		*/
		ZSPACE_EXTERNAL int ext_meshField_boolean_subtract(zExtMeshScalarField& extField, zExtFloatArray& fieldValues_A, zExtFloatArray& fieldValues_B, zExtFloatArray& fieldValues_Result, bool normalise = true);

		/*! \brief This method creates a intersect of the fields at the input buffers and stores them in the result buffer.
		*	\param	[in, out]	extField			- zExtField object.
		*	\param	[in]		fieldValues_A		- field Values A.
		*	\param	[in]		fieldValues_B		- field Values B.
		*	\param	[in]		fieldValues_Result	- resultant field value.
		*	\param	[in]		normalise			- true if the scalars need to mapped between -1 and 1. generally used for contouring.
		*	\since version 0.0.4
		*/
		ZSPACE_EXTERNAL int ext_meshField_boolean_intersect(zExtMeshScalarField& extField, zExtFloatArray& fieldValues_A, zExtFloatArray& fieldValues_B, zExtFloatArray& fieldValues_Result, bool normalise = true);

		/*! \brief This method creates a difference of the fields at the input buffers and stores them in the result buffer.
		*	\param	[in, out]	extField			- zExtField object.
		*	\param	[in]		fieldValues_A		- field Values A.
		*	\param	[in]		fieldValues_B		- field Values B.
		*	\param	[in]		fieldValues_Result	- resultant field value.
		*	\param	[in]		normalise			- true if the scalars need to mapped between -1 and 1. generally used for contouring.
		*	\since version 0.0.4
		*/
		ZSPACE_EXTERNAL int ext_meshField_boolean_difference(zExtMeshScalarField& extField, zExtFloatArray& fieldValues_A, zExtFloatArray& fieldValues_B, zExtFloatArray& fieldValues_Result, bool normalise = true);

		/*! \brief This method uses an input plane to clip an existing scalar field.
		*
		*	\param	[in]	field			- input field mesh.
		*	\param	[in]	scalars				- vector of scalar values. Need to be equivalent to number of mesh vertices.
		*	\param	[in]	clipPlane			- input zPlane used for clipping.
		*	\since version 0.0.2
		*/
		ZSPACE_EXTERNAL int ext_meshField_boolean_clipwithPlane(zExtMeshScalarField& extField, zExtFloatArray& scalars, zExtTransform& clipPlane);

		/*! \brief This method uses an input plane to clip an existing scalar field.
		*
		*	\param	[in, out]	extField			- zExtField object.
		*	\param	[in]	fieldValues_A			- field Values A.
		* 	\param	[in]	fieldValues_Result		- resultant field value.
		*	\param	[in]	clipPlane_center		- input clipPlane origin.
		*	\param	[in]	clipPlane_Norm			- input clipPlane normal.
		*	\since version 0.0.4
		*/
		ZSPACE_EXTERNAL int ext_meshField_boolean_clipwithPlaneCenterAndNormal(zExtMeshScalarField& extField, zExtFloatArray& fieldValues_A, zExtFloatArray& fieldValues_Result, zPoint& clipPlane_center, zVector& clipPlane_Norm);






		//--------------------------
		//----  BLEND METHODS
		//--------------------------

		/*! \brief This method returns the blend between the two fields at the input current frame.
		*	\param	[in, out]	extField			- zExtField object.
		*	\param	[in]	currentFrame			- current frame value ( between 0 & totalFrames).
		*	\param	[in]	totalFrames				- total number of frames for the blend.
		*	\param	[in]	fieldValues_A			- field Values A.
		*	\param	[in]	fieldValues_B			- field Values B.
		*	\param	[in]	fieldValues_Result		- resultant field value.
		*	\since version 0.0.4
		*/
		ZSPACE_EXTERNAL int ext_meshField_blend_linear(zExtMeshScalarField& extField, int currentFrame, int totalFrames, zExtFloatArray& fieldValues_A, zExtFloatArray& fieldValues_B, zExtFloatArray& fieldValues_Result);


		//--------------------------
		//---- CONTOUR METHODS
		//--------------------------

		/*! \brief This method creates a isocontour graph from the input field mesh at the given field threshold.
		*
		*	\param	[in, out]	extField			- zExtField object.
		*	\param	[out]	outCoutourGraphObj	- isoline graph.
		*	\param	[in]	inThreshold		- field threshold.
		*	\return			zGraph			- contour graph.
		*	\since version 0.0.2
		*	\warning	works only with scalar fields
		*/
		ZSPACE_EXTERNAL int ext_meshField_getIsocontour(zExtMeshScalarField& extField, zExtGraph& outCoutourGraphObj, float inThreshold, int precision = PRECISION, float distTolerance = distanceTolerance);

		/*! \brief This method creates a isoline mesh from the input field mesh at the given field threshold.
		*
		*	\details based on https://en.wikipedia.org/wiki/Marching_squares.
		*	\param	[in, out]	extField			- zExtField object.
		*	\param	[out]	outCoutourMeshObj	- isoline mesh.
		*	\param	[in]	inThreshold		- field threshold.
		*	\param	[in]	invertMesh		- true if inverted mesh is required.
		*	\return			zMesh			- isoline mesh.
		*	\since version 0.0.2
		*	\warning	works only with scalar fields
		*/
		ZSPACE_EXTERNAL int ext_meshField_getIsolineMesh(zExtMeshScalarField& extField, zExtMesh& outCoutourMeshObj, float inThreshold = 0.5, bool invertMesh = false);

		/*! \brief This method creates a isoband mesh from the input field mesh at the given field threshold.
		*
		*	\details based on https://en.wikipedia.org/wiki/Marching_squares.
		*	\param	[in, out]	extField			- zExtField object.
		*	\param	[out]	outCoutourMeshObj	- isoband mesh.
		*	\param	[in]	inThresholdLow	- field threshold domain minimum.
		*	\param	[in]	inThresholdHigh	- field threshold domain maximum.
		*	\since version 0.0.2
		*	\warning	works only with scalar fields
		*/
		ZSPACE_EXTERNAL int ext_meshField_getIsobandMesh(zExtMeshScalarField& extField, zExtMesh& outCoutourMeshObj, float inThresholdLow, float inThresholdHigh);
	





	}



}




#if defined(ZSPACE_EXTERNAL_STATIC_LIBRARY)  || defined(ZSPACE_EXTERNAL_DYNAMIC_LIBRARY)
// All defined OK so do nothing
#else
#include<source/zCore/Field/zExtField.cpp>
#endif

#endif