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

#ifndef ZSPACE_EXT_DATA_KMEANS_H
#define ZSPACE_EXT_DATA_KMEANS_H



#pragma once
#include "headers/base/zSpace_External.h"

#include <headers/zToolsets/data/zTsKMeans.h>


namespace zSpace
{
	ZSPACE_EXTERNAL_C{
		ZSPACE_EXTERNAL void ext_KMean_computeKmeansManualInput(zTsKMeans*& kmean, double* _data, int dataCount, int strideCount, int& numCluster, int& numIterations, double* initMeans, int* outClusterID);
		ZSPACE_EXTERNAL void ext_KMean_computeKmeans(zTsKMeans*& kmean, double* _data, int dataCount, int strideCount, int& numCluster, int& numIterations, int initMethod, int seed1, int seed2, int* outClusterID);
		ZSPACE_EXTERNAL void ext_KMean_getMeans(zTsKMeans*& kmean, double* outMeans);
		ZSPACE_EXTERNAL int ext_KMean_findOptimalK(double* _data, int dataCount, int strideCount, int& numIterations, int initMethod, int seed1, int seed2, int min, int max, int increment, int optimalCountMethod, int* outK, double* outScore);
		ZSPACE_EXTERNAL void ext_kmean_test_test(int test);
	}

}




#if defined(ZSPACE_EXTERNAL_DYNAMIC_LIBRARY)  || defined(ZSPACE_EXTERNAL_DYNAMIC_LIBRARY)
// All defined OK so do nothing
#else
#include<source/zToolsets/data/zExtKMeans.cpp>
#endif

#endif