#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Core/Mathematics/GraphicsMathematics.h>

struct CameraSpaceMatrix
{
	Vector3f Position			{Vector3f(0.0f, 0.0f, 0.0f)};
	Matrix4f ViewSpaceMatrix	{ Matrix4f::Identity() };
	Matrix4f ProjectionMatrix	{ Matrix4f::Identity() };
	
	CameraSpaceMatrix() = default;

};