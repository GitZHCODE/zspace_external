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


#include "headers/zToolsets/statics/zExtVault.h"


namespace zSpace
{
	ZSPACE_EXTERNAL_INLINE zExtVault::zExtVault()
	{
		graphPointer = nullptr;
		meshPointer = nullptr;
		vaultType = -1;
	}
	ZSPACE_EXTERNAL_INLINE zExtVault::zExtVault(zTsMeshVault* meshPointer)
	{
		graphPointer = nullptr;
		meshPointer = meshPointer;
		vaultType = 1;
	}
	ZSPACE_EXTERNAL_INLINE zExtVault::zExtVault(zTsGraphVault* graphPointer)
	{
		graphPointer = graphPointer;
		meshPointer = nullptr;
		vaultType = 0;
	}
	ZSPACE_EXTERNAL_INLINE zExtVault::zExtVault(int type)
	{
		switch (type)
		{
		case 0:
			graphPointer = new zTsGraphVault();
			meshPointer = nullptr;
			vaultType = 0;
			break;
		case 1:
			graphPointer = nullptr;
			meshPointer = new zTsMeshVault();
			vaultType = 1;
			break;
		default:
			graphPointer = nullptr;
			meshPointer = nullptr;
			vaultType = -1;
			break;
		}
		
	}
	ZSPACE_EXTERNAL_INLINE zExtVault::zExtVault(zObjMesh* oMesh)
	{
		graphPointer = nullptr;
		meshPointer = new zTsMeshVault(*oMesh);
		vaultType = 1;
	}
	ZSPACE_EXTERNAL_INLINE zExtVault::zExtVault(zObjGraph* oGraph)
	{
		graphPointer = new zTsGraphVault(*oGraph);
		meshPointer = nullptr;
		vaultType = 0;
	}
	ZSPACE_EXTERNAL_INLINE zExtVault::~zExtVault()
	{
			delete graphPointer;
			graphPointer = nullptr;

			delete meshPointer;
			meshPointer = nullptr;

	}

	ZSPACE_EXTERNAL_INLINE bool zExtVault::checkIfAssigned()
	{
		vector<bool> checkList;

		checkList.assign(2, false);
		checkList[0] = !(graphPointer == nullptr && meshPointer == nullptr);
		checkList[1] = (vaultType == 0 || vaultType == 1);

		for (auto b : checkList)
		{
			if (!b)
			{
				zExtVault();
				return false;
			}
		}
		return true;
	}
	ZSPACE_EXTERNAL_INLINE int zExtVault::checkMemAlloc(bool allocateMemory)
	{
		return 0;
	}

	ZSPACE_EXTERNAL_INLINE void zExtVault::updateAttributes()
	{
	}

	

