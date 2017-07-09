#include "MTransform.h"


const Quaternion<float> Miracle::MTransform::s_DefuatDirection = Quaternion<float>(0.0f, Vector3f(0.0f,0.0,1.0f));
const Vector3f Miracle::MTransform::s_UpAixs = Vector3f(0.0f, 1.0f, 0.0f);

Miracle::MTransform::MTransform()
	: m_Rotation(0.0f, 0.0f, 0.0f)
	, m_Translate(0.0f, 0.0f, 0.0f)
	, m_Scale3D(1.0f, 1.0f, 1.0f)
	, m_Direction(s_DefuatDirection)
{
}

Miracle::MTransform::MTransform(const Vector3f& a_Rotation, const Vector3f& a_Translate, const Vector3f& a_Scale3D)
	: m_Rotation(a_Rotation)
	, m_Translate(a_Translate)
	, m_Scale3D(a_Scale3D)
{
	CalcDirection();
}

Miracle::MTransform::~MTransform()
{
}

Matrix4f Miracle::MTransform::ToMartix4f()
{
	return Matrix4f::FromScaleVector(m_Scale3D) * Quaternion<float>::FromEulerAngles(m_Rotation).ToMatrix4() * Matrix4f::FromTranslationVector(m_Translate);
}

void Miracle::MTransform::Rotate(const _F32& a_PitchRadian, const _F32& a_YawRadian, const _F32& a_RollRadian)
{
	TRANSFORM_PITCH += a_PitchRadian;
	TRANSFORM_YAW += a_YawRadian;
	TRANSFORM_ROLL += a_RollRadian;
	CalcDirection();
}

void Miracle::MTransform::Rotate(const Vector3f& a_RotateRadian)
{
	Rotate(a_RotateRadian[0], a_RotateRadian[1], a_RotateRadian[2]);
}

void Miracle::MTransform::RotatePitchAndYaw(const _F32& a_PitchRadian, const _F32& a_YawRadian)
{
	TRANSFORM_PITCH += a_PitchRadian;
	TRANSFORM_YAW += a_YawRadian;
	CalcDirection();
}

void Miracle::MTransform::RotatePitchAndYaw(const Vector2f& a_RotateRadian)
{
	RotatePitchAndYaw(a_RotateRadian[0], a_RotateRadian[1]);
}

void Miracle::MTransform::RotateYawAndRoll(const _F32& a_YawRadian, const _F32& a_RollRadian)
{
	TRANSFORM_YAW += a_YawRadian;
	TRANSFORM_ROLL += a_RollRadian;
	CalcDirection();
}

void Miracle::MTransform::RotateYawAndRoll(const Vector2f& a_RotateRadian)
{
	RotateYawAndRoll(a_RotateRadian[0], a_RotateRadian[1]);
}

void Miracle::MTransform::RotateRollAndPitch(const _F32& a_RollRadian, const _F32& a_PitchRadian)
{
	TRANSFORM_PITCH += a_PitchRadian;
	TRANSFORM_ROLL += a_RollRadian;
	CalcDirection();
}

void Miracle::MTransform::RotateRollAndPitch(const Vector2f& a_RotateRadian)
{
	RotateRollAndPitch(a_RotateRadian[0], a_RotateRadian[1]);
}

void Miracle::MTransform::RotatePitch(const _F32& a_Radian)
{
	TRANSFORM_PITCH += a_Radian;
	CalcDirection();
}

void Miracle::MTransform::RotateYaw(const _F32& a_Radian)
{
	TRANSFORM_YAW += a_Radian;
	CalcDirection();
}

void Miracle::MTransform::RotateRoll(const _F32& a_Radian)
{
	TRANSFORM_ROLL += a_Radian;
	CalcDirection();
}

void Miracle::MTransform::Move(const Vector3f& a_Displacement)
{
	m_Translate += a_Displacement;
}

void Miracle::MTransform::Move(const _F32& a_x, const _F32& a_y, const _F32& a_z)
{
	Move(Vector3f(a_x,a_y,a_z));
}

