#include <Rendering/OpenGL/Resource/State/OpenGLDepthStencilState.h>

const GLboolean Miracle::OpenGLDepthStencilState::WriteMask[] =
{
	GL_FALSE,
	GL_TRUE
};

const GLenum Miracle::OpenGLDepthStencilState::Comparison[] =
{
	GL_NEVER,
	GL_LESS,
	GL_EQUAL,
	GL_LEQUAL,
	GL_GREATER,
	GL_NOTEQUAL,
	GL_GEQUAL,
	GL_ALWAYS
};

const GLenum Miracle::OpenGLDepthStencilState::Operation[] =
{
	GL_KEEP,
	GL_ZERO,
	GL_REPLACE,
	GL_INCR,  
	GL_DECR,  
	GL_INVERT,
	GL_INCR,
	GL_DECR
};

Miracle::OpenGLDepthStencilState::OpenGLDepthStencilState(DepthStencilState* a_DepthStencilState)
	:OpenGLState(a_DepthStencilState)
{
	m_DepthEnable = (a_DepthStencilState->depthEnable ? GL_TRUE : GL_FALSE);
	m_WriteMask = WriteMask[a_DepthStencilState->writeMask];
	m_Comparison = Comparison[a_DepthStencilState->comparison];
	m_StencilEnable = (a_DepthStencilState->stencilEnable ? GL_TRUE : GL_FALSE);
	m_StencilReadMask = a_DepthStencilState->stencilReadMask;
	m_StencilWriteMask = a_DepthStencilState->stencilWriteMask;
	DepthStencilState::Face front = a_DepthStencilState->frontFace;
	m_FrontFace.onFail = Operation[front.fail];
	m_FrontFace.onZFail = Operation[front.depthFail];
	m_FrontFace.onZPass = Operation[front.pass];
	m_FrontFace.comparison = Comparison[front.comparison];
	DepthStencilState::Face back = a_DepthStencilState->backFace;
	m_BackFace.onFail = Operation[back.fail];
	m_BackFace.onZFail = Operation[back.depthFail];
	m_BackFace.onZPass = Operation[back.pass];
	m_BackFace.comparison = Comparison[back.comparison];
	m_Reference = a_DepthStencilState->reference;
}

Miracle::OpenGLDepthStencilState::~OpenGLDepthStencilState()
{

}

void Miracle::OpenGLDepthStencilState::Enable()
{
	if (m_DepthEnable)
	{
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(m_Comparison);
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
	}

	glDepthMask(m_WriteMask);

	if (m_StencilEnable)
	{
		glEnable(GL_STENCIL_TEST);

		glStencilFuncSeparate(GL_FRONT, m_FrontFace.comparison, m_Reference, m_StencilReadMask);
		glStencilMaskSeparate(GL_FRONT, m_StencilWriteMask);
		glStencilOpSeparate(GL_FRONT, m_FrontFace.onFail, m_FrontFace.onZFail, m_FrontFace.onZPass);
		glStencilFuncSeparate(GL_BACK, m_BackFace.comparison, m_Reference, m_StencilReadMask);
		glStencilMaskSeparate(GL_BACK, m_StencilWriteMask);
		glStencilOpSeparate(GL_BACK, m_BackFace.onFail, m_BackFace.onZFail, m_BackFace.onZPass);
	}
	else
	{
		glDisable(GL_STENCIL_TEST);
	}
}

std::shared_ptr<Miracle::RenderResource> Miracle::OpenGLDepthStencilState::Create(void* a_Stupid, GraphicsObject* a_GraphicsResource)
{
	if (a_GraphicsResource->GetType() == GraphicsObject::DEPTH_STENCIL_STATE)
	{
		return std::make_shared<OpenGLDepthStencilState>(static_cast<DepthStencilState*>(a_GraphicsResource));
	}

	MENGINE_ASSERT_MSG(false, "Invalid object type.");
	return nullptr;
}
