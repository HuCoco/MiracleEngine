#include <Rendering/OpenGL/OpenGLEngine.h>

#include <Rendering/Base/Resource/Buffer/VertexBuffer.h>
#include <Rendering/Base/Resource/Buffer/IndexBuffer.h>
#include <Rendering/Base/Resource/Buffer/ConstantBuffer.h>

#include <Rendering/Base/Resource/Texture/TextureSingle.h>
#include <Rendering/Base/Resource/Texture/TextureArray.h>
#include <Rendering/Base/Resource/Texture/Texture1D.h>
#include <Rendering/Base/Resource/Texture/Texture2D.h>
#include <Rendering/Base/Resource/Texture/Texture3D.h>

#include <Rendering/OpenGL/Resource/Buffer/OpenGLConstantBuffer.h>
#include <Rendering/OpenGL/Resource/Buffer/OpenGLVertexBuffer.h>
#include <Rendering/OpenGL/Resource/Buffer/OpenGLIndexBuffer.h>
#include <Rendering/OpenGL/Resource/Texture/OpenGLTextureSingle.h>
#include <Rendering/OpenGL/Resource/Texture/OpenGLTexture1D.h>
#include <Rendering/OpenGL/Resource/Texture/OpenGLTexture2D.h>
#include <Rendering/OpenGL/Resource/Texture/OpenGLTexture3D.h>
#include <Rendering/OpenGL/Resource/Texture/OpenGLTextureRenderTarget.h>
#include <Rendering/OpenGL/Resource/Texture/OpenGLTextureDepthStencil.h>
#include <Rendering/OpenGL/Resource/Texture/OpenGLTextureArray.h>
#include <Rendering/OpenGL/Resource/Texture/OpenGLTexture1DArray.h>
#include <Rendering/OpenGL/Resource/Texture/OpenGLTexture2DArray.h>
#include <Rendering/OpenGL/Resource/Texture/OpenGLTextureCube.h>
#include <Rendering/OpenGL/Resource/Texture/OpenGLTextureCubeArray.h>
#include <Rendering/OpenGL/Resource/Texture/OpenGLRenderTarget.h>

#include <Rendering/OpenGL/Resource/State/OpenGLSamplerState.h>
#include <Rendering/OpenGL/Resource/State/OpenGLBlendState.h>
#include <Rendering/OpenGL/Resource/State/OpenGLRasterizerState.h>
#include <Rendering/OpenGL/Resource/State/OpenGLDepthStencilState.h>

#include <Rendering/OpenGL/Shaders/GLSLVisualProgram.h>
#include <Rendering/OpenGL/InputLayout/OpenGLInputLayout.h>
#include <Rendering/OpenGL/InputLayout/OpenGLInputLayoutManager.h>

Miracle::OpenGLEngine::OpenGLEngine(GLFWwindow* a_hWnd)
	: m_hWnd(a_hWnd)
{
	m_InputLayoutManager = std::make_unique<OpenGLInputLayoutManager>();

	m_RenderTargetResourceCreator = &OpenGLRenderTarget::Create;
	m_RenderResourceCreators =
	{
		nullptr,							//	GRAPHICS_RESOURCE[abstract]
		nullptr,							//	RESOURCE[abstract] 
		nullptr,							//	BUFFER[abstract]  
		&OpenGLConstantBuffer::Create,		//	CONSTANT_BUFFER,
		nullptr,							//	TEXTURE_BUFFER,
		&OpenGLVertexBuffer::Create,		//	VERTEX_BUFFER,
		&OpenGLIndexBuffer::Create,			//	INDEX_BUFFER,
		nullptr, 							//	TEXTURE[abstract]  
		nullptr, 							//	TEXTURE_SINGLE[abstract] 
		&OpenGLTexture1D::Create,			//	TEXTURE1D,
		&OpenGLTexture2D::Create,			//	TEXTURE2D,
		&OpenGLTextureRenderTarget::Create,	//	TEXTURE_RENDER_TARGET,
		&OpenGLTextureDepthStencil::Create,	//	TEXTURE_DEPTH_STENCIL,
		&OpenGLTexture3D::Create,			//	TEXTURE3D,
		nullptr, 							//	TEXTURE_ARRAY[abstract] 
		&OpenGLTexture1DArray::Create,		//	TEXTURE1D_ARRAY,
		&OpenGLTexture2DArray::Create,		//	TEXTURE2D_ARRAY,
		&OpenGLTextureCube::Create,			//	TEXTURE_CUBE,
		&OpenGLTextureCubeArray::Create,	//	TEXTURE_CUBE_ARRAY,
		nullptr, 							//	SHADER, 
		nullptr, 							//	VERTEX_SHADER,
		nullptr, 							//	GEOMETRY_SHADER,
		nullptr, 							//	PIXEL_SHADER,
		nullptr, 							//	COMPUTE_SHADER,
		nullptr, 							//	STATE[abstract] 
		&OpenGLSamplerState::Create,		//	SAMPLER_STATE,
		&OpenGLBlendState::Create,			//	BLEND_STATE,
		&OpenGLDepthStencilState::Create,	//	DEPTH_STENCIL_STATE,
		&OpenGLRasterizerState::Create		//	RASTERIZER_STATE,
	};						
	CreateDefaultGlobalState();
}


