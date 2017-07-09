#include <Core/Mathematics/Vector2f.h>
#include <Core/Mathematics/MathUtils.h>

NAMESPACE_MENGINE_BEGIN

Vector2f::Vector2f()
	: x(0.0f)
	, y(0.0f)
{
	
}



#if defined (MATH_SSE)
Vector2f::Vector2f(__m128 _vec)
	: x(_vec.m128_f32[0])
	, y(_vec.m128_f32[1])
{
	
}
#endif

Vector2f::Vector2f(_F32 _x, _F32 _y)
	: x(_x)
	, y(_y)
{

}

Vector2f::~Vector2f()
{
}

_F32 Vector2f::operator[](_I32 pos) const
{
	MeAssertM((pos >= 0 && pos < 2),"Vector2f error : over index");
	return f[pos];
}

_F32& Vector2f::operator[](_I32 pos)
{
	MeAssertM((pos >= 0 && pos < 2), "Vector2f error : over index");
	return f[pos];
}

Vector2f Vector2f::operator-(void)
{
	return Vector2f(-x, -y);
}

Vector2f Vector2f::operator/(const Vector2f& Vector) const
{
#if defined (MATH_SSE)
	__m128 xmm0 = _mm_set_ps(0.0f,0.0f,y,x);
	__m128 xmm1 = _mm_set_ps(0.0f, 0.0f, Vector.y, Vector.x);
	__m128 result = _mm_div_ps(xmm0, xmm1);
	return Vector2f(result);
#else
	return Vector2f(x / Vector.x, y / Vector.y);
#endif
	
}

Vector2f Vector2f::operator/(_F32 value) const
{
#if defined (MATH_SSE)
	__m128 xmm0 = _mm_set_ps(0.0f,0.0f,y,x);
	__m128 Divisor = _mm_set_ps1(value);
	__m128 result = _mm_div_ps(xmm0, Divisor);
	return Vector2f(result);
#else
	return Vector2f(x / value, y / value);
#endif
	
}

Vector2f Vector2f::operator*(const Vector2f& Vector) const
{
#if defined (MATH_SSE)
	__m128 xmm0 = _mm_set_ps(0.0f,0.0f,y,x);
	__m128 xmm1 = _mm_set_ps(0.0f, 0.0f, Vector.y, Vector.x);
	__m128 result = _mm_mul_ps(xmm0, xmm1);
	return Vector2f(result);
#else
	return Vector2f(x * Vector.x, y * Vector.y);
#endif
	
}

Vector2f Vector2f::operator*(_F32 value) const
{
#if defined (MATH_SSE)
	__m128 xmm0 = _mm_set_ps(0.0f,0.0f,y,x);
	__m128 multiplier = _mm_set_ps1(value);
	__m128 result = _mm_mul_ps(xmm0, multiplier);
	return Vector2f(result);
#else
	return Vector2f(x * value, y * value);
#endif
	
}

Vector2f Vector2f::operator-(const Vector2f& Vector) const
{
#if defined (MATH_SSE)
	__m128 xmm0 = _mm_set_ps(0.0f,0.0f,y,x);
	__m128 xmm1 = _mm_set_ps(0.0f, 0.0f, Vector.y, Vector.x);
	__m128 result = _mm_sub_ps(xmm0, xmm1);
	return Vector2f(result);
#else
	return Vector2f(x - Vector.x, y - Vector.y);
#endif
	
}

Vector2f Vector2f::operator+(const Vector2f& Vector) const
{
#if defined (MATH_SSE)
	__m128 xmm0 = _mm_set_ps(0.0f,0.0f,y,x);
	__m128 xmm1 = _mm_set_ps(0.0f, 0.0f, Vector.y, Vector.x);
	__m128 result = _mm_add_ps(xmm0, xmm1);
	return Vector2f(result);
#else
	return Vector2f(x + Vector.x, y + Vector.y);
#endif
	
}

Vector2f& Vector2f::operator*=(const Vector2f& Vector)
{
#if defined (MATH_SSE)	
	__m128 xmm0 = _mm_set_ps(0.0f,0.0f,y,x);
	__m128 xmm1 = _mm_set_ps(0.0f, 0.0f, Vector.y, Vector.x);
	__m128 result = _mm_mul_ps(xmm0, xmm1);
	x = result.m128_f32[0];
	y = result.m128_f32[1];
#else
	x *= Vector.x;
	y *= Vector.y;
#endif
	return (*this);
}

Vector2f& Vector2f::operator/=(const Vector2f& Vector)
{
#if defined (MATH_SSE)
	__m128 xmm0 = _mm_set_ps(0.0f,0.0f,y,x);
	__m128 xmm1 = _mm_set_ps(0.0f, 0.0f, Vector.y, Vector.x);
	__m128 result = _mm_div_ps(xmm0, xmm1);
	x = result.m128_f32[0];
	y = result.m128_f32[1];
#else
	x /= Vector.x;
	y /= Vector.y;
#endif
	return (*this);
}

Vector2f& Vector2f::operator-=(const Vector2f& Vector)
{
#if defined (MATH_SSE)
	__m128 xmm0 = _mm_set_ps(0.0f,0.0f,y,x);
	__m128 xmm1 = _mm_set_ps(0.0f, 0.0f, Vector.y, Vector.x);
	__m128 result = _mm_sub_ps(xmm0, xmm1);
	x = result.m128_f32[0];
	y = result.m128_f32[1];
#else
	x -= Vector.x;
	y -= Vector.y;
#endif
	return (*this);
}

Vector2f& Vector2f::operator+=(const Vector2f& Vector)
{
#if defined (MATH_SSE)
	__m128 xmm0 = _mm_set_ps(0.0f,0.0f,y,x);
	__m128 xmm1 = _mm_set_ps(0.0f, 0.0f, Vector.y, Vector.x);
	__m128 result = _mm_add_ps(xmm0, xmm1);
	x = result.m128_f32[0];
	y = result.m128_f32[1];
#else
	x += Vector.x;
	y += Vector.y;
#endif
	return (*this);
}

Vector2f& Vector2f::operator=(const Vector2f& Vector)
{
	x = Vector.x;
	y = Vector.y;
	return (*this);
}


_F32 Vector2f::Length()
{
#if defined (MATH_SSE)
	__m128 xmm7 = _mm_set_ps(0.0f,0.0f,y,x);
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
	length += x * x + y * y;
	return sqrtf(length);
#endif

}

void Vector2f::Zero()
{
	x = 0.0f;
	y = 0.0f;
}

void Vector2f::Normalize()
{
#if defined (MATH_SSE)
	__m128 xmm7 = _mm_set_ps(0.0f,0.0f,y,x);
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
#else
	_F32 length = 0.0f;
	length += x * x + y * y;
	_F32 r = MathUtils::Rsqrt(length);
	*this = (*this) * r;
#endif
}

NAMESPACE_MENGINE_END