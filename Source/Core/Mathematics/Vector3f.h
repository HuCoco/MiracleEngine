#pragma once
#include <Core/Mathematics/Vector.h>
#include <Core/Mathematics/SIMD/SIMD4F.h>

#ifdef SIMD_DEPTH_ACCELERATION
#define VECTOR3_STORE3(simd_to_store, data)				\
  { (data).simd = simd_to_store; }
#define VECTOR3_LOAD3(data) (data).simd
#define VECTOR3_INIT3(data, v1, v2, v3)					\
  { (data).simd = simd4f_create(v1, v2, v3, 0); }
#else
#define VECTOR3_STORE3(simd_to_store, vec)				\
  { SIMD4F_USTORE3(simd_to_store, (vec).data); }
#define VECTOR3_LOAD3(vec) SIMD4F_ULOAD3((vec).data)
#define VECTOR3_INIT3(vec, v1, v2, v3)					\
  {														\
    (vec).data[0] = v1;									\
    (vec).data[1] = v2;									\
    (vec).data[2] = v3;									\
  }
#endif  // SIMD_DEPTH_ACCELERATION

typedef Vector<float, 3> Vector3f;

template <>
class Vector<float, 3> 
{
public:

	inline Vector() {}

	inline Vector(const Vector<float, 3>& v) 
	{
#ifdef SIMD_DEPTH_ACCELERATION
		simd = v.simd;
#else
		VECTOR3_INIT3(*this, v[0], v[1], v[2]);
#endif  // SIMD_DEPTH_ACCELERATION
	}

	explicit inline Vector(const Vector<int, 3>& v) 
	{
		VECTOR3_INIT3(*this, 
			static_cast<float>(v[0]),
			static_cast<float>(v[1]), 
			static_cast<float>(v[2]));
	}

	inline Vector(const SIMD4F& v) 
	{ 
		VECTOR3_STORE3(v, *this); 
	}

	explicit inline Vector(const float& s) 
	{
		VECTOR3_INIT3(*this, s, s, s);
	}

	inline Vector(const float& v1, const float& v2, const float& v3) 
	{
		VECTOR3_INIT3(*this, v1, v2, v3);
	}

	inline Vector(const Vector<float, 2>& v12, const float& v3) 
	{
		VECTOR3_INIT3(*this, v12[0], v12[1], v3);
	}

