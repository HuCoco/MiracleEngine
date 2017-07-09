#include <Rendering/OpenGL/Resource/State/OpenGLBlendState.h>

const GLenum Miracle::OpenGLBlendState::Mode[] =
{
	GL_ZERO,
	GL_ONE,
	GL_SRC_COLOR,
	GL_ONE_MINUS_SRC_COLOR,
	GL_SRC_ALPHA,
	GL_ONE_MINUS_SRC_ALPHA,
	GL_DST_ALPHA,
	GL_ONE_MINUS_DST_ALPHA,
	GL_DST_COLOR,
	GL_ONE_MINUS_DST_COLOR,
	GL_SRC_ALPHA_SATURATE,
	GL_CONSTANT_COLOR,
	GL_ONE_MINUS_CONSTANT_COLOR,
	GL_SRC1_COLOR,
	GL_ONE_MINUS_SRC1_COLOR,
	GL_SRC1_ALPHA,
	GL_ONE_MINUS_SRC1_ALPHA
};

const GLenum Miracle::OpenGLBlendState::Operation[] =
{
	GL_FUNC_ADD,
	GL_FUNC_SUBTRACT,
	GL_FUNC_REVERSE_SUBTRACT,
	GL_MIN,
	GL_MAX
};

Miracle::OpenGLBlendState::OpenGLBlendState(BlendState* a_BlendState)
	: OpenGLState(a_BlendState)
{
	m_EnableAlphaToCoverage = a_BlendState->enableAlphaToCoverage;
	m_EnableIndependentBlend = a_BlendState->enableIndependentBlend;
	for (_U32 i = 0; i < BlendState::NUM_TARGETS; ++i)
	{
		BlendState::Target const& input = a_BlendState->target[i];
		Target& output = m_Target[i];
		output.enable = (input.enable ? GL_TRUE : GL_FALSE);
		output.srcColor = Mode[input.srcColor];
		output.dstColor = Mode[input.dstColor];
		output.opColor = Operation[input.opColor];
		output.srcAlpha = Mode[input.srcAlpha];
		output.dstAlpha = Mode[input.dstAlpha];
		output.opAlpha = Operation[input.opAlpha];
		output.rMask = (input.mask & 1 ? GL_TRUE : GL_FALSE);
		output.gMask = (input.mask & 2 ? GL_TRUE : GL_FALSE);
		output.bMask = (input.mask & 4 ? GL_TRUE : GL_FALSE);
		output.aMask = (input.mask & 8 ? GL_TRUE : GL_FALSE);
	}
	m_BlendColor = a_BlendState->blendColor;
	m_SampleMask = a_BlendState->sampleMask;
}

Miracle::OpenGLBlendState::~OpenGLBlendState()
{
}

void Miracle::OpenGLBlendState::Enable()
{
	if (m_EnableAlphaToCoverage)
	{
		glEnable(GL_SAMPLE_COVERAGE);
	}
	else
	{
		glDisable(GL_SAMPLE_COVERAGE);
	}

	if (m_EnableIndependentBlend)
	{
		for (unsigned int i = 0; i < BlendState::NUM_TARGETS; ++i)
		{
			Target const& target = m_Target[i];
			if (target.enable)
			{
				glEnable(GL_BLEND);
				glBlendFuncSeparatei(i, target.srcColor, target.dstColor,
					target.srcAlpha, target.dstAlpha);
				glBlendEquationSeparatei(i, target.opColor, target.opAlpha);
			}
			else
			{
				glDisable(GL_BLEND);
			}
			glColorMaski(i, target.rMask, target.gMask, target.bMask, target.aMask);
			glSampleMaski(i, m_SampleMask);
		}
	}
	else
	{
		Target const& target = m_Target[0];
		if (target.enable)
		{
			glEnable(GL_BLEND);
			glBlendFuncSeparate(target.srcColor, target.dstColor,
				target.srcAlpha, target.dstAlpha);
			glBlendEquationSeparate(target.opColor, target.opAlpha);
		}
		else
		{
			glDisable(GL_BLEND);
		}
		glColorMask(target.rMask, target.gMask, target.bMask, target.aMask);
		glSampleMaski(0, m_SampleMask);
	}

	glBlendColor(m_BlendColor[0], m_BlendColor[1], m_BlendColor[2], m_BlendColor[3]);
}

std::shared_ptr<Miracle::RenderResource> Miracle::OpenGLBlendState::Create(void* a_Stupid, GraphicsObject* a_GraphicsResource)
{
	if (a_GraphicsResource->GetType() == GraphicsObject::BLEND_STATE)
	{
		return std::make_shared<OpenGLBlendState>(static_cast<BlendState*>(a_GraphicsResource));
	}

	MENGINE_ASSERT_MSG(false,"Invalid object type.");
	return nullptr;
}

