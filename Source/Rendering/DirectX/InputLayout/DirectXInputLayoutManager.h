#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <ThirdParty/GraphicsKit/DirectXPreCompileHeader.h>
#include <Rendering/Manager/InputLayoutManager.h>
#include <Rendering/DirectX/InputLayout/DirectXInputLayout.h>
#include <Independent/DataStructure/MSet.h>

NAMESPACE_MENGINE_BEGIN

class DirectXInputLayoutManager : public InputLayoutManager
{
public:
	DirectXInputLayoutManager();
	virtual ~DirectXInputLayoutManager();

	DirectXInputLayout* Bind(ID3D11Device* a_Device, VertexBuffer* a_VertexBuffer, Shader* a_Shader);
	virtual bool Unbind(VertexBuffer* a_VertexBuffer, void* a_Shader) override;
	virtual void UnbindAll() override;
private:
	typedef std::pair<VertexBuffer*, Shader*> LayoutPair;

	bool Insert(LayoutPair a_LayoutPair, std::shared_ptr<DirectXInputLayout> a_InputLayout);
	bool Get(LayoutPair a_LayoutPair, std::shared_ptr<DirectXInputLayout>& a_InputLayout) const;

private:
	
	MSet<LayoutPair, std::shared_ptr<DirectXInputLayout>> m_Tree;
};

NAMESPACE_MENGINE_END