Miracle::OpenGLEngine::~OpenGLEngine()
{
}

bool Miracle::OpenGLEngine::EnableShaders(const std::shared_ptr<VisualEffect>& a_Effect, GLuint program)
{
	VertexShader* vShader = a_Effect->GetVertexShader().get();
	if (!vShader)
	{
		MENGINE_ASSERT_MSG(false, "Effect does not have a vertex shader.");
		return false;
	}

	PixelShader* pShader = a_Effect->GetPixelShader().get();
	if (!pShader)
	{
		MENGINE_ASSERT_MSG(false, "Effect does not have a pixel shader.");
		return false;
	}

	Enable(vShader, program);
	Enable(pShader, program);

	return true;
}

void Miracle::OpenGLEngine::DisableShaders(const std::shared_ptr<VisualEffect>& a_Effect, GLuint program)
{
	VertexShader* vShader = a_Effect->GetVertexShader().get();
	PixelShader* pShader = a_Effect->GetPixelShader().get();
	Disable(vShader, program);
	Disable(pShader, program);
}

void Miracle::OpenGLEngine::Enable(Shader* a_Shader, GLuint a_Program)
{
	EnableCBuffer(a_Shader, a_Program);
	EnableTextures(a_Shader, a_Program);
	EnableTexturesArray(a_Shader, a_Program);
	EnableSamplers(a_Shader, a_Program);
}

void Miracle::OpenGLEngine::Disable(Shader* a_Shader, GLuint a_Program)
{
	DisableCBuffer(a_Shader, a_Program);
	DisableTextures(a_Shader, a_Program);
	DisableTexturesArray(a_Shader, a_Program);
	DisableSamplers(a_Shader, a_Program);
}

void Miracle::OpenGLEngine::Enable(const std::shared_ptr<RenderTarget>& target)
{
	auto gl4Target = static_cast<OpenGLRenderTarget*>(Bind(target));
	gl4Target->Enable();
}

void Miracle::OpenGLEngine::Disable(const std::shared_ptr<RenderTarget>& target)
{
	auto gl4Target = static_cast<OpenGLRenderTarget*>(Get(target));
	if (gl4Target)
	{
		gl4Target->Disable();
	}
}
void Miracle::OpenGLEngine::EnableDepthStencil(const std::shared_ptr<RenderTarget>& target)
{
	auto gl4Target = static_cast<OpenGLRenderTarget*>(Bind(target));
	gl4Target->EnableDepthStencilBuffer();
}

void Miracle::OpenGLEngine::DisableDepthStencil(const std::shared_ptr<RenderTarget>& target)
{
	auto gl4Target = static_cast<OpenGLRenderTarget*>(Bind(target));
	gl4Target->DisableDepthStencilBuffer();
}


