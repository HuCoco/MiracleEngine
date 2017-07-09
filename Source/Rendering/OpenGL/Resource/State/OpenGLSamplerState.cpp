#include <Rendering/OpenGL/Resource/State/OpenGLSamplerState.h>

const GLint Miracle::OpenGLSamplerState::Mode[] =
{
	GL_REPEAT,          // WRAP
	GL_MIRRORED_REPEAT, // MIRROR
	GL_CLAMP_TO_EDGE,   // CLAMP
	GL_CLAMP_TO_BORDER, // BORDER
	GL_MIRRORED_REPEAT  // MIRROR_ONCE
};


Miracle::OpenGLSamplerState::OpenGLSamplerState(SamplerState* a_SamplerState)
	: OpenGLState(a_SamplerState)
{
	glGenSamplers(1, &m_Handle);

	glSamplerParameteri(m_Handle, GL_TEXTURE_WRAP_S, Mode[a_SamplerState->mode[0]]);
	glSamplerParameteri(m_Handle, GL_TEXTURE_WRAP_T, Mode[a_SamplerState->mode[1]]);
	glSamplerParameteri(m_Handle, GL_TEXTURE_WRAP_R, Mode[a_SamplerState->mode[2]]);

	// TODO - GL_TEXTURE_MAX_ANISOTROPY_EXT is not defined?
	// glSamplerParameterf(samplerState, GL_TEXTURE_MAX_ANISOTROPY_EXT, samplerState->maxAnisotropy);

	glSamplerParameterf(m_Handle, GL_TEXTURE_MIN_LOD, a_SamplerState->minLOD);
	glSamplerParameterf(m_Handle, GL_TEXTURE_MAX_LOD, a_SamplerState->maxLOD);
	glSamplerParameterf(m_Handle, GL_TEXTURE_LOD_BIAS, a_SamplerState->mipLODBias);

	float borderColor[4];
	borderColor[0] = a_SamplerState->borderColor[0];
	borderColor[1] = a_SamplerState->borderColor[1];
	borderColor[2] = a_SamplerState->borderColor[2];
	borderColor[3] = a_SamplerState->borderColor[3];
	glSamplerParameterfv(m_Handle, GL_TEXTURE_BORDER_COLOR, borderColor);

	switch (a_SamplerState->filter)
	{
	case SamplerState::MIN_P_MAG_P_MIP_P:
		glSamplerParameteri(m_Handle, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glSamplerParameteri(m_Handle, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		break;
	case SamplerState::MIN_P_MAG_P_MIP_L:
		glSamplerParameteri(m_Handle, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glSamplerParameteri(m_Handle, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		break;
	case SamplerState::MIN_P_MAG_L_MIP_P:
		glSamplerParameteri(m_Handle, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glSamplerParameteri(m_Handle, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	case SamplerState::MIN_P_MAG_L_MIP_L:
		glSamplerParameteri(m_Handle, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glSamplerParameteri(m_Handle, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	case SamplerState::MIN_L_MAG_P_MIP_P:
		glSamplerParameteri(m_Handle, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glSamplerParameteri(m_Handle, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		break;
	case SamplerState::MIN_L_MAG_P_MIP_L:
		glSamplerParameteri(m_Handle, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glSamplerParameteri(m_Handle, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		break;
	case SamplerState::MIN_L_MAG_L_MIP_P:
		glSamplerParameteri(m_Handle, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glSamplerParameteri(m_Handle, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	case SamplerState::MIN_L_MAG_L_MIP_L:
		glSamplerParameteri(m_Handle, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glSamplerParameteri(m_Handle, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	default:
		MENGINE_ASSERT_MSG(false, "OpenGL does not support.");
		glSamplerParameteri(m_Handle, GL_TEXTURE_MAG_FILTER, 0);
		glSamplerParameteri(m_Handle, GL_TEXTURE_MIN_FILTER, 0);
		break;
	}
}

Miracle::OpenGLSamplerState::~OpenGLSamplerState()
{
}

std::shared_ptr<Miracle::RenderResource> Miracle::OpenGLSamplerState::Create(void* a_Stupid, GraphicsObject* a_GraphicsResource)
{
	if (a_GraphicsResource->GetType() == GraphicsObject::SAMPLER_STATE)
	{
		return std::make_shared<OpenGLSamplerState>(static_cast<SamplerState*>(a_GraphicsResource));
	}

	MENGINE_ASSERT_MSG(false, "Invalid object type.");
	return nullptr;
}
