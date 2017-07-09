#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/BaseRenderEngine.h>
#include <Rendering/Base/Resource/RenderResource.h>
#include <Rendering/Base/Resource/GraphicsResource.h>
#include <Rendering/Base/Resource/Buffer/Buffer.h>
#include <Rendering/Base/Resource/Buffer/VertexBuffer.h>
#include <Rendering/Base/Resource/Buffer/IndexBuffer.h>
#include <Rendering/Base/Resource/Buffer/ConstantBuffer.h>
#include <Rendering/Base/Resource/Texture/TextureSingle.h>
#include <Rendering/Base/Resource/Texture/TextureArray.h>
#include <Rendering/Base/Resource/Texture/RenderTarget.h>
#include <Rendering/Base/Resource/RenderTargetResource.h>
#include <Rendering/Manager/ResourceManager.h>
#include <Rendering/Manager/RenderTargetManager.h>
#include <Rendering/VisualEffect/VisualEffect.h>
#include <Rendering/Manager/InputLayoutManager.h>

NAMESPACE_MENGINE_BEGIN

class GraphicsEngine : public BaseRenderEngine
{
public:
	~GraphicsEngine();
	virtual void ClearColorBuffer() = 0;
	virtual void ClearDepthBuffer() = 0;
	virtual void ClearStencilBuffer() = 0;
	virtual void ClearBuffers() = 0;
	virtual void DisplayColorBuffer(unsigned int syncInterval) = 0;
	RenderResource* Bind(const std::shared_ptr<GraphicsObject>& a_Object);
	RenderTargetResource* Bind(const std::shared_ptr<RenderTarget>& target);
	RenderResource* Get(const std::shared_ptr<GraphicsObject>& a_Object) const;
	RenderTargetResource* Get(const std::shared_ptr<RenderTarget>& target) const;

	virtual void Enable(const std::shared_ptr<RenderTarget>& target) = 0;
	virtual void Disable(const std::shared_ptr<RenderTarget>& target) = 0;
	virtual void EnableDepthStencil(const std::shared_ptr<RenderTarget>& target) = 0;
	virtual void DisableDepthStencil(const std::shared_ptr<RenderTarget>& target) = 0;

	virtual bool Update(const std::shared_ptr<Buffer>& a_Buffer) = 0;
	virtual bool Update(const std::shared_ptr<TextureSingle>& a_Texture) = 0;
	virtual bool Update(const std::shared_ptr<TextureSingle>& a_Texture, _U32 a_Level) = 0;
	virtual bool Update(const std::shared_ptr<TextureArray>& a_TextureArray) = 0;
	virtual bool Update(const std::shared_ptr<TextureArray>& a_TextureArray, _U32 a_Item, _U32 a_Level) = 0;

	virtual bool CopyMem2GraphMem(const std::shared_ptr<Buffer>& a_Buffer) = 0;
	virtual bool CopyMem2GraphMem(const std::shared_ptr<TextureSingle>& a_Texture) = 0;
	virtual bool CopyMem2GraphMem(const std::shared_ptr<TextureSingle>& a_Texture, _U32 a_Level) = 0;
	virtual bool CopyMem2GraphMem(const std::shared_ptr<TextureArray>& textureArray) = 0;
	virtual bool CopyMem2GraphMem(const std::shared_ptr<TextureArray>& textureArray, _U32 a_Item, _U32 a_Level) = 0;

	virtual bool CopyGraphMem2Mem(const std::shared_ptr<Buffer>& a_Buffer) = 0;
	virtual bool CopyGraphMem2Mem(const std::shared_ptr<TextureSingle>& a_Texture) = 0;
	virtual bool CopyGraphMem2Mem(const std::shared_ptr<TextureSingle>& a_Texture, _U32 a_Level) = 0;
	virtual bool CopyGraphMem2Mem(const std::shared_ptr<TextureArray>& a_TextureArray) = 0;
	virtual bool CopyGraphMem2Mem(const std::shared_ptr<TextureArray>& a_TextureArray, _U32 a_Item, _U32 a_Level) = 0;

	virtual void WaitForFinish() = 0;

	virtual void Flush() = 0;
protected:
	GraphicsEngine();
	GraphicsEngine(const GraphicsEngine&) = delete;
	GraphicsEngine& operator=(const GraphicsEngine&) = delete;
public:
	virtual _U64 DrawPrimitive( 
		const std::shared_ptr<VertexBuffer>& a_VertexBuffer,
		const std::shared_ptr<IndexBuffer>& a_IndexBuffer,
		const std::shared_ptr<VisualEffect>& a_Effect) = 0;


	ResourceManager m_ResourceMananger;
	RenderTargetManager m_RenderTargetMananger;
	std::unique_ptr<InputLayoutManager> m_InputLayoutManager;

	typedef std::shared_ptr<RenderResource>(*CreateRenderResource)(void*,GraphicsObject*);
	typedef std::shared_ptr<RenderTargetResource>(*CreateRenderTargetResource)(RenderTarget*, std::vector<RenderResource*>&, RenderResource*);
	std::array<CreateRenderResource, GraphicsObject::NUM_GRAPHICS_OBJECT_TYPES> m_RenderResourceCreators;
	CreateRenderTargetResource m_RenderTargetResourceCreator;
	void* m_CreatorDevice;

};

NAMESPACE_MENGINE_END