void Miracle::OpenGLEngine::EnableCBuffer(Shader* a_Shader, GLuint a_Program)
{
	const _I32 index = ConstantBuffer::ShaderDataIndex;
	for each (const auto& cb in a_Shader->GetData(index))
	{
		if (cb.GraphicsResourceObject)
		{
			OpenGLConstantBuffer* GLConstantBuffer = static_cast<OpenGLConstantBuffer*>(Bind(cb.GraphicsResourceObject));
			if (GLConstantBuffer)
			{
				GLConstantBuffer->Update();
				const auto blockIndex = cb.BindPoint;
				if (blockIndex != GL_INVALID_INDEX)
				{
					const auto unit = m_UniformUnitMap.AcquireUnit(a_Program, blockIndex);
					glUniformBlockBinding(a_Program, blockIndex, unit);
					GLConstantBuffer->AttachToUnit(unit);
				}
			}
			else
			{
				MENGINE_ASSERT_MSG(false,"Failed to bind constant buffer.");
			}
		}
		else
		{
			MENGINE_ASSERT_MSG(false,"constant buffer is null.");
		}
	}
}

void Miracle::OpenGLEngine::DisableCBuffer(Shader* a_Shader, GLuint a_Program)
{
	const _I32 index = ConstantBuffer::ShaderDataIndex;
	for (const auto& cb : a_Shader->GetData(index))
	{
		const auto blockIndex = cb.BindPoint;
		if (GL_INVALID_INDEX != blockIndex)
		{
			const auto unit = m_UniformUnitMap.GetUnit(a_Program, blockIndex);
			glBindBufferBase(GL_UNIFORM_BUFFER, unit, 0);
			m_UniformUnitMap.ReleaseUnit(unit);
		}

	}
}

void Miracle::OpenGLEngine::EnableTextures(Shader* a_Shader, GLuint a_Program)
{
	const _I32 index = TextureSingle::ShaderDataIndex;
	for each (const auto& tex in a_Shader->GetData(index))
	{
		if (!tex.GraphicsResourceObject)
		{
			MENGINE_ASSERT_MSG(false, "tex is null.");
			continue;
		}
		
		OpenGLTextureSingle* texture = static_cast<OpenGLTextureSingle*>(Bind(tex.GraphicsResourceObject));
		if (!texture)
		{
			MENGINE_ASSERT_MSG(false,"Failed to create texture.");
			continue;
		}

		GLuint handle = texture->GetHandle();
		if (tex.IsGpuWritable)
		{
			GLint unit = m_TextureImageUnitMap.AcquireUnit(a_Program, tex.BindPoint);
			glUniform1i(tex.BindPoint, unit);
			DataFormat format = texture->GetTexture()->GetDataFormat();
			GLuint internalFormat = texture->GetInternalFormat(format);
			glBindImageTexture(unit, handle, 0, GL_TRUE, 0, GL_READ_WRITE, internalFormat);
		}
		else
		{
			GLint unit = m_TextureSamplerUnitMap.AcquireUnit(a_Program, tex.BindPoint);
			glUniform1i(tex.BindPoint, unit);
			glActiveTexture(GL_TEXTURE0 + unit);
			glBindTexture(texture->GetTarget(), handle);
		}
	}
}

void Miracle::OpenGLEngine::DisableTextures(Shader* a_Shader, GLuint a_Program)
{
	const _I32 index = TextureSingle::ShaderDataIndex;
	for (auto const& tex : a_Shader->GetData(index))
	{
		if (!tex.GraphicsResourceObject)
		{
			MENGINE_ASSERT_MSG(false, "texture is null.");
			continue;
		}

		OpenGLTextureSingle* texture = static_cast<OpenGLTextureSingle*>(Bind(tex.GraphicsResourceObject));
		if (!texture)
		{
			MENGINE_ASSERT_MSG(false,"Failed to get texture.");
			continue;
		}

		if (tex.IsGpuWritable)
		{
			GLint unit = m_TextureImageUnitMap.GetUnit(a_Program, tex.BindPoint);
			m_TextureImageUnitMap.ReleaseUnit(unit);
		}
		else
		{
			GLint unit = m_TextureSamplerUnitMap.GetUnit(a_Program, tex.BindPoint);
			glActiveTexture(GL_TEXTURE0 + unit);
			glBindTexture(texture->GetTarget(), 0);
			m_TextureSamplerUnitMap.ReleaseUnit(unit);
		}
	}
}

