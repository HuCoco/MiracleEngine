#pragma once
#include "SIMD4F.h"
#include <math.h>

typedef __declspec(align(16)) struct {
	SIMD4F x, y, z, w;
} SIMD4X4F;

SIMD_INLINE SIMD4X4F SIMD4X4F_CREATE(SIMD4F x, SIMD4F y, SIMD4F z, const SIMD4F& w) {
	SIMD4X4F s = { x, y, z, w };
	return s;
}

SIMD_INLINE void SIMD4X4F_IDENTITY(SIMD4X4F* m)
{
	*m = SIMD4X4F_CREATE(
		SIMD4F_CREATE(1.0f, 0.0f, 0.0f, 0.0f),
		SIMD4F_CREATE(0.0f, 1.0f, 0.0f, 0.0f),
		SIMD4F_CREATE(0.0f, 0.0f, 1.0f, 0.0f),
		SIMD4F_CREATE(0.0f, 0.0f, 0.0f, 1.0f));
}

SIMD_INLINE void SIMD4X4F_ULOAD(SIMD4X4F* m, const float *f)
{
	m->x = SIMD4F_ULOAD4(f + 0);
	m->y = SIMD4F_ULOAD4(f + 4);
	m->z = SIMD4F_ULOAD4(f + 8);
	m->w = SIMD4F_ULOAD4(f + 12);
}

#ifdef MENGINE_SCALAR
#include <Core/Mathematics/SIMD/SIMD4x4F_SCALAR.h>
#elif defined(MENGINE_SSE)
#include <Core/Mathematics/SIMD/SIMD4X4F_SSE.h>
#elif defined(MENGINE_GNU)
// TODO
#elif defined(MENGINE_NEON)
// TODO
#else
#error No implementation defined
#endif

SIMD_INLINE void SIMD4X4F_SUM(const SIMD4X4F* a, SIMD4F* out)
{
	SIMD4F t;
	t = SIMD4F_ADD(a->x, a->y);
	t = SIMD4F_ADD(t, a->z);
	t = SIMD4F_ADD(t, a->w);
	*out = t;
}

SIMD_INLINE void SIMD4X4F_MATRIX_VECTOR_MUL(const SIMD4X4F* a, const SIMD4F * b, SIMD4F* out) {

	const SIMD4F x = a->x;
	const SIMD4F y = a->y;
	const SIMD4F z = a->z;
	const SIMD4F w = a->w;
	const SIMD4F v = *b;
	const SIMD4F vx = SIMD4F_SET_X(v);
	const SIMD4F vy = SIMD4F_SET_Y(v);
	const SIMD4F vz = SIMD4F_SET_Z(v);
	const SIMD4F vw = SIMD4F_SET_W(v);


	*out = SIMD4F_ADD(
		SIMD4F_MUL(x, vx), SIMD4F_ADD(
			SIMD4F_MUL(y, vy), SIMD4F_ADD(
				SIMD4F_MUL(z, vz), SIMD4F_MUL(w, vw))));

}

SIMD_INLINE void SIMD4X4F_MATRIX_VECTOR3_MUL(const SIMD4X4F* a, const SIMD4F * b, SIMD4F* out) 
{
	*out = SIMD4F_ADD(
		SIMD4F_MUL(a->x, SIMD4F_SET_X(*b)), SIMD4F_ADD(
			SIMD4F_MUL(a->y, SIMD4F_SET_Y(*b)), SIMD4F_MUL(a->z, SIMD4F_SET_Z(*b))));
}

SIMD_INLINE void SIMD4X4F_MATRIX_POINT3_MUL(const SIMD4X4F* a, const SIMD4F * b, SIMD4F* out)
{
	*out = SIMD4F_ADD(
		SIMD4F_MUL(a->x, SIMD4F_SET_X(*b)), SIMD4F_ADD(
			SIMD4F_MUL(a->y, SIMD4F_SET_Y(*b)), SIMD4F_ADD(
				SIMD4F_MUL(a->z, SIMD4F_SET_Z(*b)), a->w)));
}

SIMD_INLINE void SIMD4X4F_INV_ORTHO_MATRIX_POINT3_MUL(const SIMD4X4F* a, const SIMD4F * b, SIMD4F* out) 
{
	SIMD4F translation = SIMD4F_SUB(*b, a->w);

	SIMD4X4F transpose = *a;

	transpose.w = SIMD4F_CREATE(0, 0, 0, 0);
	SIMD4X4F_TRANSPOSE_INPLACE(&transpose);

	SIMD4X4F_MATRIX_POINT3_MUL(&transpose, &translation, out);
}


