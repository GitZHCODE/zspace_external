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

#ifndef ZSPACE_EXT_TS_ROBOT_H
#define ZSPACE_EXT_TS_ROBOT_H



#pragma once

#include <headers/zCore/base/zExtern.h>
#include <headers/zInterface/functionsets/zFnMesh.h>
#include <headers/zInterface/functionsets/zFnGraph.h>

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>

#include<execution>

#include<headers/zToolsets/digifab/zTsRobot.h>
#include<headers/zToolsets/digifab/zTsRobotFab.h>

#include "headers/base/zSpace_External.h"
#include "headers/zCore/Geometry/zExtMesh.h"

using namespace std;




namespace zSpace
{
	/** \addtogroup zExternal
	*	\brief Collection of external structs and methods for applications.
	*  @{
	*/

	/** \addtogroup zToolsets
	*	\brief external structs and methods for zToolsets.
	*  @{
	*/

	/** \addtogroup DigiFab
	*	\brief external structs and methods for digital fabrication related utilities.
	*  @{
	*/

	/*! \struct zTsRobot
	*	\brief An external struct for zTsRobot.
	*	\since version 0.0.1
	*/

	/** @}*/

	/** @}*/

	/** @}*/

	struct zExtRobot
	{
		zTsRobot* robot;							///< Pointer to the original robot object.
		zExtTransform robotJointTransforms[6];		///< Array of joint transforms.
		float robotJointRotation[6];				///< Array of joint rotations.
		float robotJointRotationMax[6];				///< Array of maximum joint rotations.
		float robotJointRotationMin[6];				///< Array of minimum joint rotations.
		float robotJointRotationHome[6];			///< Array of home joint rotations.
		float robotJointRotationMask[6];			///< Array of joint rotation masks.
		float robotJointRotationPulse[6];			///< Array of joint rotation pulses.
		float robotJointRotationOffset[6];			///< Array of joint rotation offsets.

		zExtRobot();

		/**
		 * \brief Constructs a new zExtRobot object.
		 * \param[in,out] r		-Pointer to the original robot object.
		 * \since version 0.0.1
		 */
		zExtRobot(zTsRobot* r);


		/**
		 * \brief Updates the zExtRobot attributes.
		 * \since version 0.0.1
		 */
		void updateAttributes();
	};


