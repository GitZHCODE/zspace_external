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
			o_FabricationMeshes[i] = *fabMesh[i].mesh;
		}
	}

	ZSPACE_EXTERNAL_INLINE void ext_zTsRobot_setFabricationPlane(zExtRobot& extRobot, zExtTransform fabBasePlane)
	{
		extRobot.robot->setFabricationRobotHome(*fabBasePlane._transform);
	}
	ZSPACE_EXTERNAL_INLINE void ext_zTsRobot_setRobotHomePlane(zExtRobot& extRobot, zExtTransform workBasePlane)
	{
		extRobot.robot->setFabricationWorkbase(*workBasePlane._transform);
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
	//----SET METHODS
	//--------------------------
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
	ZSPACE_EXTERNAL_INLINE void ext_zTsRobot_getTargets(zExtRobot& extRobot, zExtTransform* targets, bool* targetsReachability, int* targetsTypes)
	{
		for (int i = 0; i < extRobot.robot->robotTargets.size(); i++)
		{
			targets[i]._transform = &extRobot.robot->robotTargets[i];

			targets[i].updateAttributes();
			cout << endl << "reachability: " << extRobot.robot->robotTargetReachabilities[i];

			targetsReachability[i] = extRobot.robot->robotTargetReachabilities[i];
			cout << endl << "reachability: " << targetsReachability[i];
			targetsTypes[i] = extRobot.robot->robotTargetTypes[i];
			cout << endl << "type: " << targetsTypes[i];


		}
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

	ZSPACE_EXTERNAL_INLINE bool ext_zTsRobot_inverseKinematics(zExtRobot& extRobot, zExtTransform& targetTransformation, float& dot, float& angle, float& dotZeroZ, float& angleZeroZ)
	{
		extRobot.robot->setTarget(*targetTransformation._transform);

		extRobot.robot->inverseKinematics();

		zFnMesh fnbox(extRobot.robot->o_fabObj.bbox);
		zPoint boxC = fnbox.getCenter();

		zPoint targetPos((*targetTransformation._transform)(3, 0), (*targetTransformation._transform)(3, 1), (*targetTransformation._transform)(3, 2));
		zVector targetNormal((*targetTransformation._transform)(2, 0), (*targetTransformation._transform)(2, 1), (*targetTransformation._transform)(2, 2));
		zVector vecCentreToPos = targetPos - boxC;
		zVector unitZ(0, 0, 1);
		float angleZ = targetNormal.angle(unitZ);
		dot = targetNormal * targetPos;
		angle = targetNormal.angle(vecCentreToPos);
		//unify the z
		targetNormal.z = 0;
		vecCentreToPos.z = 0;

		dotZeroZ = targetNormal * targetPos;
		angleZeroZ = targetNormal.angle(vecCentreToPos);

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