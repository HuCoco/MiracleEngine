#pragma once
#include "MathPreCompileHead.h"
#include "MathUtilities.h"

#define VECTOR_STRIDE_FLOATS(vector) (sizeof(vector) / sizeof(float))

#define MAT_OPERATION(OP) UNROLLED_LOOP(i, columns, OP)

#define MAT_OPERATOR(OP)						  \
  {                                               \
    Matrix<T, rows, columns> result;              \
    MAT_OPERATION(result.data[i] = (OP));		  \
    return result;                                \
  }

#define MAT_SELF_OPERATOR(OP)		 \
  {                                  \
    MAT_OPERATION(OP);				 \
    return *this;                    \
  }
	
#define MATRIX_4X4_DOT(data1, data2, r)									\
  ((data1)[r] * (data2)[0] + (data1)[(r) + 4] * (data2)[1] +			\
(data1)[(r) + 8] * (data2)[2] + (data1)[(r) + 12] * (data2)[3])

#define MATRIX_3X3_DOT(data1, data2, r, size)							\
  ((data1)[r] * (data2)[0] + (data1)[(r) + (size)] * (data2)[1] +		\
   (data1)[(r) + 2 * (size)] * (data2)[2])



template <class T, int rows, int columns = rows>
class Matrix;

template <class T, int rows, int columns>
inline Matrix<T, rows, columns> IdentityHelper();

template <bool check_invertible, class T, int rows, int columns>
inline bool InverseHelper(const Matrix<T, rows, columns>& m, Matrix<T, rows, columns>* const inverse);

template <class T, int rows, int columns>
inline void TimesHelper(const Matrix<T, rows, columns>& m1, const Matrix<T, rows, columns>& m2, Matrix<T, rows, columns>* out_m);

template <class T, int rows, int columns>
static inline Matrix<T, rows, columns> OuterProductHelper(const Vector<T, rows>& v1, const Vector<T, columns>& v2);

template <class T>
inline Matrix<T, 4, 4> PerspectiveHelper(T fovy, T aspect, T znear, T zfar, T handedness);

template <class T>
static inline Matrix<T, 4, 4> OrthoHelper(T left, T right, T bottom, T top, T znear, T zfar, T handedness);

template <class T>
static inline Matrix<T, 4, 4> LookAtHelper(const Vector<T, 3>& at, const Vector<T, 3>& eye, const Vector<T, 3>& up, T handedness);


template <class T, int rows, int columns>
class Matrix 
{
public:
	inline Matrix() {}

	inline Matrix(const Matrix<T, rows, columns>& m) 
	{
		MAT_OPERATION(data[i] = m.data[i]);
	}

	explicit inline Matrix(const T& s) 
	{
		MAT_OPERATION((data[i] = Vector<T, rows>(s)));
	}

	inline Matrix(const T& s00, const T& s10,
				  const T& s01, const T& s11) 
	{
		MENGINE_STATIC_ASSERT(rows == 2 && columns == 2);
		data[0] = Vector<T, rows>(s00, s10);
		data[1] = Vector<T, rows>(s01, s11);
	}

	inline Matrix(const T& s00, const T& s10, const T& s20,
				  const T& s01, const T& s11, const T& s21,
				  const T& s02, const T& s12,const T& s22) 
	{
		MENGINE_STATIC_ASSERT(rows == 3 && columns == 3);
		data[0] = Vector<T, rows>(s00, s10, s20);
		data[1] = Vector<T, rows>(s01, s11, s21);
		data[2] = Vector<T, rows>(s02, s12, s22);
	}

	inline Matrix(const T& s00, const T& s10, const T& s20, const T& s30,
				  const T& s01, const T& s11, const T& s21, const T& s31,
				  const T& s02, const T& s12, const T& s22, const T& s32)
	{
		MENGINE_STATIC_ASSERT(rows == 4 && columns == 3);
		data[0] = Vector<T, rows>(s00, s10, s20, s30);
		data[1] = Vector<T, rows>(s01, s11, s21, s31);
		data[2] = Vector<T, rows>(s02, s12, s22, s32);
	}

	inline Matrix(const T& s00, const T& s10, const T& s20, const T& s30,
				  const T& s01, const T& s11, const T& s21, const T& s31,
				  const T& s02, const T& s12, const T& s22, const T& s32,
				  const T& s03, const T& s13, const T& s23, const T& s33) 
	{
		MENGINE_STATIC_ASSERT(rows == 4 && columns == 4);
		data[0] = Vector<T, rows>(s00, s10, s20, s30);
		data[1] = Vector<T, rows>(s01, s11, s21, s31);
		data[2] = Vector<T, rows>(s02, s12, s22, s32);
		data[3] = Vector<T, rows>(s03, s13, s23, s33);
	}