	ZSPACE_EXTERNAL_C
	{

		//--------------------------
		//----CREATE METHODS
		//--------------------------
		/**
		 * \brief Reads a robot JSON file.
		 * \param [in,out]							-extRobot The zExtRobot object to read into.
		 * \param [in]								-path The path to the JSON file.
		 * \since version 0.0.1
		 */
		ZSPACE_EXTERNAL void ext_zTsRobot_createRobotFromFile(zExtRobot & extRobot, char* path);


		/**
		 * \brief Sets the fabrication mesh, base plane, and computes targets for an zExtRobot.
		 * \param [in,out]	extRobot 				-The zExtRobot object.
		 * \param [in]		dir 					-The directory of the robot mesh to set.
		 * \since version 0.0.1
		 */
		ZSPACE_EXTERNAL void ext_zTsRobot_createRobotJointMeshesfromFile(zExtRobot& extRobot, char* dir);



		//--------------------------
		//----SET METHODS
		//--------------------------

		/**
		 * \brief Sets the end effector transform for an zExtRobot.
		 * \param [in,out]	extRobot 				-The zExtRobot object.
		 * \param [in]		eeTransform 			-The end effector transform to set.
		 * \since version 0.0.1
		 */
		ZSPACE_EXTERNAL void ext_zTsRobot_setEndEffector(zExtRobot& extRobot, zExtTransform& eeTransform);
		/**
		* \brief Sets the fabrication mesh from JSON dir for an zExtRobot.
		* \param [in,out]	extRobot 				-The zExtRobot object.
		* \param [in]		dir 				-The directory of the fabrication mesh to set.
		* \since version 0.0.1
		*/
		ZSPACE_EXTERNAL void ext_zTsRobot_setFabricationMeshJSONFromDir(zExtRobot& extRobot, char* dir);
		
		/**
		* \brief Sets the fabrication mesh from OBJ dir for an zExtRobot.
		* \param [in,out]	extRobot 				-The zExtRobot object.
		* \param [in]		dir 			-The directory of the fabrication mesh to set.
		* \since version 0.0.1
		*/
		ZSPACE_EXTERNAL void ext_zTsRobot_setFabricationMeshOBJFromDir(zExtRobot& extRobot, char* dir);

		/**
		 * \brief Set fabrication mesh for an zExtRobot.
		 * \param [in,out]	extRobot 				-The zExtRobot object.
		 * \param [in]		fabBasePlane 			-The base plane to set.
		 * \param [in]		workBasePlane 			-The work base plane to set.
		 * \since version 0.0.1
		 */
		ZSPACE_EXTERNAL void ext_zTsRobot_setFabricationMesh(zExtRobot& extRobot, zExtMesh* fabMesh, int fabMeshCount);

		/**
		 * \brief Sets the fabrication base plane for an zExtRobot.
		 * \param [in,out]	extRobot 				-The zExtRobot object.
		 * \param [in]		fabBasePlane 			-The base plane to set.
		 * \param [in]		workBasePlane 			-The work base plane to set.
		 * \since version 0.0.1
		 */
		ZSPACE_EXTERNAL void ext_zTsRobot_setFabricationPlane(zExtRobot& extRobot, zExtTransform fabBasePlane);

		/**
		 * \brief Sets the robot home an zExtRobot.
		 * \param [in,out]	extRobot 				-The zExtRobot object.
		 * \param [in]		fabBasePlane 			-The base plane to set.
		 * \param [in]		workBasePlane 			-The work base plane to set.
		 * \since version 0.0.1
		 */
		ZSPACE_EXTERNAL void ext_zTsRobot_setRobotHomePlane(zExtRobot& extRobot, zExtTransform workBasePlane);

		/**
		 * \brief Sets the robot base for an zExtRobot.
		 * \param [in,out]	extRobot 				-The zExtRobot object.
		 * \param [in]		robotBase 				-The base plane of the robot.
		 * \since version 0.0.1
		 */
		ZSPACE_EXTERNAL void ext_zTsRobot_setRobotBasePlane(zExtRobot& extRobot, zExtTransform robotBase);

		//--------------------------
		//----GET METHODS
		//--------------------------
		/**
		 * \brief Computes the gCode for an zExtRobot based on zTsRHWC computeGcode method.
		 * \param [in,out]	extRobot 					-The zExtRobot object.
		 * \param [out]		targets 					-Array of tragets transforms.
		 * \param [out]		targetsReachability 		-Array of tragets reachability.
		 * \param [out]		ovAngles			 		-Array of Omniverse cutting plane angles.
		 * \since version 0.0.1
		 */
		ZSPACE_EXTERNAL void ext_zTsRobot_getTargets(zExtRobot& extRobot, zExtTransform* targets, bool* targetsReachability, int* targetsTypes, float* ovAngles, float* speed);

		//--------------------------
		//----GET METHODS
		//--------------------------
		/**
		 * \brief Computes the gCode for an zExtRobot based on zTsRHWC computeGcode method.
		 * \param [in,out]	extRobot 					-The zExtRobot object.
		 * \param [out]		targets 					-Array of tragets transforms.
		 * \param [out]		targetsReachability 		-Array of tragets reachability.
		 * \param [out]		ovAngles			 		-Array of Omniverse cutting plane angles.
		 * \since version 0.0.1
		 */
		ZSPACE_EXTERNAL void ext_zTsRobot_getTargetsPerpToMesh(zExtRobot& extRobot, zExtTransform* targets);



		/**
		* \brief Get base plane, and woekplane for an zExtRobot.
		* \param [in,out]	extRobot 				-The zExtRobot object.
		* \param [out]		fabBasePlane 			-The base plane.
		* \param [out]		workBasePlane 			-The robot home plane.
		* \since version 0.0.1
		*/
		ZSPACE_EXTERNAL void ext_zTsRobot_getFabricationPlane(zExtRobot& extRobot, zExtTransform& fabBasePlane);

		/**
		* \brief Get base plane, and woekplane for an zExtRobot.
		* \param [in,out]	extRobot 				-The zExtRobot object.
		* \param [out]		workBasePlane 			-The robot home plane.
		* \since version 0.0.1
		*/
		ZSPACE_EXTERNAL void ext_zTsRobot_getRobotHomePlane(zExtRobot& extRobot, zExtTransform& workBasePlane);

		/**
		*\brief Get base plane, and woekplane for an zExtRobot.
		* \param[in, out]	extRobot			- The zExtRobot object.
		* \param[in, out]	meshArray			- zExtMeshArray
		* \since version 0.0.1
		*/
		ZSPACE_EXTERNAL void ext_zTsRobot_getFabricationMeshes(zExtRobot & extRobot, zExtMeshArray& meshArray);

		/**
		*\brief Get the bounding box of the fabrication mesh for an zExtRobot.
		* \param[in, out]	extRobot			- The zExtRobot object.
		* \param[in, out]	meshArray			- zExtMesh bounding box
		* \since version 0.0.1
		*/
		ZSPACE_EXTERNAL void ext_zTsRobot_getFabricationBoundingBox(zExtRobot& extRobot, zExtMesh& boundingBox);



		//--------------------------
		//----COMPUTE METHODS
		//--------------------------

		/**
		 * \brief Computes the forward kinematics for an zExtRobot.
		 * \param [in,out]	extRobot				-The zExtRobot object.
		 * \param [in]		jointRotation			-The joint rotation values to use.
		 * \since version 0.0.1
		 */
		ZSPACE_EXTERNAL void ext_zTsRobot_forwardKinematics(zExtRobot& extRobot, float* jointRotation);

		/**
		 * \brief Computes the inverse kinematics for an zExtRobot.
		 * \param [in,out]	extRobot				-The zExtRobot object.
		 * \param [in,out]	targetTransformation	-The target transformation values to use.
		 * \since version 0.0.1
		 */
		ZSPACE_EXTERNAL bool ext_zTsRobot_inverseKinematics(zExtRobot& extRobot, zExtTransform& targetTransformation);

		//--------------------------
		//----COMPUTE METHODS (RHWC SPECIFIC)
		//--------------------------

		/**
		 * \brief Computes targets for an zExtRobot based on zTsRHWC computeTarget method.
		 * \param [in,out]	extRobot 				-The zExtRobot object.
		 * \param [in,out]	targetCount 			-The target count.
		 * \since version 0.0.1
		 */
		ZSPACE_EXTERNAL void ext_zTsRobot_computeTargetzTsRHWC(zExtRobot& extRobot, int& targetCount);

		/**
		 * \brief Computes the gCode for an zExtRobot based on zTsRHWC computeGcode method.
		 * \param [in,out]	extRobot 				-The zExtRobot object.
		 * \since version 0.0.1
		 */
		ZSPACE_EXTERNAL void ext_zTsRobot_computeGCodeTsRHWC(zExtRobot& extRobot);


		//--------------------------
		//----EXPORT METHODS
		//--------------------------

		/**
		 * \brief Export the gcode of the zExtRobot.
		 * \param [in,out]	extRobot 				-The zExtRobot object.
		 * \param [in]		dir 					-The directory to export the GCode.
		 * \since version 0.0.1
		 */
		ZSPACE_EXTERNAL void ext_zTsRobot_exportGCodeABB(zExtRobot& extRobot, char* dir);

	}

}






#if defined(ZSPACE_EXTERNAL_STATIC_LIBRARY)  || defined(ZSPACE_EXTERNAL_DYNAMIC_LIBRARY)
// All defined OK so do nothing
#else
#include<source/zToolsets/digiFab/zExtRobot.cpp>
#endif

#endif