#pragma once
#include <Core/Mathematics/Vector.h>
#include <Core/Mathematics/SIMD/SIMD4F.h>


#ifdef SIMD_DEPTH_ACCELERATION
#define VECTOR2_STORE2(simd_to_store, data) \
  { (data).simd = simd_to_store; }
#define VECTOR2_LOAD2(data) (data).simd
#define VECTOR2_INIT2(data, v1, v2,) \
  { (data).simd = SIMD4F_CREATE(v1, v2, 0, 0); }
#else
#define VECTOR2_STORE2(simd_to_store, vec) \
  { SIMD4F_USTORE2(simd_to_store, (vec).data); }
#define VECTOR2_LOAD2(vec) SIMD4F_ULOAD2((vec).data)
#define VECTOR2_INIT2(vec, v1, v2) \
  {                                            \
    (vec).data[0] = v1;                      \
    (vec).data[1] = v2;                      \
  }
#endif  // SIMD_DEPTH_ACCELERATION


typedef Vector<float, 2> Vector2f;

template <>
class Vector<float, 2>
{
public:
	inline Vector() {}

	inline Vector(const Vector<float, 2>& v) {
#ifdef SIMD_DEPTH_ACCELERATION
		simd = v.simd;
#else
		VECTOR2_INIT2(*this, v[0], v[1]);
#endif  // SIMD_DEPTH_ACCELERATION
	}

	explicit inline Vector(const Vector<int, 2>& v) 
	{
		VECTOR2_INIT2(*this, static_cast<float>(v[0]), static_cast<float>(v[1]));
	}

	inline Vector(const SIMD4F& v)
	{ 
		VECTOR2_STORE2(v, *this);
	}

	explicit inline Vector(const float& s) 
	{
		VECTOR2_INIT2(*this, s, s);
	}

	inline Vector(const float& v1, const float& v2)
	{
		VECTOR2_INIT2(*this, v1, v2);
	}

	explicit inline Vector(const float* v) {
#ifdef SIMD_DEPTH_ACCELERATION
		simd = SIMD4F_ULOAD2(v);
#else
		VECTOR2_INIT2(*this, v[0], v[1]);
#endif  // SIMD_DEPTH_ACCELERATION
	}

	inline Vector<float, 2> xy() 
	{ 
		return Vector<float, 2>(x, y); 
	}

	inline const Vector<float, 2> xy() const 
	{ 
		return Vector<float, 2>(x, y); 
	}

	inline float& operator()(const int i) { return data[i]; }

	inline const float& operator()(const int i) const { return data[i]; }

	inline float& operator[](const int i) { return data[i]; }

	inline const float& operator[](const int i) const { return data[i]; }

	inline Vector<float, 2> operator-() const
	{
		return Vector<float, 2>(SIMD4F_SUB(SIMD4F_ZERO(), VECTOR2_LOAD2(*this)));
	}

	inline Vector<float, 2> operator*(const Vector<float, 2>& v) const
	{
		return Vector<float, 2>(SIMD4F_MUL(VECTOR2_LOAD2(*this), VECTOR2_LOAD2(v)));
	}

	inline Vector<float, 2> operator/(const Vector<float, 2>& v) const
	{
		return Vector<float, 2>(SIMD4F_DIV(VECTOR2_LOAD2(*this), VECTOR2_LOAD2(v)));
	}

	inline Vector<float, 2> operator+(const Vector<float, 2>& v) const
	{
		return Vector<float, 2>(SIMD4F_ADD(VECTOR2_LOAD2(*this), VECTOR2_LOAD2(v)));
	}

	inline Vector<float, 2> operator-(const Vector<float, 2>& v) const
	{
		return Vector<float, 2>(SIMD4F_SUB(VECTOR2_LOAD2(*this), VECTOR2_LOAD2(v)));
	}

	inline Vector<float, 2> operator*(const float& s) const
	{
		return Vector<float, 2>(SIMD4F_MUL(VECTOR2_LOAD2(*this), SIMD4F_SET(s)));
	}

	inline Vector<float, 2> operator/(const float& s) const
	{
		return Vector<float, 2>(SIMD4F_DIV(VECTOR2_LOAD2(*this), SIMD4F_SET(s)));
	}

	inline Vector<float, 2> operator+(const float& s) const
	{
		return Vector<float, 2>(SIMD4F_ADD(VECTOR2_LOAD2(*this), SIMD4F_SET(s)));
	}

	inline Vector<float, 2> operator-(const float& s) const
	{
		return Vector<float, 2>(SIMD4F_SUB(VECTOR2_LOAD2(*this), SIMD4F_SET(s)));
	}

	inline Vector<float, 2>& operator*=(const Vector<float, 2>& v)
	{
		*this = SIMD4F_MUL(VECTOR2_LOAD2(*this), VECTOR2_LOAD2(v));
		return *this;
	}

