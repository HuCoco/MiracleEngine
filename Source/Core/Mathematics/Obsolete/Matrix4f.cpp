#include <Core/Mathematics/Matrix4f.h>
#include <Core/Mathematics/Vector3f.h>
#include <Core/Mathematics/MathUtils.h>

NAMESPACE_MENGINE_BEGIN

Matrix4f::Matrix4f()
{
#if defined (MATH_SSE)
	for (_I32 i = 0; i < 4; ++i)
	{
		m_Row[i] = _mm_setzero_ps();
	}
#else
	for (_I32 i = 0; i < 4; ++i)
	{
		for (_I32 j = 0; j < 4; ++j)
		{
			f[i][j] = 0.0f;
		}
	}
#endif
}


Matrix4f::Matrix4f( _F32 _00, _F32 _01, _F32 _02, _F32 _03, 
					_F32 _10, _F32 _11, _F32 _12, _F32 _13,
					_F32 _20, _F32 _21, _F32 _22, _F32 _23,
					_F32 _30, _F32 _31, _F32 _32, _F32 _33)
{
#if defined (MATH_SSE)
	m_Row[0] = _mm_setr_ps(_00, _01, _02, _03);
	m_Row[1] = _mm_setr_ps(_10, _11, _12, _13);
	m_Row[2] = _mm_setr_ps(_20, _21, _22, _23);
	m_Row[3] = _mm_setr_ps(_30, _31, _32, _33);
#else
	f[0][0] = _00;
	f[0][1] = _01;
	f[0][2] = _02;
	f[0][3] = _03;

	f[1][0] = _10;
	f[1][1] = _11;
	f[1][2] = _12;
	f[1][3] = _13;

	f[2][0] = _20;
	f[2][1] = _21;
	f[2][2] = _22;
	f[2][3] = _23;

	f[3][0] = _30;
	f[3][1] = _31;
	f[3][2] = _32;
	f[3][3] = _33;
#endif
}

Matrix4f::Matrix4f(const __m128& _0, const __m128& _1, const __m128& _2, const __m128& _3)
{
	m_Row[0] = _0;
	m_Row[1] = _1;
	m_Row[2] = _2;
	m_Row[3] = _3;
}

Matrix4f::~Matrix4f()
{

}

const _F32* Matrix4f::operator[](_I32 pos) const 
{
	assert((pos >= 0 || pos < 4) &&  "Matrix4f error : over index");
	return f[pos];
}



Matrix4f Matrix4f::Transpose() const 
{
#if defined (MATH_SSE)
	__m128 row0 = _mm_setr_ps(f[0][0], f[0][1], f[0][2], f[0][3]);
	__m128 row1 = _mm_setr_ps(f[1][0], f[1][1], f[1][2], f[1][3]);
	__m128 row2 = _mm_setr_ps(f[2][0], f[2][1], f[2][2], f[2][3]);
	__m128 row3 = _mm_setr_ps(f[3][0], f[3][1], f[3][2], f[3][3]);

	__m128 tmp0 = _mm_shuffle_ps(row0, row1, 0x44);
	__m128 tmp2 = _mm_shuffle_ps(row0, row1, 0xEE);
	__m128 tmp1 = _mm_shuffle_ps(row2, row3, 0x44);
	__m128 tmp3 = _mm_shuffle_ps(row2, row3, 0xEE);

	__m128 result[4];
	result[0] = _mm_shuffle_ps(tmp0, tmp1, 0x88);
	result[1] = _mm_shuffle_ps(tmp0, tmp1, 0xDD);
	result[2] = _mm_shuffle_ps(tmp2, tmp3, 0x88);
	result[3] = _mm_shuffle_ps(tmp2, tmp3, 0xDD);
	return Matrix4f(result[0], result[1], result[2], result[3]);
#else
	float result[4][4];

	for (_I32 i = 0; i < 4; ++i)
	{
		for (_I32 j = 0; j < 4; ++j)
		{
			result[j][i] = f[i][j];
		}
	}
	return Matrix4f(
		result[0][0], result[0][1], result[0][2], result[0][3],
		result[1][0], result[1][1], result[1][2], result[1][3],
		result[2][0], result[2][1], result[2][2], result[2][3],
		result[3][0], result[3][1], result[3][2], result[3][3]);
#endif

}

