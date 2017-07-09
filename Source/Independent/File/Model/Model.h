#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Core/StringUtils/StringUtils.h>
#include <Independent/File/Model/Mesh.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

NAMESPACE_MENGINE_BEGIN

class Model
{
public:
	Model() = default;
	~Model();
	inline const std::vector<Mesh*>& GetMeshs() const;
	inline Mesh* GetMesh(_U32 Index);
	void AddMesh(Mesh* a_Mesh);
private:
	std::vector<Mesh*> m_Meshs;
};

inline const std::vector<Mesh*>& Model::GetMeshs() const
{
	return m_Meshs;
}

inline Mesh* Model::GetMesh(_U32 Index)
{
	_U32 NumMesh = m_Meshs.size();
	if (Index < NumMesh && Index >= 0)
	{
		return m_Meshs[Index];
	}
	return nullptr;
}

NAMESPACE_MENGINE_END