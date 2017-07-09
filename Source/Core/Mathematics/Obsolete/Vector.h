#pragma once

#include <Independent/Platform/PreCompileHeader.h>

struct FLOAT4
{
	float f[4];
};

//#define MATH_SSE

#if defined (MATH_SSE)

#include <xmmintrin.h>

#endif

