#pragma once
#include <Core/Mathematics/Vector.h>

NAMESPACE_MENGINE_BEGIN

class Vector3f;
class __declspec(align(16)) Matrix4f
{
public:
	Matrix4f();
	Matrix4f(_F32 _00, _F32 _01, _F32 _02, _F32 _03,
			 _F32 _10, _F32 _11, _F32 _12, _F32 _13,
			 _F32 _20, _F32 _21, _F32 _22, _F32 _23,
			 _F32 _30, _F32 _31, _F32 _32, _F32 _33);
	Matrix4f(const __m128& _0, const __m128& _1, const __m128& _2, const __m128& _3);
	~Matrix4f();

	Matrix4f& operator =(const Matrix4f& Matrix);

	_F32* GetDataAddress() const { return const_cast<_F32*>(&f[0][0]); }
	const _F32* operator[] (_I32 pos) const;

	Matrix4f operator +(const Matrix4f& Matrix) const;
	Matrix4f operator -(const Matrix4f& Matrix) const;
	Matrix4f operator *(const Matrix4f& Matrix) const;
	Matrix4f operator *(_F32 value) const;
	Matrix4f operator /(_F32 value) const;

	Matrix4f operator -(void);
	Matrix4f& operator +=(const Matrix4f& Matrix);
	Matrix4f& operator -=(const Matrix4f& Matrix);
	Matrix4f& operator *=(const Matrix4f& Matrix);

	Matrix4f Transpose() const;
	Matrix4f Inverse() const;
	void MakeZero();
	void MakeIdentity();

	void RotationX(_F32 radians);
	void RotationY(_F32 radians);
	void RotationZ(_F32 radians);
	void Scale(_F32 _x, _F32 _y, _F32 _z);
	void Translate(_F32 _x, _F32 _y, _F32 _z);

	static Matrix4f RotationMatrixXYZ(_F32 radiansX, _F32 radiansY, _F32 radiansZ);
	static Matrix4f RotationMatrixXYZ(Vector3f rotation);
	static Matrix4f RotationMatrixX(_F32 radians);
	static Matrix4f RotationMatrixY(_F32 radians);
	static Matrix4f RotationMatrixZ(_F32 radians);
	static Matrix4f ScaleMatrixXYZ(_F32 _x, _F32 _y, _F32 _z);
	static Matrix4f ScaleMatrixXYZ(Vector3f scale);
	static Matrix4f TranslationMatrix(_F32 _x, _F32 _y, _F32 _z);
	static Matrix4f TranslationMatrix(Vector3f position);
	static Matrix4f Zero();
	static Matrix4f Identity();
	static Matrix4f LookAtLHMatrix(Vector3f& eye, Vector3f& at, Vector3f& up);
	static Matrix4f LookToLHMatrix(Vector3f& eye, Vector3f& to, Vector3f& up);
	static Matrix4f PerspectiveFovLHMatrix(_F32 fovy, _F32 aspect, _F32 zn, _F32 zf);
	//static Matrix4f OrthographicLHMatrix(float zn, float zf, float width, float height);

private:
	__declspec(align(16)) union 
	{
		__m128 m_Row[4];
		_F32 f[4][4];
	};
	
};

NAMESPACE_MENGINE_END