	inline Matrix(const Vector<T, 4>& column0, const Vector<T, 4>& column1, const Vector<T, 4>& column2, const Vector<T, 4>& column3)
	{
		MENGINE_STATIC_ASSERT(rows == 4 && columns == 4);
		data[0] = column0;
		data[1] = column1;
		data[2] = column2;
		data[3] = column3;
	}

	explicit inline Matrix(const T* const a) {
		MAT_OPERATION((data[i] = Vector<T, rows>(&a[i * columns])));
	}

	inline const T& operator()(const int row, const int column) const 
	{
		return data[column][row];
	}

	inline T& operator()(const int row, const int column) 
	{
		return data[column][row];
	}

	inline const T& operator()(const int i) const 
	{ 
		return operator[](i);
	}

	inline T& operator()(const int i) 
	{ 
		return operator[](i); 
	}

	inline const T& operator[](const int i) const
	{
		return const_cast<Matrix<T, rows, columns>*>(this)->operator[](i);
	}

	inline T& operator[](const int i) {
#if defined(SIMD_DEPTH_ACCELERATION)
		// In this case Vector<T, 3> is padded, so the element offset must be
		// accessed using the array operator.
		if (rows == 3) {
			const int row = i % rows;
			const int col = i / rows;
			return data[col][row];
		}
		else {
			return reinterpret_cast<T*>(data)[i];
		}
#else
		return reinterpret_cast<T*>(data)[i];
#endif  // defined(SIMD_DEPTH_ACCELERATION)
	}

	inline Vector<T, rows>& GetColumn(const int i)
	{ 
		return data[i]; 
	}

	inline const Vector<T, rows>& GetColumn(const int i) const 
	{
		return data[i];
	}

	inline Matrix<T, rows, columns> operator-() const {
		MAT_OPERATOR(-data[i]);
	}

	inline Matrix<T, rows, columns> operator+(const Matrix<T, rows, columns>& m) const 
	{
		MAT_OPERATOR(data[i] + m.data[i]);
	}

	inline Matrix<T, rows, columns> operator-(const Matrix<T, rows, columns>& m) const
	{
		MAT_OPERATOR(data[i] - m.data[i]);
	}

	inline Matrix<T, rows, columns> operator+(const T& s) const 
	{
		MAT_OPERATOR(data[i] + s);
	}

	inline Matrix<T, rows, columns> operator-(const T& s) const 
	{
		MAT_OPERATOR(data[i] - s);
	}

	inline Matrix<T, rows, columns> operator*(const T& s) const 
	{
		MAT_OPERATOR(data[i] * s);
	}

	inline Matrix<T, rows, columns> operator/(const T& s) const 
	{
		return (*this) * (static_cast<T>(1) / s);
	}

	inline Matrix<T, rows, columns> operator*(const Matrix<T, rows, columns>& m) const 
	{
		Matrix<T, rows, columns> result;
		TimesHelper(*this, m, &result);
		return result;
	}

	inline Matrix<T, rows, columns>& operator+=(const Matrix<T, rows, columns>& m) 
	{
		MAT_SELF_OPERATOR(data[i] += m.data[i]);
	}

	inline Matrix<T, rows, columns>& operator-=(const Matrix<T, rows, columns>& m) 
	{
		MAT_SELF_OPERATOR(data[i] -= m.data[i]);
	}

	inline Matrix<T, rows, columns>& operator+=(const T& s) 
	{
		MAT_SELF_OPERATOR(data[i] += s);
	}

	inline Matrix<T, rows, columns>& operator-=(const T& s) 
	{
		MAT_SELF_OPERATOR(data[i] -= s);
	}

	inline Matrix<T, rows, columns>& operator*=(const T& s) 
	{
		MAT_SELF_OPERATOR(data[i] *= s);
	}

	inline Matrix<T, rows, columns>& operator/=(const T& s) 
	{
		return (*this) *= (static_cast<T>(1) / s);
	}

	inline Matrix<T, rows, columns>& operator*=( const Matrix<T, rows, columns>& m) 
	{ 
		const Matrix<T, rows, columns> copy_of_this(*this);
		TimesHelper(copy_of_this, m, this);
		return *this;
	}

	inline Matrix<T, rows, columns> Inverse() const 
	{
		Matrix<T, rows, columns> inverse;
		InverseHelper<false>(*this, &inverse);
		return inverse;
	}

	inline bool InverseWithDeterminantCheck(Matrix<T, rows, columns>* const inverse) const 
	{
		return InverseHelper<true>(*this, inverse);
	}

