#pragma once
#include <Core/Mathematics/Vector.h>
#include <Core/Mathematics/MathUtilities.h>
#include <Core/Mathematics/SIMD/SIMD4F.h>


typedef Vector<float, 4> Vector4f;

template <>
class Vector<float,4>
{
public:
	inline Vector() {};

	inline Vector(const Vector<float, 4>& v)
	{
		simd = v.simd;
	};

	explicit inline Vector(const Vector<int, 4>& v)
	{
		data[0] = static_cast<float>(v[0]);
		data[1] = static_cast<float>(v[1]);
		data[2] = static_cast<float>(v[2]);
		data[3] = static_cast<float>(v[3]);
	}

	explicit inline Vector(const SIMD4F& v) 
	{ 
		simd = v; 
	}

	explicit inline Vector(const float& s)
	{
		simd = SIMD4F_SET(s);
	}

	explicit inline Vector(const float* a)
	{
		simd = SIMD4F_ULOAD4(a);
	}

	inline Vector(const float& s1, const float& s2, const float& s3, const float& s4) 
	{
		simd = SIMD4F_CREATE(s1, s2, s3, s4);
	}

	inline Vector(const Vector<float, 3>& vector3, const float& value) 
	{
		simd = SIMD4F_CREATE(vector3[0], vector3[1], vector3[2], value);
	}

	inline Vector(const Vector<float, 2>& v12, const Vector<float, 2>& v34) 
	{
		simd = SIMD4F_CREATE(v12[0], v12[1], v34[0], v34[1]);
	}

	inline float& operator()(const int i) 
	{
		return data[i]; 
	}

	inline const float& operator()(const int i) const 
	{ 
		return data[i]; 
	}

	inline float& operator[](const int i) 
	{ 
		return data[i]; 
	}

	inline const float& operator[](const int i) const 
	{ 
		return data[i]; 
	}

	inline Vector<float, 3> xyz()
	{
		return Vector<float, 3>(x, y, z);
	}

	inline const Vector<float, 3> xyz() const 
	{
		return Vector<float, 3>(x, y, z);
	}

	inline Vector<float, 2> xy() 
	{
		return Vector<float, 2>(x, y); 
	}

	inline const Vector<float, 2> xy() const 
	{
		return Vector<float, 2>(x, y); 
	}

	inline Vector<float, 2> zw()
	{ 
		return Vector<float, 2>(z, w);
	}

	inline const Vector<float, 2> zw() const 
	{
		return Vector<float, 2>(z, w); 
	}

	inline Vector<float, 4> operator-() const 
	{
		return Vector<float, 4>(SIMD4F_SUB(SIMD4F_ZERO(), simd));
	}

	inline Vector<float, 4> operator*(const Vector<float, 4>& v) const 
	{
		return Vector<float, 4>(SIMD4F_MUL(simd, v.simd));
	}

	inline Vector<float, 4> operator/(const Vector<float, 4>& v) const 
	{
		return Vector<float, 4>(SIMD4F_DIV(simd, v.simd));
	}

	inline Vector<float, 4> operator+(const Vector<float, 4>& v) const 
	{
		return Vector<float, 4>(SIMD4F_ADD(simd, v.simd));
	}

	inline Vector<float, 4> operator-(const Vector<float, 4>& v) const 
	{
		return Vector<float, 4>(SIMD4F_SUB(simd, v.simd));
	}

	inline Vector<float, 4> operator*(const float& s) const 
	{
		return Vector<float, 4>(SIMD4F_MUL(simd, SIMD4F_SET(s)));
	}

	inline Vector<float, 4> operator/(const float& s) const 
	{
		return Vector<float, 4>(SIMD4F_DIV(simd, SIMD4F_SET(s)));
	}

	inline Vector<float, 4> operator+(const float& s) const 
	{
		return Vector<float, 4>(SIMD4F_ADD(simd, SIMD4F_SET(s)));
	}

