 //This file is part of zspace, a simple C++ collection of geometry data-structures & algorithms, 
 //data analysis & visualization framework.

 //Copyright (C) 2019 ZSPACE 
 //
 //This Source Code Form is subject to the terms of the MIT License 
 //If a copy of the MIT License was not distributed with this file, You can 
 //obtain one at https://opensource.org/licenses/MIT.

 //Author : Heba Eiz <heba.eiz@zaha-hadid.com>



#include<headers/zToolsets/digifab/zExtRobot.h>



namespace zSpace
{
	
	ZSPACE_EXTERNAL_INLINE zExtRobot::zExtRobot(zTsRobot* r)
	{
		robot = r;
		updateAttributes();
	}

	ZSPACE_EXTERNAL_INLINE void zExtRobot::updateAttributes()
	{

		for (int i = 0; i < 6; i++)
		{
			robotJointTransforms[i]._transform = &robot->robotJointTransforms[i];
			robotJointTransforms[i].updateAttributes();

		}

		for (int i = 0; i < 6; i++)
		{
			robotJointRotation[i] = robot->jointRotations[i].rotation;
			robotJointRotationMax[i] = robot->jointRotations[i].maximum;
			robotJointRotationMin[i] = robot->jointRotations[i].minimum;
			robotJointRotationHome[i] = robot->jointRotations[i].home;
			robotJointRotationOffset[i] = robot->jointRotations[i].offset;
			robotJointRotationPulse[i] = robot->jointRotations[i].pulse;
			robotJointRotationMask[i] = robot->jointRotations[i].mask;
		}
	}
	

	ZSPACE_EXTERNAL_INLINE void ext_zTsRobot_setDirectory(zExtRobot& extRobot, char* dirPath)
	{
		printf("\n ext_zTsRobot_setDirectory - 0");

		vector<string> robotFile;

		zUtilsCore core;
		zObjMeshArray r_meshObjs;
		zObjGraph r_graphObj;
		printf("\n ext_zTsRobot_setDirectory - 1");

		core.getFilesFromDirectory(robotFile, dirPath, zJSON);

		printf("\n ext_zTsRobot_setDirectory - 2");


		int nF = core.getNumfiles_Type(dirPath, zOBJ);
		if (nF < 8) nF = 8;

		r_meshObjs.assign(nF, zObjMesh());

		extRobot.robot = new zTsRHWC();

		printf("\n ext_zTsRobot_setDirectory - 3");


		cout << endl << robotFile[0];

		extRobot.robot->createRobotfromFile(robotFile[0], zJSON);

		printf("\n ext_zTsRobot_setDirectory - 4");

		

		extRobot.robot->createRobotJointMeshesfromFile(dirPath, zOBJ, true);


		zTransform robotTarget;
		zTransform robotEE;

		// set target transform

		robotTarget.setIdentity();
		robotTarget(0, 0) = -1; robotTarget(0, 1) = 0; robotTarget(0, 2) = 0;
		robotTarget(1, 0) = 0; robotTarget(1, 1) = 1; robotTarget(1, 2) = 0;
		robotTarget(2, 0) = 0; robotTarget(2, 1) = 0; robotTarget(2, 2) = -1;
		robotTarget(3, 0) = 2.0; robotTarget(3, 1) = 0; robotTarget(3, 2) = 0;

		// set EE transform
		robotEE.setIdentity();

		robotEE(0, 0) = 0; robotEE(0, 1) = 0; robotEE(0, 2) = -1;
		robotEE(1, 0) = 0; robotEE(1, 1) = 1; robotEE(1, 2) = 0;
		robotEE(2, 0) = 1; robotEE(2, 1) = 0; robotEE(2, 2) = 0;
		robotEE(3, 0) = -0.2; robotEE(3, 1) = 0; robotEE(3, 2) = -0.346;


		extRobot.robot->setEndEffector(robotEE);

		extRobot.updateAttributes();


	}

	ZSPACE_EXTERNAL_INLINE void ext_zTsRobot_createRobotFromFile(zExtRobot& extRobot, char* path)
	{

		string pathSt(path);
	
		extRobot.robot = new zTsRobot();
		extRobot.robot->createRobotfromFile(pathSt, zJSON);
		extRobot.updateAttributes();


	}
	ZSPACE_EXTERNAL_INLINE void ext_zTsRobot_getComputedTargets(zExtRobot& extRobot, float* outTargets)
	{
		printf("\n ext_zTsRobot_getComputedTargets");

		vector<zTransform> tt = extRobot.robot->robotTargets;
		for (int i = 0; i < 6; i++)
		{
			float* data = tt.at(i).data();
			for (int j = 0; j < 16; j++)
			{
				outTargets[i * 16 + j] = data[j];
			}
		}
	}
	ZSPACE_EXTERNAL_INLINE void ext_zTsRobot_setEndEffector(zExtRobot& extRobot, zExtTransform eeTransform)
	{

		extRobot.robot->setEndEffector(*eeTransform._transform);
		extRobot.updateAttributes();

	}

