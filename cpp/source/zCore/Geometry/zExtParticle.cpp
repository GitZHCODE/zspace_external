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


#include "headers/zCore/Geometry/zExtParticle.h"


namespace zSpace
{
	ZSPACE_EXTERNAL_INLINE zExtParticle::~zExtParticle()
	{
		delete pointer;
		pointer = nullptr;
	}
	ZSPACE_EXTERNAL_INLINE void zExtParticle::updateAttributes()
	{
		/*mass = pointer->particle.m;
		fixed = pointer->particle.fixed;

		force.pointer = &pointer->particle.f;
		force.updateAttributes();

		position.pointer = pointer->particle.s.p;
		position.updateAttributes();

		velocity.pointer = &pointer->particle.s.v;
		velocity.updateAttributes();

		posDerivative.pointer = &pointer->particle.derivative.dP;
		posDerivative.updateAttributes();

		velDerivative.pointer = &pointer->particle.derivative.dV;
		velDerivative.updateAttributes();*/
	}

	ZSPACE_EXTERNAL_INLINE zExtParticleArray::~zExtParticleArray()
	{
		delete pointer;
		pointer = nullptr;
	}

}