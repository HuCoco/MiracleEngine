#pragma once
#include <Core/Mathematics/Vector.h>

NAMESPACE_MENGINE_BEGIN

class Vector2f
{
public:
	Vector2f();
	Vector2f(_F32 _x, _F32 _y);

	~Vector2f();

	Vector2f& operator =(const Vector2f& Vector);

	_F32 operator[] (_I32 pos) const;
	_F32& operator[] (_I32 pos);

	Vector2f operator +(const Vector2f& Vector) const;
	Vector2f operator -(const Vector2f& Vector) const;
	Vector2f operator *(const Vector2f& Vector) const;
	Vector2f operator /(const Vector2f& Vector) const;
	Vector2f operator *(_F32 value) const;
	Vector2f operator /(_F32 value) const;
	
	Vector2f operator -(void);
	Vector2f& operator +=(const Vector2f& Vector);
	Vector2f& operator -=(const Vector2f& Vector);
	Vector2f& operator *=(const Vector2f& Vector);
	Vector2f& operator /=(const Vector2f& Vector);

	_F32 Length();
	void Zero();
	void Normalize();

private:
#if defined (MATH_SSE)
	Vector2f(__m128 a_Result);
#endif
	union
	{
		struct
		{
			union
			{
				_F32 x;
				_F32 u;
			};

			union
			{
				_F32 y;
				_F32 v;
			};
		};
	
		_F32 f[2];
	};
};

NAMESPACE_MENGINE_END