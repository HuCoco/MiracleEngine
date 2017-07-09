#include <Rendering/OpenGL/Resource/State/OpenGLRasterizerState.h>


const GLenum Miracle::OpenGLRasterizerState::FillMode[] =
{
	GL_FILL,
	GL_LINE
};

const GLenum Miracle::OpenGLRasterizerState::CullFace[] =
{
	0,
	GL_FRONT,
	GL_BACK
};


Miracle::OpenGLRasterizerState::OpenGLRasterizerState(RasterizerState* a_RasterizerState)
	: OpenGLState(a_RasterizerState)
{
	m_FillMode = FillMode[a_RasterizerState->fillMode];
	m_CullFace = CullFace[a_RasterizerState->cullMode];
	m_FrontFace = (a_RasterizerState->frontCCW ? GL_CCW : GL_CW);
	m_DepthScale = a_RasterizerState->slopeScaledDepthBias;
	m_DepthBias = static_cast<float>(a_RasterizerState->depthBias);
	m_EnableScissor = (a_RasterizerState->enableScissor ? GL_TRUE : GL_FALSE);
}

Miracle::OpenGLRasterizerState::~OpenGLRasterizerState()
{

}

void Miracle::OpenGLRasterizerState::Enable()
{
	glPolygonMode(GL_FRONT_AND_BACK, m_FillMode);

	if (m_CullFace != 0)
	{
		glEnable(GL_CULL_FACE);
		glFrontFace(m_FrontFace);
		glCullFace(m_CullFace);
	}
	else
	{
		glDisable(GL_CULL_FACE);
	}

	if (m_DepthScale != 0.0f && m_DepthBias != 0.0f)
	{
		glEnable(GL_POLYGON_OFFSET_FILL);
		glEnable(GL_POLYGON_OFFSET_LINE);
		glEnable(GL_POLYGON_OFFSET_POINT);
		glPolygonOffset(m_DepthScale, m_DepthBias);
	}
	else
	{
		glDisable(GL_POLYGON_OFFSET_FILL);
		glDisable(GL_POLYGON_OFFSET_LINE);
		glDisable(GL_POLYGON_OFFSET_POINT);
	}
}

std::shared_ptr<Miracle::RenderResource> Miracle::OpenGLRasterizerState::Create(void* a_Stupid, GraphicsObject* a_GraphicsResource)
{
	if (a_GraphicsResource->GetType() == GraphicsObject::RASTERIZER_STATE)
	{
		return std::make_shared<OpenGLRasterizerState>(static_cast<RasterizerState*>(a_GraphicsResource));
	}

	MENGINE_ASSERT_MSG(false, "Invalid object type.");
	return nullptr;
}
