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

#ifndef ZSPACE_EXT_TS_VAULT_H
#define ZSPACE_EXT_TS_VAULT_H



#pragma once

//#include <headers/zToolsets/geometry/zTsSDFSlicer.h>

#include <headers/base/zSpace_External.h>

#include <headers/zCore/base/zExtern.h>
//#include <headers/zInterface/functionsets/zFnMesh.h>
//#include <headers/zInterface/functionsets/zFnGraph.h>
#include <headers/zToolsets/statics/zTsVault.h>
#include<headers/zCore/zExtMesh.h>
#include<headers/zCore/zExtGraph.h>

//#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>

#include<execution>

using namespace std;

namespace zSpace
{



	struct ZSPACE_EXTERNAL zExtVault
	{
		zTsMeshVault* meshPointer = nullptr; /**< A pointer to zTsMeshVault */
		zTsGraphVault* graphPointer = nullptr; /**< A pointer to zTsGraphVault */
		int vaultType = -1; /**< 1 if the vault is a mesh, 0 is the vault is a graph */

		zExtVault();
		zExtVault(int type);
		zExtVault(zTsMeshVault* meshPointer);
		zExtVault(zTsGraphVault* graphPointer);
		zExtVault(zObjMesh* oMesh);
		zExtVault(zObjGraph* oGraph);


		~zExtVault();

		bool checkIfAssigned();

		int checkMemAlloc(bool allocateMemory = true);
		/**
		 * \brief Updates the attributes of the external object
		 */
		void updateAttributes();
		/**
		 * \brief get items from array
		 */

	};

	