	inline Vector<float, 4> operator-(const float& s) const 
	{
		return Vector<float, 4>(SIMD4F_SUB(simd, SIMD4F_SET(s)));
	}

	inline Vector<float, 4>& operator*=(const Vector<float, 4>& v) 
	{
		simd = SIMD4F_MUL(simd, v.simd);
		return *this;
	}

	inline Vector<float, 4>& operator/=(const Vector<float, 4>& v) 
	{
		simd = SIMD4F_DIV(simd, v.simd);
		return *this;
	}

	inline Vector<float, 4>& operator+=(const Vector<float, 4>& v) 
	{
		simd = SIMD4F_ADD(simd, v.simd);
		return *this;
	}

	inline Vector<float, 4>& operator-=(const Vector<float, 4>& v) 
	{
		simd = SIMD4F_SUB(simd, v.simd);
		return *this;
	}

	inline Vector<float, 4>& operator*=(const float& s) 
	{
		simd = SIMD4F_MUL(simd, SIMD4F_SET(s));
		return *this;
	}

	inline Vector<float, 4>& operator/=(const float& s) 
	{
		simd = SIMD4F_DIV(simd, SIMD4F_SET(s));
		return *this;
	}

	inline Vector<float, 4>& operator+=(const float& s)
	{
		simd = SIMD4F_ADD(simd, SIMD4F_SET(s));
		return *this;
	}

	inline Vector<float, 4>& operator-=(const float& s) 
	{
		simd = SIMD4F_SUB(simd, SIMD4F_SET(s));
		return *this;
	}

	inline bool operator==(const Vector<float, 4>& v) const 
	{
		for (int i = 0; i < 4; ++i) 
		{
			if ((*this)[i] != v[i])
			{
				return false;
			}
		}
		return true;
	}

	inline bool operator!=(const Vector<float, 4>& v) const
	{
		return !operator==(v);
	}

	inline float LengthSquared() const 
	{ 
		return SIMD4F_GET_X(SIMD4F_DOT4(simd, simd));
	}

	inline float Length() const 
	{ 
		return SIMD4F_GET_X(SIMD4F_LENGTH4(simd));
	}

	inline float Normalize() 
	{ 
		const float length = Length();
		simd = SIMD4F_MUL(simd, SIMD4F_SET(1 / length));
		return length;
	}

	inline Vector<float, 4> Normalized() const 
	{ 
		return Vector<float, 4>(SIMD4F_NORMALIZE4(simd));
	}

	static inline float DotProduct(const Vector<float, 4>& v1, const Vector<float, 4>& v2) 
	{
		return SIMD4F_GET_X(SIMD4F_DOT4(v1.simd, v2.simd));
	}

	static inline Vector<float, 4> HadamardProduct(const Vector<float, 4>& v1,
		const Vector<float, 4>& v2) 
	{
		return Vector<float, 4>(SIMD4F_MUL(v1.simd, v2.simd));
	}

	static inline Vector<float, 4> Lerp(const Vector<float, 4>& v1,
		const Vector<float, 4>& v2, const float percent) 
	{
		const Vector<float, 4> percentv(percent);
		const Vector<float, 4> one(1.0f);
		const Vector<float, 4> one_minus_percent = one - percentv;
		return Vector<float, 4>(
			SIMD4F_ADD(SIMD4F_MUL(one_minus_percent.simd, v1.simd),
				SIMD4F_MUL(percentv.simd, v2.simd)));
	}

	static inline Vector<float, 4> Max(const Vector<float, 4>& v1, const Vector<float, 4>& v2) 
	{
		return Vector<float, 4>(SIMD4F_MAX(v1.simd, v2.simd));
	}

	static inline Vector<float, 4> Min(const Vector<float, 4>& v1,
		const Vector<float, 4>& v2) 
	{
		return Vector<float, 4>(SIMD4F_MIN(v1.simd, v2.simd));
	}
public:
	union {
		SIMD4F simd;
		float data[4];
		struct {
			float x;
			float y;
			float z;
			float w;
		};
	};
};