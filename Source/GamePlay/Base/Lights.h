#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Core/Mathematics/GraphicsMathematics.h>


static const _U32 MAX_NUM_OF_DIRECTIONAL_LIGHTS = 1;
static const _U32 MAX_NUM_OF_POINT_LIGHTS = 32;
static const _U32 MAX_NUM_OF_SPOT_LIGHTS = 1;

struct DirectionalLight
{
	Vector4f Direction	{ Vector4f(0.0f,0.0f,0.0f,0.0f) };
	Vector4f Ambient	{ Vector4f(0.0f,0.0f,0.0f,0.0f) };
	Vector4f Diffuse	{ Vector4f(0.0f,0.0f,0.0f,0.0f) };
	Vector4f Specular	{ Vector4f(0.0f,0.0f,0.0f,0.0f) };
	Vector4f Color		{ Vector4f(1.0f,1.0f,1.0f,1.0f) };

	DirectionalLight() = default;


	DirectionalLight(const Vector4f& a_Direction, const Vector4f& a_Ambient, const Vector4f& a_Diffuse,
		const Vector4f& a_Specular, const Vector4f& a_Color = Vector4f(1.0f, 1.0f, 1.0f, 1.0f))
		: Direction(a_Direction)
		, Ambient(a_Ambient)
		, Diffuse(a_Diffuse)
		, Specular(a_Specular)
		, Color(a_Color)
	{

	}
};

struct PointLight
{
	Vector4f Position{ Vector4f(0.0f,0.0f,0.0f,0.0f) };
	Vector4f Ambient{ Vector4f(0.0f,0.0f,0.0f,0.0f) };
	Vector4f Diffuse{ Vector4f(0.0f,0.0f,0.0f,0.0f) };
	Vector4f Specular{ Vector4f(0.0f,0.0f,0.0f,0.0f) };
	Vector4f Color{ Vector4f(1.0f,1.0f,1.0f,1.0f) };
	_F32 Constant{ 0.0f };
	_F32 Linear{ 0.0f };
	_F32 Quadratic{ 0.0f };

	PointLight() = default;

	PointLight(const Vector4f& a_Ambient, const Vector4f& a_Diffuse, const Vector4f& a_Specular,
		const _F32& a_Constant, const _F32& a_Linear, const _F32& a_Quadratic,
		const Vector4f& a_Color = Vector4f(1.0f, 1.0f, 1.0f, 1.0f))
		: Ambient(a_Ambient)
		, Diffuse(a_Diffuse)
		, Specular(a_Specular)
		, Constant(a_Constant)
		, Linear(a_Linear)
		, Quadratic(a_Quadratic)
		, Color(a_Color)
	{

	}
};

struct SpotLight
{
	Vector4f Direction{ Vector4f(0.0f,0.0f,0.0f,0.0f) };
	Vector4f Position{ Vector4f(0.0f,0.0f,0.0f,0.0f) };
	Vector4f Ambient{ Vector4f(0.0f,0.0f,0.0f,0.0f) };
	Vector4f Diffuse{ Vector4f(0.0f,0.0f,0.0f,0.0f) };
	Vector4f Specular{ Vector4f(0.0f,0.0f,0.0f,0.0f) };
	Vector4f Color{ Vector4f(1.0f,1.0f,1.0f,1.0f) };
	_F32 Constant{ 0.0f };
	_F32 Linear{ 0.0f };
	_F32 Quadratic{ 0.0f };
	_F32 CutOff{ 0.0f };
	_F32 OuterCutOff{ 0.0f };

	SpotLight() = default;

	SpotLight(const Vector4f& a_Ambient, const Vector4f& a_Diffuse, const Vector4f& a_Specular,
		const _F32& a_Constant, const _F32& a_Linear, const _F32& a_Quadratic, const _F32& a_CutOff, const _F32& a_OuterCutOff,
		const Vector4f& a_Color = Vector4f(1.0f, 1.0f, 1.0f, 1.0f))
		: Ambient(a_Ambient)
		, Diffuse(a_Diffuse)
		, Specular(a_Specular)
		, Constant(a_Constant)
		, Linear(a_Linear)
		, Quadratic(a_Quadratic)
		, CutOff(a_CutOff)
		, OuterCutOff(a_OuterCutOff)
		, Color(a_Color)
	{

	}
};