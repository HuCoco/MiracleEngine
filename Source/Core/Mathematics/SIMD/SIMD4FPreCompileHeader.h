#pragma once
#include <memory.h>

#define SIMD_INLINE    static inline


#if defined(__SSE__) || (_M_IX86_FP > 0) || (_M_X64 > 0)
#define MENGINE_SSE
#elif defined(__ARM_NEON__) 
#define MENGINE_NEON
#elif defined(__GNUC__) && !defined(__arm__)
#define MENGINE_GNU
#else
#define MENGINE_SCALAR
#endif



#ifdef __cplusplus
#define SIMD_PARAM(t, p) const t& p
#else
#define SIMD_PARAM(t, p) t p
#endif

#define MENGINE_PI      3.14159265f
#define MENGINE_HALFPI  1.57079633f