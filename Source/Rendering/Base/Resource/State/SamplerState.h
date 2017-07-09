#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <ThirdParty/GraphicsKit/OpenGLPreCompileHeader.h>
#include <Rendering/Base/Resource/State/State.h>
#include <Core/Mathematics/GraphicsMathematics.h>
NAMESPACE_MENGINE_BEGIN

class SamplerState : public State
{
public:

	enum Filter
	{
		MIN_P_MAG_P_MIP_P,
		MIN_P_MAG_P_MIP_L,
		MIN_P_MAG_L_MIP_P,
		MIN_P_MAG_L_MIP_L,
		MIN_L_MAG_P_MIP_P,
		MIN_L_MAG_P_MIP_L,
		MIN_L_MAG_L_MIP_P,
		MIN_L_MAG_L_MIP_L,
		ANISOTROPIC,
		COMPARISON_MIN_P_MAG_P_MIP_P,
		COMPARISON_MIN_P_MAG_P_MIP_L,
		COMPARISON_MIN_P_MAG_L_MIP_P,
		COMPARISON_MIN_P_MAG_L_MIP_L,
		COMPARISON_MIN_L_MAG_P_MIP_P,
		COMPARISON_MIN_L_MAG_P_MIP_L,
		COMPARISON_MIN_L_MAG_L_MIP_P,
		COMPARISON_MIN_L_MAG_L_MIP_L,
		COMPARISON_ANISOTROPIC
	};

	enum Mode
	{
		WRAP,
		MIRROR,
		CLAMP,
		BORDER,
		MIRROR_ONCE
	};

	enum Comparison
	{
		NEVER,
		LESS,
		EQUAL,
		LESS_EQUAL,
		GREATER,
		NOT_EQUAL,
		GREATER_EQUAL,
		ALWAYS
	};

	SamplerState();
	virtual ~SamplerState();


	Filter filter;
	Mode mode[3];
	_F32 mipLODBias;
	_U32 maxAnisotropy;
	Vector4f borderColor;
	Comparison comparison;

	_F32 minLOD;
	_F32 maxLOD;

	static const _I32 ShaderDataIndex = SamplerStateShaderDataIndex;
};

NAMESPACE_MENGINE_END