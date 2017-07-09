#pragma once

#if defined(_M_IX86_FP)
#if _M_IX86_FP >=2
#define MENGINE_USE_SSE4_1
#endif
#elif defined(__SSE4_1__)
#define MENGINE_USE_SSE4_1
#endif

#include <xmmintrin.h>
#if defined(MENGINE_USE_SSE4_1)
#include <smmintrin.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef __m128 SIMD4F;

typedef union {
	SIMD4F s;
	float f[4];
	unsigned int ui[4];
} SIMD_4F_UNION;

// creating
SIMD_INLINE SIMD4F SIMD4F_CREATE(float x, float y, float z, float w)
{
	return _mm_setr_ps(x, y, z, w);
}

SIMD_INLINE SIMD4F SIMD4F_ZERO()
{
	return _mm_setzero_ps();
}

SIMD_INLINE SIMD4F SIMD4F_ULOAD4(const float* arr)
{
	return _mm_loadu_ps(arr);
}

SIMD_INLINE SIMD4F SIMD4F_ULOAD3(const float* arr)
{
	return SIMD4F_CREATE(arr[0], arr[1], arr[2], 0.0f);
}

SIMD_INLINE SIMD4F SIMD4F_ULOAD2(const float* arr)
{
	return SIMD4F_CREATE(arr[0], arr[1], 0.0f, 0.0f);
}

SIMD_INLINE void SIMD4F_USTORE4(const SIMD4F val, float* arr)
{
	_mm_storeu_ps(arr, val);
}

SIMD_INLINE void SIMD4F_USTORE3(const SIMD4F val, float* arr)
{
	memcpy(arr, &val, sizeof(float) * 3);
}

SIMD_INLINE void SIMD4F_USTORE2(const SIMD4F val, float* arr)
{
	memcpy(arr, &val, sizeof(float) * 2);
}


// utilites
SIMD_INLINE SIMD4F SIMD4F_SET(float v) 
{
	return  _mm_set1_ps(v);
}

SIMD_INLINE SIMD4F SIMD4F_SET_X(SIMD4F v)
{
	return _mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 0, 0, 0));
}

SIMD_INLINE SIMD4F SIMD4F_SET_Y(SIMD4F v)
{
	return _mm_shuffle_ps(v, v, _MM_SHUFFLE(1, 1, 1, 1));
}

SIMD_INLINE SIMD4F SIMD4F_SET_Z(SIMD4F v)
{
	return _mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 2, 2, 2));
}

SIMD_INLINE SIMD4F SIMD4F_SET_W(SIMD4F v)
{
	return _mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 3, 3, 3));
}

// arithmetic

SIMD_INLINE SIMD4F SIMD4F_ADD(SIMD4F lhs, SIMD4F rhs) 
{
	return _mm_add_ps(lhs, rhs);
}

SIMD_INLINE SIMD4F SIMD4F_SUB(SIMD4F lhs, SIMD4F rhs) 
{
	return _mm_sub_ps(lhs, rhs);
}

SIMD_INLINE SIMD4F SIMD4F_MUL(SIMD4F lhs, SIMD4F rhs) 
{
	return _mm_mul_ps(lhs, rhs);
}

SIMD_INLINE SIMD4F SIMD4F_DIV(SIMD4F lhs, SIMD4F rhs) 
{
	return _mm_div_ps(lhs, rhs);
}

SIMD_INLINE SIMD4F SIMD4F_MADD(SIMD4F m1, SIMD4F m2, SIMD4F a) 
{
	return SIMD4F_ADD(SIMD4F_MUL(m1, m2), a);
}

SIMD_INLINE SIMD4F SIMD4F_RECIPROCAL(SIMD4F v) 
{
	SIMD4F s = _mm_rcp_ps(v);
	const SIMD4F two = SIMD4F_CREATE(2.0f, 2.0f, 2.0f, 2.0f);
	return SIMD4F_MUL(s, SIMD4F_SUB(two, SIMD4F_MUL(v, s)));
}

SIMD_INLINE SIMD4F SIMD4F_SQRT(SIMD4F v)
{
	return _mm_sqrt_ps(v);
}

SIMD_INLINE SIMD4F SIMD4F_RSQRT(SIMD4F v)
{
	SIMD4F s = _mm_rsqrt_ps(v);
	const SIMD4F half = SIMD4F_SET(0.5f);
	const SIMD4F three = SIMD4F_SET(3.0f);
	return SIMD4F_MUL(SIMD4F_MUL(s, half), SIMD4F_SUB(three, SIMD4F_MUL(s, SIMD4F_MUL(v, s))));
}