MEngine::Matrix4f MEngine::Matrix4f::Inverse() const
{

	float fA0 = f[0][0] * f[1][1] - f[0][1] * f[1][0];
	float fA1 = f[0][0] * f[1][2] - f[0][2] * f[1][0];
	float fA2 = f[0][0] * f[1][3] - f[0][3] * f[1][0];
	float fA3 = f[0][1] * f[1][2] - f[0][2] * f[1][1];
	float fA4 = f[0][1] * f[1][3] - f[0][3] * f[1][1];
	float fA5 = f[0][2] * f[1][3] - f[0][3] * f[1][2];
	float fB0 = f[2][0] * f[3][1] - f[2][1] * f[3][0];
	float fB1 = f[2][0] * f[3][2] - f[2][2] * f[3][0];
	float fB2 = f[2][0] * f[3][3] - f[2][3] * f[3][0];
	float fB3 = f[2][1] * f[3][2] - f[2][2] * f[3][1];
	float fB4 = f[2][1] * f[3][3] - f[2][3] * f[3][1];
	float fB5 = f[2][2] * f[3][3] - f[2][3] * f[3][2];

	float fDet = fA0*fB5 - fA1*fB4 + fA2*fB3 + fA3*fB2 - fA4*fB1 + fA5*fB0;
	if (fDet <= 0.0001 && fDet >= -0.0001)
	{
		return Matrix4f::Zero();
	}


	Matrix4f kInv;
	kInv.f[0][0] = +f[1][1] * fB5 - f[1][2] * fB4 + f[1][3] * fB3;
	kInv.f[1][0] = -f[1][0] * fB5 + f[1][2] * fB2 - f[1][3] * fB1;
	kInv.f[2][0] = +f[1][0] * fB4 - f[1][1] * fB2 + f[1][3] * fB0;
	kInv.f[3][0] = -f[1][0] * fB3 + f[1][1] * fB1 - f[1][2] * fB0;
	kInv.f[0][1] = -f[0][1] * fB5 + f[0][2] * fB4 - f[0][3] * fB3;
	kInv.f[1][1] = +f[0][0] * fB5 - f[0][2] * fB2 + f[0][3] * fB1;
	kInv.f[2][1] = -f[0][0] * fB4 + f[0][1] * fB2 - f[0][3] * fB0;
	kInv.f[3][1] = +f[0][0] * fB3 - f[0][1] * fB1 + f[0][2] * fB0;
	kInv.f[0][2] = +f[3][1] * fA5 - f[3][2] * fA4 + f[3][3] * fA3;
	kInv.f[1][2] = -f[3][0] * fA5 + f[3][2] * fA2 - f[3][3] * fA1;
	kInv.f[2][2] = +f[3][0] * fA4 - f[3][1] * fA2 + f[3][3] * fA0;
	kInv.f[3][2] = -f[3][0] * fA3 + f[3][1] * fA1 - f[3][2] * fA0;
	kInv.f[0][3] = -f[2][1] * fA5 + f[2][2] * fA4 - f[2][3] * fA3;
	kInv.f[1][3] = +f[2][0] * fA5 - f[2][2] * fA2 + f[2][3] * fA1;
	kInv.f[2][3] = -f[2][0] * fA4 + f[2][1] * fA2 - f[2][3] * fA0;
	kInv.f[3][3] = +f[2][0] * fA3 - f[2][1] * fA1 + f[2][2] * fA0;

	float fInvDet = ((float)1.0) / fDet;
	for (int iRow = 0; iRow < 4; iRow++)
	{
		for (int iCol = 0; iCol < 4; iCol++)
			kInv.f[iRow][iCol] *= fInvDet;
	}

	return(kInv);
}

void Matrix4f::MakeZero()
{
#if defined (MATH_SSE)
	for (_I32 i = 0; i < 4; ++i)
	{
		m_Row[i] = _mm_setzero_ps();
	}
#else
	for (_I32 i = 0; i < 4; ++i)
	{
		for (_I32 j = 0; j < 4; ++j)
		{
			f[i][j] = 0.0f;
		}
	}
#endif
}

void Matrix4f::MakeIdentity()
{
	MakeZero();
	f[0][0] = 1.0f;
	f[1][1] = 1.0f;
	f[2][2] = 1.0f;
	f[3][3] = 1.0f;
}

