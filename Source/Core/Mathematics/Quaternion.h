#pragma once

#include "Matrix.h"
#include "vector.h"

#include <math.h>

template <class T>
class Quaternion {
public:
	inline Quaternion() {}

	inline Quaternion(const Quaternion<T>& q) 
	{
		s = q.s;
		v = q.v;
	}

	inline Quaternion(const T& s1, const T& s2, const T& s3, const T& s4) 
	{
		s = s1;
		v = Vector<T, 3>(s2, s3, s4);
	}

	inline Quaternion(const T& s1, const Vector<T, 3>& v1)
	{
		s = s1;
		v = v1;
	}

	inline T& scalar() 
	{ 
		return s; 
	}

	inline const T& scalar() const 
	{ 
		return s; 
	}

	inline void set_scalar(const T& qs)
	{ 
		s = qs; 
	}

	inline Vector<T, 3>& vector()
	{ 
		return v;
	}

	inline const Vector<T, 3>& vector() const 
	{
		return v; 
	}

	inline void set_vector(const Vector<T, 3>& qv)
	{ 
		v = qv; 
	}

	inline Quaternion<T> Inverse() const 
	{ 
		return Quaternion<T>(s, -v); 
	}

	inline Quaternion<T> operator*(const Quaternion<T>& q) const
	{
		return Quaternion<T>(
			s * q.s - Vector<T, 3>::DotProduct(v, q.v),
			s * q.v + q.s * v + Vector<T, 3>::CrossProduct(v, q.v));
	}

	inline Quaternion<T> operator*(const T& s1) const 
	{
		T angle;
		Vector<T, 3> axis;
		ToAngleAxis(&angle, &axis);
		angle *= s1;
		return Quaternion<T>(cos(0.5f * angle),
			axis.Normalized() * static_cast<T>(sin(0.5f * angle)));
	}

	inline Vector<T, 3> operator*(const Vector<T, 3>& v1) const 
	{
		T ss = s + s;
		return ss * Vector<T, 3>::CrossProduct(v, v1) + (ss * s - 1) * v1 +
			2 * Vector<T, 3>::DotProduct(v, v1) * v;
	}

	inline T Normalize() 
	{
		T length = sqrt(s * s + Vector<T, 3>::DotProduct(v, v));
		T scale = (1 / length);
		s *= scale;
		v *= scale;
		return length;
	}

	inline Quaternion<T> Normalized() const 
	{
		Quaternion<T> q(*this);
		q.Normalize();
		return q;
	}

	inline void ToAngleAxis(T* angle, Vector<T, 3>* axis) const 
	{
		*axis = s > 0 ? v : -v;
		*angle = 2 * atan2(axis->Normalize(), s > 0 ? s : -s);
	}

	inline Vector<T, 3> ToEulerAngles() const 
	{
		Matrix<T, 3> m(ToMatrix());
		T cos2 = m[0] * m[0] + m[1] * m[1];
		if (cos2 < 1e-6f) 
		{
			return Vector<T, 3>(
				0,
				m[2] < 0 ? static_cast<T>(0.5f * 3.1415926f) : static_cast<T>(-0.5f * 3.1415926f),
				-std::atan2(m[3], m[4]));
		}
		else 
		{
			return Vector<T, 3>(
				std::atan2(m[5], m[8]),
				std::atan2(-m[2], std::sqrt(cos2)),
				std::atan2(m[1], m[0]));
		}
	}

	inline Matrix<T, 3> ToMatrix() const 
	{
		const T x2 = v[0] * v[0], y2 = v[1] * v[1], z2 = v[2] * v[2];
		const T sx = s * v[0], sy = s * v[1], sz = s * v[2];
		const T xz = v[0] * v[2], yz = v[1] * v[2], xy = v[0] * v[1];
		return Matrix<T, 3>(1 - 2 * (y2 + z2), 2 * (xy + sz), 2 * (xz - sy),
			2 * (xy - sz), 1 - 2 * (x2 + z2), 2 * (sx + yz),
			2 * (sy + xz), 2 * (yz - sx), 1 - 2 * (x2 + y2));
	}

