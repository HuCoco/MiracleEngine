#pragma once
#include <Rendering/OpenGL/Resource/State/OpenGLState.h>
#include <Rendering/Base/Resource/State/SamplerState.h>

NAMESPACE_MENGINE_BEGIN

class OpenGLSamplerState : public OpenGLState
{
public:
	OpenGLSamplerState(SamplerState* a_SamplerState);
	virtual ~OpenGLSamplerState();

	static std::shared_ptr<RenderResource> Create(void* a_Stupid, GraphicsObject* a_GraphicsResource);

	inline SamplerState* GetSamplerState() const;
private:
	static const GLint Mode[];
};

inline SamplerState* OpenGLSamplerState::GetSamplerState() const
{
	return static_cast<SamplerState*>(m_pGraphicsObject);
}

NAMESPACE_MENGINE_END