void Matrix4f::RotationX(_F32 radians)
{
	MakeIdentity();
	_F32 fSin = sinf(MathUtils::Angle2Radian(radians));
	_F32 fCos = cosf(MathUtils::Angle2Radian(radians));

	f[1][1] = fCos;
	f[1][2] = fSin;
	f[2][1] = -fSin;
	f[2][2] = fCos;
}

void Matrix4f::RotationY(_F32 radians)
{
	MakeIdentity();
	_F32 fSin = sinf(MathUtils::Angle2Radian(radians));
	_F32 fCos = cosf(MathUtils::Angle2Radian(radians));

	f[0][0] = fCos;
	f[0][2] = -fSin;
	f[2][0] = fSin;
	f[2][2] = fCos;
}

void Matrix4f::RotationZ(_F32 radians)
{
	MakeIdentity();
	_F32 fSin = sinf(MathUtils::Angle2Radian(radians));
	_F32 fCos = cosf(MathUtils::Angle2Radian(radians));

	f[0][0] = fCos;
	f[0][1] = fSin;
	f[1][0] = -fSin;
	f[1][1] = fCos;
}


void Matrix4f::Scale(_F32 _x, _F32 _y, _F32 _z)
{
	MakeZero();
	f[0][0] = _x;
	f[1][1] = _y;
	f[2][2] = _z;
	f[3][3] = 1.0f;
}

void Matrix4f::Translate(_F32 _x, _F32 _y, _F32 _z)
{
	MakeIdentity();
	f[3][0] = _x;
	f[3][1] = _y;
	f[3][2] = _z;

}

Matrix4f Matrix4f::RotationMatrixXYZ(_F32 radiansX, _F32 radiansY, _F32 radiansZ)
{
	return Matrix4f::RotationMatrixX(radiansX) * Matrix4f::RotationMatrixY(radiansY) *Matrix4f::RotationMatrixZ(radiansZ);
}

MEngine::Matrix4f MEngine::Matrix4f::RotationMatrixXYZ(Vector3f rotation)
{
	return RotationMatrixXYZ(rotation[0], rotation[1], rotation[2]);
}

Matrix4f Matrix4f::RotationMatrixX(_F32 radians)
{
	Matrix4f ret;
	ret.RotationX(radians);
	return ret;
}

Matrix4f Matrix4f::RotationMatrixY(_F32 radians)
{
	Matrix4f ret;
	ret.RotationY(radians);
	return ret;
}

Matrix4f Matrix4f::RotationMatrixZ(_F32 radians)
{
	Matrix4f ret;
	ret.RotationZ(radians);
	return ret;
}

Matrix4f Matrix4f::ScaleMatrixXYZ(_F32 _x, _F32 _y, _F32 _z)
{
	Matrix4f ret;
	ret.Scale(_x, _y, _z);
	return ret;
}

MEngine::Matrix4f MEngine::Matrix4f::ScaleMatrixXYZ(Vector3f scale)
{
	return ScaleMatrixXYZ(scale[0], scale[1], scale[2]);
}

Matrix4f Matrix4f::TranslationMatrix(_F32 _x, _F32 _y, _F32 _z)
{
	Matrix4f ret;
	ret.Translate(_x, _y, _z);
	return ret;
}

MEngine::Matrix4f MEngine::Matrix4f::TranslationMatrix(Vector3f position)
{
	return TranslationMatrix(position[0], position[1], position[2]);
}

Matrix4f Matrix4f::Zero()
{
	Matrix4f ret;
	ret.MakeZero();
	return ret;
}

Matrix4f Matrix4f::Identity()
{
	Matrix4f ret;
	ret.MakeIdentity();
	return ret;
}

Matrix4f Matrix4f::LookAtLHMatrix(Vector3f& eye, Vector3f& at, Vector3f& up)
{
	Matrix4f ret;

	Vector3f zaxis = at - eye;
	zaxis.Normalize();

	Vector3f xaxis = up.Cross(zaxis);
	xaxis.Normalize();

	Vector3f yaxis = zaxis.Cross(xaxis);

	ret.f[0][0] = xaxis[0];
	ret.f[0][1] = yaxis[0];
	ret.f[0][2] = zaxis[0];
	ret.f[0][3] = 0.0f;

	ret.f[1][0] = xaxis[1];
	ret.f[1][1] = yaxis[1];
	ret.f[1][2] = zaxis[1];
	ret.f[1][3] = 0.0f;

	ret.f[2][0] = xaxis[2];
	ret.f[2][1] = yaxis[2];
	ret.f[2][2] = zaxis[2];
	ret.f[2][3] = 0.0f;

	ret.f[3][0] = -(xaxis.Dot(eye));
	ret.f[3][1] = -(yaxis.Dot(eye));
	ret.f[3][2] = -(zaxis.Dot(eye));
	ret.f[3][3] = 1.0f;

	return ret;
}

