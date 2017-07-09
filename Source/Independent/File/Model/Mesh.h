#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/Resource/Texture/Texture2D.h>
#include <Rendering/Base/Resource/Buffer/IndexBuffer.h>
#include <Rendering/Base/Resource/Buffer/VertexBuffer.h>
NAMESPACE_MENGINE_BEGIN

class Mesh
{
public:

	std::shared_ptr<VertexBuffer> GetVertexBuffer();
	std::shared_ptr<IndexBuffer> GetIndexBuffer();

	inline std::shared_ptr<Texture2D> GetDiffuseTextrue() const;
	inline std::shared_ptr<Texture2D> GetSpecularTexture() const;
	inline std::shared_ptr<Texture2D> GetNormalTexture() const;
 	inline std::string GetMeshName() const;

	Mesh(const std::shared_ptr<VertexBuffer>& a_VertexBuffer, const std::shared_ptr<IndexBuffer>& a_IndexBuffer,
		std::shared_ptr<Texture2D> a_DiffuseTexture, std::shared_ptr<Texture2D> a_SpecularTexture, std::shared_ptr<Texture2D> a_NoramlTexure,
		const std::string& a_Name = "");
	~Mesh();

private:
	std::shared_ptr<Texture2D> m_DiffuseTexture;
	std::shared_ptr<Texture2D> m_SpecularTexture;
	std::shared_ptr<Texture2D> m_NoramlTexure;
	std::shared_ptr<VertexBuffer> m_VertexBuffer;
	std::shared_ptr<IndexBuffer> m_IndexBuffer;
	std::string m_MeshName;

};

inline std::shared_ptr<Texture2D> Mesh::GetDiffuseTextrue() const
{
	return m_DiffuseTexture;
}

inline std::shared_ptr<Texture2D> Mesh::GetSpecularTexture() const
{
	return m_SpecularTexture;
}

inline std::shared_ptr<Texture2D> Mesh::GetNormalTexture() const
{
	return m_NoramlTexure;
}

inline std::string Mesh::GetMeshName() const
{
	return m_MeshName;
}


NAMESPACE_MENGINE_END