	inline Matrix<T, 4> ToMatrix4() const
	{
		const T x2 = v[0] * v[0], y2 = v[1] * v[1], z2 = v[2] * v[2];
		const T sx = s * v[0], sy = s * v[1], sz = s * v[2];
		const T xz = v[0] * v[2], yz = v[1] * v[2], xy = v[0] * v[1];
		return Matrix<T, 4>(
			1 - 2 * (y2 + z2), 2 * (xy + sz), 2 * (xz - sy), 0.0f,
			2 * (xy - sz), 1 - 2 * (x2 + z2), 2 * (sx + yz), 0.0f,
			2 * (sy + xz), 2 * (yz - sx), 1 - 2 * (x2 + y2), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
	}

	static Quaternion<T> FromAngleAxis(const T& angle, const Vector<T, 3>& axis) 
	{
		const T halfAngle = static_cast<T>(0.5) * angle;
		Vector<T, 3> localAxis(axis);
		return Quaternion<T>(
			cos(halfAngle),
			localAxis.Normalized() * static_cast<T>(sin(halfAngle)));
	}

	static Quaternion<T> FromEulerAngles(const Vector<T, 3>& angles) 
	{
		const Vector<T, 3> halfAngles(static_cast<T>(0.5) * angles[0],
			static_cast<T>(0.5) * angles[1],
			static_cast<T>(0.5) * angles[2]);
		const T sinx = std::sin(halfAngles[0]);
		const T cosx = std::cos(halfAngles[0]);
		const T siny = std::sin(halfAngles[1]);
		const T cosy = std::cos(halfAngles[1]);
		const T sinz = std::sin(halfAngles[2]);
		const T cosz = std::cos(halfAngles[2]);
		return Quaternion<T>(cosx * cosy * cosz + sinx * siny * sinz,
			sinx * cosy * cosz - cosx * siny * sinz,
			cosx * siny * cosz + sinx * cosy * sinz,
			cosx * cosy * sinz - sinx * siny * cosz);
	}

	static Quaternion<T> FromMatrix(const Matrix<T, 3>& m) 
	{
		const T trace = m(0, 0) + m(1, 1) + m(2, 2);
		if (trace > 0) 
		{
			const T s = sqrt(trace + 1) * 2;
			const T oneOverS = 1 / s;
			return Quaternion<T>(static_cast<T>(0.25) * s, (m[5] - m[7]) * oneOverS,
				(m[6] - m[2]) * oneOverS, (m[1] - m[3]) * oneOverS);
		}
		else if (m[0] > m[4] && m[0] > m[8]) 
		{
			const T s = sqrt(m[0] - m[4] - m[8] + 1) * 2;
			const T oneOverS = 1 / s;
			return Quaternion<T>((m[5] - m[7]) * oneOverS, static_cast<T>(0.25) * s,
				(m[3] + m[1]) * oneOverS, (m[6] + m[2]) * oneOverS);
		}
		else if (m[4] > m[8])
		{
			const T s = sqrt(m[4] - m[0] - m[8] + 1) * 2;
			const T oneOverS = 1 / s;
			return Quaternion<T>((m[6] - m[2]) * oneOverS, (m[3] + m[1]) * oneOverS,
				static_cast<T>(0.25) * s, (m[5] + m[7]) * oneOverS);
		}
		else 
		{
			const T s = sqrt(m[8] - m[0] - m[4] + 1) * 2;
			const T oneOverS = 1 / s;
			return Quaternion<T>((m[1] - m[3]) * oneOverS, (m[6] + m[2]) * oneOverS,
				(m[5] + m[7]) * oneOverS, static_cast<T>(0.25) * s);
		}
	}

	static Quaternion<T> FromMatrix(const Matrix<T, 4>& m)
	{
		const T trace = m(0, 0) + m(1, 1) + m(2, 2);
		if (trace > 0) 
		{
			const T s = sqrt(trace + 1) * 2;
			const T oneOverS = 1 / s;
			return Quaternion<T>(static_cast<T>(0.25) * s, (m[6] - m[9]) * oneOverS,
				(m[8] - m[2]) * oneOverS, (m[1] - m[4]) * oneOverS);
		}
		else if (m[0] > m[5] && m[0] > m[10]) 
		{
			const T s = sqrt(m[0] - m[5] - m[10] + 1) * 2;
			const T oneOverS = 1 / s;
			return Quaternion<T>((m[6] - m[9]) * oneOverS, static_cast<T>(0.25) * s,
				(m[4] + m[1]) * oneOverS, (m[8] + m[2]) * oneOverS);
		}
		else if (m[5] > m[10])
		{
			const T s = sqrt(m[5] - m[0] - m[10] + 1) * 2;
			const T oneOverS = 1 / s;
			return Quaternion<T>((m[8] - m[2]) * oneOverS, (m[4] + m[1]) * oneOverS,
				static_cast<T>(0.25) * s, (m[6] + m[9]) * oneOverS);
		}
		else 
		{
			const T s = sqrt(m[10] - m[0] - m[5] + 1) * 2;
			const T oneOverS = 1 / s;
			return Quaternion<T>((m[1] - m[4]) * oneOverS, (m[8] + m[2]) * oneOverS,
				(m[6] + m[9]) * oneOverS, static_cast<T>(0.25) * s);
		}
	}

	static inline T DotProduct(const Quaternion<T>& q1, const Quaternion<T>& q2) 
	{
		return q1.s * q2.s + Vector<T, 3>::DotProduct(q1.v_, q2.v_);
	}

	static inline Quaternion<T> Slerp(const Quaternion<T>& q1, const Quaternion<T>& q2, const T& s1) 
	{
		if (q1.s * q2.s + Vector<T, 3>::DotProduct(q1.v, q2.v) > 0.999999f)
		{
			return Quaternion<T>(q1.s * (1 - s1) + q2.s * s1,
				q1.v * (1 - s1) + q2.v * s1);
		}
		return q1 * ((q1.Inverse() * q2) * s1);
	}

	inline T& operator[](const int i)
	{
		if (i == 0)
		{
			return s;
		}
		return v[i - 1];
	}

	inline const T& operator[](const int i) const 
	{
		return const_cast<Quaternion<T>*>(this)->operator[](i);
	}

	static inline Vector<T, 3> PerpendicularVector(const Vector<T, 3>& v) 
	{

		Vector<T, 3> axis = Vector<T, 3>::CrossProduct(
			Vector<T, 3>(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0)),
			v);
		if (axis.LengthSquared() < static_cast<T>(0.05)) {
			axis = Vector<T, 3>::CrossProduct(
				Vector<T, 3>(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0)),
				v);
		}
		return axis;
	}

	static inline Quaternion<T> RotateFromToWithAxis(
		const Vector<T, 3>& v1, const Vector<T, 3>& v2,
		const Vector<T, 3>& preferred_axis)
	{
		Vector<T, 3> start = v1.Normalized();
		Vector<T, 3> end = v2.Normalized();

		T dot_product = Vector<T, 3>::DotProduct(start, end);

		if (dot_product >= static_cast<T>(0.99999847691)) {
			return Quaternion<T>::identity;
		}

		if (dot_product <= static_cast<T>(-0.99999847691)) {
			return Quaternion<T>(static_cast<T>(0), preferred_axis);
		}

		Vector<T, 3> cross_product = Vector<T, 3>::CrossProduct(start, end);

		return Quaternion<T>(static_cast<T>(1.0) + dot_product, cross_product)
			.Normalized();
	}

	static inline Quaternion<T> RotateFromTo(const Vector<T, 3>& v1,
		const Vector<T, 3>& v2)
	{
		Vector<T, 3> start = v1.Normalized();
		Vector<T, 3> end = v2.Normalized();

		T dot_product = Vector<T, 3>::DotProduct(start, end);
		if (dot_product >= static_cast<T>(0.99999847691)) {
			return Quaternion<T>::identity;
		}

		if (dot_product <= static_cast<T>(-0.99999847691)) {
			return Quaternion<T>(0, PerpendicularVector(start));
		}
		Vector<T, 3> cross_product = Vector<T, 3>::CrossProduct(start, end);

		return Quaternion<T>(static_cast<T>(1.0) + dot_product, cross_product)
			.Normalized();
	}

	static Quaternion<T> identity;

private:
	T s;
	Vector<T, 3> v;
};

template <typename T>
Quaternion<T> Quaternion<T>::identity = Quaternion<T>(1, 0, 0, 0);

template <class T>
inline Quaternion<T> operator*(const T& s, const Quaternion<T>& q) {
	return q * s;
}