MEngine::Matrix4f MEngine::Matrix4f::LookToLHMatrix(Vector3f& eye, Vector3f& to, Vector3f& up)
{
	Matrix4f ret;

	Vector3f zaxis = to;
	zaxis.Normalize();

	Vector3f xaxis = up.Cross(zaxis);
	xaxis.Normalize();

	Vector3f yaxis = zaxis.Cross(xaxis);

	ret.f[0][0] = xaxis[0];
	ret.f[0][1] = yaxis[0];
	ret.f[0][2] = zaxis[0];
	ret.f[0][3] = 0.0f;

	ret.f[1][0] = xaxis[1];
	ret.f[1][1] = yaxis[1];
	ret.f[1][2] = zaxis[1];
	ret.f[1][3] = 0.0f;

	ret.f[2][0] = xaxis[2];
	ret.f[2][1] = yaxis[2];
	ret.f[2][2] = zaxis[2];
	ret.f[2][3] = 0.0f;

	ret.f[3][0] = -(xaxis.Dot(eye));
	ret.f[3][1] = -(yaxis.Dot(eye));
	ret.f[3][2] = -(zaxis.Dot(eye));
	ret.f[3][3] = 1.0f;

	return ret;
}

Matrix4f Matrix4f::PerspectiveFovLHMatrix(_F32 fovy, _F32 aspect, _F32 zn, _F32 zf)
{
	Matrix4f ret;

	_F32 tanY = tan(fovy / 2.0f);
	if (0.0f == tanY) tanY = 0.001f;
	_F32 yScale = 1.0f / tanY;

	if (0.0f == aspect) aspect = 0.001f;
	_F32 xScale = yScale / aspect;

	ret.f[0][0] = xScale;
	ret.f[0][1] = 0.0f;
	ret.f[0][2] = 0.0f;
	ret.f[0][3] = 0.0f;

	ret.f[1][0] = 0.0f;
	ret.f[1][1] = yScale;
	ret.f[1][2] = 0.0f;
	ret.f[1][3] = 0.0f;

	ret.f[2][0] = 0.0f;
	ret.f[2][1] = 0.0f;
	ret.f[2][2] = zf / (zf - zn);
	ret.f[2][3] = 1.0f;

	ret.f[3][0] = 0.0f;
	ret.f[3][1] = 0.0f;
	ret.f[3][2] = -zn*zf / (zf - zn);
	ret.f[3][3] = 0.0f;

	return ret;
}

Matrix4f& Matrix4f::operator*=(const Matrix4f& Matrix)
{
#if defined (MATH_SSE)
	__m128 xmm0;
	__m128 xmm1;
	__m128 xmm2;
	__m128 xmm3;
	__m128 xmm4 = Matrix.m_Row[0];
	__m128 xmm5 = Matrix.m_Row[1];
	__m128 xmm6 = Matrix.m_Row[2];
	__m128 xmm7 = Matrix.m_Row[3];
	for (_I32 i = 0; i < 4; ++i)
	{
		xmm0 = xmm1 = xmm2 = xmm3 = m_Row[i];
		xmm0 = _mm_shuffle_ps(xmm0, xmm0, 0b00000000);
		xmm1 = _mm_shuffle_ps(xmm1, xmm1, 0b01010101);
		xmm2 = _mm_shuffle_ps(xmm2, xmm2, 0b10101010);
		xmm3 = _mm_shuffle_ps(xmm3, xmm3, 0b11111111);

		xmm0 = _mm_mul_ps(xmm0, xmm4);
		xmm1 = _mm_mul_ps(xmm1, xmm5);
		xmm2 = _mm_mul_ps(xmm2, xmm6);
		xmm3 = _mm_mul_ps(xmm3, xmm7);

		xmm0 = _mm_add_ps(xmm0, xmm1);
		xmm2 = _mm_add_ps(xmm2, xmm3);
		xmm0 = _mm_add_ps(xmm0, xmm2);

		m_Row[i] = xmm0;
	}

#else
	for (_I32 i = 0; i < 4; ++i)
	{
		for (_I32 j = 0; j < 4; ++j)
		{
			_F32 add_result = 0.0f;
			for (_I32 k = 0; k < 4; ++k)
			{
				add_result += f[i][k] * Matrix.f[k][j];
			}
			f[i][j] = add_result;
		}
	}
#endif
	return (*this);
}

