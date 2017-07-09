#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <ThirdParty/GraphicsKit/DirectXPreCompileHeader.h>
#include <Rendering/Base/Shaders/VisualProgram.h>

NAMESPACE_MENGINE_BEGIN

class HLSLVisualProgram : public VisualProgram
{
public:
	HLSLVisualProgram();
	virtual ~HLSLVisualProgram();
};

NAMESPACE_MENGINE_END