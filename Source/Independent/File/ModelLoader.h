#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Core/StringUtils/StringUtils.h>
#include <Independent/File/Model/Model.h>
#include <Independent/File/Model/Mesh.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

NAMESPACE_MENGINE_BEGIN

class ModelLoader
{
public:
	static Model* Load(const std::string& a_FilePath);

private:
	static void Load(Model* a_Model, aiNode* node, const aiScene* scene, const std::string& a_RootDic);
	static Mesh* Load(aiMesh* mesh, const aiScene* scene, const std::string& a_RootDic);
	static std::shared_ptr<VertexBuffer> GenerateVertexBuffer(aiMesh* a_Mesh, bool a_IsGenTangent);
	static std::shared_ptr<IndexBuffer> GenerateIndexBuffer(aiMesh* a_Mesh);
	static std::shared_ptr<Texture2D> GenerateMaterial(aiMesh* a_Mesh, const aiScene* scene, aiTextureType a_Type,const std::string& a_RootDic);
	static std::string GenerateRootDic(const std::string& a_FilePath);
};

NAMESPACE_MENGINE_END