void Miracle::OpenGLEngine::EnableTexturesArray(Shader* a_Shader, GLuint a_Program)
{
	int const index = TextureArray::ShaderDataIndex;
	for (auto const& texs : a_Shader->GetData(index))
	{
		if (!texs.GraphicsResourceObject)
		{
			MENGINE_ASSERT_MSG(false,"texture array is null.");
			continue;
		}

		auto texture = static_cast<OpenGLTextureArray*>(Bind(texs.GraphicsResourceObject));
		if (!texture)
		{
			MENGINE_ASSERT_MSG(false,"Failed to bind texture array.");
			continue;
		}


		GLuint handle = texture->GetHandle();
		if (texs.IsGpuWritable)
		{
			GLint unit = m_TextureImageUnitMap.AcquireUnit(a_Program, texs.BindPoint);
			glUniform1i(texs.BindPoint, unit);
			DataFormat format = texture->GetTexture()->GetDataFormat();
			GLuint internalFormat = texture->GetInternalFormat(format);
			glBindImageTexture(unit, handle, 0, GL_TRUE, 0, GL_READ_WRITE, internalFormat);
		}
		else
		{
			GLint unit = m_TextureSamplerUnitMap.AcquireUnit(a_Program, texs.BindPoint);
			glUniform1i(texs.BindPoint, unit);
			glActiveTexture(GL_TEXTURE0 + unit);
			glBindTexture(texture->GetTarget(), handle);
		}
	}
}

void Miracle::OpenGLEngine::DisableTexturesArray(Shader* a_Shader, GLuint a_Program)
{
	int const index = TextureArray::ShaderDataIndex;
	for (auto const& texs : a_Shader->GetData(index))
	{
		if (!texs.GraphicsResourceObject)
		{
			MENGINE_ASSERT_MSG(false, "texture array is null.");
			continue;
		}

		auto texture = static_cast<OpenGLTextureArray*>(Get(texs.GraphicsResourceObject));
		if (!texture)
		{
			MENGINE_ASSERT_MSG(false, "Failed to get texture array.");
			continue;
		}


		if (texs.IsGpuWritable)
		{
			GLint unit = m_TextureImageUnitMap.GetUnit(a_Program, texs.BindPoint);
			m_TextureImageUnitMap.ReleaseUnit(unit);
		}
		else
		{
			GLint unit = m_TextureSamplerUnitMap.GetUnit(a_Program, texs.BindPoint);
			glActiveTexture(GL_TEXTURE0 + unit);
			glBindTexture(texture->GetTarget(), 0);
			m_TextureSamplerUnitMap.ReleaseUnit(unit);
		}
	}
}

void Miracle::OpenGLEngine::EnableSamplers(Shader* a_Shader, GLuint a_Program) 
{
	int const index = SamplerState::ShaderDataIndex;
	for (auto const& sampler : a_Shader->GetData(index))
	{
		if (sampler.GraphicsResourceObject)
		{
			OpenGLSamplerState* GLSampler = static_cast<OpenGLSamplerState*>(Bind(sampler.GraphicsResourceObject));
			if (GLSampler)
			{
				auto const location = sampler.BindPoint;
				auto const unit = m_TextureSamplerUnitMap.AcquireUnit(a_Program, location);
				glBindSampler(unit, GLSampler->GetHandle());
			}
			else
			{
				MENGINE_ASSERT_MSG(false,"Failed to bind sampler.");
			}
		}
		else
		{
			MENGINE_ASSERT_MSG(false,"sampler is null.");
		}
	}
}
void Miracle::OpenGLEngine::DisableSamplers(Shader* a_Shader, GLuint a_Program)
{
	int const index = SamplerState::ShaderDataIndex;
	for (auto const& sampler : a_Shader->GetData(index))
	{
		if (sampler.GraphicsResourceObject)
		{
			OpenGLSamplerState* GLSampler = static_cast<OpenGLSamplerState*>(Bind(sampler.GraphicsResourceObject));
			if (GLSampler)
			{
				auto const location = sampler.BindPoint;
				auto const unit = m_TextureSamplerUnitMap.GetUnit(a_Program, location);
				glBindSampler(unit, 0);
				m_TextureSamplerUnitMap.ReleaseUnit(unit);
			}
			else
			{
				MENGINE_ASSERT_MSG(false,"Failed to get sampler.");
			}
		}
		else
		{
			MENGINE_ASSERT_MSG(false, "sampler is null.");
		}
	}
}


