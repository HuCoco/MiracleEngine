#include <Rendering/DirectX/InputLayout/DirectXInputLayoutManager.h>


Miracle::DirectXInputLayoutManager::DirectXInputLayoutManager()
{

}

Miracle::DirectXInputLayoutManager::~DirectXInputLayoutManager()
{
	m_Tree.Destory();
}

Miracle::DirectXInputLayout* Miracle::DirectXInputLayoutManager::Bind(ID3D11Device* a_Device, VertexBuffer* a_VertexBuffer, Shader* a_Shader)
{
	std::shared_ptr<DirectXInputLayout> layout;
	if (a_Shader)
	{
		if (a_VertexBuffer)
		{
			if (!Get(std::make_pair(a_VertexBuffer, a_Shader), layout))
			{
				layout = std::make_shared<DirectXInputLayout>(a_Device, a_VertexBuffer, a_Shader);
				m_Tree.Insert(std::make_pair(a_VertexBuffer, a_Shader), layout);
			}
		}
	}
	else
	{
		MENGINE_ASSERT_MSG(false,"Vertex shader must be nonnull.");
	}
	return layout.get();
}

bool Miracle::DirectXInputLayoutManager::Unbind(VertexBuffer* a_VertexBuffer, void* a_Shader)
{
	Shader* shader = reinterpret_cast<Shader*>(a_Shader);
	if (shader)
	{
		if (a_VertexBuffer)
		{
			LayoutPair pair = std::make_pair(a_VertexBuffer, shader);
			m_Tree.Remove(pair);
			return true;
		}
	}
	else
	{
		MENGINE_ASSERT_MSG(false, "Vertex shader must be nonnull.");
	}
	return false;
}

void Miracle::DirectXInputLayoutManager::UnbindAll()
{
	m_Tree.Destory();
}


bool Miracle::DirectXInputLayoutManager::Insert(LayoutPair a_LayoutPair, std::shared_ptr<DirectXInputLayout> a_InputLayout)
{
	return m_Tree.Insert(a_LayoutPair, a_InputLayout);
}

bool Miracle::DirectXInputLayoutManager::Get(LayoutPair a_LayoutPair, std::shared_ptr<DirectXInputLayout>& a_InputLayout) const
{
	auto node = m_Tree.Find(a_LayoutPair);
	if (node == nullptr)
	{
		return false;
	}
	a_InputLayout = node->Value;
	return true;
}
