#pragma once
#include "MathPreCompileHead.h"
#include "MathUtilities.h"


#define VECTOR_OPERATION(OP) UNROLLED_LOOP(i, d, OP)

#define VECTOR_OPERATOR(OP)					 \
  {                                          \
    Vector<T, d> result;                     \
    VECTOR_OPERATION(result[i] = OP);		 \
    return result;                           \
  }

#define VECTOR_SELF_OPERATOR(OP)		\
  {                                     \
    VECTOR_OPERATION(OP);				\
    return *this;                       \
  }


template <class T, int d>
class Vector;

/// @cond MATHFU_INTERNAL
template <class T, int d>
static inline T DotProductHelper(const Vector<T, d>& v1, const Vector<T, d>& v2);
template <class T>
static inline T DotProductHelper(const Vector<T, 2>& v1, const Vector<T, 2>& v2);
template <class T>
static inline T DotProductHelper(const Vector<T, 3>& v1, const Vector<T, 3>& v2);
template <class T>
static inline T DotProductHelper(const Vector<T, 4>& v1, const Vector<T, 4>& v2);


template<class T, int d>
class Vector
{
public:

	inline Vector() {};

	inline Vector(const Vector<T,d>& v) 
	{
		VECTOR_OPERATION(data[i] = v.data[i]);
	};

	template <typename U>
	explicit inline Vector(const Vector<U, d>& v) 
	{
		VECTOR_OPERATION(data[i] = static_cast<T>(v[i]));
	}

	explicit inline Vector(const T& s) 
	{
		VECTOR_OPERATION(data[i] = s);
	}

	explicit inline Vector(const T* a) 
	{
		VECTOR_OPERATION(data[i] = a[i]);
	}

	inline Vector(const T& s1, const T& s2) 
	{
		MENGINE_STATIC_ASSERT(d == 2);
		data[0] = s1;
		data[1] = s2;
	}

	inline Vector(const T& s1, const T& s2, const T& s3)
	{
		MENGINE_STATIC_ASSERT(d == 3);
		data[0] = s1;
		data[1] = s2;
		data[2] = s3;
	}

	inline Vector(const Vector<T, 2>& v12, const T& s3) {
		MENGINE_STATIC_ASSERT(d == 3);
		data[0] = v12[0];
		data[1] = v12[1];
		data[2] = s3;
	}

	inline Vector(const T& s1, const T& s2, const T& s3, const T& s4) {
		MENGINE_STATIC_ASSERT(d == 4);
		data[0] = s1;
		data[1] = s2;
		data[2] = s3;
		data[3] = s4;
	}

	inline Vector(const Vector<T, 3>& vector3, const T& value) {
		MENGINE_STATIC_ASSERT(d == 4);
		data[0] = vector3[0];
		data[1] = vector3[1];
		data[2] = vector3[2];
		data[3] = value;
	}

	inline Vector(const Vector<T, 2>& v12, const Vector<T, 2>& v34) {
		MENGINE_STATIC_ASSERT(d == 4);
		data[0] = v12[0];
		data[1] = v12[1];
		data[2] = v34[0];
		data[3] = v34[1];
	}

	// operator function
	inline T& operator()(const int i)
	{
		return data[i]; 
	}

	inline const T& operator()(const int i) const 
	{ 
		return data[i]; 
	}

	inline T& operator[](const int i)
	{ 
		return data[i]; 
	}

	inline const T& operator[](const int i) const 
	{ 
		return data[i]; 
	}

	inline Vector<T, 3> xyz() 
	{
		MENGINE_STATIC_ASSERT(d > 3);
		return Vector<T, 3>(data[0], data[1], data[2]);
	}

	inline const Vector<T, 3> xyz() const 
	{
		MENGINE_STATIC_ASSERT(d > 3);
		return Vector<T, 3>(data[0], data[1], data[2]);
	}

	inline Vector<T, 2> xy() 
	{
		MENGINE_STATIC_ASSERT(d > 2);
		return Vector<T, 2>(data[0], data[1]);
	}
	
	inline const Vector<T, 2> xy() const 
	{
		MENGINE_STATIC_ASSERT(d > 2);
		return Vector<T, 2>(data[0], data[1]);
	}

	inline Vector<T, 2> zw() {
		MENGINE_STATIC_ASSERT(d == 4);
		return Vector<T, 2>(data[2], data[3]);
	}

