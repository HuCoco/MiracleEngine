#pragma once
#include <Core/Mathematics/Matrix.h>
#include <Core/Mathematics/SIMD/SIMD4x4F.h>


static const Vector<float, 4> kAffineWColumn(0.0f, 0.0f, 0.0f, 1.0f);

typedef union
{
	SIMD4F simd;
	float float_array[4];
}SIMD4F_UNION;


typedef Matrix<float, 4> Matrix4f;

template <>
class Matrix<float, 4> 
{
public:
	Matrix() {}

	inline Matrix(const Matrix<float, 4>& m) 
	{
		data.simd_matrix.x = m.data.simd_matrix.x;
		data.simd_matrix.y = m.data.simd_matrix.y;
		data.simd_matrix.z = m.data.simd_matrix.z;
		data.simd_matrix.w = m.data.simd_matrix.w;
	}

	explicit inline Matrix(const float& s) 
	{
		SIMD4F v = SIMD4F_CREATE(s, s, s, s);
		data.simd_matrix = SIMD4X4F_CREATE(v, v, v, v);
	}

	inline Matrix(
		const float& s00, const float& s10, const float& s20, const float& s30, 
		const float& s01, const float& s11, const float& s21, const float& s31,
		const float& s02, const float& s12, const float& s22, const float& s32,
		const float& s03, const float& s13, const float& s23, const float& s33) 
	{
		data.simd_matrix = SIMD4X4F_CREATE(
			SIMD4F_CREATE(s00, s10, s20, s30), SIMD4F_CREATE(s01, s11, s21, s31),
			SIMD4F_CREATE(s02, s12, s22, s32), SIMD4F_CREATE(s03, s13, s23, s33));
	}

	explicit inline Matrix(const float* m) {
		data.simd_matrix =
			SIMD4X4F_CREATE(
				SIMD4F_CREATE(m[0], m[1], m[2], m[3]),
				SIMD4F_CREATE(m[4], m[5], m[6], m[7]),
				SIMD4F_CREATE(m[8], m[9], m[10], m[11]),
				SIMD4F_CREATE(m[12], m[13], m[14], m[15]));
	}

	inline Matrix(const Vector<float, 4>& column0,
		const Vector<float, 4>& column1,
		const Vector<float, 4>& column2,
		const Vector<float, 4>& column3) {
#if defined(SIMD_DEPTH_ACCELERATION)
		data.simd_matrix = SIMD4X4F_CREATE(column0.data.simd, column1.data.simd,
			column2.data.simd, column3.data.simd);
#else
		data.simd_matrix = SIMD4X4F_CREATE(
			SIMD4F_CREATE(column0[0], column0[1], column0[2], column0[3]),
			SIMD4F_CREATE(column1[0], column1[1], column1[2], column1[3]),
			SIMD4F_CREATE(column2[0], column2[1], column2[2], column2[3]),
			SIMD4F_CREATE(column3[0], column3[1], column3[2], column3[3]));
#endif  // defined(SIMD_DEPTH_ACCELERATION)
	}

	inline const float& operator()(const int i, const int j) const 
	{
		return FindElem(i, FindColumn(j));
	}

	inline float& operator()(const int i, const int j) 
	{
		return FindElem(i, FindColumn(j));
	}

	inline const float& operator()(const int i) const 
	{
		return this->operator[](i);
	}

	inline float& operator()(const int i) 
	{ 
		return this->operator[](i); 
	}

	inline const float& operator[](const int i) const 
	{
		const int col = i / 4;
		const int row = i % 4;
		return FindElem(row, FindColumn(col));
	}

	inline float& operator[](const int i) 
	{
		const int col = i / 4;
		const int row = i % 4;
		return FindElem(row, FindColumn(col));
	}

	inline Matrix<float, 4> operator-() const
	{
		Matrix<float, 4> m(0.f);
		SIMD4X4F_SUB(&m.data.simd_matrix, &data.simd_matrix,
			&m.data.simd_matrix);
		return m;
	}

	inline Matrix<float, 4> operator+(const Matrix<float, 4>& m) const 
	{
		Matrix<float, 4> return_m;
		SIMD4X4F_ADD(&data.simd_matrix, &m.data.simd_matrix,
			&return_m.data.simd_matrix);
		return return_m;
	}

	inline Matrix<float, 4> operator-(const Matrix<float, 4>& m) const 
	{
		Matrix<float, 4> return_m;
		SIMD4X4F_SUB(&data.simd_matrix, &m.data.simd_matrix,
			&return_m.data.simd_matrix);
		return return_m;
	}

	inline Matrix<float, 4> operator*(const float& s) const 
	{
		Matrix<float, 4> m(s);
		SIMD4X4F_MUL(&m.data.simd_matrix, &data.simd_matrix,
			&m.data.simd_matrix);
		return m;
	}

