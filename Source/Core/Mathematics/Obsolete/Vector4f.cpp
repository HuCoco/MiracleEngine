#include <Core/Mathematics/Vector4f.h>
#include <Core/Mathematics/MathUtils.h>


MEngine::Vector4f::Vector4f()
{
	for (_I32 i = 0; i < 4; ++i)
	{
		f[i] = 0.0f;
	}
}



MEngine::Vector4f::Vector4f(_F32 _x, _F32 _y, _F32 _z, _F32 _w)
{
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

#if defined (MATH_SSE)
MEngine::Vector4f::Vector4f(__m128 a_Result)
{
	x = a_Result.m128_f32[0];
	y = a_Result.m128_f32[1];
	z = a_Result.m128_f32[2];
	w = a_Result.m128_f32[3];
}
#endif

MEngine::Vector4f::~Vector4f()
{
}

_F32 MEngine::Vector4f::operator[](_I32 pos) const
{
	MeAssertM((pos >= 0 && pos < 4), "Vector4f Error : over index");
	return f[pos];
}

_F32& MEngine::Vector4f::operator[](_I32 pos)
{
	MeAssertM((pos >= 0 && pos < 4), "Vector4f Error : over index");
	return f[pos];
}

MEngine::Vector4f MEngine::Vector4f::operator-(void)
{
	return Vector4f(-x, -y, -z, -w);
}

MEngine::Vector4f MEngine::Vector4f::operator/(const Vector4f& Vector) const
{
#if defined (MATH_SSE)
	__m128 xmm0 = _mm_set_ps(w, z, y, x);
	__m128 xmm1 = _mm_set_ps(Vector.w, Vector.z, Vector.y, Vector.x);
	__m128 result = _mm_div_ps(xmm0, xmm1);
	return Vector4f(result);
#else
	return Vector4f(x / Vector.x, y / Vector.y, z / Vector.z, w / Vector.w);
#endif

}

MEngine::Vector4f MEngine::Vector4f::operator/(_F32 value) const
{
#if defined (MATH_SSE)
	__m128 Divisor = _mm_set_ps1(value);
	__m128 xmm0 = _mm_set_ps(w, z, y, x);
	__m128 result = _mm_div_ps(xmm0, Divisor);
	return Vector4f(result);
#else
	return Vector4f(x / value, y / value, z / value, w / value);
#endif

}

MEngine::Vector4f MEngine::Vector4f::operator*(const Vector4f& Vector) const
{
#if defined (MATH_SSE)
	__m128 xmm0 = _mm_set_ps(w, z, y, x);
	__m128 xmm1 = _mm_set_ps(Vector.w, Vector.z, Vector.y, Vector.x);
	__m128 result = _mm_mul_ps(xmm0, xmm1);
	return Vector4f(result);
#else
	return Vector4f(x * Vector.x, y * Vector.y, z * Vector.z, w * Vector.w);
#endif

}

MEngine::Vector4f MEngine::Vector4f::operator*(_F32 value) const
{
#if defined (MATH_SSE)
	__m128 multiplier = _mm_set_ps1(value);
	__m128 xmm0 = _mm_set_ps(w, z, y, x);
	__m128 result = _mm_mul_ps(xmm0, multiplier);
	return Vector4f(result);
#else
	return Vector4f(x * value, y * value, z * value, w * value);
#endif

}

MEngine::Vector4f MEngine::Vector4f::operator-(const Vector4f& Vector) const
{
#if defined (MATH_SSE)
	__m128 xmm0 = _mm_set_ps(w, z, y, x);
	__m128 xmm1 = _mm_set_ps(Vector.w, Vector.z, Vector.y, Vector.x);
	__m128 result = _mm_sub_ps(xmm0, xmm1);
	return Vector4f(result);
#else
	return Vector4f(x - Vector.x, y - Vector.y, z - Vector.z, w - Vector.z);
#endif

}

MEngine::Vector4f MEngine::Vector4f::operator+(const Vector4f& Vector) const
{
#if defined (MATH_SSE)
	__m128 xmm0 = _mm_set_ps(w, z, y, x);
	__m128 xmm1 = _mm_set_ps(Vector.w, Vector.z, Vector.y, Vector.x);
	__m128 result = _mm_add_ps(xmm0, xmm1);
	return Vector4f(result);
#else
	return Vector4f(x + Vector.x, y + Vector.y, z + Vector.z , w + Vector.w);
#endif

}

MEngine::Vector4f& MEngine::Vector4f::operator*=(const Vector4f& Vector)
{
#if defined (MATH_SSE)
	__m128 xmm0 = _mm_set_ps(w, z, y, x);
	__m128 xmm1 = _mm_set_ps(Vector.w, Vector.z, Vector.y, Vector.x);
	__m128 result = _mm_mul_ps(xmm0, xmm1);
	_mm_store_ps(f, result);
#else
	x *= Vector.x;
	y *= Vector.y;
	z *= Vector.z;
	w *= Vector.w;
#endif
	return (*this);
}

MEngine::Vector4f& MEngine::Vector4f::operator/=(const Vector4f& Vector)
{
#if defined (MATH_SSE)
	__m128 xmm0 = _mm_set_ps(w, z, y, x);
	__m128 xmm1 = _mm_set_ps(Vector.w, Vector.z, Vector.y, Vector.x);
	__m128 result = _mm_div_ps(xmm0, xmm1);
	_mm_store_ps(f, result);
#else
	x /= Vector.x;
	y /= Vector.y;
	z /= Vector.z;
	w /= Vector.w;
#endif
	return (*this);
}

MEngine::Vector4f& MEngine::Vector4f::operator-=(const Vector4f& Vector)
{
#if defined (MATH_SSE)
	__m128 xmm0 = _mm_set_ps(w, z, y, x);
	__m128 xmm1 = _mm_set_ps(Vector.w, Vector.z, Vector.y, Vector.x);
	__m128 result = _mm_sub_ps(xmm0, xmm1);
	_mm_store_ps(f, result);
#else
	x -= Vector.x;
	y -= Vector.y;
	z -= Vector.z;
	w -= Vector.w;
#endif
	return (*this);
}

MEngine::Vector4f& MEngine::Vector4f::operator+=(const Vector4f& Vector)
{
#if defined (MATH_SSE)
	__m128 xmm0 = _mm_set_ps(w, z, y, x);
	__m128 xmm1 = _mm_set_ps(Vector.w, Vector.z, Vector.y, Vector.x);
	__m128 result = _mm_add_ps(xmm0, xmm1);
	_mm_store_ps(f, result);
#else
	x += Vector.x;
	y += Vector.y;
	z += Vector.z;
	w += Vector.w;
#endif
	return (*this);
}

MEngine::Vector4f& MEngine::Vector4f::operator=(const Vector4f& Vector)
{
	x = Vector.x;
	y = Vector.y;
	z = Vector.z;
	w = Vector.w;
	return (*this);
}

_F32 MEngine::Vector4f::Length()
{
#if defined (MATH_SSE)
	__m128 xmm7 = _mm_set_ps(w, z, y, x);
	__m128 xmm0 = _mm_mul_ps(xmm7, xmm7);
	__m128 xmm1 = _mm_load_ps(xmm0.m128_f32);
	xmm1 = _mm_shuffle_ps(xmm1, xmm1, 0x4e);
	xmm0 = _mm_add_ps(xmm0, xmm1);
	xmm1 = _mm_load_ps(xmm0.m128_f32);
	xmm1 = _mm_shuffle_ps(xmm1, xmm1, 0x11);
	xmm0 = _mm_add_ps(xmm0, xmm1);
	xmm0 = _mm_sqrt_ps(xmm0);
	return xmm0.m128_f32[0];
#else
	_F32 length = 0.0f;
	length += x * x + y * y + z * z + w * w;
	return sqrtf(length);
#endif

}

void MEngine::Vector4f::Zero()
{
	for (_I32 i = 0; i < 4; ++i)
	{
		f[i] = 0.0f;
	}
}

void MEngine::Vector4f::Normalize()
{
#if defined (MATH_SSE)
	__m128 xmm7 = _mm_set_ps(w, z, y, x);
	__m128 xmm0 = _mm_mul_ps(xmm7, xmm7);
	__m128 xmm1 = _mm_load_ps(xmm0.m128_f32);
	xmm1 = _mm_shuffle_ps(xmm1, xmm1, 0x4e);
	xmm0 = _mm_add_ps(xmm0, xmm1);
	xmm1 = _mm_load_ps(xmm0.m128_f32);
	xmm1 = _mm_shuffle_ps(xmm1, xmm1, 0x11);
	xmm0 = _mm_add_ps(xmm0, xmm1);
	xmm0 = _mm_rsqrt_ps(xmm0);
	xmm0 = _mm_set_ps1(xmm0.m128_f32[0]);
	__m128 result = _mm_mul_ps(xmm0, xmm7);
	_mm_store_ps(f, result);
#else
	_F32 length = 0.0f;
	length += x * x + y * y + z * z + w * w;
	_F32 r = MathUtils::Rsqrt(length);
	*this = (*this) * r;
#endif
}
