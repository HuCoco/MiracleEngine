#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <ThirdParty/GraphicsKit/DirectXPreCompileHeader.h>
#include <Rendering/Manager/InputLayoutManager.h>
#include <Rendering/OpenGL/InputLayout/OpenGLInputLayout.h>
#include <Independent/DataStructure/MSet.h>

NAMESPACE_MENGINE_BEGIN


class OpenGLInputLayoutManager : public InputLayoutManager
{
public:
	OpenGLInputLayoutManager();
	~OpenGLInputLayoutManager();

	OpenGLInputLayout* Bind(GLuint a_ProgramHandle, GLuint a_VertexBufferHandle, VertexBuffer* a_Buffer);
	virtual bool Unbind(VertexBuffer* vbuffer, void* a_ProgramHandle) override;
	virtual void UnbindAll() override;
private:
	typedef std::pair<VertexBuffer*, GLuint> LayoutPair;

	bool Insert(LayoutPair a_LayoutPair, std::shared_ptr<OpenGLInputLayout> a_InputLayout);
	bool Get(LayoutPair a_LayoutPair, std::shared_ptr<OpenGLInputLayout>& a_InputLayout) const;

private:

	MSet<LayoutPair, std::shared_ptr<OpenGLInputLayout>> m_Tree;
};


NAMESPACE_MENGINE_END