_U64 Miracle::OpenGLEngine::DrawPrimitive(	const std::shared_ptr<VertexBuffer>& a_VertexBuffer,
											const std::shared_ptr<IndexBuffer>& a_IndexBuffer,
											const std::shared_ptr<VisualEffect>& a_Effect)
{
	GLSLVisualProgram* OpenGLProgram = dynamic_cast<GLSLVisualProgram*>(a_Effect->GetProgram().get());
	if (!OpenGLProgram)
	{
		MENGINE_ASSERT_MSG(false,"HLSL effect passed to GLSL engine.");
		return 0;
	}

	auto ProgramHandle = OpenGLProgram->GetProgramHandle();
	glUseProgram(ProgramHandle);

	if (EnableShaders(a_Effect, ProgramHandle))
	{
		OpenGLVertexBuffer* VertexBufferRenderResource = static_cast<OpenGLVertexBuffer*>(Bind(a_VertexBuffer));
		if (VertexBufferRenderResource == nullptr)
		{
			MENGINE_ASSERT_MSG(false, "Create vertex buffer render resource fail.");
		}

		OpenGLIndexBuffer* IndexBufferRenderResource = static_cast<OpenGLIndexBuffer*>(Bind(a_IndexBuffer));
		if (IndexBufferRenderResource == nullptr)
		{
			MENGINE_ASSERT_MSG(false, "Create index buffer render resource fail.");
		}
		OpenGLInputLayoutManager* InputLayoutManager = static_cast<OpenGLInputLayoutManager*>(m_InputLayoutManager.get());
		OpenGLInputLayout* InputLayoutRenderResource = InputLayoutManager->Bind(ProgramHandle,
			VertexBufferRenderResource->GetHandle(),
			a_VertexBuffer.get());


		InputLayoutRenderResource->Enable();
		IndexBufferRenderResource->Enable();

		DrawPrimitive(a_VertexBuffer.get(), a_IndexBuffer.get());

		InputLayoutRenderResource->Disable();
		IndexBufferRenderResource->Disable();

		DisableShaders(a_Effect, ProgramHandle);
	}
	glUseProgram(0);
	return 0;
}

_U64 Miracle::OpenGLEngine::DrawPrimitive(VertexBuffer* vbuffer, IndexBuffer* ibuffer)
{
	_U32 numActiveVertices = vbuffer->GetNumActiveElements();
	_U32 vertexOffset = vbuffer->GetOffset();

	_U32 numActiveIndices = ibuffer->GetNumActiveIndices();
	_U32 indexSize = ibuffer->GetElementSize();
	GLenum indexType = (indexSize == 4 ? GL_UNSIGNED_INT : GL_UNSIGNED_SHORT);

	GLenum topology = 0;
	PrimitiveType type = ibuffer->GetPrimitiveType();
	switch (type)
	{
	case PrimitiveType::POLYPOINT:
		topology = GL_POINTS;
		break;
	case PrimitiveType::POLYSEGMENT_DISJOINT:
		topology = GL_LINES;
		break;
	case PrimitiveType::POLYSEGMENT_CONTIGUOUS:
		topology = GL_LINE_STRIP;
		break;
	case PrimitiveType::TRIMESH:
		topology = GL_TRIANGLES;
		break;
	case PrimitiveType::TRISTRIP:
		topology = GL_TRIANGLE_STRIP;
		break;
	case PrimitiveType::POLYSEGMENT_DISJOINT_ADJ:
		topology = GL_LINES_ADJACENCY;
		break;
	case PrimitiveType::POLYSEGMENT_CONTIGUOUS_ADJ:
		topology = GL_LINE_STRIP_ADJACENCY;
		break;
	case PrimitiveType::TRIMESH_ADJ:
		topology = GL_TRIANGLES_ADJACENCY;
		break;
	case PrimitiveType::TRISTRIP_ADJ:
		topology = GL_TRIANGLE_STRIP_ADJACENCY;
		break;
	default:
		MENGINE_ASSERT_MSG(false,"Unknown primitive topology");
		return 0;
	}
	unsigned int offset = ibuffer->GetOffset();
	if (ibuffer->IsIndexed())
	{
		void const* data = (char*)0 + indexSize * offset;
		glDrawRangeElements(topology, 0, numActiveVertices - 1,
			static_cast<GLsizei>(numActiveIndices), indexType, data);
	}
	else
	{
		glDrawArrays(topology, static_cast<GLint>(vertexOffset),
			static_cast<GLint>(numActiveVertices));
	}
	return 0;
}