SIMD_INLINE void SIMD4X4F_INV_ORTHO_MATRIX_VECTOR3_MUL(const SIMD4X4F* a, const SIMD4F * b, SIMD4F* out)
{
	SIMD4F translation = *b;

	SIMD4X4F transpose = *a;

	transpose.w = SIMD4F_CREATE(0, 0, 0, 0);
	SIMD4X4F_TRANSPOSE_INPLACE(&transpose);

	SIMD4X4F_MATRIX_VECTOR3_MUL(&transpose, &translation, out);
}

SIMD_INLINE void SIMD4X4F_MATRIX_MUL(const SIMD4X4F* a, const SIMD4X4F* b, SIMD4X4F* out)
{

	SIMD4X4F_MATRIX_VECTOR_MUL(a, &b->x, &out->x);
	SIMD4X4F_MATRIX_VECTOR_MUL(a, &b->y, &out->y);
	SIMD4X4F_MATRIX_VECTOR_MUL(a, &b->z, &out->z);
	SIMD4X4F_MATRIX_VECTOR_MUL(a, &b->w, &out->w);
}

SIMD_INLINE void SIMD4X4F_PERSPECTIVE(SIMD4X4F *m, float fovy_radians, float aspect, float znear, float zfar) 
{

	float deltaz = zfar - znear;
	float cotangent = tanf(MENGINE_HALFPI - fovy_radians * 0.5f);

	float a = cotangent / aspect;
	float b = cotangent;
	float c = -(zfar + znear) / deltaz;
	float d = -2 * znear * zfar / deltaz;

	m->x = SIMD4F_CREATE(a, 0, 0, 0);
	m->y = SIMD4F_CREATE(0, b, 0, 0);
	m->z = SIMD4F_CREATE(0, 0, c, -1);
	m->w = SIMD4F_CREATE(0, 0, d, 0);

}

SIMD_INLINE void SIMD4X4F_ORTHO(SIMD4X4F *m, float left, float right, float bottom, float top, float znear, float zfar) 
{

	float deltax = right - left;
	float deltay = top - bottom;
	float deltaz = zfar - znear;

	float a = 2.0f / deltax;
	float b = -(right + left) / deltax;
	float c = 2.0f / deltay;
	float d = -(top + bottom) / deltay;
	float e = -2.0f / deltaz;
	float f = -(zfar + znear) / deltaz;

	m->x = SIMD4F_CREATE(a, 0, 0, 0);
	m->y = SIMD4F_CREATE(0, c, 0, 0);
	m->z = SIMD4F_CREATE(0, 0, e, 0);
	m->w = SIMD4F_CREATE(b, d, f, 1);

}

SIMD_INLINE void SIMD4X4F_LOOKAT(SIMD4X4F *m, SIMD4F eye, SIMD4F center, SIMD4F up)
{

	SIMD4F zaxis = SIMD4F_NORMALIZE3(SIMD4F_SUB(center, eye));
	SIMD4F xaxis = SIMD4F_NORMALIZE3(SIMD4F_CROSS3(zaxis, up));
	SIMD4F yaxis = SIMD4F_CROSS3(xaxis, zaxis);

	zaxis = SIMD4F_SUB(SIMD4F_ZERO(), zaxis);

	float x = -SIMD4F_DOT3_SCALAR(xaxis, eye);
	float y = -SIMD4F_DOT3_SCALAR(yaxis, eye);
	float z = -SIMD4F_DOT3_SCALAR(zaxis, eye);

	m->x = xaxis;
	m->y = yaxis;
	m->z = zaxis;

	m->w = SIMD4F_CREATE(0, 0, 0, 1);
	SIMD4X4F_TRANSPOSE_INPLACE(m);
	m->w = SIMD4F_CREATE(x, y, z, 1);

}

SIMD_INLINE void SIMD4X4F_TRANSLATION(SIMD4X4F* m, float x, float y, float z) {
	*m = SIMD4X4F_CREATE(
		SIMD4F_CREATE(1.0f, 0.0f, 0.0f, 0.0f),
		SIMD4F_CREATE(0.0f, 1.0f, 0.0f, 0.0f),
		SIMD4F_CREATE(0.0f, 0.0f, 1.0f, 0.0f),
		SIMD4F_CREATE(x, y, z, 1.0f));
}