	inline Matrix<T, columns, rows> Transpose() const 
	{
		Matrix<T, columns, rows> transpose;
		UNROLLED_LOOP(
			i, columns, UNROLLED_LOOP(
				j, rows, transpose.GetColumn(j)[i] = GetColumn(i)[j]))
			return transpose;
	}

	inline Vector<T, 2> TranslationVector2D() const 
	{
		MENGINE_STATIC_ASSERT(rows == 3 && columns == 3);
		return Vector<T, 2>(data[2][0], data[2][1]);
	}

	inline Vector<T, 3> TranslationVector3D() const 
	{
		MENGINE_STATIC_ASSERT(rows == 4 && columns == 4);
		return Vector<T, 3>(data[3][0], data[3][1], data[3][2]);
	}

	static inline Matrix<T, rows, columns> OuterProduct(const Vector<T, rows>& v1, const Vector<T, columns>& v2) 
	{
		return OuterProductHelper(v1, v2);
	}

	static inline Matrix<T, rows, columns> HadamardProduct(const Matrix<T, rows, columns>& m1, const Matrix<T, rows, columns>& m2) 
	{
		MAT_OPERATOR(m1[i] * m2[i]);
	}

	static inline Matrix<T, rows, columns> Identity() 
	{
		return IdentityHelper<T, rows, columns>();
	}

	static inline Matrix<T, 3> FromTranslationVector(const Vector<T, 2>& v) 
	{
		return Matrix<T, 3>(
			1, 0, 0,
			0, 1, 0,
			v[0], v[1], 1);
	}

	static inline Matrix<T, 4> FromTranslationVector(const Vector<T, 3>& v) 
	{
		return Matrix<T, 4>(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			v[0], v[1], v[2], 1);
	}

	static inline Matrix<T, rows> FromScaleVector(const Vector<T, rows - 1>& v) 
	{
		// TODO OPT
		Matrix<T, rows> return_matrix(Identity());
		for (int i = 0; i < rows - 1; ++i)
		{
			return_matrix(i, i) = v[i];
		}
		return return_matrix;
	}

	static inline Matrix<T, 4> FromRotationMatrix(const Matrix<T, 3>& m) 
	{
		return Matrix<T, 4>(
			m[0], m[1], m[2], 0, 
			m[3], m[4], m[5], 0, 
			m[6], m[7], m[8], 0, 
			0, 0, 0, 1);
	}

	static inline Matrix<T, 3> ToRotationMatrix(const Matrix<T, 4>& m) 
	{
		return Matrix<T, 3>(
			m[0], m[1], m[2],
			m[4], m[5], m[6],
			m[8], m[9], m[10]);
	}

	static inline Matrix<T, 4> FromAffineTransform(const Matrix<T, 4, 3>& affine) 
	{
		return Matrix<T, 4>(
			affine[0], affine[4], affine[8], static_cast<T>(0),
			affine[1], affine[5], affine[9], static_cast<T>(0),
			affine[2], affine[6], affine[10], static_cast<T>(0),
			affine[3], affine[7], affine[11], static_cast<T>(1));
	}

	static inline Matrix<T, 4, 3> ToAffineTransform(const Matrix<T, 4>& m) 
	{
		return Matrix<T, 4, 3>(
			m[0], m[4], m[8], m[12], 
			m[1], m[5], m[9], m[13],
			m[2], m[6], m[10], m[14]);
	}

	static inline Matrix<T, 3> RotationX(const Vector<T, 2>& v) 
	{
		return Matrix<T, 3>(
			1, 0, 0,
			0, v.x, v.y,
			0, -v.y, v.x);
	}

	static inline Matrix<T, 3> RotationY(const Vector<T, 2>& v) 
	{
		return Matrix<T, 3>(
			v.x, 0, -v.y,
			0, 1, 0, 
			v.y, 0, v.x);
	}

	static inline Matrix<T, 3> RotationZ(const Vector<T, 2>& v) 
	{
		return Matrix<T, 3>(
			v.x, v.y, 0,
			-v.y, v.x, 0,
			0, 0, 1);
	}

	static inline Matrix<T, 3> RotationX(T angle)
	{
		return RotationX(Vector<T, 2>(cosf(angle), sinf(angle)));
	}

	static inline Matrix<T, 3> RotationY(T angle) 
	{
		return RotationY(Vector<T, 2>(cosf(angle), sinf(angle)));
	}

	static inline Matrix<T, 3> RotationZ(T angle)
	{
		return RotationZ(Vector<T, 2>(cosf(angle), sinf(angle)));
	}

	static inline Matrix<T, 4, 4> Perspective(T fovy, T aspect, T znear, T zfar, T handedness = -1) 
	{
		return PerspectiveHelper(fovy, aspect, znear, zfar, handedness);
	}