	inline const Vector<T, 2> zw() const 
	{
		MENGINE_STATIC_ASSERT(d == 4);
		return Vector<T, 2>(data[2], data[3]);
	}

	inline T LengthSquared() const
	{ 
		return LengthSquaredHelper(*this); 
	}

	inline T Length() const 
	{
		return LengthHelper(*this); 
	}

	inline T Normalize() 
	{
		return NormalizeHelper(*this); 
	}

	inline Vector<T, d> Normalized() const 
	{ 
		return NormalizedHelper(*this); 
	}

	static inline T DotProduct(const Vector<T, d>& v1, const Vector<T, d>& v2) 
	{
		return DotProductHelper(v1, v2);
	}

	static inline Vector<T, d> HadamardProduct(const Vector<T, d>& v1, const Vector<T, d>& v2) 
	{
		return HadamardProductHelper(v1, v2);
	}

	static inline Vector<T, 3> CrossProduct(const Vector<T, 3>& v1,
		const Vector<T, 3>& v2) 
	{
		return CrossProductHelper(v1, v2);
	}

	static inline Vector<T, d> Lerp(const Vector<T, d>& v1, const Vector<T, d>& v2, const T percent) 
	{
		return LerpHelper(v1, v2, percent);
	}

	static inline Vector<T, d> Max(const Vector<T, d>& v1, const Vector<T, d>& v2) 
	{
		return MaxHelper(v1, v2);
	}

	static inline Vector<T, d> Min(const Vector<T, d>& v1, const Vector<T, d>& v2) 
	{
		return MinHelper(v1, v2);
	}

public:
	T data[d];
};


template <class T, int d>
inline bool operator==(const Vector<T, d>& lhs, const Vector<T, d>& rhs)
{
	for (int i = 0; i < d; ++i)
	{
		if (lhs[i] != rhs[i])
		{
			return false;
		}
	}
	return true;
}

template <class T, int d>
inline bool operator!=(const Vector<T, d>& lhs, const Vector<T, d>& rhs) 
{
	return !(lhs == rhs);
}

template <class T, int d>
inline Vector<T, d> operator-(const Vector<T, d>& v)
{
	VECTOR_OPERATOR(-v.data[i]);
}

template <class T, int d>
inline Vector<T, d> operator*(const T& s, const Vector<T, d>& v) 
{
	VECTOR_OPERATOR(v.data[i] * s);
}

template <class T, int d>
inline Vector<T, d> operator/(const Vector<T, d>& v, const T& s) 
{
	VECTOR_OPERATOR(v.data[i] / s);
}

template <class T, int d>
inline Vector<T, d> operator+(const T& s, const Vector<T, d>& v) {
	VECTOR_OPERATOR(v.data[i] + s);
}

template <class T, int d>
inline Vector<T, d> operator-(const T& s, const Vector<T, d>& v) {
	VECTOR_OPERATOR(v.data[i] - s);
}

template <class T, int d>
inline Vector<T, d> operator*(const Vector<T, d>& lhs,
	const Vector<T, d>& rhs) {
	return HadamardProductHelper(lhs, rhs);
}

template <class T, int d>
inline Vector<T, d> operator/(const Vector<T, d>& lhs, const Vector<T, d>& rhs)
{
	VECTOR_OPERATOR(lhs.data[i] / rhs[i]);
}

template <class T, int d>
inline Vector<T, d> operator+(const Vector<T, d>& lhs, const Vector<T, d>& rhs) 
{
	VECTOR_OPERATOR(lhs.data[i] + rhs[i]);
}

template <class T, int d>
inline Vector<T, d> operator-(const Vector<T, d>& lhs, const Vector<T, d>& rhs) 
{
	VECTOR_OPERATOR(lhs.data[i] - rhs[i]);
}

template <class T, int d>
inline Vector<T, d> operator*(const Vector<T, d>& v, const T& s) 
{
	VECTOR_OPERATOR(v.data[i] * s);
}

template <class T, int d>
inline Vector<T, d> operator+(const Vector<T, d>& v, const T& s) 
{
	VECTOR_OPERATOR(v.data[i] + s);
}

template <class T, int d>
inline Vector<T, d> operator-(const Vector<T, d>& v, const T& s) 
{
	VECTOR_OPERATOR(v.data[i] - s);
}

template <class T, int d>
inline Vector<T, d>& operator*=(Vector<T, d>& lhs, const Vector<T, d>& rhs) 
{
	VECTOR_OPERATION(lhs.data[i] *= rhs[i]);
	return lhs;
}

