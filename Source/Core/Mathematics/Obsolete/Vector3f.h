#pragma once
#include <Core/Mathematics/Vector.h>

NAMESPACE_MENGINE_BEGIN

class Vector3f
{
public:
	Vector3f();
	Vector3f(_F32 _x, _F32 _y, _F32 _z);
	~Vector3f();

	Vector3f& operator =(const Vector3f& Vector);

	_F32 operator[] (_I32 pos) const;
	_F32& operator[] (_I32 pos);

	Vector3f operator +(const Vector3f& Vector) const;
	Vector3f operator -(const Vector3f& Vector) const;
	Vector3f operator *(const Vector3f& Vector) const;
	Vector3f operator /(const Vector3f& Vector) const;
	Vector3f operator *(_F32 value) const;
	Vector3f operator /(_F32 value) const;

	Vector3f operator -(void);
	Vector3f& operator +=(const Vector3f& Vector);
	Vector3f& operator -=(const Vector3f& Vector);
	Vector3f& operator *=(const Vector3f& Vector);
	Vector3f& operator /=(const Vector3f& Vector);
	bool operator ==(const Vector3f& Vector);
	Vector3f Cross(const Vector3f& Vector) const;
	_F32 Dot(const Vector3f& Vector)const;
	_F32 Length();
	void Zero();
	void Normalize();

private:
#if defined (MATH_SSE)
	Vector3f(__m128 a_Result);
#endif
	union
	{
		struct
		{
			_F32 x;
			_F32 y;
			_F32 z;
		};

		_F32 f[3];
	};
};

NAMESPACE_MENGINE_END