	static inline Matrix<T, 4, 4> Ortho(T left, T right, T bottom, T top, T znear, T zfar, T handedness = -1) 
	{
		return OrthoHelper(left, right, bottom, top, znear, zfar, handedness);
	}

	static inline Matrix<T, 4, 4> LookAt(const Vector<T, 3>& at, const Vector<T, 3>& eye, const Vector<T, 3>& up, T handedness = -1) 
	{
		return LookAtHelper(at, eye, up, handedness);
	}

	friend inline Vector<T, columns> operator*(const Vector<T, rows>& v, const Matrix<T, rows, columns>& m) 
	{
		const int d = columns;
		VECTOR_OPERATOR((Vector<T, rows>::DotProduct(m.data[i], v)));
	}

	// Dimensions of the matrix.
	/// Number of rows in the matrix.
	static const int kRows = rows;
	/// Number of columns in the matrix.
	static const int kColumns = columns;
	/// Total number of elements in the matrix.
	static const int kElements = rows * columns;
public:
	Vector<T, rows> data[columns];
};


template <class T, int rows, int columns>
inline Matrix<T, rows, columns> operator*(const T& s, const Matrix<T, columns, rows>& m) 
{
	return m * s;
}

template <class T, int rows, int columns>
inline Vector<T, rows> operator*(const Matrix<T, rows, columns>& m, const Vector<T, columns>& v) 
{ 
	const Vector<T, rows> result(0);
	int offset = 0;
	for (int column = 0; column < columns; column++) 
	{
		for (int row = 0; row < rows; row++) 
		{
			result[row] += m[offset + row] * v[column];
		}
		offset += rows;
	}
	return result;
}

template <class T>
inline Vector<T, 2> operator*(const Matrix<T, 2, 2>& m, const Vector<T, 2>& v) 
{
	return Vector<T, 2>(m[0] * v[0] + m[2] * v[1], m[1] * v[0] + m[3] * v[1]);
}

template <class T>
inline Vector<T, 3> operator*(const Matrix<T, 3, 3>& m, const Vector<T, 3>& v) 
{
	return Vector<T, 3>(
		MATRIX_3X3_DOT(&m[0], v, 0, 3),
		MATRIX_3X3_DOT(&m[0], v, 1, 3),
		MATRIX_3X3_DOT(&m[0], v, 2, 3));
}

template <>
inline Vector<float, 3> operator*(const Matrix<float, 3, 3>& m, const Vector<float, 3>& v) 
{
	return Vector<float, 3>(
		MATRIX_3X3_DOT(&m[0], v, 0, VECTOR_STRIDE_FLOATS(v)),
		MATRIX_3X3_DOT(&m[0], v, 1, VECTOR_STRIDE_FLOATS(v)),
		MATRIX_3X3_DOT(&m[0], v, 2, VECTOR_STRIDE_FLOATS(v)));
}

template <class T>
inline Vector<T, 4> operator*(const Matrix<T, 4, 4>& m, const Vector<T, 4>& v) {
	return Vector<T, 4>(
		MATRIX_4X4_DOT(&m[0], v, 0), MATRIX_4X4_DOT(&m[0], v, 1),
		MATRIX_4X4_DOT(&m[0], v, 2), MATRIX_4X4_DOT(&m[0], v, 3));
}

template <class T>
inline Vector<T, 3> operator*(const Matrix<T, 4, 4>& m, const Vector<T, 3>& v) 
{
	Vector<T, 4> v4(v[0], v[1], v[2], 1);
	v4 = m * v4;
	return Vector<T, 3>(v4[0] / v4[3], v4[1] / v4[3], v4[2] / v4[3]);
}

template <class T, int size1, int size2, int size3>
inline void TimesHelper(const Matrix<T, size1, size2>& m1, const Matrix<T, size2, size3>& m2, Matrix<T, size1, size3>* out_m) 
{
	for (int i = 0; i < size1; i++) 
	{
		for (int j = 0; j < size3; j++) 
		{
			Vector<T, size2> row;
			for (int k = 0; k < size2; k++) 
			{
				row[k] = m1(i, k);
			}
			(*out_m)(i, j) = Vector<T, size2>::DotProduct(m2.GetColumn(j), row);
		}
	}
}

template <class T>
inline void TimesHelper(const Matrix<T, 2, 2>& m1, const Matrix<T, 2, 2>& m2, Matrix<T, 2, 2>* out_m) 
{
	Matrix<T, 2, 2>& out = *out_m;
	out[0] = m1[0] * m2[0] + m1[2] * m2[1];
	out[1] = m1[1] * m2[0] + m1[3] * m2[1];
	out[2] = m1[0] * m2[2] + m1[2] * m2[3];
	out[3] = m1[1] * m2[2] + m1[3] * m2[3];
}

