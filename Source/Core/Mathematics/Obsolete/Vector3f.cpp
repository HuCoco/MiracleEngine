#include <Core/Mathematics/Vector3f.h>
#include <Core/Mathematics/MathUtils.h>

NAMESPACE_MENGINE_BEGIN

Vector3f::Vector3f()
	: x(0.0f)
	, y(0.0f)
	, z(0.0f)
{

}



#if defined (MATH_SSE)
Vector3f::Vector3f(__m128 _vec)
	: x(_vec.m128_f32[0])
	, y(_vec.m128_f32[1])
	, z(_vec.m128_f32[2])
{

}
#endif

Vector3f::Vector3f(_F32 _x, _F32 _y, _F32 _z)
	: x(_x)
	, y(_y)
	, z(_z)
{

}

Vector3f::~Vector3f()
{
}

_F32 Vector3f::operator[](_I32 pos) const
{
	assert( (pos >= 0 && pos < 3) && "Vector3f Error : over index");
	return f[pos];
}

_F32& Vector3f::operator[](_I32 pos)
{
	assert((pos >= 0 && pos < 3) && "Vector3f Error : over index");
	return f[pos];
}

Vector3f Vector3f::operator-(void)
{
	return Vector3f(-x, -y, -z);
}

Vector3f Vector3f::operator/(const Vector3f& Vector) const
{
#if defined (MATH_SSE)
	__m128 xmm0 = _mm_set_ps(0.0f, z, y, x);
	__m128 xmm1 = _mm_set_ps(0.0f, Vector.z, Vector.y, Vector.x);
	__m128 result = _mm_div_ps(xmm0, xmm1);
	return Vector3f(result);
#else
	return Vector3f(x / Vector.x, y / Vector.y, z / Vector.z);
#endif

}

Vector3f Vector3f::operator/(_F32 value) const
{
#if defined (MATH_SSE)
	__m128 xmm0 = _mm_set_ps(0.0f, z, y, x);
	__m128 Divisor = _mm_set_ps1(value);
	__m128 result = _mm_div_ps(xmm0, Divisor);
	return Vector3f(result);
#else
	return Vector3f(x / value, y / value, z / value);
#endif

}

Vector3f Vector3f::operator*(const Vector3f& Vector) const
{
#if defined (MATH_SSE)
	__m128 xmm0 = _mm_set_ps(0.0f, z, y, x);
	__m128 xmm1 = _mm_set_ps(0.0f, Vector.z, Vector.y, Vector.x);
	__m128 result = _mm_mul_ps(xmm0, xmm1);
	return Vector3f(result);
#else
	return Vector3f(x * Vector.x, y * Vector.y, z * Vector.z);
#endif

}

Vector3f Vector3f::operator*(_F32 value) const
{
#if defined (MATH_SSE)
	__m128 xmm0 = _mm_set_ps(0.0f, z, y, x);
	__m128 multiplier = _mm_set_ps1(value);
	__m128 result = _mm_mul_ps(xmm0, multiplier);
	return Vector3f(result);
#else
	return Vector3f(x * value, y * value, z * value);
#endif

}

Vector3f Vector3f::operator-(const Vector3f& Vector) const
{
#if defined (MATH_SSE)
	__m128 xmm0 = _mm_set_ps(0.0f, z, y, x);
	__m128 xmm1 = _mm_set_ps(0.0f, Vector.z, Vector.y, Vector.x);
	__m128 result = _mm_sub_ps(xmm0, xmm1);
	return Vector3f(result);
#else
	return Vector3f(x - Vector.x, y - Vector.y, z - Vector.z);
#endif

}

Vector3f Vector3f::operator+(const Vector3f& Vector) const
{
#if defined (MATH_SSE)
	__m128 xmm0 = _mm_set_ps(0.0f, z, y, x);
	__m128 xmm1 = _mm_set_ps(0.0f, Vector.z, Vector.y, Vector.x);
	__m128 result = _mm_add_ps(xmm0, xmm1);
	return Vector3f(result);
#else
	return Vector3f(x + Vector.x, y + Vector.y, z + Vector.z);
#endif

}

Vector3f& Vector3f::operator*=(const Vector3f& Vector)
{
#if defined (MATH_SSE)
	__m128 xmm0 = _mm_set_ps(0.0f, z, y, x);
	__m128 xmm1 = _mm_set_ps(0.0f, Vector.z, Vector.y, Vector.x);
	__m128 result = _mm_mul_ps(xmm0, xmm1);
	x = result.m128_f32[0];
	y = result.m128_f32[1];
	z = result.m128_f32[2];
#else
	x *= Vector.x;
	y *= Vector.y;
	z *= Vector.z;
#endif
	return (*this);
}

