#include "PerspectiveCameraComponent.h"



Miracle::PerspectiveCameraComponent::PerspectiveCameraComponent()
	: m_Fov(MENGINE_PI / 4.0f)
	, m_Aspect(1920.0f / 1080.0f)
	, m_NearPlane(0.1f)
	, m_FarPlane(1000.0f)
{
}


Miracle::PerspectiveCameraComponent::~PerspectiveCameraComponent()
{
}

void Miracle::PerspectiveCameraComponent::CameraUpdateFunc()
{
	auto transfrom = GetTransfomInWorldSpace();
	auto Front = transfrom.GetDirection();
	auto Up = transfrom.GetUpDirection();
	m_CameraSpaceMatrix.Position = transfrom.GetTranslate();
	m_CameraSpaceMatrix.ViewSpaceMatrix = Matrix4f::LookTo(Front, transfrom.GetTranslate(), Up);
	m_CameraSpaceMatrix.ProjectionMatrix = Matrix4f::Perspective(m_Fov, m_Aspect, m_NearPlane, m_FarPlane);
}
