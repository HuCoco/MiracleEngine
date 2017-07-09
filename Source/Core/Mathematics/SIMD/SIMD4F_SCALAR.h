#pragma once
#include <math.h>
#include <string.h>  // memcpy


typedef struct
{
	float x;
	float y;
	float z;
	float w;
} SIMD4F;

SIMD_INLINE SIMD4F SIMD4F_CREATE(float x, float y, float z, float w) 
{
	SIMD4F s = { x, y, z, w };
	return s;
}

SIMD_INLINE SIMD4F SIMD4F_ZERO()
{ 
	return SIMD4F_CREATE(0.0f, 0.0f, 0.0f, 0.0f); 
}

SIMD_INLINE SIMD4F SIMD4F_ULOAD4(const float *arr)
{
	SIMD4F s = { arr[0], arr[1], arr[2], arr[3] };
	return s;
}

SIMD_INLINE SIMD4F SIMD4F_ULOAD3(const float *arr)
{
	SIMD4F s = { arr[0], arr[1], arr[2], 0 };
	return s;
}

SIMD_INLINE SIMD4F SIMD4F_ULOAD2(const float *arr) 
{
	SIMD4F s = { arr[0], arr[1], 0, 0 };
	return s;
}


SIMD_INLINE void SIMD4F_USTORE4(const SIMD4F val, float *arr) 
{
	memcpy(arr, &val, sizeof(float) * 4);
}

SIMD_INLINE void SIMD4F_USTORE3(const SIMD4F val, float *arr) 
{
	memcpy(arr, &val, sizeof(float) * 3);
}

SIMD_INLINE void SIMD4F_USTORE2(const SIMD4F val, float *arr) 
{
	memcpy(arr, &val, sizeof(float) * 2);
}



// utilities
SIMD_INLINE SIMD4F SIMD4F_SET(float v) 
{
	SIMD4F s = { v, v, v, v };
	return s;
}

SIMD_INLINE SIMD4F SIMD4F_SET_X(SIMD4F v)
{
	SIMD4F s = { v.x, v.x, v.x, v.x };
	return s;
}

SIMD_INLINE SIMD4F SIMD4F_SET_Y(SIMD4F v)
{
	SIMD4F s = { v.y, v.y, v.y, v.y };
	return s;
}

SIMD_INLINE SIMD4F SIMD4F_SET_Z(SIMD4F v)
{
	SIMD4F s = { v.z, v.z, v.z, v.z };
	return s;
}

SIMD_INLINE SIMD4F SIMD4F_SET_W(SIMD4F v) 
{
	SIMD4F s = { v.w, v.w, v.w, v.w };
	return s;
}

SIMD_INLINE SIMD4F SIMD4F_RECIPROCAL(SIMD4F v) 
{
	SIMD4F s = { 1.0f / v.x, 1.0f / v.y, 1.0f / v.z, 1.0f / v.w };
	return s;
}

SIMD_INLINE SIMD4F SIMD4F_SQRT(SIMD4F v)
{
	SIMD4F s = { sqrtf(v.x), sqrtf(v.y), sqrtf(v.z), sqrtf(v.w) };
	return s;
}

SIMD_INLINE SIMD4F SIMD4F_RSQRT(SIMD4F v)
{
	SIMD4F s = { 1.0f / sqrtf(v.x), 1.0f / sqrtf(v.y), 1.0f / sqrtf(v.z), 1.0f / sqrtf(v.w) };
	return s;
}

SIMD_INLINE SIMD4F SIMD4F_ADD(SIMD4F lhs, SIMD4F rhs) 
{
	SIMD4F ret = { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w };
	return ret;
}

SIMD_INLINE SIMD4F SIMD4F_SUB(SIMD4F lhs, SIMD4F rhs)
{
	SIMD4F ret = { lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w };
	return ret;
}

SIMD_INLINE SIMD4F SIMD4F_MUL(SIMD4F lhs, SIMD4F rhs)
{
	SIMD4F ret = { lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w };
	return ret;
}

