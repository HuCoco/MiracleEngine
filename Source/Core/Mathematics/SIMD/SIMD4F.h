#pragma once
#include "SIMD4FPreCompileHeader.h"

#ifdef MENGINE_SCALAR
#include <Core/Mathematics/SIMD/SIMD4F_SCALAR.h>
#elif defined(MENGINE_SSE)
#include <Core/Mathematics/SIMD/SIMD4F_SSE.h>
#elif defined(MENGINE_GNU)
// TODO
#elif defined(MENGINE_NEON)
// TODO
#else
#error No implementation defined
#endif

#include "SIMD4F_COMMON.h"