SIMD_INLINE float SIMD4F_GET_X(SIMD4F s) 
{
	SIMD_4F_UNION u = { s };
	return u.f[0]; 
}

SIMD_INLINE float SIMD4F_GET_Y(SIMD4F s)
{
	SIMD_4F_UNION u = { s };
	return u.f[1];
}

SIMD_INLINE float SIMD4F_GET_Z(SIMD4F s)
{
	SIMD_4F_UNION u = { s };
	return u.f[2];
}

SIMD_INLINE float SIMD4F_GET_W(SIMD4F s)
{
	SIMD_4F_UNION u = { s };
	return u.f[3];
}

SIMD_INLINE SIMD4F SIMD4F_DOT3(SIMD4F lhs, SIMD4F rhs) {
#if defined(MENGINE_USE_SSE4_1)
	return _mm_dp_ps(lhs, rhs, 0x7f);
#else
	__declspec(align(16)) const unsigned int mask_array[] = { 0xffffffff, 0xffffffff, 0xffffffff, 0 };
	const SIMD4F mask = _mm_load_ps((const float*)mask_array);
	const SIMD4F m = _mm_mul_ps(lhs, rhs);
	const SIMD4F s0 = _mm_and_ps(m, mask);
	const SIMD4F s1 = _mm_add_ps(s0, _mm_movehl_ps(s0, s0));
	const SIMD4F s2 = _mm_add_ss(s1, _mm_shuffle_ps(s1, s1, 1));
	return _mm_shuffle_ps(s2, s2, 0);
#endif
}

SIMD_INLINE float SIMD4F_DOT3_SCALAR(SIMD4F lhs, SIMD4F rhs) {
	return SIMD4F_GET_X(SIMD4F_DOT3(lhs, rhs));
}

SIMD_INLINE SIMD4F SIMD4F_CROSS3(SIMD4F lhs, SIMD4F rhs) 
{
	const SIMD4F lyzx = _mm_shuffle_ps(lhs, lhs, _MM_SHUFFLE(3, 0, 2, 1));
	const SIMD4F lzxy = _mm_shuffle_ps(lhs, lhs, _MM_SHUFFLE(3, 1, 0, 2));

	const SIMD4F ryzx = _mm_shuffle_ps(rhs, rhs, _MM_SHUFFLE(3, 0, 2, 1));
	const SIMD4F rzxy = _mm_shuffle_ps(rhs, rhs, _MM_SHUFFLE(3, 1, 0, 2));

	return _mm_sub_ps(_mm_mul_ps(lyzx, rzxy), _mm_mul_ps(lzxy, ryzx));
}


SIMD_INLINE SIMD4F SIMD4F_SHUFFLE_WXYZ(SIMD4F s) 
{ 
	return _mm_shuffle_ps(s, s, _MM_SHUFFLE(2, 1, 0, 3)); 
}

SIMD_INLINE SIMD4F SIMD4F_SHUFFLE_ZWXY(SIMD4F s) 
{ 
	return _mm_shuffle_ps(s, s, _MM_SHUFFLE(1, 0, 3, 2)); 
}

SIMD_INLINE SIMD4F SIMD4F_SHUFFLE_YZWX(SIMD4F s) 
{ 
	return _mm_shuffle_ps(s, s, _MM_SHUFFLE(0, 3, 2, 1)); 
}

SIMD_INLINE SIMD4F SIMD4F_MERGE_HIGH(SIMD4F xyzw, SIMD4F abcd)
{
	return _mm_movehl_ps(abcd, xyzw);
}

typedef __declspec(align(16)) union {
	unsigned int ui[4];
	float f[4];
} SIMD4F_UIF;

SIMD_INLINE SIMD4F SIMD4F_FLIP_SIGN_0101(SIMD4F s) 
{
	const SIMD4F_UIF upnpn = { { 0x00000000, 0x80000000, 0x00000000, 0x80000000 } };
	return _mm_xor_ps(s, _mm_load_ps(upnpn.f));
}

SIMD_INLINE SIMD4F SIMD4F_FLIP_SIGN_1010(SIMD4F s) 
{
	const SIMD4F_UIF unpnp = { { 0x80000000, 0x00000000, 0x80000000, 0x00000000 } };
	return _mm_xor_ps(s, _mm_load_ps(unpnp.f));
}

SIMD_INLINE SIMD4F SIMD4F_MIN(SIMD4F a, SIMD4F b) 
{
	return _mm_min_ps(a, b);
}

SIMD_INLINE SIMD4F SIMD4F_MAX(SIMD4F a, SIMD4F b) 
{
	return _mm_max_ps(a, b);
}
#ifdef __cplusplus
}
#endif