SIMD_INLINE void SIMD4X4F_AXIS_ROTATION(SIMD4X4F* m, float radians, SIMD4F axis) {

	radians = -radians;

	axis = SIMD4F_NORMALIZE3(axis);

	const float sine = sinf(radians);
	const float cosine = cosf(radians);

	const float x = SIMD4F_GET_X(axis);
	const float y = SIMD4F_GET_Y(axis);
	const float z = SIMD4F_GET_Z(axis);

	const float ab = x * y * (1 - cosine);
	const float bc = y * z * (1 - cosine);
	const float ca = z * x * (1 - cosine);

	const float tx = x * x;
	const float ty = y * y;
	const float tz = z * z;

	const SIMD4F i = SIMD4F_CREATE(tx + cosine * (1 - tx), ab - z * sine, ca + y * sine, 0);
	const SIMD4F j = SIMD4F_CREATE(ab + z * sine, ty + cosine * (1 - ty), bc - x * sine, 0);
	const SIMD4F k = SIMD4F_CREATE(ca - y * sine, bc + x * sine, tz + cosine * (1 - tz), 0);

	*m = SIMD4X4F_CREATE(i, j, k, SIMD4F_CREATE(0, 0, 0, 1));

}

SIMD_INLINE void SIMD4X4F_ADD(const SIMD4X4F* a, const SIMD4X4F* b, SIMD4X4F* out) {

	out->x = SIMD4F_ADD(a->x, b->x);
	out->y = SIMD4F_ADD(a->y, b->y);
	out->z = SIMD4F_ADD(a->z, b->z);
	out->w = SIMD4F_ADD(a->w, b->w);

}

SIMD_INLINE void SIMD4X4F_SUB(const SIMD4X4F* a, const SIMD4X4F* b, SIMD4X4F* out) {

	out->x = SIMD4F_SUB(a->x, b->x);
	out->y = SIMD4F_SUB(a->y, b->y);
	out->z = SIMD4F_SUB(a->z, b->z);
	out->w = SIMD4F_SUB(a->w, b->w);

}

SIMD_INLINE void SIMD4X4F_MUL(const SIMD4X4F* a, const SIMD4X4F* b, SIMD4X4F* out) {

	out->x = SIMD4F_MUL(a->x, b->x);
	out->y = SIMD4F_MUL(a->y, b->y);
	out->z = SIMD4F_MUL(a->z, b->z);
	out->w = SIMD4F_MUL(a->w, b->w);

}

SIMD_INLINE void SIMD4X4F_DIV(SIMD4X4F* a, SIMD4X4F* b, SIMD4X4F* out) {

	out->x = SIMD4F_DIV(a->x, b->x);
	out->y = SIMD4F_DIV(a->y, b->y);
	out->z = SIMD4F_DIV(a->z, b->z);
	out->w = SIMD4F_DIV(a->w, b->w);

}