template <class T, int d>
inline Vector<T, d>& operator/=(Vector<T, d>& lhs, const Vector<T, d>& rhs) 
{
	VECTOR_OPERATION(lhs.data[i] /= rhs[i]);
	return lhs;
}

template <class T, int d>
inline Vector<T, d>& operator+=(Vector<T, d>& lhs, const Vector<T, d>& rhs) 
{
	VECTOR_OPERATION(lhs.data[i] += rhs[i]);
	return lhs;
}

template <class T, int d>
inline Vector<T, d>& operator-=(Vector<T, d>& lhs, const Vector<T, d>& rhs) 
{
	VECTOR_OPERATION(lhs.data[i] -= rhs[i]);
	return lhs;
}

template <class T, int d>
inline Vector<T, d>& operator*=(Vector<T, d>& v, const T& s) 
{
	VECTOR_OPERATION(v.data[i] *= s);
	return v;
}

template <class T, int d>
inline Vector<T, d>& operator/=(Vector<T, d>& v, const T& s) 
{
	VECTOR_OPERATION(v.data[i] /= s);
	return v;
}

template <class T, int d>
inline Vector<T, d>& operator+=(Vector<T, d>& v, const T& s) {
	VECTOR_OPERATION(v.data[i] += s);
	return v;
}

template <class T, int d>
inline Vector<T, d>& operator-=(Vector<T, d>& v, const T& s) 
{
	VECTOR_OPERATION(v.data[i] -= s);
	return v;
}

template <class T, int d>
inline Vector<T, d> HadamardProductHelper(const Vector<T, d>& v1, const Vector<T, d>& v2) 
{
	VECTOR_OPERATOR(v1[i] * v2[i]);
}

template <class T>
inline Vector<T, 3> CrossProductHelper(const Vector<T, 3>& v1, const Vector<T, 3>& v2) {
	return Vector<T, 3>(
		v1[1] * v2[2] - v1[2] * v2[1],
		v1[2] * v2[0] - v1[0] * v2[2],
		v1[0] * v2[1] - v1[1] * v2[0]);
}

template <class T, int d>
inline T LengthSquaredHelper(const Vector<T, d>& v) 
{
	return DotProductHelper(v, v);
}

template <class T, int d>
inline T LengthHelper(const Vector<T, d>& v) 
{
	return sqrt(LengthSquaredHelper(v));
}

template <class T, int d>
inline T NormalizeHelper(Vector<T, d>& v) 
{
	const T length = LengthHelper(v);
	v *= (static_cast<T>(1) / length);
	return length;
}

template <class T, int d>
inline Vector<T, d> NormalizedHelper(const Vector<T, d>& v) 
{
	return v * (static<T>(1) / LengthHelper(v));
}

template <class T, int d>
inline Vector<T, d> LerpHelper(const Vector<T, d>& v1, const Vector<T, d>& v2, const T percent) 
{
	const T one_minus_percent = static_cast<T>(1.0) - percent;
	VECTOR_OPERATOR(one_minus_percent * v1[i] + percent * v2[i]);
}

template <class T, int d>
inline Vector<T, d> MaxHelper(const Vector<T, d>& v1, const Vector<T, d>& v2) 
{
	Vector<T, d> result;
	VECTOR_OPERATION(result[i] = std::max(v1[i], v2[i]));
	return result;
}

template <class T, int d>
inline Vector<T, d> MinHelper(const Vector<T, d>& v1, const Vector<T, d>& v2) 
{
	Vector<T, d> result;
	VECTOR_OPERATION(result[i] = std::min(v1[i], v2[i]));
	return result;
}

template <class T, int d>
static inline T DotProductHelper(const Vector<T, d>& v1, const Vector<T, d>& v2) 
{
	T result = 0;
	VECTOR_OPERATION(result += v1[i] * v2[i]);
	return result;
}

template <class T>
static inline T DotProductHelper(const Vector<T, 2>& v1, const Vector<T, 2>& v2) 
{
	return v1[0] * v2[0] + v1[1] * v2[1];
}

template <class T>
static inline T DotProductHelper(const Vector<T, 3>& v1, const Vector<T, 3>& v2) 
{
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

template <class T>
static inline T DotProductHelper(const Vector<T, 4>& v1, const Vector<T, 4>& v2) 
{
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2] + v1[3] * v2[3];
}