	ZSPACE_EXTERNAL_INLINE void ext_zTsRobot_setFabricationMesh(zExtRobot& extRobot, zExtMesh* fabMesh, int fabMeshCount)
	{

		zObjMeshArray o_FabricationMeshes;
		o_FabricationMeshes.assign(fabMeshCount, zObjMesh());

		for (int i = 0; i < fabMeshCount; i++)
		{
			o_FabricationMeshes[i] = *fabMesh[i].mesh;
		}
	}

	ZSPACE_EXTERNAL_INLINE void ext_zTsRobot_setFabricationPlanes(zExtRobot& extRobot, zExtTransform fabBasePlane, zExtTransform workBasePlane)
	{
		extRobot.robot->setFabricationWorkbase(*workBasePlane._transform);
		extRobot.robot->setFabricationRobotHome(*fabBasePlane._transform);
	}

	ZSPACE_EXTERNAL_INLINE void ext_zTsRobot_setFabricationMeshJSONFromDir(zExtRobot& extRobot, char* dir)
	{
		extRobot.robot->createFabMeshesfromDir(dir, zJSON);
	}
	ZSPACE_EXTERNAL_INLINE void ext_zTsRobot_setFabricationMeshOBJFromDir(zExtRobot& extRobot, char* dir)
	{
		extRobot.robot->createFabMeshesfromDir(dir, zOBJ);
	}
	ZSPACE_EXTERNAL_INLINE void ext_zTsRobot_createRobotJointMeshesfromFile(zExtRobot& extRobot, char* dir)
	{
		extRobot.robot->createRobotJointMeshesfromFile(dir, zOBJ, true);
	}
	ZSPACE_EXTERNAL_INLINE void ext_zTsRobot_forwardKinematics(zExtRobot& extRobot, float* jointRotation)
	{
		
		for (int i = 0; i < 6; i++)
		{
			extRobot.robot->jointRotations[i].rotation = jointRotation[i];
		}

		extRobot.robot->forwardKinematics();

		extRobot.updateAttributes();

	}

	ZSPACE_EXTERNAL_INLINE bool ext_zTsRobot_inverseKinematics(zExtRobot& extRobot, zExtTransform& targetTransformation)
	{
		extRobot.robot->setTarget(*targetTransformation._transform);

		extRobot.robot->inverseKinematics();

		extRobot.updateAttributes();
		return extRobot.robot->inReach;
	}

	ZSPACE_EXTERNAL_INLINE void ext_zTsRobot_exportGCodeABB(zExtRobot& extRobot, char* dir)
	{
		extRobot.robot->gCode_to(dir, zRobotABB);
	}

	ZSPACE_EXTERNAL_INLINE void ext_zTsRobot_computeTargetzTsRHWC(zExtRobot& extRobot, int& targetCount)
	{
		zTsRHWC rhwc = *extRobot.robot;
		rhwc.computeTargets();

		//rhwc.computeGcode();
		*extRobot.robot = rhwc;
		targetCount = extRobot.robot->robotTargets.size();
		extRobot.updateAttributes();
	}

	ZSPACE_EXTERNAL_INLINE void ext_zTsRobot_computeGCodeTsRHWC(zExtRobot& extRobot)
	{
		zTsRHWC rhwc = *extRobot.robot;
		rhwc.computeGcode();
		*extRobot.robot = rhwc;
		extRobot.updateAttributes();
	}

	ZSPACE_EXTERNAL_INLINE void ext_zTsRobot_getTargets(zExtRobot& extRobot, zTransform* targets, bool* targetsReachability, int* targetsTypes)
	{
		for (int i = 0; i < extRobot.robot->robotTargets.size(); i++)
		{
			targets[i] = extRobot.robot->robotTargets[i];
			targetsReachability[i] = extRobot.robot->robotTargetReachabilities[i];
			targetsTypes[i] = extRobot.robot->robotTargetTypes[i];
		}
	}

	ZSPACE_EXTERNAL_INLINE void ext_zTsRobot_getFabricationPlanes(zExtRobot& extRobot, zExtTransform& fabBasePlane, zExtTransform& workBasePlane)
	{
		fabBasePlane._transform = &extRobot.robot->o_fabObj.fabrication_base;
		fabBasePlane.updateAttributes();
		workBasePlane._transform = &extRobot.robot->o_fabObj.robot_home;
		workBasePlane.updateAttributes();
	}

	ZSPACE_EXTERNAL_INLINE void ext_zTsRobot_getFabricationMeshes(zExtRobot& extRobot, zExtMeshArray& meshArray)
	{
		meshArray.pointer = &extRobot.robot->o_fabObj.fabMeshes;
		meshArray.updateAttributes();
	}
	



}