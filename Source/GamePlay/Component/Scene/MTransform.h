#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Core/Mathematics/GraphicsMathematics.h>

NAMESPACE_MENGINE_BEGIN


#define TRANSFORM_PITCH			m_Rotation[0]
#define TRANSFORM_YAW			m_Rotation[1]
#define TRANSFORM_ROLL			m_Rotation[2]
#define TRANSFORM_TRANSLATE_X	m_Translate[0]
#define TRANSFORM_TRANSLATE_Y	m_Translate[1]
#define TRANSFORM_TRANSLATE_Z	m_Translate[2]
#define TRANSFORM_SCALE_X		m_Scale3D[0]
#define TRANSFORM_SCALE_Y		m_Scale3D[1]
#define TRANSFORM_SCALE_Z		m_Scale3D[2]

class MTransform
{
public:
	MTransform();
	MTransform(const Vector3f& a_Rotation, const Vector3f& a_Translate, const Vector3f& a_Scale3D);
	~MTransform();

	// Output Matrix Function
	Matrix4f ToMartix4f();

	// Modify Function
	void Rotate(const _F32& a_PitchRadian, const _F32& a_YawRadian, const _F32& a_RollRadian);
	void Rotate(const Vector3f& a_RotateRadian);
	void RotatePitchAndYaw(const _F32& a_PitchRadian, const _F32& a_YawRadian);
	void RotatePitchAndYaw(const Vector2f& a_RotateRadian);
	void RotateYawAndRoll(const _F32& a_YawRadian, const _F32& a_RollRadian);
	void RotateYawAndRoll(const Vector2f& a_RotateRadian);
	void RotateRollAndPitch(const _F32& a_RollRadian, const _F32& a_PitchRadian);
	void RotateRollAndPitch(const Vector2f& a_RotateRadian);
	void RotatePitch(const _F32& a_Radian);
	void RotateYaw(const _F32& a_Radian);
	void RotateRoll(const _F32& a_Radian);

	void Move(const Vector3f& a_Displacement);
	void Move(const _F32& a_x, const _F32& a_y, const _F32& a_z);
	void MoveXY(const Vector2f& a_Displacement);
	void MoveXY(const _F32& a_x, const _F32& a_y);
	void MoveYZ(const Vector2f& a_Displacement);
	void MoveYZ(const _F32& a_y, const _F32& a_z);
	void MoveZX(const Vector2f& a_Displacement);
	void MoveZX(const _F32& a_z, const _F32& a_x);
	void MoveX(const _F32& a_x);
	void MoveY(const _F32& a_y);
	void MoveZ(const _F32& a_z);
	
	void Zoom(const Vector3f& a_Scale);
	void Zoom(const _F32& a_x, const _F32& a_y, const _F32& a_z);
	void ZoomXY(const Vector2f& a_ScaleXY);
	void ZoomXY(const _F32& a_x, const _F32& a_y);
	void ZoomYZ(const Vector2f& a_ScaleYZ);
	void ZoomYZ(const _F32& a_y, const _F32& a_z);
	void ZoomZX(const Vector2f& a_ScaleZX);
	void ZoomZX(const _F32& a_z, const _F32& a_x);
	void ZoomX(const _F32& a_x);
	void ZoomY(const _F32& a_y);
	void ZoomZ(const _F32& a_z);




	// Rotation Function
	inline const Vector3f& GetRotation() const
	{
		return m_Rotation;
	}

	inline _F32 GetRotationPitch() const
	{
		return TRANSFORM_PITCH;
	}

	inline _F32 GetRotationYaw() const
	{
		return TRANSFORM_YAW;
	}

	inline _F32 GetRotationRoll() const
	{
		return TRANSFORM_ROLL;
	}

	inline void SetRotation(const Vector3f& a_Rotation)
	{
		m_Rotation = a_Rotation;
		CalcDirection();
	}

	inline void SetRotationPitch(const _F32& a_Pitch)
	{
		TRANSFORM_PITCH = a_Pitch;
	}

	inline void SetRotationYaw(const _F32& a_Yaw)
	{
		TRANSFORM_YAW = a_Yaw;
	}

	inline void SetRotationRoll(const _F32& a_Roll)
	{
		TRANSFORM_ROLL = a_Roll;
	}

	// Translate Function
	inline const Vector3f& GetTranslate() const
	{
		return m_Translate;
	}

	inline _F32 GetTranslateX() const
	{
		return TRANSFORM_TRANSLATE_X;
	}

	inline _F32 GetTranslateY() const
	{
		return TRANSFORM_TRANSLATE_Y;
	}

	inline _F32 GetTranslateZ() const
	{
		return TRANSFORM_TRANSLATE_Z;
	}

	inline void SetTranslate(const Vector3f& a_Translate)
	{
		m_Translate = a_Translate;
	}

	inline void SetTranslateX(const _F32& a_x)
	{
		TRANSFORM_TRANSLATE_X = a_x;
	}

	inline void SetTranslateY(const _F32& a_y)
	{
		TRANSFORM_TRANSLATE_Y = a_y;
	}

	inline void SetTranslateZ(const _F32& a_z)
	{
		TRANSFORM_TRANSLATE_Z = a_z;
	}


	// Scale3D Function

	inline const Vector3f& GetScale3D() const
	{
		return m_Scale3D;
	}

	inline const _F32 GetScale3DX() const
	{
		return TRANSFORM_SCALE_X;
	}

	inline const _F32 GetScale3DY() const
	{
		return TRANSFORM_SCALE_Y;
	}

	inline const _F32 GetScale3DZ() const
	{
		return TRANSFORM_SCALE_Z;
	}

	inline void SetScale3D(const Vector3f& a_Scale3D)
	{
		m_Scale3D = a_Scale3D;
	}

	inline void SetScale3DX(const _F32& a_x)
	{
		TRANSFORM_SCALE_X = a_x;
	}

	inline void SetScale3DY(const _F32& a_y)
	{
		TRANSFORM_SCALE_Y = a_y;
	}

	inline void SetScale3DZ(const _F32& a_z)
	{
		TRANSFORM_SCALE_Z = a_z;
	}

	inline const Vector3f& GetDirection() const
	{
		return m_Direction.vector();
	}

	// Operator Function
	inline MTransform operator+ (const MTransform& a_Other)
	{
		return MTransform(m_Rotation + a_Other.GetRotation(), m_Translate + a_Other.GetTranslate(), m_Scale3D * a_Other.GetScale3D());
	}

	Vector3f GetUpDirection();
	Vector3f GetRightDirection();

private:
	void CalcDirection();


protected:
	Vector3f m_Rotation;
	Quaternion<float> m_Direction;
	Vector3f m_Translate;
	Vector3f m_Scale3D;

	static const Quaternion<float> s_DefuatDirection;
	static const Vector3f s_UpAixs;
};

NAMESPACE_MENGINE_END