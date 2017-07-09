#include "OpenGLInputLayoutManager.h"

Miracle::OpenGLInputLayoutManager::OpenGLInputLayoutManager()
{
}


Miracle::OpenGLInputLayoutManager::~OpenGLInputLayoutManager()
{
}

Miracle::OpenGLInputLayout* Miracle::OpenGLInputLayoutManager::Bind(GLuint a_ProgramHandle, GLuint a_VertexBufferHandle, VertexBuffer* a_Buffer)
{
	std::shared_ptr<OpenGLInputLayout> layout;
	if (a_ProgramHandle)
	{
		if (a_Buffer)
		{
			if (!Get(std::make_pair(a_Buffer, a_ProgramHandle), layout))
			{
				layout = std::make_shared<OpenGLInputLayout>(a_ProgramHandle, a_VertexBufferHandle, a_Buffer);
				Insert(std::make_pair(a_Buffer, a_ProgramHandle), layout);
			}
		}
	}
	else
	{
		MENGINE_ASSERT_MSG(false,"Program must exist.");
	}
	return layout.get();
}

bool Miracle::OpenGLInputLayoutManager::Unbind(VertexBuffer* vbuffer, void* a_ProgramHandle)
{
	int* shader = reinterpret_cast<int*>(a_ProgramHandle);
	if (a_ProgramHandle)
	{
		if (vbuffer)
		{
			LayoutPair pair = std::make_pair(vbuffer, *shader);
			m_Tree.Remove(pair);
			return true;
		}
	}
	else
	{
		MENGINE_ASSERT_MSG(false, "Program must exist.");
	}
	return false;
}

void Miracle::OpenGLInputLayoutManager::UnbindAll()
{
	m_Tree.Destory();
}

bool Miracle::OpenGLInputLayoutManager::Insert(LayoutPair a_LayoutPair, std::shared_ptr<OpenGLInputLayout> a_InputLayout)
{
	return m_Tree.Insert(a_LayoutPair, a_InputLayout);
}

bool Miracle::OpenGLInputLayoutManager::Get(LayoutPair a_LayoutPair, std::shared_ptr<OpenGLInputLayout>& a_InputLayout) const
{
	auto node = m_Tree.Find(a_LayoutPair);
	if (node == nullptr)
	{
		return false;
	}
	a_InputLayout = node->Value;
	return true;
}