	inline Matrix<float, 4> operator/(const float& s) const
	{
		Matrix<float, 4> m(1 / s);
		SIMD4X4F_MUL(&m.data.simd_matrix, &data.simd_matrix,
			&m.data.simd_matrix);
		return m;
	}

	inline Vector<float, 3> operator*(const Vector<float, 3>& v) const 
	{
		Vector<float, 3> return_v;
		SIMD4F_UNION temp_v;
#ifdef SIMD_DEPTH_ACCELERATION
		temp_v.simd = v.data.simd;
		temp_v.float_array[3] = 1;
		simd4x4f_matrix_vector_mul(&data.simd_matrix, &temp_v.simd,
			&return_v.data.simd);
		return_v *= (1 / return_v.data.float_array[3]);
#else
		temp_v.simd = SIMD4F_CREATE(v[0], v[1], v[2], 1.0f);
		SIMD4X4F_MATRIX_VECTOR_MUL(&data.simd_matrix, &temp_v.simd, &temp_v.simd);
		SIMD4F_MUL(temp_v.simd, SIMD4F_SET(temp_v.float_array[3]));
		VECTOR3_STORE3(temp_v.simd, return_v);
#endif  // SIMD_DEPTH_ACCELERATION
		return return_v;
	}

	inline Vector<float, 4> operator*(const Vector<float, 4>& v) const 
	{
		Vector<float, 4> return_v;
		SIMD4X4F_MATRIX_VECTOR_MUL(&data.simd_matrix, &v.simd,
			&return_v.simd);
		return return_v;
	}

	inline Vector<float, 4> VecMatTimes(const Vector<float, 4>& v) const
	{
		return Vector<float, 4>(
			SIMD4F_DOT3_SCALAR(v.simd, data.simd_matrix.x),
			SIMD4F_DOT3_SCALAR(v.simd, data.simd_matrix.y),
			SIMD4F_DOT3_SCALAR(v.simd, data.simd_matrix.z),
			SIMD4F_DOT3_SCALAR(v.simd, data.simd_matrix.w));
	}

	inline Matrix<float, 4> operator*(const Matrix<float, 4>& m) const
	{
		Matrix<float, 4> return_m;
		SIMD4X4F_MATRIX_MUL(&data.simd_matrix, &m.data.simd_matrix,
			&return_m.data.simd_matrix);
		return return_m;
	}

	inline Matrix<float, 4> Inverse() const 
	{
		Matrix<float, 4> return_m;
		SIMD4X4F_INVERSE(&data.simd_matrix, &return_m.data.simd_matrix);
		return return_m;
	}

	inline bool InverseWithDeterminantCheck(Matrix<float, 4, 4>* const inverse) const 
	{
		return fabs(SIMD4F_GET_X(SIMD4X4F_INVERSE(&data.simd_matrix,
			&inverse->data.simd_matrix))) >= GetDeterminantThreshold<float>();
	}

	inline Matrix<float, 4, 4> Transpose() const
	{
		Matrix<float, 4, 4> transpose;
		SIMD4X4F_TRANSPOSE(&data.simd_matrix, &transpose.data.simd_matrix);
		return transpose;
	}

	inline Vector<float, 3> TranslationVector3D() const
	{
		Vector<float, 3> return_v;
		VECTOR3_STORE3(FindColumn(3).simd, return_v);
		return return_v;
	}

	inline Matrix<float, 4>& operator+=(const Matrix<float, 4>& m) 
	{
		SIMD4X4F_ADD(&data.simd_matrix, &m.data.simd_matrix, &data.simd_matrix);
		return *this;
	}

	inline Matrix<float, 4>& operator-=(const Matrix<float, 4>& m) 
	{
		SIMD4X4F_SUB(&data.simd_matrix, &m.data.simd_matrix, &data.simd_matrix);
		return *this;
	}

	inline Matrix<float, 4>& operator*=(const float& s) 
	{
		Matrix<float, 4> m(s);
		SIMD4X4F_MUL(&m.data.simd_matrix, &data.simd_matrix, &data.simd_matrix);
		return *this;
	}

	inline Matrix<float, 4>& operator/=(const float& s) 
	{
		Matrix<float, 4> m(1 / s);
		SIMD4X4F_MUL(&m.data.simd_matrix, &data.simd_matrix, &data.simd_matrix);
		return *this;
	}

	inline Matrix<float, 4> operator*=(const Matrix<float, 4>& m)
	{
		Matrix<float, 4> copy_of_this(*this);
		SIMD4X4F_MATRIX_MUL(&copy_of_this.data.simd_matrix, &m.data.simd_matrix,
			&data.simd_matrix);
		return *this;
	}

