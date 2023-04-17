// This file is part of zspace, a simple C++ collection of geometry data-structures & algorithms, 
// data analysis & visualization framework.
//
// Copyright (C) 2022 ZSPACE 
// 
// This Source Code Form is subject to the terms of the MIT License 
// If a copy of the MIT License was not distributed with this file, You can 
// obtain one at https://opensource.org/licenses/MIT.
//
// Author : Heba Eiz <heba.eiz@zaha-hadid.com>
//


#ifdef ZSPACE_EXTERNAL
#undef ZSPACE_EXTERNAL
#endif

#if defined(ZSPACE_EXTERNAL_DYNAMIC_LIBRARY)
#define ZSPACE_EXTERNAL  __declspec(dllexport)
#else
#define ZSPACE_EXTERNAL
#endif

#if defined(ZSPACE_EXTERNAL_STATIC_LIBRARY)  || defined(ZSPACE_EXTERNAL_DYNAMIC_LIBRARY)
#  define ZSPACE_EXTERNAL_INLINE
#else
#  define ZSPACE_EXTERNAL_INLINE inline
#endif

#define ZSPACE_EXTERNAL_C extern "C"