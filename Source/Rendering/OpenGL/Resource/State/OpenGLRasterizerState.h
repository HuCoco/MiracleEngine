#pragma once
#include <Rendering/OpenGL/Resource/State/OpenGLState.h>
#include <Rendering/Base/Resource/State/RasterizerState.h>

NAMESPACE_MENGINE_BEGIN

class OpenGLRasterizerState : public OpenGLState
{
public:
	OpenGLRasterizerState(RasterizerState* a_RasterizerState);
	virtual ~OpenGLRasterizerState();

	static std::shared_ptr<RenderResource> Create(void* a_Stupid, GraphicsObject* a_GraphicsResource);

	inline RasterizerState* GetRasterizerState() const;

	void Enable();

private:
	GLenum m_FillMode;
	GLenum m_CullFace;
	GLenum m_FrontFace;
	float m_DepthScale;
	float m_DepthBias;
	GLboolean m_EnableScissor;

	static const GLenum FillMode[];
	static const GLenum CullFace[];
};

inline RasterizerState* OpenGLRasterizerState::GetRasterizerState() const
{
	return static_cast<RasterizerState*>(m_pGraphicsObject);
}

NAMESPACE_MENGINE_END
