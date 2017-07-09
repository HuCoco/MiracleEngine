#pragma once
#include <Core/Mathematics/Vector.h>
#include <Core/Mathematics/Vector3f.h>

NAMESPACE_MENGINE_BEGIN

class Quaternion
{
public:
	Quaternion();
	Quaternion(_F32 _w,_F32 _x,_F32 _y,_F32 _z);
	Quaternion(_F32 _angle,const Vector3f& _n);
	Quaternion(const Vector3f& _v);
	Quaternion Conjugate() const;
	Quaternion Inverse() const;
	
	_F32 Length() const;
	_F32 LengthSquared() const;
	//float Dot(const Quaternion& a) const;
	Quaternion& operator=(const Quaternion& a);
	//Quaternion operator+(const Quaternion& a) const;
	//Quaternion operator-(const Quaternion& a) const;
	Quaternion operator*(const Quaternion& a) const;
	//Quaternion operator/(const Quaternion& a) const;
	//Quaternion operator*(const float& real) const;
	Quaternion operator/(const _F32& real) const;

	~Quaternion();
	static Quaternion Identity();
	static Vector3f Rotation(Quaternion* p, _U32 num_of_p, const Vector3f& v);
private:

#if defined(MATH_SSE)
	Quaternion(__m128 _vec);
#endif

	union
	{
		struct
		{
			_F32 w;
			_F32 x;
			_F32 y;
			_F32 z;
		};

		struct 
		{
			_F32 w;
			Vector3f v;
		};

		_F32 f[4];
	};
};

NAMESPACE_MENGINE_END