void Miracle::MTransform::MoveXY(const Vector2f& a_Displacement)
{
	MoveXY(a_Displacement[0], a_Displacement[1]);
}

void Miracle::MTransform::MoveXY(const _F32& a_x, const _F32& a_y)
{
	TRANSFORM_TRANSLATE_X += a_x;
	TRANSFORM_TRANSLATE_Y += a_y;
}

void Miracle::MTransform::MoveYZ(const Vector2f& a_Displacement)
{
	MoveYZ(a_Displacement[0], a_Displacement[1]);
}

void Miracle::MTransform::MoveYZ(const _F32& a_y, const _F32& a_z)
{
	TRANSFORM_TRANSLATE_Y += a_y;
	TRANSFORM_TRANSLATE_Z += a_z;
}

void Miracle::MTransform::MoveZX(const Vector2f& a_Displacement)
{
	MoveZX(a_Displacement[0], a_Displacement[1]);
}

void Miracle::MTransform::MoveZX(const _F32& a_z, const _F32& a_x)
{
	TRANSFORM_TRANSLATE_Z += a_z;
	TRANSFORM_TRANSLATE_X += a_x;
}

void Miracle::MTransform::MoveX(const _F32& a_x)
{
	TRANSFORM_TRANSLATE_X += a_x;
}

void Miracle::MTransform::MoveY(const _F32& a_y)
{
	TRANSFORM_TRANSLATE_Y += a_y;
}

void Miracle::MTransform::MoveZ(const _F32& a_z)
{
	TRANSFORM_TRANSLATE_Z += a_z;
}

void Miracle::MTransform::Zoom(const Vector3f& a_Scale)
{
	m_Scale3D += a_Scale;
}

void Miracle::MTransform::Zoom(const _F32& a_x, const _F32& a_y, const _F32& a_z)
{
	Zoom(Vector3f(a_x, a_y, a_z));
}

void Miracle::MTransform::ZoomXY(const Vector2f& a_ScaleXY)
{
	ZoomXY(a_ScaleXY[0], a_ScaleXY[1]);
}

void Miracle::MTransform::ZoomXY(const _F32& a_x, const _F32& a_y)
{
	TRANSFORM_SCALE_X += a_x;
	TRANSFORM_SCALE_Y += a_y;
}

void Miracle::MTransform::ZoomYZ(const Vector2f& a_ScaleYZ)
{
	ZoomXY(a_ScaleYZ[0], a_ScaleYZ[1]);
}

void Miracle::MTransform::ZoomYZ(const _F32& a_y, const _F32& a_z)
{
	TRANSFORM_SCALE_Y += a_y;
	TRANSFORM_SCALE_Z += a_z;
}

void Miracle::MTransform::ZoomZX(const Vector2f& a_ScaleZX)
{
	ZoomXY(a_ScaleZX[0], a_ScaleZX[1]);
}

void Miracle::MTransform::ZoomZX(const _F32& a_z, const _F32& a_x)
{
	TRANSFORM_SCALE_Z += a_z;
	TRANSFORM_SCALE_X += a_x;
}

void Miracle::MTransform::ZoomX(const _F32& a_x)
{
	TRANSFORM_SCALE_X += a_x;
}

void Miracle::MTransform::ZoomY(const _F32& a_y)
{
	TRANSFORM_SCALE_Y += a_y;
}


void Miracle::MTransform::ZoomZ(const _F32& a_z)
{
	TRANSFORM_SCALE_Z += a_z;
}

void Miracle::MTransform::CalcDirection()
{
	Quaternion<float> RotationQuat = Quaternion<float>::FromEulerAngles(m_Rotation);
	m_Direction = RotationQuat * s_DefuatDirection * RotationQuat.Inverse();
}

Vector3f Miracle::MTransform::GetUpDirection()
{
	Vector3f Right = Vector3f::CrossProduct(m_Direction.vector(), s_UpAixs);
	return Vector3f::CrossProduct(Right, m_Direction.vector());
}

Vector3f Miracle::MTransform::GetRightDirection()
{
	return Vector3f::CrossProduct(m_Direction.vector(), s_UpAixs);
}

