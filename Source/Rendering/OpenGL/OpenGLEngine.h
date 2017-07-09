#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <ThirdParty/GraphicsKit/OpenGLPreCompileHeader.h>
#include <Rendering/Base/GraphicsEngine.h>
#include <Rendering/VisualEffect/VisualEffect.h>

NAMESPACE_MENGINE_BEGIN

class OpenGLEngine : public GraphicsEngine
{
public:
	OpenGLEngine(GLFWwindow* a_hWnd);
	virtual ~OpenGLEngine();

private:
	_U64 DrawPrimitive(VertexBuffer* vbuffer, IndexBuffer* ibuffer);

	bool EnableShaders(const std::shared_ptr<VisualEffect>& a_Effect, GLuint program);
	void DisableShaders(const std::shared_ptr<VisualEffect>& a_Effect, GLuint program);
	void Enable(Shader* a_Shader, GLuint a_Program);
	void Disable(Shader* a_Shader, GLuint a_Program);
	void EnableCBuffer(Shader* a_Shader, GLuint a_Program);
	void DisableCBuffer(Shader* a_Shader, GLuint a_Program);
	void EnableTextures(Shader* a_Shader, GLuint a_Program);
	void DisableTextures(Shader* a_Shader, GLuint a_Program);
	void EnableTexturesArray(Shader* a_Shader, GLuint a_Program);
	void DisableTexturesArray(Shader* a_Shader, GLuint a_Program);
	void EnableSamplers(Shader* a_Shader, GLuint a_Program);
	void DisableSamplers(Shader* a_Shader, GLuint a_Program);

	class ProgramIndexUnitMap
	{
	public:
		~ProgramIndexUnitMap();
		ProgramIndexUnitMap();

		int AcquireUnit(GLint program, GLint index);
		int GetUnit(GLint program, GLint index) const;
		void ReleaseUnit(unsigned index);
		_U32 GetUnitLinkCount(unsigned unit) const;
		bool GetUnitProgramIndex(unsigned unit, GLint &program, GLint &index) const;
	private:
		struct LinkInfo
		{
			unsigned linkCount;
			GLint program;
			GLint index;
		};

		std::vector<LinkInfo> mLinkMap;
	};

	ProgramIndexUnitMap m_TextureSamplerUnitMap;
	ProgramIndexUnitMap m_TextureImageUnitMap;
	ProgramIndexUnitMap m_UniformUnitMap;

public:
	virtual void SetViewport(_I32 a_X, _I32 a_Y, _I32 a_Wdith, _I32 a_Height) override;
	virtual void GetViewport(_I32& a_X, _I32& a_Y, _I32& a_Wdith, _I32& a_Height) const override;
	virtual void SetDepthRange(_F32 a_Near, _F32 a_Far) override;
	virtual void GetDepthRange(_F32& a_Near, _F32& a_Far) const override;

	virtual bool Resize(_U32 a_Wdith ,_U32 a_Height);

	virtual void ClearColorBuffer() override;
	virtual void ClearDepthBuffer() override;
	virtual void ClearStencilBuffer() override;
	virtual void ClearBuffers() override;
	virtual void DisplayColorBuffer(unsigned int syncInterval);

	virtual void SetBlendState(const std::shared_ptr<BlendState>& a_State) override ;
	virtual void SetDepthStencilState(const std::shared_ptr<DepthStencilState>& a_State) override ;
	virtual void SetRasterizerState(const std::shared_ptr<RasterizerState>& a_State);

	virtual void Enable(const std::shared_ptr<RenderTarget>& target) override;
	virtual void Disable(const std::shared_ptr<RenderTarget>& target) override;
	virtual void EnableDepthStencil(const std::shared_ptr<RenderTarget>& target) override;
	virtual void DisableDepthStencil(const std::shared_ptr<RenderTarget>& target) override;

	virtual bool Update(const std::shared_ptr<Buffer>& a_Buffer) override ;
	virtual bool Update(const std::shared_ptr<TextureSingle>& a_Texture) override ;
	virtual bool Update(const std::shared_ptr<TextureSingle>& a_Texture, _U32 a_Level) override ;
	virtual bool Update(const std::shared_ptr<TextureArray>& a_TextureArray) override ;
	virtual bool Update(const std::shared_ptr<TextureArray>& a_TextureArray, _U32 a_Item, _U32 a_Level) override ;

	virtual bool CopyMem2GraphMem(const std::shared_ptr<Buffer>& a_Buffer) override ;
	virtual bool CopyMem2GraphMem(const std::shared_ptr<TextureSingle>& a_Texture) override ;
	virtual bool CopyMem2GraphMem(const std::shared_ptr<TextureSingle>& a_Texture, _U32 a_Level) override ;
	virtual bool CopyMem2GraphMem(const std::shared_ptr<TextureArray>& textureArray) override ;
	virtual bool CopyMem2GraphMem(const std::shared_ptr<TextureArray>& textureArray, _U32 a_Item, _U32 a_Level) override ;

	virtual bool CopyGraphMem2Mem(const std::shared_ptr<Buffer>& a_Buffer) override ;
	virtual bool CopyGraphMem2Mem(const std::shared_ptr<TextureSingle>& a_Texture) override ;
	virtual bool CopyGraphMem2Mem(const std::shared_ptr<TextureSingle>& a_Texture, _U32 a_Level) override ;
	virtual bool CopyGraphMem2Mem(const std::shared_ptr<TextureArray>& a_TextureArray) override ;
	virtual bool CopyGraphMem2Mem(const std::shared_ptr<TextureArray>& a_TextureArray, _U32 a_Item, _U32 a_Level) override ;

	virtual void WaitForFinish();

	virtual void Flush();

public:
	virtual _U64 DrawPrimitive(
		const std::shared_ptr<VertexBuffer>& a_VertexBuffer,
		const std::shared_ptr<IndexBuffer>& a_IndexBuffer,
		const std::shared_ptr<VisualEffect>& a_Effect);

private:
	GLFWwindow* m_hWnd;
};

NAMESPACE_MENGINE_END