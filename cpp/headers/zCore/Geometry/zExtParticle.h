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

#ifndef ZSPACE_EXT_CORE_PARTICLE_H
#define ZSPACE_EXT_CORE_PARTICLE_H



#pragma once

//#include <headers/zToolsets/geometry/zTsSDFSlicer.h>

#include "headers/base/zSpace_External.h"
#include "headers/zCore/Base/zExtPoint.h"

#include <headers/zCore/base/zExtern.h>
#include <headers/zInterface/objects/zObjParticle.h>
#include <headers/zInterface/functionsets/zFnMesh.h>
#include <headers/zInterface/functionsets/zFnGraph.h>

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>

#include<execution>

using namespace std;

namespace zSpace
{

	struct ZSPACE_EXTERNAL zExtParticle
	{
		zObjParticle* pointer = nullptr;
		double mass;
		bool fixed;
		zExtPoint force;
		zExtPoint position;
		zExtPoint velocity;
		zExtPoint posDerivative;
		zExtPoint velDerivative;
		

		zExtParticle(zObjParticle* t);
		~zExtParticle();

		void updateAttributes();
	};

	struct ZSPACE_EXTERNAL zExtParticleArray
	{
		zObjParticleArray * pointer = nullptr; /**< A pointer to the array object */
		int arrayCount; /**< The number of items in the array */
		zExtParticleArray(zObjParticleArray* a);
		~zExtParticleArray();

		/**
		 * \brief Updates the attributes of the external object
		 */
		void updateAttributes();
		/**
		 * \brief get items from array
		 */
		void getItems(zExtParticle* items);
	};


	ZSPACE_EXTERNAL_C
	{
		ZSPACE_EXTERNAL void ext_particle_setVelocity(zExtParticle& particle);
		ZSPACE_EXTERNAL void ext_particle_setForce(zExtParticle& particle);
		ZSPACE_EXTERNAL void ext_particle_setPosition(zExtParticle& particle);
		ZSPACE_EXTERNAL void ext_particle_setMass(zExtParticle& particle);
	}
}




#if defined(ZSPACE_EXTERNAL_STATIC_LIBRARY)  || defined(ZSPACE_EXTERNAL_DYNAMIC_LIBRARY)
// All defined OK so do nothing
#else
#include<source/zCore/Geometry/zExtParticle.cpp>
#endif

#endif