	ZSPACE_EXTERNAL_INLINE int ext_vault_createMeshVault(zExtMesh& extMesh, zExtVault& extVault)
	{
		try
		{			
			if (extMesh.pointer == nullptr)
			{
				return 0;
			}
			extVault = zExtVault(extMesh.pointer);

			//delete extVault.graphPointer;
			//extVault.graphPointer = nullptr;
			////extVault.meshPointer = new  zTsVault<zObjMesh, zFnMesh>();
			////extVault.meshPointer = new  zTsMeshVault();

			//extVault.meshPointer = new zTsMeshVault(*extMesh.pointer);
			//extVault.vaultType = 1;

			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
	}

	ZSPACE_EXTERNAL_INLINE int ext_vault_createGraphVault(zExtGraph& extGraph, zExtVault& extVault)
	{
		try
		{
			if (extGraph.pointer == nullptr)
			{
				return 0;
			}
			extVault = zExtVault(extGraph.pointer);
			/*delete extVault.meshPointer;
			extVault.meshPointer = nullptr;

			if (extGraph.pointer == nullptr)
			{
				return 0;
			}
			extVault.graphPointer = new zTsGraphVault(*extGraph.pointer);
			extVault.vaultType = 0;*/

			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
	}

	ZSPACE_EXTERNAL_INLINE int ext_vault_duplicate(zExtVault& extVault, zExtVault& outExtVault)
	{
		//try
		//{
		//	printf("\n ext_vault_duplicate 0");
		//	if (!extVault.checkIfAssigned())
		//	{
		//		return 0;
		//	}
		//	outExtVault = zExtVault(extVault.vaultType);
		//	printf("\n ext_vault_duplicate 1");

		//	switch (extVault.vaultType)
		//	{
		//	case 0:
		//		*outExtVault.graphPointer = zTsGraphVault(*extVault.graphPointer); //not using new because I have already created memory in the constructor
		//		break;
		//	case 1:
		//		*outExtVault.meshPointer = zTsMeshVault(*extVault.meshPointer);
		//		break;
		//	default:
		//		printf("\n ext_vault_duplicate 3");

		//		return 0;
		//		break;
		//	}
		//	printf("\n ext_vault_duplicate 2");

		//	return 1;
		//}
		//catch (const std::exception&)
		//{
			return 0;
		//}
	}

	ZSPACE_EXTERNAL_INLINE int ext_vault_getMesh(zExtVault& extVault, zDiagramType type, zExtMesh& outExtMesh)
	{
		try
		{
			if (!extVault.checkIfAssigned())
			{
				return 0;
			}
			if (extVault.meshPointer == nullptr || extVault.vaultType!=1)
			{
				return 0;
			}
			outExtMesh.checkMemAlloc();
			switch (type)
			{
			case zSpace::zFormDiagram:
				outExtMesh.pointer = extVault.meshPointer->formObj;
				break;
			case zSpace::zForceDiagram:
				outExtMesh.pointer = extVault.meshPointer->forceObj;
				break;
			case zSpace::zResultDiagram:
				outExtMesh.pointer = extVault.meshPointer->resultObj;
				break;
			default:
				break;
			}
			outExtMesh.updateAttributes();
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
	}

	ZSPACE_EXTERNAL_INLINE int ext_vault_getGraph(zExtVault& extVault, zDiagramType type, zExtGraph& outExtGraph)
	{
		try
		{
			if (!extVault.checkIfAssigned())
			{
				return 0;
			}
			if (extVault.graphPointer == nullptr || extVault.vaultType != 0)
			{
				return 0;
			}
			outExtGraph.checkMemAlloc();
			switch (type)
			{
			case zSpace::zFormDiagram:
				outExtGraph.pointer = extVault.graphPointer->formObj;
				break;
			case zSpace::zForceDiagram:
				//outExtGraph.pointer = extVault.graphPointer->forceObj;
				printf("force diagram for graph is not supported yet");
				return 0;
				break;
			case zSpace::zResultDiagram:
				outExtGraph.pointer = extVault.graphPointer->resultObj;
				break;
			default:
				break;
			}
			outExtGraph.updateAttributes();
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}

	}

	ZSPACE_EXTERNAL_INLINE int ext_vault_setConstraints(zExtVault& extVault, zDiagramType type, zExtIntArray& fixedVertices)
	{
		try
		{
			if (!extVault.checkIfAssigned())
			{
				return 0;
			}
			switch (extVault.vaultType)
			{
			case 0:
				(fixedVertices.arrayCount ==0)? extVault.graphPointer->setConstraints(type) : extVault.graphPointer->setConstraints(type, *fixedVertices.pointer);
				break;
			case 1:
				(fixedVertices.arrayCount == 0)? extVault.meshPointer->setConstraints(type) : extVault.meshPointer->setConstraints(type, *fixedVertices.pointer);
				break;
			default:
				return 0;
				break;
			}
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
	}

	ZSPACE_EXTERNAL_INLINE int ext_vault_setVertexWeightsfromConstraints(zExtVault& extVault, zDiagramType type)
	{
		try
		{
			if (!extVault.checkIfAssigned())
			{
				return 0;
			}
			switch (extVault.vaultType)
			{
			case 0:
				extVault.graphPointer->setVertexWeightsfromConstraints(type);
				break;
			case 1:
				extVault.meshPointer->setVertexWeightsfromConstraints(type);
				break;
			default:
				return 0;
				break;
			}
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
	}

	ZSPACE_EXTERNAL_INLINE int ext_vault_setVertexThickness(zExtVault& extVault, float thickness)
	{
		try
		{
			if (!extVault.checkIfAssigned())
			{
				return 0;
			}
			switch (extVault.vaultType)
			{
			case 0:
				//(thickness.arrayCount != 0) ? extVault.graphPointer->setVertexThickness()->setVertexThickness() : 
				extVault.graphPointer->setVertexThickness(thickness);
				break;
			case 1:
				//(thickness.arrayCount == 0) ? extVault.meshPointer->setVertexThickness() : 
				extVault.meshPointer->setVertexThickness(thickness);
				break;
			default:
				return 0;
				break;
			}
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
	}

	ZSPACE_EXTERNAL_INLINE int ext_vault_setVertexThicknessForEach(zExtVault& extVault, zExtFloatArray& thickness)
	{
		try
		{
			if (!extVault.checkIfAssigned())
			{
				return 0;
			}
			switch (extVault.vaultType)
			{
			case 0:
				//(thickness.arrayCount != 0) ? extVault.graphPointer->setVertexThickness()->setVertexThickness() : 
				extVault.graphPointer->setVertexThickness(*thickness.pointer);
				break;
			case 1:
				//(thickness.arrayCount == 0) ? extVault.meshPointer->setVertexThickness() : 
				extVault.meshPointer->setVertexThickness(*thickness.pointer);
				break;
			default:
				return 0;
				break;
			}
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
	}

	ZSPACE_EXTERNAL_INLINE int ext_vault_setVertexMass(zExtVault& extVault, float mass)
	{
		try
		{
			if (!extVault.checkIfAssigned())
			{
				return 0;
			}
			switch (extVault.vaultType)
			{
			case 0:
				//(mass.arrayCount != 0) ? extVault.graphPointer->setVertexMass()->setVertexMass() : 
				extVault.graphPointer->setVertexMass(mass);
				break;
			case 1:
				//(mass.arrayCount == 0) ? extVault.meshPointer->setVertexMass() : 
				extVault.meshPointer->setVertexMass(mass);
				break;
			default:
				return 0;
				break;
			}
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
	}

	ZSPACE_EXTERNAL_INLINE int ext_vault_setVertexMassForEach(zExtVault& extVault, zExtFloatArray& mass)
	{
		try
		{
			if (!extVault.checkIfAssigned())
			{
				return 0;
			}
			switch (extVault.vaultType)
			{
			case 0:
				//(mass.arrayCount != 0) ? extVault.graphPointer->setVertexMass()->setVertexMass() : 
				extVault.graphPointer->setVertexMass(*mass.pointer);
				break;
			case 1:
				//(mass.arrayCount == 0) ? extVault.meshPointer->setVertexMass() : 
				extVault.meshPointer->setVertexMass(*mass.pointer);
				break;
			default:
				return 0;
				break;
			}
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
		
	}

	ZSPACE_EXTERNAL_INLINE int ext_vault_setForceDensity(zExtVault& extVault, float fDensity)
	{
		try
		{
			if (!extVault.checkIfAssigned())
			{
				return 0;
			}
			switch (extVault.vaultType)
			{
			case 0:
				//(fDensity.arrayCount != 0) ? extVault.graphPointer->setForceDensity()->setForceDensity() : 
				extVault.graphPointer->setForceDensity(fDensity);
				break;
			case 1:
				//(fDensity.arrayCount == 0) ? extVault.meshPointer->setForceDensity() : 
				extVault.meshPointer->setForceDensity(fDensity);
				break;
			default:
				return 0;
				break;
			}
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
		
	}

	ZSPACE_EXTERNAL_INLINE int ext_vault_setForceDensityForEach(zExtVault& extVault, zExtFloatArray& fDensities)
	{
		try
		{
			if (!extVault.checkIfAssigned())
			{
				return 0;
			}

			switch (extVault.vaultType)
			{
			case 0:
				//(fDensities.arrayCount != 0) ? extVault.graphPointer->setForceDensity()->setForceDensity() : 
				extVault.graphPointer->setForceDensities(*fDensities.pointer);
				break;
			case 1:
				//(fDensities.arrayCount == 0) ? extVault.meshPointer->setForceDensity() : 
				extVault.meshPointer->setForceDensities(*fDensities.pointer);
				break;
			default:
				return 0;
				break;
			}
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
		
	}

	ZSPACE_EXTERNAL_INLINE int ext_vault_forceDensityMethod(zExtVault& extVault)
	{
		bool success = false;
		try
		{
			if (!extVault.checkIfAssigned())
			{
				return 0;
			}
			switch (extVault.vaultType)
			{
			case 0:
				success = extVault.graphPointer->forceDensityMethod();
				break;
			case 1:
				success = extVault.meshPointer->forceDensityMethod();
				break;
			default:
				return 0;
				break;
			}
			return success? 1:0;
		}
		catch (const std::exception& e)
		{
			return 0;
		}
		
	}

	


	

	

}