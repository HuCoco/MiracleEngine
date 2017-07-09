#include <Core/Mathematics/Quaternion.h>
#include <Core/Mathematics/MathUtils.h>

NAMESPACE_MENGINE_BEGIN

Quaternion::Quaternion()
{

}


Quaternion::Quaternion(_F32 _w, _F32 _x, _F32 _y, _F32 _z)
{
	w = _w;
	x = _x;
	y = _y;
	z = _z;
}

#if defined(MATH_SSE)
Quaternion::Quaternion(__m128 _vec)
{
	w = _vec.m128_f32[0];
	x = _vec.m128_f32[1];
	y = _vec.m128_f32[2];
	z = _vec.m128_f32[3];
}
#endif

Quaternion::Quaternion(_F32 _angle, const Vector3f& _n)
{
#if defined (MATH_SSE)
	__m128 n = _mm_setr_ps(0.0f, _n[0], _n[1], _n[2]);
	__m128 sinAngle = _mm_set_ps1(std::sin(MathUtils::Angle2Radian(_angle / 2.0f)));
	__m128 result  = _mm_mul_ps(n, sinAngle);
	w = std::cos(MathUtils::Angle2Radian(_angle / 2.0f));
	x = result.m128_f32[1];
	y = result.m128_f32[2];
	z = result.m128_f32[3];
	
#else
	w = std::cos(MathUtils::Angle2Radian(_angle / 2.0f));
	x = std::sin(MathUtils::Angle2Radian(_angle / 2.0f) * _n[0]);
	y = std::sin(MathUtils::Angle2Radian(_angle / 2.0f) * _n[1]);
	z = std::sin(MathUtils::Angle2Radian(_angle / 2.0f) * _n[2]);
#endif
}

Quaternion::Quaternion(const Vector3f& _v)
{
	w = 0.0f;
	x = _v[0];
	y = _v[1];
	z = _v[2];
}

Quaternion Quaternion::Conjugate() const
{
	return Quaternion(w, -x, -y, -z);
}

Quaternion Quaternion::Inverse() const
{
	return (Conjugate() / Length());
}

_F32 Quaternion::Length() const
{
	return sqrtf(LengthSquared());
}

_F32 Quaternion::LengthSquared() const
{
#if defined (MATH_SSE)
	__m128 xmm0 = _mm_set_ps(z, y, x, w);
	__m128 pow2 = _mm_mul_ps(xmm0, xmm0);
	_F32 result = 0.0f;
	for (_I32 i = 0 ; i < 4 ; ++i)
	{
		result += pow2.m128_f32[i];
	}
#else
	_F32 result = 0.0f;
	for (_I32 i = 0; i < 4; ++i)
	{
		result += f[i] * f[i];
	}
#endif
	return result;
}

Quaternion& Quaternion::operator=(const Quaternion& a)
{
	w = a.w;
	x = a.x;
	y = a.y;
	z = a.z;
	
	return (*this);
}

Quaternion Quaternion::operator*(const Quaternion& a) const
{
#if defined (MATH_SSE)
	Quaternion result;
	_F32 w1w2 = w * a.w;
	Vector3f v1v2 = -(v * a.v);
	Vector3f w1v2 = a.v * w;
	Vector3f w2v1 = v * a.w;
	Vector3f v1xv2 = v.Cross(a.v);
	result.w = w1w2 - v1v2[0] - v1v2[1] - v1v2[2];
	Vector3f res_part2 = w1v2 + w2v1 + v1xv2;
	for (_I32 i = 1; i < 4; ++i)
	{
		result.f[i] = res_part2[i-1];
	}
	return result;
#else
	Quaternion result;
	result.w = a.w * w - a.x * x - a.y * y - a.z * z;
	result.x = a.w * x + a.x * w + a.y * z - a.z * y;
	result.y = a.w * y + a.y * w - a.x * z + a.z * x;
	result.z = a.w * z + a.z * w + a.x * y - a.y * x;
	return(result);
#endif
}

Quaternion Quaternion::operator/(const _F32& value) const
{
	MeAssertM(value != 0.0f, "Quaternion Error : value is 0 !");
#if defined (MATH_SSE)
	__m128 Divisor = _mm_set_ps1(value);
	__m128 xmm0 = _mm_set_ps(z, y, x, w);
	__m128 result = _mm_div_ps(xmm0, Divisor);
	return (Quaternion(result));
#else
	return(Quaternion(w / value, x / value, y / value, z / value));
#endif
}

Quaternion::~Quaternion()
{
}

MEngine::Quaternion MEngine::Quaternion::Identity()
{
	return Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
}

Vector3f Quaternion::Rotation(Quaternion* p, _U32 num_of_p, const Vector3f& v)
{
	Quaternion ResultQuat = Quaternion::Identity();

	for (_I32 ReverseIndex = num_of_p - 1; ReverseIndex >= 0; --ReverseIndex)
	{
		ResultQuat = ResultQuat * p[ReverseIndex];
	}

	ResultQuat = ResultQuat * v;

	for (_I32 PositiveIndex = 0 ; PositiveIndex < num_of_p; ++PositiveIndex)
	{
		ResultQuat = ResultQuat * p[PositiveIndex].Inverse();
	}

	return Vector3f(ResultQuat.x, ResultQuat.y, ResultQuat.z);
}

NAMESPACE_MENGINE_END