SIMD_INLINE SIMD4F SIMD4F_DIV(SIMD4F lhs, SIMD4F rhs) 
{
	SIMD4F ret = { lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z, lhs.w / rhs.w };
	return ret;
}

SIMD_INLINE SIMD4F SIMD4F_MADD(SIMD4F m1, SIMD4F m2, SIMD4F a) 
{
	return SIMD4F_ADD(SIMD4F_MUL(m1, m2), a);
}

SIMD_INLINE float SIMD4F_DOT3_SCALAR(SIMD4F lhs, SIMD4F rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

SIMD_INLINE SIMD4F SIMD4F_DOT3(SIMD4F lhs, SIMD4F rhs) {
	return SIMD4F_SET(SIMD4F_DOT3_SCALAR(lhs, rhs));
}

SIMD_INLINE SIMD4F SIMD4F_CROSS3(SIMD4F lhs, SIMD4F rhs) 
{
	return SIMD4F_CREATE(
		lhs.y * rhs.z - lhs.z * rhs.y,
		lhs.z * rhs.x - lhs.x * rhs.z,
		lhs.x * rhs.y - lhs.y * rhs.x, 0);
}


SIMD_INLINE float SIMD4F_GET_X(SIMD4F s) 
{ 
	return s.x;
}

SIMD_INLINE float SIMD4F_GET_Y(SIMD4F s) 
{ 
	return s.y;
}

SIMD_INLINE float SIMD4F_GET_Z(SIMD4F s) 
{ 
	return s.z; 
}

SIMD_INLINE float SIMD4F_GET_W(SIMD4F s)
{ 
	return s.w;
}


SIMD_INLINE SIMD4F SIMD4F_SHUFFLE_WXYZ(SIMD4F s) 
{ 
	return SIMD4F_CREATE(s.w, s.x, s.y, s.z); 
}

SIMD_INLINE SIMD4F SIMD4F_SHUFFLE_ZWXY(SIMD4F s)
{ 
	return SIMD4F_CREATE(s.z, s.w, s.x, s.y); 
}

SIMD_INLINE SIMD4F SIMD4F_SHUFFLE_YZWX(SIMD4F s) 
{ 
	return SIMD4F_CREATE(s.y, s.z, s.w, s.x); 
}


SIMD_INLINE SIMD4F SIMD4F_ZERO_W(SIMD4F s) 
{
	return SIMD4F_CREATE(s.x, s.y, s.z, 0.0f);
}

SIMD_INLINE SIMD4F SIMD4F_ZERO_ZW(SIMD4F s)
{
	return SIMD4F_CREATE(s.x, s.y, 0.0f, 0.0f);
}


SIMD_INLINE SIMD4F SIMD4F_MERGE_HIGH(SIMD4F abcd, SIMD4F xyzw)
{
	return SIMD4F_CREATE(abcd.z, abcd.w, xyzw.z, xyzw.w);
}

SIMD_INLINE SIMD4F SIMD4F_FLIP_SIGN_0101(SIMD4F s) 
{
	return SIMD4F_CREATE(s.x, -s.y, s.z, -s.w);
}

SIMD_INLINE SIMD4F SIMD4F_FLIP_SIGN_1010(SIMD4F s) 
{
	return SIMD4F_CREATE(-s.x, s.y, -s.z, s.w);
}

SIMD_INLINE SIMD4F SIMD4F_MIN(SIMD4F a, SIMD4F b) 
{
	return SIMD4F_CREATE(
		a.x < b.x ? a.x : b.x,
		a.y < b.y ? a.y : b.y,
		a.z < b.z ? a.z : b.z,
		a.w < b.w ? a.w : b.w);
}

SIMD_INLINE SIMD4F SIMD4F_MAX(SIMD4F a, SIMD4F b) 
{
	return SIMD4F_CREATE(
		a.x > b.x ? a.x : b.x,
		a.y > b.y ? a.y : b.y,
		a.z > b.z ? a.z : b.z,
		a.w > b.w ? a.w : b.w);
}
