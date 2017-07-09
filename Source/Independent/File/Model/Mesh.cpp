#include "Mesh.h"



Miracle::Mesh::Mesh(const std::shared_ptr<VertexBuffer>& a_VertexBuffer, const std::shared_ptr<IndexBuffer>& a_IndexBuffer,
	std::shared_ptr<Texture2D> a_DiffuseTexture, std::shared_ptr<Texture2D> a_SpecularTexture, std::shared_ptr<Texture2D> a_NoramlTexure,
	const std::string& a_Name /*= ""*/)
	: m_VertexBuffer(a_VertexBuffer)
	, m_IndexBuffer(a_IndexBuffer)
	, m_DiffuseTexture(a_DiffuseTexture)
	, m_SpecularTexture(a_SpecularTexture)
	, m_NoramlTexure(a_NoramlTexure)
	, m_MeshName(a_Name)
{

}

Miracle::Mesh::~Mesh()
{

}

std::shared_ptr<Miracle::VertexBuffer> Miracle::Mesh::GetVertexBuffer()
{
	return m_VertexBuffer;
}

std::shared_ptr<Miracle::IndexBuffer> Miracle::Mesh::GetIndexBuffer()
{
	return m_IndexBuffer;
}
