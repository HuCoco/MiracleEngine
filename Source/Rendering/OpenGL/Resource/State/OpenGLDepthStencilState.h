#pragma once
#include <Rendering/OpenGL/Resource/State/OpenGLState.h>
#include <Rendering/Base/Resource/State/DepthStencilState.h>

NAMESPACE_MENGINE_BEGIN

class OpenGLDepthStencilState : public OpenGLState
{
public:
	OpenGLDepthStencilState(DepthStencilState* a_DepthStencilState);
	virtual ~OpenGLDepthStencilState();

	static std::shared_ptr<RenderResource> Create(void* a_Stupid, GraphicsObject* a_GraphicsResource);

	inline DepthStencilState* GetDepthStencilState() const;

	void Enable();

private:
	struct Face
	{
		GLenum onFail;
		GLenum onZFail;
		GLenum onZPass;
		GLenum comparison;
	};

	GLboolean m_DepthEnable;
	GLboolean m_WriteMask;
	GLenum m_Comparison;
	GLboolean m_StencilEnable;
	GLuint m_StencilReadMask;
	GLuint m_StencilWriteMask;
	Face m_FrontFace;
	Face m_BackFace;
	GLuint m_Reference;

	static const GLboolean WriteMask[];
	static const GLenum Comparison[];
	static const GLenum Operation[];
};

inline DepthStencilState* OpenGLDepthStencilState::GetDepthStencilState() const
{
	return static_cast<DepthStencilState*>(m_pGraphicsObject);
}

NAMESPACE_MENGINE_END