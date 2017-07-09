#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/OpenGL/Resource/State/OpenGLState.h>
#include <Rendering/Base/Resource/State/BlendState.h>


NAMESPACE_MENGINE_BEGIN

class OpenGLBlendState : public OpenGLState
{
public:
	OpenGLBlendState(BlendState* a_BlendState);
	virtual ~OpenGLBlendState();

	static std::shared_ptr<RenderResource> Create(void* a_Stupid, GraphicsObject* a_GraphicsResource);

	inline BlendState* GetBlendState() const;

	void Enable();

private:
	struct Target
	{
		GLboolean enable;
		GLenum srcColor;
		GLenum dstColor;
		GLenum opColor;
		GLenum srcAlpha;
		GLenum dstAlpha;
		GLenum opAlpha;
		GLboolean rMask;
		GLboolean gMask;
		GLboolean bMask;
		GLboolean aMask;
	};

	bool m_EnableAlphaToCoverage;
	bool m_EnableIndependentBlend;
	Target m_Target[BlendState::NUM_TARGETS];
	Vector4f m_BlendColor;
	_U32 m_SampleMask;

	static const GLenum Mode[];
	static const GLenum Operation[];
};

inline BlendState* OpenGLBlendState::GetBlendState() const
{
	return static_cast<BlendState*>(m_pGraphicsObject);
}

NAMESPACE_MENGINE_END