template <typename T>
inline void TimesHelper(const Matrix<T, 3, 3>& m1, const Matrix<T, 3, 3>& m2, Matrix<T, 3, 3>* out_m) 
{
	Matrix<T, 3, 3>& out = *out_m;
	{
		Vector<T, 3> row(m1[0], m1[3], m1[6]);
		out[0] = Vector<T, 3>::DotProduct(m2.GetColumn(0), row);
		out[3] = Vector<T, 3>::DotProduct(m2.GetColumn(1), row);
		out[6] = Vector<T, 3>::DotProduct(m2.GetColumn(2), row);
	}
	{
		Vector<T, 3> row(m1[1], m1[4], m1[7]);
		out[1] = Vector<T, 3>::DotProduct(m2.GetColumn(0), row);
		out[4] = Vector<T, 3>::DotProduct(m2.GetColumn(1), row);
		out[7] = Vector<T, 3>::DotProduct(m2.GetColumn(2), row);
	}
	{
		Vector<T, 3> row(m1[2], m1[5], m1[8]);
		out[2] = Vector<T, 3>::DotProduct(m2.GetColumn(0), row);
		out[5] = Vector<T, 3>::DotProduct(m2.GetColumn(1), row);
		out[8] = Vector<T, 3>::DotProduct(m2.GetColumn(2), row);
	}
}

template <class T>
inline void TimesHelper(const Matrix<T, 4, 4>& m1, const Matrix<T, 4, 4>& m2, Matrix<T, 4, 4>* out_m) 
{
	Matrix<T, 4, 4>& out = *out_m;
	{
		Vector<T, 4> row(m1[0], m1[4], m1[8], m1[12]);
		out[0] = Vector<T, 4>::DotProduct(m2.GetColumn(0), row);
		out[4] = Vector<T, 4>::DotProduct(m2.GetColumn(1), row);
		out[8] = Vector<T, 4>::DotProduct(m2.GetColumn(2), row);
		out[12] = Vector<T, 4>::DotProduct(m2.GetColumn(3), row);
	}
	{
		Vector<T, 4> row(m1[1], m1[5], m1[9], m1[13]);
		out[1] = Vector<T, 4>::DotProduct(m2.GetColumn(0), row);
		out[5] = Vector<T, 4>::DotProduct(m2.GetColumn(1), row);
		out[9] = Vector<T, 4>::DotProduct(m2.GetColumn(2), row);
		out[13] = Vector<T, 4>::DotProduct(m2.GetColumn(3), row);
	}
	{
		Vector<T, 4> row(m1[2], m1[6], m1[10], m1[14]);
		out[2] = Vector<T, 4>::DotProduct(m2.GetColumn(0), row);
		out[6] = Vector<T, 4>::DotProduct(m2.GetColumn(1), row);
		out[10] = Vector<T, 4>::DotProduct(m2.GetColumn(2), row);
		out[14] = Vector<T, 4>::DotProduct(m2.GetColumn(3), row);
	}
	{
		Vector<T, 4> row(m1[3], m1[7], m1[11], m1[15]);
		out[3] = Vector<T, 4>::DotProduct(m2.GetColumn(0), row);
		out[7] = Vector<T, 4>::DotProduct(m2.GetColumn(1), row);
		out[11] = Vector<T, 4>::DotProduct(m2.GetColumn(2), row);
		out[15] = Vector<T, 4>::DotProduct(m2.GetColumn(3), row);
	}
}

template <class T, int rows, int columns>
inline Matrix<T, rows, columns> IdentityHelper() 
{
	Matrix<T, rows, columns> return_matrix(0.f);
	int min_d = rows < columns ? rows : columns;
	for (int i = 0; i < min_d; ++i)
	{
		return_matrix(i, i) = 1;
	}
	return return_matrix;
}

template <class T>
inline Matrix<T, 2, 2> IdentityHelper()
{
	return Matrix<T, 2, 2>(1, 0, 0, 1);
}

template <class T>
inline Matrix<T, 3, 3> IdentityHelper()
{
	return Matrix<T, 3, 3>(
		1, 0, 0,
		0, 1, 0, 
		0, 0, 1);
}