	explicit inline Vector(const float* v) {
#ifdef SIMD_DEPTH_ACCELERATION
		simd = SIMD4F_ULOAD3(v);
#else
		VECTOR3_INIT3(*this, v[0], v[1], v[2]);
#endif  // SIMD_DEPTH_ACCELERATION
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

	inline Vector<float, 2> xy() 
	{
		return Vector<float, 2>(x, y); 
	}

	inline const Vector<float, 2> xy() const 
	{ 
		return Vector<float, 2>(x, y); 
	}

	inline Vector<float, 3> operator-() const 
	{
		return Vector<float, 3>( SIMD4F_SUB(SIMD4F_ZERO(), VECTOR3_LOAD3(*this)));
	}

	inline Vector<float, 3> operator*(const Vector<float, 3>& v) const
	{
		return Vector<float, 3>(SIMD4F_MUL(VECTOR3_LOAD3(*this), VECTOR3_LOAD3(v)));
	}

	inline Vector<float, 3> operator/(const Vector<float, 3>& v) const 
	{
		return Vector<float, 3>(SIMD4F_DIV(VECTOR3_LOAD3(*this), VECTOR3_LOAD3(v)));
	}

	inline Vector<float, 3> operator+(const Vector<float, 3>& v) const 
	{
		return Vector<float, 3>(SIMD4F_ADD(VECTOR3_LOAD3(*this), VECTOR3_LOAD3(v)));
	}

	inline Vector<float, 3> operator-(const Vector<float, 3>& v) const 
	{
		return Vector<float, 3>(SIMD4F_SUB(VECTOR3_LOAD3(*this), VECTOR3_LOAD3(v)));
	}

	inline Vector<float, 3> operator*(const float& s) const 
	{
		return Vector<float, 3>(SIMD4F_MUL(VECTOR3_LOAD3(*this), SIMD4F_SET(s)));
	}

	inline Vector<float, 3> operator/(const float& s) const 
	{
		return Vector<float, 3>(SIMD4F_DIV(VECTOR3_LOAD3(*this), SIMD4F_SET(s)));
	}

	inline Vector<float, 3> operator+(const float& s) const 
	{
		return Vector<float, 3>(SIMD4F_ADD(VECTOR3_LOAD3(*this), SIMD4F_SET(s)));
	}

	inline Vector<float, 3> operator-(const float& s) const 
	{
		return Vector<float, 3>(SIMD4F_SUB(VECTOR3_LOAD3(*this), SIMD4F_SET(s)));
	}

	inline Vector<float, 3>& operator*=(const Vector<float, 3>& v) 
	{
		*this = SIMD4F_MUL(VECTOR3_LOAD3(*this), VECTOR3_LOAD3(v));
		return *this;
	}

	inline Vector<float, 3>& operator/=(const Vector<float, 3>& v) 
	{
		*this = SIMD4F_DIV(VECTOR3_LOAD3(*this), VECTOR3_LOAD3(v));
		return *this;
	}

	inline Vector<float, 3>& operator+=(const Vector<float, 3>& v) 
	{
		*this = SIMD4F_ADD(VECTOR3_LOAD3(*this), VECTOR3_LOAD3(v));
		return *this;
	}

	inline Vector<float, 3>& operator-=(const Vector<float, 3>& v) 
	{
		*this = SIMD4F_SUB(VECTOR3_LOAD3(*this), VECTOR3_LOAD3(v));
		return *this;
	}

	inline Vector<float, 3>& operator*=(const float& s) 
	{
		*this = SIMD4F_MUL(VECTOR3_LOAD3(*this), SIMD4F_SET(s));
		return *this;
	}

	inline Vector<float, 3>& operator/=(const float& s) 
	{
		*this = SIMD4F_DIV(VECTOR3_LOAD3(*this), SIMD4F_SET(s));
		return *this;
	}

	inline Vector<float, 3>& operator+=(const float& s) 
	{
		*this = SIMD4F_ADD(VECTOR3_LOAD3(*this), SIMD4F_SET(s));
		return *this;
	}

	inline Vector<float, 3>& operator-=(const float& s) 
	{
		*this = SIMD4F_SUB(VECTOR3_LOAD3(*this), SIMD4F_SET(s));
		return *this;
	}

	inline bool operator==(const Vector<float, 3>& v) const 
	{
		for (int i = 0; i < 3; ++i) 
		{
			if ((*this)[i] != v[i])
			{
				return false;
			}
		}
		return true;
		}

	inline bool operator!=(const Vector<float, 3>& v) const 
	{
		return !operator==(v);
	}

	inline float LengthSquared() const
	{
		return SIMD4F_DOT3_SCALAR(VECTOR3_LOAD3(*this), VECTOR3_LOAD3(*this));
	}

	inline float Length() const 
	{
		return SIMD4F_GET_X(SIMD4F_LENGTH3(VECTOR3_LOAD3(*this)));
	}

	inline float Normalize() 
	{
		const float length = Length();
		*this = SIMD4F_MUL(VECTOR3_LOAD3(*this), SIMD4F_SET(1.0f / length));
		return length;
	}

	inline Vector<float, 3> Normalized() const 
	{
		return Vector<float, 3>(SIMD4F_NORMALIZE3(VECTOR3_LOAD3(*this)));
	}

	static inline float DotProduct(const Vector<float, 3>& v1, const Vector<float, 3>& v2)
	{
		return SIMD4F_DOT3_SCALAR(VECTOR3_LOAD3(v1), VECTOR3_LOAD3(v2));
	}

	static inline Vector<float, 3> CrossProduct(const Vector<float, 3>& v1, const Vector<float, 3>& v2) 
	{
		return Vector<float, 3>(SIMD4F_CROSS3(VECTOR3_LOAD3(v1), VECTOR3_LOAD3(v2)));
	}

	static inline Vector<float, 3> HadamardProduct(const Vector<float, 3>& v1, const Vector<float, 3>& v2) 
	{
		return Vector<float, 3>(SIMD4F_MUL(VECTOR3_LOAD3(v1), VECTOR3_LOAD3(v2)));
	}

	static inline Vector<float, 3> Lerp(const Vector<float, 3>& v1, const Vector<float, 3>& v2, float percent) 
	{
		const Vector<float, 3> percentv(percent);
		const Vector<float, 3> one(1.0f);
		const Vector<float, 3> one_minus_percent = one - percentv;
		return Vector<float, 3>(SIMD4F_ADD(
			SIMD4F_MUL(VECTOR3_LOAD3(one_minus_percent), VECTOR3_LOAD3(v1)),
			SIMD4F_MUL(VECTOR3_LOAD3(percentv), VECTOR3_LOAD3(v2)))
			);
	}

//	static inline Vector<float, 3> Max(const Vector<float, 3>& v1,const Vector<float, 3>& v2) 
//	{
//#ifdef SIMD_DEPTH_ACCELERATION
//		return Vector<float, 3>(SIMD4F_MAX(VECTOR3_LOAD3(v1), VECTOR3_LOAD3(v2)));
//#else
//		return Vector<float, 3>(std::max(v1[0], v2[0]), std::max(v1[1], v2[1]),std::max(v1[2], v2[2]));
//#endif  // SIMD_DEPTH_ACCELERATION
//	}
//
//	static inline Vector<float, 3> Min(const Vector<float, 3>& v1, const Vector<float, 3>& v2) {
//#ifdef SIMD_DEPTH_ACCELERATION
//		return Vector<float, 3>(
//			SIMD4F_MIN(VECTOR3_LOAD3(v1), VECTOR3_LOAD3(v2)));
//#else
//		return Vector<float, 3>(std::min(v1[0], v2[0]), std::min(v1[1], v2[1]), std::min(v1[2], v2[2]));
//#endif  // SIMD_DEPTH_ACCELERATION
//	}

public:
	union {
#ifdef SIMD_DEPTH_ACCELERATION
		SIMD4F simd;
		float data[4];
#else
		float data[3];
#endif  // SIMD_DEPTH_ACCELERATION

		struct 
		{
			float x;
			float y;
			float z;
		};
	};
};