void Miracle::OpenGLEngine::SetViewport(_I32 a_X, _I32 a_Y, _I32 a_Wdith, _I32 a_Height)
{
	glViewport(a_X, a_Y, a_Wdith, a_Height);
}

void Miracle::OpenGLEngine::GetViewport(_I32& a_X, _I32& a_Y, _I32& a_Wdith, _I32& a_Height) const
{
	_I32 Param[4];
	glGetIntegerv(GL_VIEWPORT, Param);
	a_X = Param[0];
	a_Y = Param[1];
	a_Wdith = Param[2];
	a_Height = Param[3];
}

void Miracle::OpenGLEngine::SetDepthRange(_F32 a_Near, _F32 a_Far)
{
	glDepthRange(static_cast<GLdouble>(a_Near), static_cast<GLdouble>(a_Far));
}

void Miracle::OpenGLEngine::GetDepthRange(_F32& a_Near, _F32& a_Far) const
{
	GLdouble Param[2];
	glGetDoublev(GL_DEPTH_RANGE, Param);
	a_Near = static_cast<float>(Param[0]);
	a_Far = static_cast<float>(Param[1]); 
}

bool Miracle::OpenGLEngine::Resize(_U32 a_Wdith, _U32 a_Height)
{
	m_Width = a_Wdith;
	m_Height = a_Height;
	int param[4];
	glGetIntegerv(GL_VIEWPORT, param);
	glViewport(param[0], param[1], static_cast<GLint>(m_Width), static_cast<GLint>(m_Height));
	return true;
}

