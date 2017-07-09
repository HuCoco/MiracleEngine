#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <ThirdParty/GraphicsKit/OpenGLPreCompileHeader.h>
#include <Rendering/Base/Resource/Buffer/Buffer.h>

NAMESPACE_MENGINE_BEGIN

class ConstantBuffer : public Buffer
{
public:
	ConstantBuffer(size_t a_NumBytes,bool a_AllowDynamicUpdate);
	virtual ~ConstantBuffer();

	enum { INDEX = 0 };

	static const _I32 ShaderDataIndex = ConstantBufferShaderDataIndex;
private:
	size_t GetAlignmentBytes(size_t a_NumBytes);
private:
	static const size_t ALIGNMENT;
};

NAMESPACE_MENGINE_END