template <class T>
inline Matrix<T, 4, 4> IdentityHelper() 
{
	return Matrix<T, 4, 4>(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
}

template <class T, int rows, int columns>
static inline Matrix<T, rows, columns> OuterProductHelper(const Vector<T, rows>& v1, const Vector<T, columns>& v2) 
{
	Matrix<T, rows, columns> result(0);
	int offset = 0;
	for (int column = 0; column < columns; column++) 
	{
		for (int row = 0; row < rows; row++) 
		{
			result[row + offset] = v1[row] * v2[column];
		}
		offset += rows;
	}
	return result;
}

template <class T>
static inline Matrix<T, 2, 2> OuterProductHelper(const Vector<T, 2>& v1, const Vector<T, 2>& v2) 
{
	return Matrix<T, 2, 2>(
		v1[0] * v2[0], v1[1] * v2[0],
		v1[0] * v2[1], v1[1] * v2[1]);
}

template <class T>
static inline Matrix<T, 3, 3> OuterProductHelper(const Vector<T, 3>& v1, const Vector<T, 3>& v2) 
{
	return Matrix<T, 3, 3>(
		v1[0] * v2[0], v1[1] * v2[0], v1[2] * v2[0],
		v1[0] * v2[1], v1[1] * v2[1], v1[2] * v2[1],
		v1[0] * v2[2], v1[1] * v2[2], v1[2] * v2[2]);
}

template <class T>
static inline Matrix<T, 4, 4> OuterProductHelper(const Vector<T, 4>& v1, const Vector<T, 4>& v2) 
{
	return Matrix<T, 4, 4>(
		v1[0] * v2[0], v1[1] * v2[0], v1[2] * v2[0], v1[3] * v2[0],
		v1[0] * v2[1], v1[1] * v2[1], v1[2] * v2[1], v1[3] * v2[1], 
		v1[0] * v2[2], v1[1] * v2[2], v1[2] * v2[2], v1[3] * v2[2],
		v1[0] * v2[3], v1[1] * v2[3], v1[2] * v2[3], v1[3] * v2[3]);
}


template <class T>
static T GetDeterminantThreshold() 
{
	assert(false);
	return 0;
}

template <>
static float GetDeterminantThreshold()
{
	assert(false);
	return 1e-7f;;
}

template <>
static double GetDeterminantThreshold()
{
	assert(false);
	return 1e-15;;
}

template <bool check_invertible, class T, int rows, int columns>
inline bool InverseHelper(const Matrix<T, rows, columns>& m, Matrix<T, rows, columns>* const inverse) 
{
	assert(false);
	(void)m;
	*inverse = T::Identity();
	return false;
}

template <bool check_invertible, class T>
inline bool InverseHelper(const Matrix<T, 2, 2>& m, Matrix<T, 2, 2>* const inverse) 
{
	T determinant = m[0] * m[3] - m[1] * m[2];
	if (check_invertible && fabs(determinant) < GetDeterminantThreshold<T>()) 
	{
		return false;
	}
	T inverseDeterminant = 1 / determinant;
	(*inverse)[0] = inverseDeterminant * m[3];
	(*inverse)[1] = -inverseDeterminant * m[1];
	(*inverse)[2] = -inverseDeterminant * m[2];
	(*inverse)[3] = inverseDeterminant * m[0];
	return true;
}

template <bool check_invertible, class T>
inline bool InverseHelper(const Matrix<T, 3, 3>& m,
	Matrix<T, 3, 3>* const inverse) {
	T sub11 = m[4] * m[8] - m[5] * m[7];
	T sub12 = -m[1] * m[8] + m[2] * m[7];
	T sub13 = m[1] * m[5] - m[2] * m[4];

	T determinant = m[0] * sub11 + m[3] * sub12 + m[6] * sub13;
	if (check_invertible && fabs(determinant) < GetDeterminantThreshold<T>()) 
	{
		return false;
	}

	*inverse = Matrix<T, 3, 3>(
		sub11, sub12, sub13, 
		m[6] * m[5] - m[3] * m[8], m[0] * m[8] - m[6] * m[2],
		m[3] * m[2] - m[0] * m[5], m[3] * m[7] - m[6] * m[4],
		m[6] * m[1] - m[0] * m[7], m[0] * m[4] - m[3] * m[1]);

	*(inverse) *= 1 / determinant;
	return true;
}

template <class T>
inline int FindLargestPivotElem(const Matrix<T, 4, 4>& m) 
{
	Vector<T, 4> fabs_column(fabs(m[0]), fabs(m[1]), fabs(m[2]), fabs(m[3]));
	if (fabs_column[0] > fabs_column[1]) 
	{
		if (fabs_column[0] > fabs_column[2]) 
		{
			if (fabs_column[0] > fabs_column[3]) 
			{
				return 0;
			}
			else 
			{
				return 3;
			}
		}
		else if (fabs_column[2] > fabs_column[3]) 
		{
			return 2;
		}
		else 
		{
			return 3;
		}
	}
	else if (fabs_column[1] > fabs_column[2]) 
	{
		if (fabs_column[1] > fabs_column[3])
		{
			return 1;
		}
		else 
		{
			return 3;
		}
	}
	else if (fabs_column[2] > fabs_column[3]) 
	{
		return 2;
	}
	else 
	{
		return 3;
	}
}

template <bool check_invertible, class T>
bool InverseHelper(const Matrix<T, 4, 4>& m, Matrix<T, 4, 4>* const inverse)
{
	// This will find the pivot element.
	int pivot_elem = FindLargestPivotElem(m);
	// This will perform the pivot and find the row, column, and 3x3 submatrix
	// for this pivot.
	Vector<T, 3> row, column;
	Matrix<T, 3> matrix;
	if (pivot_elem == 0) 
	{
		row = Vector<T, 3>(m[4], m[8], m[12]);
		column = Vector<T, 3>(m[1], m[2], m[3]);
		matrix = Matrix<T, 3>(m[5], m[6], m[7], m[9], m[10], m[11], m[13], m[14], m[15]);
	}
	else if (pivot_elem == 1)
	{
		row = Vector<T, 3>(m[5], m[9], m[13]);
		column = Vector<T, 3>(m[0], m[2], m[3]);
		matrix = Matrix<T, 3>(m[4], m[6], m[7], m[8], m[10], m[11], m[12], m[14], m[15]);
	}
	else if (pivot_elem == 2) 
	{
		row = Vector<T, 3>(m[6], m[10], m[14]);
		column = Vector<T, 3>(m[0], m[1], m[3]);
		matrix = Matrix<T, 3>(m[4], m[5], m[7], m[8], m[9], m[11], m[12], m[13], m[15]);
	}
	else
	{
		row = Vector<T, 3>(m[7], m[11], m[15]);
		column = Vector<T, 3>(m[0], m[1], m[2]);
		matrix = Matrix<T, 3>(m[4], m[5], m[6], m[8], m[9], m[10], m[12], m[13], m[14]);
	}
	T pivot_value = m[pivot_elem];
	if (check_invertible && fabs(pivot_value) < Constants<T>::GetDeterminantThreshold()) 
	{
		return false;
	}
	// This will compute the inverse using the row, column, and 3x3 submatrix.
	T inv = -1 / pivot_value;
	row *= inv;
	matrix += Matrix<T, 3>::OuterProduct(column, row);
	Matrix<T, 3> mat_inverse;
	if (!InverseHelper<check_invertible>(matrix, &mat_inverse) && check_invertible) 
	{
		return false;
	}
	Vector<T, 3> col_inverse = mat_inverse * (column * inv);
	Vector<T, 3> row_inverse = row * mat_inverse;
	T pivot_inverse = Vector<T, 3>::DotProduct(row, col_inverse) - inv;
	if (pivot_elem == 0) 
	{
		*inverse = Matrix<T, 4, 4>(
			pivot_inverse, col_inverse[0], col_inverse[1], col_inverse[2],
			row_inverse[0], mat_inverse[0], mat_inverse[1], mat_inverse[2],
			row_inverse[1], mat_inverse[3], mat_inverse[4], mat_inverse[5],
			row_inverse[2], mat_inverse[6], mat_inverse[7], mat_inverse[8]);
	}
	else if (pivot_elem == 1) 
	{
		*inverse = Matrix<T, 4, 4>(
			row_inverse[0], mat_inverse[0], mat_inverse[1], mat_inverse[2],
			pivot_inverse, col_inverse[0], col_inverse[1], col_inverse[2],
			row_inverse[1], mat_inverse[3], mat_inverse[4], mat_inverse[5],
			row_inverse[2], mat_inverse[6], mat_inverse[7], mat_inverse[8]);
	}
	else if (pivot_elem == 2) 
	{
		*inverse = Matrix<T, 4, 4>(
			row_inverse[0], mat_inverse[0], mat_inverse[1], mat_inverse[2],
			row_inverse[1], mat_inverse[3], mat_inverse[4], mat_inverse[5],
			pivot_inverse, col_inverse[0], col_inverse[1], col_inverse[2],
			row_inverse[2], mat_inverse[6], mat_inverse[7], mat_inverse[8]);
	}
	else 
	{
		*inverse = Matrix<T, 4, 4>(
			row_inverse[0], mat_inverse[0], mat_inverse[1], mat_inverse[2],
			row_inverse[1], mat_inverse[3], mat_inverse[4], mat_inverse[5],
			row_inverse[2], mat_inverse[6], mat_inverse[7], mat_inverse[8],
			pivot_inverse, col_inverse[0], col_inverse[1], col_inverse[2]);
	}
	return true;
}

template <class T>
inline Matrix<T, 4, 4> PerspectiveHelper(T fovy, T aspect, T znear, T zfar, T handedness) 
{
	const T y = 1 / std::tan(fovy * static_cast<T>(.5));
	const T x = y / aspect;
	const T zdist = (znear - zfar);
	const T zfar_per_zdist = zfar / zdist;
	return Matrix<T, 4, 4>(
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, zfar_per_zdist * handedness, -1 * handedness,
		0, 0, 1.0f * znear * zfar_per_zdist, 0);
}

template <class T>
static inline Matrix<T, 4, 4> OrthoHelper(T left, T right, T bottom, T top, T znear, T zfar, T handedness) 
{
	return Matrix<T, 4, 4>(static_cast<T>(2) / (right - left), 0, 0, 0, 0,
		static_cast<T>(2) / (top - bottom), 0, 0, 0, 0,
		-handedness * static_cast<T>(2) / (zfar - znear), 0,
		-(right + left) / (right - left),
		-(top + bottom) / (top - bottom),
		-(zfar + znear) / (zfar - znear), static_cast<T>(1));
}

template <class T>
static void LookAtHelperCalculateAxes(const Vector<T, 3>& at, const Vector<T, 3>& eye, const Vector<T, 3>& up, T handedness, Vector<T, 3>* const axes)
{
	// Notice that y-axis is always the same regardless of handedness.
	axes[2] = (at - eye).Normalized();
	axes[0] = Vector<T, 3>::CrossProduct(up, axes[2]).Normalized();
	axes[1] = Vector<T, 3>::CrossProduct(axes[2], axes[0]);
	axes[3] = Vector<T, 3>(handedness * Vector<T, 3>::DotProduct(axes[0], eye),
		-Vector<T, 3>::DotProduct(axes[1], eye),
		handedness * Vector<T, 3>::DotProduct(axes[2], eye));

	// Default calculation is left-handed (i.e. handedness=-1).
	// Negate x and z axes for right-handed (i.e. handedness=+1) case.
	const T neg = -handedness;
	axes[0] *= neg;
	axes[2] *= neg;
}

template <class T>
static void LookToHelperCalculateAxes(const Vector<T, 3>& to, const Vector<T, 3>& eye, const Vector<T, 3>& up, T handedness, Vector<T, 3>* const axes)
{
	// Notice that y-axis is always the same regardless of handedness.
	axes[2] = to.Normalized();
	axes[0] = Vector<T, 3>::CrossProduct(up, axes[2]).Normalized();
	axes[1] = Vector<T, 3>::CrossProduct(axes[2], axes[0]);
	axes[3] = Vector<T, 3>(handedness * Vector<T, 3>::DotProduct(axes[0], eye),
		-Vector<T, 3>::DotProduct(axes[1], eye),
		handedness * Vector<T, 3>::DotProduct(axes[2], eye));

	// Default calculation is left-handed (i.e. handedness=-1).
	// Negate x and z axes for right-handed (i.e. handedness=+1) case.
	const T neg = -handedness;
	axes[0] *= neg;
	axes[2] *= neg;
}

template <class T>
static inline Matrix<T, 4, 4> LookAtHelper(const Vector<T, 3>& at, const Vector<T, 3>& eye, const Vector<T, 3>& up, T handedness) {
	Vector<T, 3> axes[4];
	LookAtHelperCalculateAxes(at, eye, up, handedness, axes);
	const Vector<T, 4> column0(axes[0][0], axes[1][0], axes[2][0], 0);
	const Vector<T, 4> column1(axes[0][1], axes[1][1], axes[2][1], 0);
	const Vector<T, 4> column2(axes[0][2], axes[1][2], axes[2][2], 0);
	const Vector<T, 4> column3(axes[3], 1);
	return Matrix<T, 4, 4>(column0, column1, column2, column3);
}

template <class T>
static inline Matrix<T, 4, 4> LookToHelper(const Vector<T, 3>& to, const Vector<T, 3>& eye, const Vector<T, 3>& up, T handedness) {
	Vector<T, 3> axes[4];
	LookToHelperCalculateAxes(to, eye, up, handedness, axes);
	const Vector<T, 4> column0(axes[0][0], axes[1][0], axes[2][0], 0);
	const Vector<T, 4> column1(axes[0][1], axes[1][1], axes[2][1], 0);
	const Vector<T, 4> column2(axes[0][2], axes[1][2], axes[2][2], 0);
	const Vector<T, 4> column3(axes[3], 1);
	return Matrix<T, 4, 4>(column0, column1, column2, column3);
}

typedef Matrix<float, 4, 3> AffineTransform;


#include "Matrix4f.h"