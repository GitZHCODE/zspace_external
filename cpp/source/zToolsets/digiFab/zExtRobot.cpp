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

	//--------------------------
	//----CREATE METHODS
	//--------------------------
	ZSPACE_EXTERNAL_INLINE void ext_zTsRobot_createRobotFromFile(zExtRobot& extRobot, char* path)
	{

		string pathSt(path);
	
		extRobot.robot = new zTsRobot();
		extRobot.robot->createRobotfromFile(pathSt, zJSON);
		extRobot.updateAttributes();


	}
	ZSPACE_EXTERNAL_INLINE void ext_zTsRobot_createRobotJointMeshesfromFile(zExtRobot& extRobot, char* dir)
	{
		extRobot.robot->createRobotJointMeshesfromFile(dir, zOBJ, true);
	}

	
	//--------------------------
	//----SET METHODS
	//--------------------------
	ZSPACE_EXTERNAL_INLINE void ext_zTsRobot_setEndEffector(zExtRobot& extRobot, zExtTransform& eeTransform)
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
			o_FabricationMeshes[i] = *fabMesh[i].extPointer;
		}
	}

	ZSPACE_EXTERNAL_INLINE void ext_zTsRobot_setFabricationPlane(zExtRobot& extRobot, zExtTransform fabBasePlane)
	{
		extRobot.robot->setFabricationWorkbase(*fabBasePlane._transform);

	}
	ZSPACE_EXTERNAL_INLINE void ext_zTsRobot_setRobotHomePlane(zExtRobot& extRobot, zExtTransform workBasePlane)
	{
		extRobot.robot->setFabricationRobotHome(*workBasePlane._transform);
	}
	ZSPACE_EXTERNAL_INLINE void ext_zTsRobot_setRobotBasePlane(zExtRobot& extRobot, zExtTransform robotBase)
	{
		extRobot.robot->setBase(*robotBase._transform);
	}
	ZSPACE_EXTERNAL_INLINE void ext_zTsRobot_setFabricationMeshJSONFromDir(zExtRobot& extRobot, char* dir)
	{
		//cout << endl << "setfab mesh - external " << 1;
		extRobot.robot->createFabMeshesfromDir(dir, zJSON);
	}
	ZSPACE_EXTERNAL_INLINE void ext_zTsRobot_setFabricationMeshOBJFromDir(zExtRobot& extRobot, char* dir)
	{
		extRobot.robot->createFabMeshesfromDir(dir, zOBJ);
	}
		
	//--------------------------
	//----GET METHODS
	//--------------------------
	ZSPACE_EXTERNAL_INLINE void ext_zTsRobot_getTargets(zExtRobot& extRobot, zExtTransform* targets, bool* targetsReachability, int* targetsTypes, float* ovAngles, float* speed)
	{
		for (int i = 0; i < extRobot.robot->robotTargets.size(); i++)
		{
			targets[i]._transform = &extRobot.robot->robotTargets[i];

			targets[i].updateAttributes();
			//cout << endl << "reachability: " << extRobot.robot->robotTargetReachabilities[i];

			targetsReachability[i] = extRobot.robot->robotTargetReachabilities[i];
			//cout << endl << "reachability: " << targetsReachability[i];
			targetsTypes[i] = extRobot.robot->robotTargetTypes[i];
			ovAngles[i] = extRobot.robot->OV_angles[i];
			ovAngles[i] = extRobot.robot->robotTargetSpeeds[i];
			//cout << endl << "type: " << targetsTypes[i];


		}
	}
	ZSPACE_EXTERNAL_INLINE void ext_zTsRobot_getTargetsPerpToMesh(zExtRobot& extRobot, zExtTransform* targets)
	{
		for (int i = 0; i < extRobot.robot->targetsPerpToMesh.size(); i++)
		{
			targets[i]._transform = &extRobot.robot->targetsPerpToMesh[i];

			targets[i].updateAttributes();
		}
		//ad
	}
	ZSPACE_EXTERNAL_INLINE void ext_zTsRobot_getFabricationPlane(zExtRobot& extRobot, zExtTransform& fabBasePlane)
	{
		fabBasePlane._transform = &extRobot.robot->o_fabObj.fabrication_base;
		fabBasePlane.updateAttributes();
	}
	ZSPACE_EXTERNAL_INLINE void ext_zTsRobot_getRobotHomePlane(zExtRobot& extRobot, zExtTransform& workBasePlane)
	{
		workBasePlane._transform = &extRobot.robot->o_fabObj.robot_home;
		workBasePlane.updateAttributes();
	}
	ZSPACE_EXTERNAL_INLINE void ext_zTsRobot_getFabricationMeshes(zExtRobot& extRobot, zExtMeshArray& meshArray)
	{
		meshArray.pointer = &extRobot.robot->o_fabObj.fabMeshes;
		meshArray.updateAttributes();
	}
	ZSPACE_EXTERNAL_INLINE void ext_zTsRobot_getFabricationBoundingBox(zExtRobot& extRobot, zExtMesh& boundingBox)
	{
		boundingBox.extPointer = new zObjMesh;
		extRobot.robot->getFabBbox(*boundingBox.extPointer);
		boundingBox.updateAttributes();
	}
	
	//--------------------------
	//----COMPUTE METHODS
	//--------------------------
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

		//zTsRHWC rhwc = *extRobot.robot;
		//rhwc.getOVAngle(*targetTransformation._transform, angle, rhwc.o_fabObj.fabMeshes[0]);
		//*extRobot.robot = rhwc;


		/*cout << endl << "dot: " << dot;
		cout << endl << "angle: " << angle;
		cout << endl << "dotZeroZ: " << dotZeroZ;
		cout << endl << "angleZeroZ: " << angleZeroZ;*/

		extRobot.updateAttributes();
		return extRobot.robot->inReach;
	}

	ZSPACE_EXTERNAL_INLINE void ext_zTsRobot_computeTargetzTsRHWC(zExtRobot& extRobot, int& targetCount)
	{
		//cout << endl << "target " << "0";

		zTsRHWC rhwc = *extRobot.robot;
		rhwc.computeTargets();
		//cout << endl << "target " << "1";

		rhwc.computeGcode();
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

	ZSPACE_EXTERNAL_INLINE void ext_zTsRobot_exportGCodeABB(zExtRobot& extRobot, char* dir)
	{
		extRobot.robot->gCode_to(dir, zRobotABB);
	}

}