	inline Vector<float, 2>& operator/=(const Vector<float, 2>& v)
	{
		*this = SIMD4F_DIV(VECTOR2_LOAD2(*this), VECTOR2_LOAD2(v));
		return *this;
	}

	inline Vector<float, 2>& operator+=(const Vector<float, 2>& v)
	{
		*this = SIMD4F_ADD(VECTOR2_LOAD2(*this), VECTOR2_LOAD2(v));
		return *this;
	}

	inline Vector<float, 2>& operator-=(const Vector<float, 2>& v)
	{
		*this = SIMD4F_SUB(VECTOR2_LOAD2(*this), VECTOR2_LOAD2(v));
		return *this;
	}

	inline Vector<float, 2>& operator*=(const float& s)
	{
		*this = SIMD4F_MUL(VECTOR2_LOAD2(*this), SIMD4F_SET(s));
		return *this;
	}

	inline Vector<float, 2>& operator/=(const float& s)
	{
		*this = SIMD4F_DIV(VECTOR2_LOAD2(*this), SIMD4F_SET(s));
		return *this;
	}

	inline Vector<float, 2>& operator+=(const float& s)
	{
		*this = SIMD4F_ADD(VECTOR2_LOAD2(*this), SIMD4F_SET(s));
		return *this;
	}

	inline Vector<float, 2>& operator-=(const float& s)
	{
		*this = SIMD4F_SUB(VECTOR2_LOAD2(*this), SIMD4F_SET(s));
		return *this;
	}

	inline bool operator==(const Vector<float, 2>& v) const
	{
		for (int i = 0; i < 2; ++i)
		{
			if ((*this)[i] != v[i])
			{
				return false;
			}
		}
		return true;
	}

	inline bool operator!=(const Vector<float, 2>& v) const
	{
		return !operator==(v);
	}

	inline float LengthSquared() const {
		return SIMD4F_DOT2_SCALAR(VECTOR2_LOAD2(*this),VECTOR2_LOAD2(*this));
	}

	inline float Length() const {
		return SIMD4F_GET_X(SIMD4F_LENGTH2(VECTOR2_LOAD2(*this)));
	}

	inline float Normalize() {
		const float length = Length();
		*this = SIMD4F_MUL(VECTOR2_LOAD2(*this), SIMD4F_SET(1 / length));
		return length;
	}

	inline Vector<float, 2> Normalized() const {
		return Vector<float, 2>(SIMD4F_NORMALIZE2(VECTOR2_LOAD2(*this)));
	}

	static inline float DotProduct(const Vector<float, 2>& v1, const Vector<float, 2>& v2)
	{
		return SIMD4F_DOT2_SCALAR(VECTOR2_LOAD2(v1), VECTOR2_LOAD2(v2));
	}

	static inline Vector<float, 2> HadamardProduct(const Vector<float, 2>& v1, const Vector<float, 2>& v2)
	{
		return Vector<float, 2>(SIMD4F_MUL(VECTOR2_LOAD2(v1), VECTOR2_LOAD2(v2)));
	}

	static inline Vector<float, 2> Lerp(const Vector<float, 2>& v1, const Vector<float, 2>& v2, float percent)
	{
		const Vector<float, 2> percentv(percent);
		const Vector<float, 2> one(1.0f);
		const Vector<float, 2> one_minus_percent = one - percentv;
		return Vector<float, 2>(SIMD4F_ADD(
			SIMD4F_MUL(VECTOR2_LOAD2(one_minus_percent), VECTOR2_LOAD2(v1)),
			SIMD4F_MUL(VECTOR2_LOAD2(percentv), VECTOR2_LOAD2(v2)))
			);
	}

//	static inline Vector<float, 2> Max(const Vector<float, 2>& v1, const Vector<float, 2>& v2)
//	{
//#ifdef SIMD_DEPTH_ACCELERATION
//		return Vector<float, 2>(SIMD4F_MAX(VECTOR2_LOAD2(v1), VECTOR2_LOAD2(v2)));
//#else
//		return Vector<float, 2>(std::max(v1[0], v2[0]), std::max(v1[1], v2[1]));
//#endif  // SIMD_DEPTH_ACCELERATION
//	}
//
//	static inline Vector<float, 2> Min(const Vector<float, 2>& v1, const Vector<float, 2>& v2)
//	{
//#ifdef SIMD_DEPTH_ACCELERATION
//		return Vector<float, 2>(SIMD4F_MIN(VECTOR2_LOAD2(v1), VECTOR2_LOAD2(v2)));
//#else
//		return Vector<float, 2>(std::min(v1[0], v2[0]), std::min(v1[1], v2[1]));
//#endif  // SIMD_DEPTH_ACCELERATION
//	}

public:
	union {
#ifdef SIMD_DEPTH_ACCELERATION
		SIMD4F simd;
		float data[4];
#else
		float data[2];
#endif  // SIMD_DEPTH_ACCELERATION

		struct
		{
			float x;
			float y;
		};
	};
};