void Miracle::OpenGLEngine::ClearColorBuffer()
{
	glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Miracle::OpenGLEngine::ClearDepthBuffer()
{
	glClearDepth(m_ClearDepth);
	glClear(GL_DEPTH_BUFFER_BIT);
}

void Miracle::OpenGLEngine::ClearStencilBuffer()
{
	glClearStencil(static_cast<GLint>(m_ClearStencil));
	glClear(GL_STENCIL_BUFFER_BIT);
}

void Miracle::OpenGLEngine::ClearBuffers()
{
	glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
	glClearDepth(m_ClearDepth);
	glClearStencil(static_cast<GLint>(m_ClearStencil));
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Miracle::OpenGLEngine::SetBlendState(const std::shared_ptr<BlendState>& a_State)
{
	if (a_State)
	{
		if (a_State != m_ActiveBlendState)
		{
			OpenGLBlendState* GLBlendState = static_cast<OpenGLBlendState*>(Bind(a_State));
			if (GLBlendState)
			{
				GLBlendState->Enable();
				m_ActiveBlendState = a_State;
			}
			else
			{
				MENGINE_ASSERT_MSG(false, "Failed to bind blend state.");
			}
		}
	}
	else
	{
		MENGINE_ASSERT_MSG(false, "Input state is null.");
	}
}

void Miracle::OpenGLEngine::SetDepthStencilState(const std::shared_ptr<DepthStencilState>& a_State)
{
	if (a_State)
	{
		if (a_State != m_ActiveDepthStencilState)
		{
			OpenGLDepthStencilState* GLDepthStencilState = static_cast<OpenGLDepthStencilState*>(Bind(a_State));
			if (GLDepthStencilState)
			{
				GLDepthStencilState->Enable();
				m_ActiveDepthStencilState = a_State;
			}
			else
			{
				MENGINE_ASSERT_MSG(false, "Failed to bind depth-stencil state.");
			}
		}
	}
	else
	{
		MENGINE_ASSERT_MSG(false, "Input state is null.");
	}
}

void Miracle::OpenGLEngine::SetRasterizerState(const std::shared_ptr<RasterizerState>& a_State)
{
	if (a_State)
	{
		if (a_State != m_ActiveRasterizerState)
		{
			OpenGLRasterizerState* GLRasterizerState = static_cast<OpenGLRasterizerState*>(Bind(a_State));
			if (GLRasterizerState)
			{
				GLRasterizerState->Enable();
				m_ActiveRasterizerState = a_State;
			}
			else
			{
				MENGINE_ASSERT_MSG(false, "Failed to bind rasterizer state.");
			}
		}
	}
	else
	{
		MENGINE_ASSERT_MSG(false, "Input state is null.");
	}
}

bool Miracle::OpenGLEngine::Update(const std::shared_ptr<Buffer>& a_Buffer)
{
	if (!a_Buffer->GetData())
	{
		MENGINE_ASSERT_MSG(false,"Buffer does not have system memory, creating it.");
	}

	auto glBuffer = static_cast<OpenGLBuffer*>(Bind(a_Buffer));
	return glBuffer->Update();
}

bool Miracle::OpenGLEngine::Update(const std::shared_ptr<TextureSingle>& a_Texture)
{
	if (!a_Texture->GetData())
	{
		MENGINE_ASSERT_MSG(false,"Texture does not have system memory, creating it.");
	}

	auto glTexture = static_cast<OpenGLTextureSingle*>(Bind(a_Texture));
	return glTexture->Update();
}

bool Miracle::OpenGLEngine::Update(const std::shared_ptr<TextureSingle>& a_Texture, _U32 a_Level)
{
	if (!a_Texture->GetData())
	{
		MENGINE_ASSERT_MSG(false, "Texture does not have system memory, creating it.");
	}

	auto glTexture = static_cast<OpenGLTextureSingle*>(Bind(a_Texture));
	return glTexture->Update(a_Level);
}

bool Miracle::OpenGLEngine::Update(const std::shared_ptr<TextureArray>& a_TextureArray)
{
	if (!a_TextureArray->GetData())
	{
		MENGINE_ASSERT_MSG(false, "Texture array does not have system memory, creating it.");
	}

	auto glTextureArray = static_cast<OpenGLTextureArray*>(Bind(a_TextureArray));
	return glTextureArray->Update();
}

bool Miracle::OpenGLEngine::Update(const std::shared_ptr<TextureArray>& a_TextureArray, _U32 a_Item, _U32 a_Level)
{
	if (!a_TextureArray->GetData())
	{
		MENGINE_ASSERT_MSG(false, "Texture array does not have system memory, creating it.");
	}

	auto glTextureArray = static_cast<OpenGLTextureArray*>(Bind(a_TextureArray));
	return glTextureArray->Update(a_Item, a_Level);
}

bool Miracle::OpenGLEngine::CopyMem2GraphMem(const std::shared_ptr<Buffer>& a_Buffer)
{
	if (!a_Buffer->GetData())
	{
		MENGINE_ASSERT_MSG(false, "Buffer does not have system memory, creating it.");
	}

	auto glBuffer = static_cast<OpenGLBuffer*>(Bind(a_Buffer));
	return glBuffer->CopyMem2GraphMem();
}

bool Miracle::OpenGLEngine::CopyMem2GraphMem(const std::shared_ptr<TextureSingle>& a_Texture)
{
	if (!a_Texture->GetData())
	{
		MENGINE_ASSERT_MSG(false, "Texture does not have system memory, creating it.");
	}

	auto glTexture = static_cast<OpenGLTextureSingle*>(Bind(a_Texture));
	return glTexture->CopyMem2GraphMem();
}

bool Miracle::OpenGLEngine::CopyMem2GraphMem(const std::shared_ptr<TextureSingle>& a_Texture, _U32 a_Level)
{
	if (!a_Texture->GetData())
	{
		MENGINE_ASSERT_MSG(false, "Texture does not have system memory, creating it.");
	}

	auto glTexture = static_cast<OpenGLTextureSingle*>(Bind(a_Texture));
	return glTexture->CopyMem2GraphMem(a_Level);
}

bool Miracle::OpenGLEngine::CopyMem2GraphMem(const std::shared_ptr<TextureArray>& a_TextureArray)
{
	if (!a_TextureArray->GetData())
	{
		MENGINE_ASSERT_MSG(false, "Texture array does not have system memory, creating it.");
	}

	auto glTextureArray = static_cast<OpenGLTextureArray*>(Bind(a_TextureArray));
	return glTextureArray->CopyMem2GraphMem();
}

bool Miracle::OpenGLEngine::CopyMem2GraphMem(const std::shared_ptr<TextureArray>& a_TextureArray, _U32 a_Item, _U32 a_Level)
{
	if (!a_TextureArray->GetData())
	{
		MENGINE_ASSERT_MSG(false, "Texture array does not have system memory, creating it.");
	}

	auto glTextureArray = static_cast<OpenGLTextureArray*>(Bind(a_TextureArray));
	return glTextureArray->CopyMem2GraphMem(a_Item, a_Level);
}

bool Miracle::OpenGLEngine::CopyGraphMem2Mem(const std::shared_ptr<Buffer>& a_Buffer)
{
	//TODO
	return true;
}

bool Miracle::OpenGLEngine::CopyGraphMem2Mem(const std::shared_ptr<TextureSingle>& a_Texture)
{
	//TODO
	return true;
}

bool Miracle::OpenGLEngine::CopyGraphMem2Mem(const std::shared_ptr<TextureSingle>& a_Texture, _U32 a_Level)
{
	//TODO
	return true;
}

bool Miracle::OpenGLEngine::CopyGraphMem2Mem(const std::shared_ptr<TextureArray>& a_TextureArray)
{
	//TODO
	return true;
}

bool Miracle::OpenGLEngine::CopyGraphMem2Mem(const std::shared_ptr<TextureArray>& a_TextureArray, _U32 a_Item, _U32 a_Level)
{
	//TODO
	return true;
}

void Miracle::OpenGLEngine::WaitForFinish()
{

}

void Miracle::OpenGLEngine::Flush()
{
	glFlush();
}

void Miracle::OpenGLEngine::DisplayColorBuffer(unsigned int syncInterval)
{
	glfwSwapBuffers(m_hWnd);
}



/* ProgramIndexUnitMap */
Miracle::OpenGLEngine::ProgramIndexUnitMap::~ProgramIndexUnitMap()
{
}

Miracle::OpenGLEngine::ProgramIndexUnitMap::ProgramIndexUnitMap()
{
}

int Miracle::OpenGLEngine::ProgramIndexUnitMap::AcquireUnit(GLint program, GLint index)
{
	int availUnit = -1;
	for (int unit = 0; unit < static_cast<int>(mLinkMap.size()); ++unit)
	{
		auto& item = mLinkMap[unit];

		// Increment link count if already assigned and in use?
		if (program == item.program && index == item.index)
		{
			++item.linkCount;
			return unit;
		}

		// Found a unit that was previously used but is now avaialble.
		if (0 == item.linkCount)
		{
			if (-1 == availUnit)
			{
				availUnit = unit;
			}
		}
	}

	// New unit number not previously used?
	if (-1 == availUnit)
	{
		// TODO: Consider querying the max number of units
		// and check that this number is not exceeded.
		availUnit = static_cast<int>(mLinkMap.size());
		mLinkMap.push_back({ 0, 0, 0 });
	}

	auto& item = mLinkMap[availUnit];
	item.linkCount = 1;
	item.program = program;
	item.index = index;
	return availUnit;
}

int Miracle::OpenGLEngine::ProgramIndexUnitMap::GetUnit(GLint program, GLint index) const
{
	for (int unit = 0; unit < static_cast<int>(mLinkMap.size()); ++unit)
	{
		auto& item = mLinkMap[unit];
		if (program == item.program && index == item.index)
		{
			return unit;
		}
	}
	return -1;
}

void Miracle::OpenGLEngine::ProgramIndexUnitMap::ReleaseUnit(unsigned index)
{
	if (index < mLinkMap.size())
	{
		auto& item = mLinkMap[index];
		if (item.linkCount > 0)
		{
			--item.linkCount;
		}
	}
}

_U32 Miracle::OpenGLEngine::ProgramIndexUnitMap::GetUnitLinkCount(unsigned unit) const
{
	if (unit < mLinkMap.size())
	{
		return mLinkMap[unit].linkCount;
	}
	return 0;
}

bool Miracle::OpenGLEngine::ProgramIndexUnitMap::GetUnitProgramIndex(unsigned unit, GLint &program, GLint &index) const
{
	if (unit < mLinkMap.size())
	{
		auto& item = mLinkMap[index];
		if (item.linkCount > 0)
		{
			program = item.program;
			index = item.index;
			return true;
		}
	}
	return false;
}
/* ProgramIndexUnitMap */