	static inline Matrix<float, 4> OuterProduct(const Vector<float, 4>& v1,
		const Vector<float, 4>& v2) {
		Matrix<float, 4> m;
		m.data.simd_matrix =
			SIMD4X4F_CREATE(
				SIMD4F_MUL(v1.simd, SIMD4F_SET(v2[0])),
				SIMD4F_MUL(v1.simd, SIMD4F_SET(v2[1])),
				SIMD4F_MUL(v1.simd, SIMD4F_SET(v2[2])),
				SIMD4F_MUL(v1.simd, SIMD4F_SET(v2[3])));
		return m;
	}

	static inline Matrix<float, 4> HadamardProduct(const Matrix<float, 4>& m1,const Matrix<float, 4>& m2) 
	{
		Matrix<float, 4> return_m;
		SIMD4X4F_MUL(&m1.data.simd_matrix, &m2.data.simd_matrix, &return_m.data.simd_matrix);
		return return_m;
	}

	static inline Matrix<float, 4> Identity() 
	{
		Matrix<float, 4> return_m;
		SIMD4X4F_IDENTITY(&return_m.data.simd_matrix);
		return return_m;
	}

	static inline Matrix<float, 4> FromTranslationVector(const Vector<float, 3>& v) 
	{
		return Matrix<float, 4>(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0, 
			v[0], v[1], v[2], 1);
	}

	static inline Matrix<float, 4> FromScaleVector(const Vector<float, 3>& v) 
	{
		return Matrix<float, 4>(
			v[0], 0, 0, 0,
			0, v[1], 0, 0,
			0, 0, v[2], 0,
			0, 0, 0, 1);
	}

	static inline Matrix<float, 4> FromRotationMatrix(const Matrix<float, 3>& m) 
	{
		return Matrix<float, 4>(
			m[0], m[1], m[2], 0,
			m[3], m[4], m[5], 0,
			m[6], m[7], m[8], 0, 
			0, 0, 0, 1);
	}

	static inline Matrix<float, 4> FromAffineTransform(const AffineTransform& affine) 
	{
		Matrix<float, 4> m;
		m.data.simd_matrix.x = SIMD4F_ULOAD4(&affine[0]);
		m.data.simd_matrix.y = SIMD4F_ULOAD4(&affine[4]);
		m.data.simd_matrix.z = SIMD4F_ULOAD4(&affine[8]);
		m.data.simd_matrix.w = SIMD4F_ULOAD4(&kAffineWColumn[0]);
		return m.Transpose();
	}

	static inline AffineTransform ToAffineTransform(const Matrix<float, 4>& m) {
		AffineTransform affine;
		const Matrix<float, 4> mt = m.Transpose();
		SIMD4F_USTORE4(mt.data.simd_matrix.x, &affine[0]);
		SIMD4F_USTORE4(mt.data.simd_matrix.y, &affine[4]);
		SIMD4F_USTORE4(mt.data.simd_matrix.z, &affine[8]);
		return affine;
	}

	static inline Matrix<float, 4, 4> Perspective(float fovy, float aspect, float znear, float zfar, float handedness = 1.0f) 
	{
		return PerspectiveHelper(fovy, aspect, znear, zfar, handedness);
	}

	static inline Matrix<float, 4, 4> Ortho(float left, float right, float bottom, float top, float znear, float zfar, float handedness = 1.0f)
	{
		return OrthoHelper(left, right, bottom, top, znear, zfar, handedness);
	}

	static inline Matrix<float, 4, 4> LookAt(const Vector<float, 3>& at, const Vector<float, 3>& eye, const Vector<float, 3>& up, float handedness = 1.0f) 
	{
		return LookAtHelper(at, eye, up, handedness);
	}

	static inline Matrix<float, 4, 4> LookTo(const Vector<float, 3>& to, const Vector<float, 3>& eye, const Vector<float, 3>& up, float handedness = 1.0f)
	{
		return LookToHelper(to, eye, up, handedness);
	}

	static const int kRows = 4;

	static const int kColumns = 4;

	static const int kElements = 4 * 4;


private:

	inline const SIMD4F_UNION& FindColumn(const int i) const {
		return data.simd4f_union_array[i];
	}

	inline SIMD4F_UNION& FindColumn(const int i) {
		return data.simd4f_union_array[i];
	}

	static inline const float& FindElem(const int i, const SIMD4F_UNION& column) {
		return column.float_array[i];
	}

	static inline float& FindElem(const int i, SIMD4F_UNION& column) {
		return column.float_array[i];
	}

public:
	union {
		SIMD4X4F simd_matrix;
		SIMD4F_UNION simd4f_union_array[4];
		float float_array[16];
	} data;
};


inline Matrix<float, 4> operator*(const float& s, const Matrix<float, 4>& m) 
{
	return m * s;
}

inline Vector<float, 4> operator*(const Vector<float, 4>& v,
	const Matrix<float, 4>& m) 
{
	return m.VecMatTimes(v);
}