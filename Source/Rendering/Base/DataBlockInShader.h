#pragma once
#include <Independent/Platform/PreCompileHeader.h>


NAMESPACE_MENGINE_BEGIN


struct SkyBoxMatrixs
{
	Matrix4f Model;
	Matrix4f View;
	Matrix4f Projection;

	void Transpose()
	{
		Model = Model.Transpose();
		View = View.Transpose();
		Projection = Projection.Transpose();
	}
};

struct __declspec(align(16)) AffineMatrixs
{
	Matrix4f Model;
	Matrix4f InverseModel;
	Matrix4f View;
	Matrix4f Projection;

	void Transpose()
	{
		Model = Model.Transpose();
		InverseModel = InverseModel.Transpose();
		View = View.Transpose();
		Projection = Projection.Transpose();
	}
};

struct OpenGLAffineMatrixs
{
	Matrix4f Model;
	Matrix4f View;
	Matrix4f Projection;
};

struct DirectionalLightBlock
{
	Vector4f Direction;
	Vector4f Ambient;
	Vector4f Diffuse;
	Vector4f Specular;
};

struct PointLightBlock
{
	Vector4f Position;
	Vector4f Ambient;
	Vector4f Diffuse;
	Vector4f Specular;
	_F32 Constant;
	_F32 Linear;
	_F32 Quadratic;

};

struct Spotlight
{
	Vector4f Position;
	Vector4f Direction;
	Vector4f Ambient;
	Vector4f Diffuse;
	Vector4f Specular;
	_F32 Constant;
	_F32 CutOff;
	_F32 Linear;
	_F32 Quadratic;
};

class MaterialBlock
{
public:
	MaterialBlock() = delete;

	struct Common
	{
		Vector4f Ambient;
		Vector4f Diffuse;
		Vector4f Specular;
		_F32 Shininess;
	};

	struct UseDiffuseTex
	{
		Vector4f Specular;
		_F32 Shininess;
	};

	struct UseSpecularTex
	{
		_F32 Shininess;
	};
};

NAMESPACE_MENGINE_END