	ZSPACE_EXTERNAL_C
	{

		/*! \brief This method creates a zExtVault object from zExtMesh.*/
		ZSPACE_EXTERNAL int ext_vault_createMeshVault(zExtMesh & extMesh, zExtVault & extVault);

		ZSPACE_EXTERNAL int ext_vault_createGraphVault(zExtGraph& extGraph, zExtVault& extVault);


		ZSPACE_EXTERNAL int ext_vault_duplicate(zExtVault& extVault, zExtVault& outExtVault);



		ZSPACE_EXTERNAL int ext_vault_getMesh(zExtVault& extVault, zDiagramType type, zExtMesh& outExtMesh);

		ZSPACE_EXTERNAL int ext_vault_getGraph(zExtVault& extVault, zDiagramType type, zExtGraph& outExtGraph);

		//setConstraints(zDiagramType type, const vector<int>& _fixedVertices)
		/*! \brief This method sets the constraints for each vertex of the input diagram type.
		* \param [in, out]	extVault							- zExtVault object to update.
		* \param		[in]	type								- type of diagram to update.
		* \param		[in]	fixedVertices						- vector of fixed vertices.
		* \return 1 on success, 0 on failure.
		*/

		ZSPACE_EXTERNAL int ext_vault_setConstraints(zExtVault& extVault, zDiagramType type, zExtIntArray& fixedVertices);

		/*! \brief This method sets the result vertex update weights for each vertex of the input diagram type based on the constraints.
		*	\param [in, out]	extVault							- zExtVault object to update.
		*	\param		[in]	type								- type of diagram to update.
		*	\return 1 on success, 0 on failure.
		*	\since version 0.0.2
		*/
		//setVertexWeightsfromConstraints(zDiagramType type)
		ZSPACE_EXTERNAL int ext_vault_setVertexWeightsfromConstraints(zExtVault& extVault, zDiagramType type);

		//void setVertexThickness(float thickness);
		/*! \brief This method sets the thickness of the input diagram type.
		* \param [in, out]	extVault							- zExtVault object to update.
		* 
		*/
		ZSPACE_EXTERNAL int ext_vault_setVertexThickness(zExtVault& extVault, float thickness);

		//void setVertexThickness(vector<float>& thickness);
		ZSPACE_EXTERNAL int ext_vault_setVertexThicknessForEach(zExtVault& extVault, zExtFloatArray& thickness);
		

		///*! \brief This method sets vertex mass of all the result vertices to the input value.
		//*
		//*	\param		[in]	mass			- mass value.
		//*	\since version 0.0.2
		//*/
		//void setVertexMass(float mass);
		ZSPACE_EXTERNAL int ext_vault_setVertexMass(zExtVault& extVault, float mass);

		///*! \brief This method sets vertex mass of all the result vertices to the input container of values.
		//*
		//*	\param		[in]	mass			- container of mass values.
		//*	\since version 0.0.2
		//*/
		//void setVertexMass(vector<float>& mass);
		ZSPACE_EXTERNAL int ext_vault_setVertexMassForEach(zExtVault& extVault, zExtFloatArray& mass);


		///*! \brief This method sets force density of all the edges to the input value.
		//*
		//*	\param		[in]	fDensity			- force density value.
		//*	\since version 0.0.2
		//*/
		//void setForceDensity(float fDensity);
		ZSPACE_EXTERNAL int ext_vault_setForceDensity(zExtVault& extVault, float fDensity);

		///*! \brief This method sets force density of the edges with the input container of values.
		//*
		//*	\param		[in]	fDensities			- container of force density values.
		//*	\since version 0.0.2
		//*/
		//void setForceDensities(vector<float>& fDensities);
		ZSPACE_EXTERNAL int ext_vault_setForceDensityForEach(zExtVault& extVault, zExtFloatArray& fDensities);

		///*! \brief This method computes the result based on the force density method.
		//*
		//*	\details Based on Schek, H-J. "The force density method for form finding and computation of general networks." Computer methods in applied mechanics and engineering 3.1 (1974): 115-134. (https://www.sciencedirect.com/science/article/pii/0045782574900450)
		//	and Linkwitz, K. (2014). Force density method. Shell Structures for Architecture: Form Finding and Optimization, Routledge, Oxon and New York, 59-71.
		//*	\return				bool								- true if solution is found.
		//*	\since version 0.0.2
		//*/
		//bool forceDensityMethod();
		ZSPACE_EXTERNAL int ext_vault_forceDensityMethod(zExtVault& extVault);






		///*! \brief This method creates the result geometry from the input file.
		//	*
		//	*	\param [in, out]	extVault		- zExtVault object to update.
		//	*	\param [in]			path			- input file name including the directory path and extension.
		//	*	\param [in]			type			- type of file to be imported.  0 for FormGeometry, 1 for ForceGeometry, 2 for ResultGeometry
		//	*	\return 1 on success, 0 on failure.
		//	*/
		//ZSPACE_EXTERNAL int ext_vault_createResultfromFile(zExtVault& extVault, char* path, int type);

		///*! \brief This method creates the force geometry from the input file.
		//*
		//*	\param [in, out]	extVault		- zExtVault object to update.
		//*	\param [in]		path			- input file name including the directory path and extension.
		//*	\param [in]		type			- type of file to be imported.
		//*	\return 1 on success, 0 on failure.
		//*	\since version 0.0.2
		//*/
		//ZSPACE_EXTERNAL int ext_vault_createForcefromFile(zExtVault& extVault, char* path, int type);

		///*! \brief This method creates the form geometry from the input file.
		//*
		//*	\param [in, out]	extVault		- zExtVault object to update.
		//*	\param [in]		path			- input file name including the directory path and extension.
		//*	\param [in]		type			- type of file to be imported.
		//*	\return 1 on success, 0 on failure.
		//*	\since version 0.0.2
		//*	\warning works only with meshes.
		//*/
		//ZSPACE_EXTERNAL int ext_vault_createFormfromFile(zExtVault& extVault, char* path, int type);

		///*! \brief This method computes the form diagram from the result.
		//*
		//*	\param [in, out]	extVault		- zExtVault object to update.
		//*	\return 1 on success, 0 on failure.
		//*	\since version 0.0.2
		//*/
		//ZSPACE_EXTERNAL int ext_vault_createFormFromResult(zExtVault& extVault);

		///*! \brief This method computes the form diagram from the force diagram.
		//*
		//*	\param [in, out]	extVault		- zExtVault object to update.
		//*	\param [in]		excludeBoundary	- true if boundary faces are to be ignored.
		//*	\param [in]		PlanarForceMesh	- true if input mesh is planar.
		//*	\param [in]		rotate90		- true if form diagram is to be rotated by 90.
		//*	\return 1 on success, 0 on failure.
		//*	\since version 0.0.2
		//*	\warning works only with graphs.
		//*/
		//ZSPACE_EXTERNAL int ext_vault_createFormFromForce(zExtVault& extVault, bool excludeBoundary, bool PlanarForceMesh, bool rotate90);

		///*! \brief This method computes the force diagram from the form diagram.
		//*
		//*	\param [in, out]	extVault		- zExtVault object to update.
		//*	\param [in]		rotate90		- true if force diagram is to be rotated by 90.
		//*	\return 1 on success, 0 on failure.
		//*	\since version 0.0.2
		//*	\warning works only with meshes.
		//*/
		//ZSPACE_EXTERNAL int ext_vault_createForceFromForm(zExtVault& extVault, bool rotate90);

		///*! \brief This method computes the result from the form.
		//*
		//*	\param [in, out]	extVault		- zExtVault object to update.
		//*	\return 1 on success, 0 on failure.
		//*	\since version 0.0.2
		//*/
		//ZSPACE_EXTERNAL int ext_vault_createResultFromForm(zExtVault& extVault);

		//


		///*! \brief This method computes the horizontal equilibrium of the form and force diagram.
		//	*
		//	*	\details Based on Block, Philippe, and John Ochsendorf. "Thrust network analysis: A new methodology for three-dimensional equilibrium." Journal of the International Association for shell and spatial structures 48.3 (2007): 167-173.
		//	*	\param [in, out]	extVault		- zExtVault object to update.
		//	*	\param		[in]	computeTargets						- true if the targets for horizontal equiibrium have to be computed.
		//	*	\param		[in]	formWeight							- weight of form mesh update. To be between 0 and 1.
		//	*	\param		[in]	dT									- integration timestep.
		//	*	\param		[in]	type								- integration type - (0) for zEuler or  (1) for zRK4.
		//	* 	\param		[out]	bool								- true if the all the correponding edges are parallel.
		//	*	\param		[in]	numIterations						- number of iterations to run.
		//	*	\param		[in]	angleTolerance						- angle tolerance for parallelity.
		//	*	\param		[in]	minMax_formEdge						- minimum value of the target edge for form mesh.
		//	*	\param		[in]	minMax_forceEdge					- minimum value of the target edge for force mesh.
		//	*	\param		[in]	printInfo							- prints information of minimum and maximum deviation if true.
		//	*	\param		[in]	colorEdges							- colors diagram edges based on deviation if true.
		//	*	\return 1 on success, 0 on failure.
		//	*	\since version 0.0.2
		//	*/
		//ZSPACE_EXTERNAL int ext_vault_equilibriumHorizontal(zExtVault& extVault, bool& computeTargets, float formWeight, float dT, int type, bool& outAllParallel, int numIterations = 1, float angleTolerance = 0.001, float minMax_formEdge = 0.1, float minMax_forceEdge = 0.1, bool colorEdges = false, bool printInfo = false);


		///*! \brief This method computes the vertical equilibrium of the result diagram using linear algebra method.
		//	*
		//	*	\param [in, out]	extVault							- zExtVault object to update.
		//	*	\param		[in]	computeForceDensitities				- true if the force densities from the diagrams have to be computed.
		//	*	\param		[in]	forceDiagramScale					- scale of force diagram.
		//	*	\param		[out]	bool								- true if the all the correponding edges are parallel.
		//	*	\return 1 on success, 0 on failure.
		//	*	\since version 0.0.2
		//	*/
		//ZSPACE_EXTERNAL int ext_vault_equilibriumVertical(zExtVault& extVault, bool computeForceDensitities, float forceDiagramScale, bool& outAllParallel);


	}

}




#if defined(ZSPACE_EXTERNAL_STATIC_LIBRARY)  || defined(ZSPACE_EXTERNAL_DYNAMIC_LIBRARY)
// All defined OK so do nothing
#else
#include<source/zToolsets/statics/zExtVault.cpp>
#endif

#endif