Matrix4f& Matrix4f::operator-=(const Matrix4f& Matrix)
{
#if defined (MATH_SSE)
	for (_I32 i = 0; i < 4; ++i)
	{
		m_Row[i] = _mm_sub_ps(m_Row[i], Matrix.m_Row[i]);
	}
#else
	for (_I32 i = 0; i < 4; ++i)
	{
		for (_I32 j = 0; j < 4; ++j)
		{
			f[i][j] -= Matrix.f[i][j];
	}
}
#endif
	return (*this);
}

Matrix4f& Matrix4f::operator+=(const Matrix4f& Matrix)
{
#if defined (MATH_SSE)
	for (_I32 i = 0; i < 4; ++i)
	{
		m_Row[i] = _mm_add_ps(m_Row[i], Matrix.m_Row[i]);
	}
#else
	for (_I32 i = 0; i < 4; ++i)
	{
		for (_I32 j = 0; j < 4; ++j)
		{
			f[i][j] += Matrix.f[i][j];
		}
	}
#endif
	return (*this);
}

Matrix4f Matrix4f::operator-(void)
{
#if defined (MATH_SSE)
	__m128 Minus = _mm_set_ps1(-1.0f);
	__m128 result[4];
	for (_I32 i = 0; i < 4; ++i)
	{
		result[i] = _mm_mul_ps(m_Row[i], Minus);
	}
	return Matrix4f(result[0], result[1], result[2], result[3]);
#else
	float result[4][4];
	for (_I32 i = 0; i < 4; ++i)
	{
		for (_I32 j = 0; j < 4; ++j)
		{
			result[i][j] = -f[i][j];
		}
	}
	return Matrix4f(
		result[0][0], result[0][1], result[0][2], result[0][3],
		result[1][0], result[1][1], result[1][2], result[1][3],
		result[2][0], result[2][1], result[2][2], result[2][3],
		result[3][0], result[3][1], result[3][2], result[3][3]);
#endif

}

Matrix4f Matrix4f::operator/(_F32 value) const
{
#if defined (MATH_SSE)
	__m128 Divisor = _mm_set_ps1(value);
	__m128 result[4];
	for (_I32 i = 0; i < 4; ++i)
	{
		result[i] = _mm_div_ps(m_Row[i], Divisor);
	}
	return Matrix4f(result[0], result[1], result[2], result[3]);
#else
	float result[4][4];
	for (_I32 i = 0; i < 4; ++i)
	{
		for (_I32 j = 0; j < 4; ++j)
		{
			result[i][j] = f[i][j] / value;
		}
	}
	return Matrix4f(
		result[0][0], result[0][1], result[0][2], result[0][3],
		result[1][0], result[1][1], result[1][2], result[1][3],
		result[2][0], result[2][1], result[2][2], result[2][3],
		result[3][0], result[3][1], result[3][2], result[3][3]);
#endif

}

Matrix4f Matrix4f::operator*(_F32 value) const
{
#if defined (MATH_SSE)
	__m128 multiplier = _mm_set_ps1(value);
	__m128 result[4];
	for (_I32 i = 0; i < 4; ++i)
	{
		result[i] = _mm_mul_ps(m_Row[i], multiplier);
	}
	return Matrix4f(result[0], result[1], result[2], result[3]);
#else
	float result[4][4];
	for (_I32 i = 0; i < 4; ++i)
	{
		for (_I32 j = 0; j < 4; ++j)
		{
			result[i][j] = f[i][j] * value;
		}
	}
	return Matrix4f(
		result[0][0], result[0][1], result[0][2], result[0][3],
		result[1][0], result[1][1], result[1][2], result[1][3],
		result[2][0], result[2][1], result[2][2], result[2][3],
		result[3][0], result[3][1], result[3][2], result[3][3]);
#endif

}


