#pragma once
#include <Core/Mathematics/Vector.h>

NAMESPACE_MENGINE_BEGIN

class Vector4f
{
public:
	Vector4f();
	~Vector4f();
	Vector4f(_F32 _x, _F32 _y = 0.0f, _F32 _z = 0.0f,_F32 _w = 0.0f);

	Vector4f& operator =(const Vector4f& Vector);

	_F32 operator[] (_I32 pos) const;
	_F32& operator[] (_I32 pos);

	Vector4f operator +(const Vector4f& Vector) const;
	Vector4f operator -(const Vector4f& Vector) const;
	Vector4f operator *(const Vector4f& Vector) const;
	Vector4f operator /(const Vector4f& Vector) const;
	Vector4f operator *(_F32 value) const;
	Vector4f operator /(_F32 value) const;

	Vector4f operator -(void);
	Vector4f& operator +=(const Vector4f& Vector);
	Vector4f& operator -=(const Vector4f& Vector);
	Vector4f& operator *=(const Vector4f& Vector);
	Vector4f& operator /=(const Vector4f& Vector);

	_F32 Length();
	void Zero();
	void Normalize();

private:
#if defined (MATH_SSE)
	Vector4f(__m128 a_Result);
#endif
	union
	{
		struct
		{
			_F32 x;
			_F32 y;
			_F32 z;
			_F32 w;
		};

		_F32 f[4];
	};
};

NAMESPACE_MENGINE_END