SIMD_INLINE SIMD4F SIMD4X4F_INVERSE(const SIMD4X4F* a, SIMD4X4F* out) {

	const SIMD4F c0 = a->x;
	const SIMD4F c1 = a->y;
	const SIMD4F c2 = a->z;
	const SIMD4F c3 = a->w;

	const SIMD4F c0_wxyz = SIMD4F_SHUFFLE_WXYZ(c0);
	const SIMD4F c0_zwxy = SIMD4F_SHUFFLE_ZWXY(c0);
	const SIMD4F c0_yzwx = SIMD4F_SHUFFLE_YZWX(c0);

	const SIMD4F c1_wxyz = SIMD4F_SHUFFLE_WXYZ(c1);
	const SIMD4F c1_zwxy = SIMD4F_SHUFFLE_ZWXY(c1);
	const SIMD4F c1_yzwx = SIMD4F_SHUFFLE_YZWX(c1);

	const SIMD4F c2_wxyz = SIMD4F_SHUFFLE_WXYZ(c2);
	const SIMD4F c2_zwxy = SIMD4F_SHUFFLE_ZWXY(c2);
	const SIMD4F c2_yzwx = SIMD4F_SHUFFLE_YZWX(c2);

	const SIMD4F c3_wxyz = SIMD4F_SHUFFLE_WXYZ(c3);
	const SIMD4F c3_zwxy = SIMD4F_SHUFFLE_ZWXY(c3);
	const SIMD4F c3_yzwx = SIMD4F_SHUFFLE_YZWX(c3);

	const SIMD4F c0_wxyz_x_c1 = SIMD4F_MUL(c0_wxyz, c1);
	const SIMD4F c0_wxyz_x_c1_yzwx = SIMD4F_MUL(c0_wxyz, c1_yzwx);
	const SIMD4F c0_wxyz_x_c1_zwxy = SIMD4F_MUL(c0_wxyz, c1_zwxy);

	const SIMD4F c2_wxyz_x_c3 = SIMD4F_MUL(c2_wxyz, c3);
	const SIMD4F c2_wxyz_x_c3_yzwx = SIMD4F_MUL(c2_wxyz, c3_yzwx);
	const SIMD4F c2_wxyz_x_c3_zwxy = SIMD4F_MUL(c2_wxyz, c3_zwxy);

	const SIMD4F ar1 = SIMD4F_SUB(SIMD4F_SHUFFLE_WXYZ(c2_wxyz_x_c3_zwxy), SIMD4F_SHUFFLE_ZWXY(c2_wxyz_x_c3));
	const SIMD4F ar2 = SIMD4F_SUB(SIMD4F_SHUFFLE_ZWXY(c2_wxyz_x_c3_yzwx), c2_wxyz_x_c3_yzwx);
	const SIMD4F ar3 = SIMD4F_SUB(c2_wxyz_x_c3_zwxy, SIMD4F_SHUFFLE_WXYZ(c2_wxyz_x_c3));

	const SIMD4F br1 = SIMD4F_SUB(SIMD4F_SHUFFLE_WXYZ(c0_wxyz_x_c1_zwxy), SIMD4F_SHUFFLE_ZWXY(c0_wxyz_x_c1));
	const SIMD4F br2 = SIMD4F_SUB(SIMD4F_SHUFFLE_ZWXY(c0_wxyz_x_c1_yzwx), c0_wxyz_x_c1_yzwx);
	const SIMD4F br3 = SIMD4F_SUB(c0_wxyz_x_c1_zwxy, SIMD4F_SHUFFLE_WXYZ(c0_wxyz_x_c1));


	const SIMD4F c0_sum = SIMD4F_MADD(c0_yzwx, ar3,
		SIMD4F_MADD(c0_zwxy, ar2,
			SIMD4F_MUL(c0_wxyz, ar1)));

	const SIMD4F c1_sum = SIMD4F_MADD(c1_wxyz, ar1,
		SIMD4F_MADD(c1_zwxy, ar2,
			SIMD4F_MUL(c1_yzwx, ar3)));

	const SIMD4F c2_sum = SIMD4F_MADD(c2_yzwx, br3,
		SIMD4F_MADD(c2_zwxy, br2,
			SIMD4F_MUL(c2_wxyz, br1)));

	const SIMD4F c3_sum = SIMD4F_MADD(c3_yzwx, br3,
		SIMD4F_MADD(c3_zwxy, br2,
			SIMD4F_MUL(c3_wxyz, br1)));


	const SIMD4F d0 = SIMD4F_MUL(c1_sum, c0);
	const SIMD4F d1 = SIMD4F_ADD(d0, SIMD4F_MERGE_HIGH(d0, d0));
	const SIMD4F det = SIMD4F_SUB(d1, SIMD4F_SET_Y(d1));

	const SIMD4F invdet = SIMD4F_SET_X(SIMD4F_DIV(SIMD4F_SET(1.0f), det));

	const SIMD4F o0 = SIMD4F_MUL(SIMD4F_FLIP_SIGN_0101(c1_sum), invdet);
	const SIMD4F o1 = SIMD4F_MUL(SIMD4F_FLIP_SIGN_1010(c0_sum), invdet);
	const SIMD4F o2 = SIMD4F_MUL(SIMD4F_FLIP_SIGN_0101(c3_sum), invdet);
	const SIMD4F o3 = SIMD4F_MUL(SIMD4F_FLIP_SIGN_1010(c2_sum), invdet);

	const SIMD4X4F mt = SIMD4X4F_CREATE(o0, o1, o2, o3);

	SIMD4X4F_TRANSPOSE(&mt, out);

	return det;
}