Vector3f& Vector3f::operator/=(const Vector3f& Vector)
{
#if defined (MATH_SSE)
	__m128 xmm0 = _mm_set_ps(0.0f, z, y, x);
	__m128 xmm1 = _mm_set_ps(0.0f, Vector.z, Vector.y, Vector.x);
	__m128 result = _mm_div_ps(xmm0, xmm1);
	x = result.m128_f32[0];
	y = result.m128_f32[1];
	z = result.m128_f32[2];
#else
	x /= Vector.x;
	y /= Vector.y;
	z /= Vector.z;
#endif
	return (*this);
}

Vector3f& Vector3f::operator-=(const Vector3f& Vector)
{
#if defined (MATH_SSE)
	__m128 xmm0 = _mm_set_ps(0.0f, z, y, x);
	__m128 xmm1 = _mm_set_ps(0.0f, Vector.z, Vector.y, Vector.x);
	__m128 result = _mm_sub_ps(xmm0, xmm1);
	x = result.m128_f32[0];
	y = result.m128_f32[1];
	z = result.m128_f32[2];
#else
	x -= Vector.x;
	y -= Vector.y;
	z -= Vector.z;
#endif
	return (*this);
}

Vector3f& Vector3f::operator+=(const Vector3f& Vector)
{
#if defined (MATH_SSE)
	__m128 xmm0 = _mm_set_ps(0.0f, z, y, x);
	__m128 xmm1 = _mm_set_ps(0.0f, Vector.z, Vector.y, Vector.x);
	__m128 result = _mm_add_ps(xmm0, xmm1);
	x = result.m128_f32[0];
	y = result.m128_f32[1];
	z = result.m128_f32[2];
#else
	x += Vector.x;
	y += Vector.y;
	z += Vector.z;
#endif
	return (*this);
}

Vector3f& Vector3f::operator=(const Vector3f& Vector)
{
	x = Vector.x;
	y = Vector.y;
	z = Vector.z;
	return (*this);
}


bool MEngine::Vector3f::operator==(const Vector3f& Vector)
{
	return MathUtils::FloatEqual(x, Vector.x) && MathUtils::FloatEqual(y, Vector.y) && MathUtils::FloatEqual(z, Vector.z);
}

Vector3f Vector3f::Cross(const Vector3f& Vector) const
{
#if defined (MATH_SSE)
	__m128 xmm0 = _mm_set_ps(0.0f, z, y, x);
	__m128 xmm1 = _mm_set_ps(0.0f, Vector.z, Vector.y, Vector.x);
	__m128 xmm2 = xmm0;
	__m128 xmm3 = xmm1;

	xmm0 = _mm_shuffle_ps(xmm0, xmm0, 0xc9);
	xmm1 = _mm_shuffle_ps(xmm1, xmm1, 0xd2);
	xmm0 = _mm_mul_ps(xmm0, xmm1);

	xmm2 = _mm_shuffle_ps(xmm2, xmm2, 0xd2);
	xmm3 = _mm_shuffle_ps(xmm3, xmm3, 0xc9);
	xmm2 = _mm_mul_ps(xmm2, xmm3);

	xmm0 = _mm_sub_ps(xmm0, xmm2);

	return Vector3f(xmm0);
#else
	return	Vector3f(
		y * Vector.z - z * Vector.y,
		z * Vector.x - x * Vector.z, 
		x * Vector.y - y * Vector.x );
#endif
}

_F32 Vector3f::Dot(const Vector3f& Vector) const
{
	_F32 ret = 0.0f;
	
	ret  = x * Vector.x;
	ret += y * Vector.y;
	ret += z * Vector.z;

	return ret;
}

_F32 Vector3f::Length()
{
#if defined (MATH_SSE)
	__m128 xmm7 = _mm_set_ps(0.0f, z, y, x);
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
	length += x * x + y * y + z * z;
	return sqrtf(length);
#endif

}

void Vector3f::Zero()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

void Vector3f::Normalize()
{
#if defined (MATH_SSE)
	__m128 xmm7 = _mm_set_ps(0.0f, z, y, x);
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
	x = result.m128_f32[0];
	y = result.m128_f32[1];
	z = result.m128_f32[2];
#else
	_F32 length = 0.0f;
	length += x * x + y * y + z * z;
	_F32 r = MathUtils::Rsqrt(length);
	*this = (*this) * r;
#endif
}

NAMESPACE_MENGINE_END