Matrix4f Matrix4f::operator*(const Matrix4f& Matrix) const
{
#if defined (MATH_SSE)
	__m128 result[4];
	__m128 xmm0;
	__m128 xmm1;
	__m128 xmm2;
	__m128 xmm3;
	__m128 xmm4 = Matrix.m_Row[0];
	__m128 xmm5 = Matrix.m_Row[1];
	__m128 xmm6 = Matrix.m_Row[2];
	__m128 xmm7 = Matrix.m_Row[3];
	for (_I32 i = 0; i < 4; ++i)
	{
		xmm0 = xmm1 = xmm2 = xmm3 = m_Row[i];
		xmm0 = _mm_shuffle_ps(xmm0, xmm0, 0b00000000);
		xmm1 = _mm_shuffle_ps(xmm1, xmm1, 0b01010101);
		xmm2 = _mm_shuffle_ps(xmm2, xmm2, 0b10101010);
		xmm3 = _mm_shuffle_ps(xmm3, xmm3, 0b11111111);

		xmm0 = _mm_mul_ps(xmm0, xmm4);
		xmm1 = _mm_mul_ps(xmm1, xmm5);
		xmm2 = _mm_mul_ps(xmm2, xmm6);
		xmm3 = _mm_mul_ps(xmm3, xmm7);

		xmm0 = _mm_add_ps(xmm0, xmm1);
		xmm2 = _mm_add_ps(xmm2, xmm3);
		xmm0 = _mm_add_ps(xmm0, xmm2);

		result[i] = xmm0;
	}
	return Matrix4f(result[0], result[1], result[2], result[3]);
#else
	float result[4][4];
	for (_I32 i = 0; i < 4; ++i)
	{
		for (_I32 j = 0; j < 4; ++j)
		{
			_F32 add_result = 0.0f;
			for (_I32 k = 0; k < 4; ++k)
			{
				add_result += f[i][k] * Matrix.f[k][j];
			}
			result[i][j] = add_result;
		}
	}
	return Matrix4f(
		result[0][0], result[0][1], result[0][2], result[0][3],
		result[1][0], result[1][1], result[1][2], result[1][3],
		result[2][0], result[2][1], result[2][2], result[2][3],
		result[3][0], result[3][1], result[3][2], result[3][3]);
#endif

}

Matrix4f Matrix4f::operator-(const Matrix4f& Matrix) const
{
#if defined (MATH_SSE)
	__m128 result[4];
	for (_I32 i = 0; i < 4; ++i)
	{
		result[i] = _mm_sub_ps(m_Row[i], Matrix.m_Row[i]);
	}
	return Matrix4f(result[0], result[1], result[2], result[3]);
#else
	float result[4][4];
	for (_I32 i = 0; i < 4; ++i)
	{
		for (_I32 j = 0; j < 4; ++j)
		{
			result[i][j] = f[i][j] - Matrix.f[i][j];
		}
	}
	return Matrix4f(
		result[0][0], result[0][1], result[0][2], result[0][3],
		result[1][0], result[1][1], result[1][2], result[1][3],
		result[2][0], result[2][1], result[2][2], result[2][3],
		result[3][0], result[3][1], result[3][2], result[3][3]);
#endif

}

Matrix4f Matrix4f::operator+(const Matrix4f& Matrix) const
{
#if defined (MATH_SSE)
	__m128 result[4];
	for (_I32 i = 0; i < 4; ++i)
	{
		result[i] = _mm_add_ps(m_Row[i], Matrix.m_Row[i]);
	}
	return Matrix4f(result[0], result[1], result[2], result[3]);
#else
	float result[4][4];
	for (_I32 i = 0; i < 4; ++i)
	{
		for (_I32 j = 0; j < 4; ++j)
		{
			result[i][j] = f[i][j] + Matrix.f[i][j];
		}
	}
	return Matrix4f(
		result[0][0], result[0][1], result[0][2], result[0][3],
		result[1][0], result[1][1], result[1][2], result[1][3],
		result[2][0], result[2][1], result[2][2], result[2][3],
		result[3][0], result[3][1], result[3][2], result[3][3]);
#endif

}

Matrix4f& Matrix4f::operator=(const Matrix4f& Matrix)
{
	for (_I32 i = 0; i < 4; ++i)
	{
		m_Row[i] = Matrix.m_Row[i];
	}

	return (*this);
}

NAMESPACE_MENGINE_END