#include "ModelLoader.h"
#include <ResourceManager/GameResourceSystem.h>

#define POSITION_X 0
#define POSITION_Y 1
#define POSITION_Z 2

#define NORMAL_X 3
#define NORMAL_Y 4
#define NORMAL_Z 5

#define TEXCOORD_U 6
#define TEXCOORD_V 7

#define TANGENT_X 8
#define TANGENT_Y 9
#define TANGENT_Z 10

#define BTANGENT_X 11
#define BTANGENT_Y 12
#define BTANGENT_Z 13

#define INDEX_1 0
#define INDEX_2 1
#define INDEX_3 2

Miracle::Model* Miracle::ModelLoader::Load(const std::string& a_FilePath)
{
	Assimp::Importer AssimpImporter;
	_U32 ImporterFlags = aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace;

	auto AssimpScene = AssimpImporter.ReadFile(a_FilePath, ImporterFlags);

	if (AssimpScene == nullptr)
	{
		return nullptr;
	}
	
	std::string RootDic = GenerateRootDic(a_FilePath);
	Model* ReturnModel = new Model;
	ModelLoader::Load(ReturnModel,AssimpScene->mRootNode, AssimpScene, RootDic);
	return ReturnModel;
}

void Miracle::ModelLoader::Load(Model* a_Model, aiNode* node, const aiScene* scene, const std::string& a_RootDic)
{

	for (_U32 i = 0; i < node->mNumMeshes; ++i)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		Mesh* pmesh = ModelLoader::Load(mesh, scene, a_RootDic);
		if (pmesh != nullptr)
		{
			a_Model->AddMesh(pmesh);
		}
	}
	for (_U32 i = 0; i < node->mNumChildren; ++i)
	{
		ModelLoader::Load(a_Model,node->mChildren[i], scene, a_RootDic);
	}

}

Miracle::Mesh* Miracle::ModelLoader::Load(aiMesh* a_Mesh, const aiScene* scene, const std::string& a_RootDic)
{
	Mesh* ReturnMesh = nullptr;
	auto MeshDiffuseTexture = GenerateMaterial(a_Mesh, scene, aiTextureType_DIFFUSE, a_RootDic);
	auto MeshSpecularTexture = GenerateMaterial(a_Mesh, scene, aiTextureType_SPECULAR, a_RootDic);
	auto MeshNormalTexure = GenerateMaterial(a_Mesh, scene, aiTextureType_HEIGHT, a_RootDic);
	auto MeshIndexBuffer = GenerateIndexBuffer(a_Mesh);
	if (MeshNormalTexure == nullptr)
	{
		auto MeshVertexBuffer = GenerateVertexBuffer(a_Mesh, false);
		ReturnMesh = new Mesh(MeshVertexBuffer, MeshIndexBuffer, MeshDiffuseTexture, MeshSpecularTexture, MeshNormalTexure, std::string(a_Mesh->mName.C_Str()));
	}
	else
	{
		auto MeshVertexBuffer = GenerateVertexBuffer(a_Mesh, true);
		ReturnMesh = new Mesh(MeshVertexBuffer, MeshIndexBuffer, MeshDiffuseTexture, MeshSpecularTexture, MeshNormalTexure, std::string(a_Mesh->mName.C_Str()));
	}

	return ReturnMesh;
}

std::shared_ptr<Miracle::VertexBuffer> Miracle::ModelLoader::GenerateVertexBuffer(aiMesh* a_Mesh, bool a_IsGenTangent)
{
	_U32 NumVertices = a_Mesh->mNumVertices;
	VertexFormat MeshVertexFormat;
	MeshVertexFormat.AddAttribute(VertexSemantic::POSITION, MENGINE_R32G32B32_FLOAT);
	MeshVertexFormat.AddAttribute(VertexSemantic::NORMAL, MENGINE_R32G32B32_FLOAT);
	MeshVertexFormat.AddAttribute(VertexSemantic::TEXCOORD, MENGINE_R32G32_FLOAT);
	if (a_IsGenTangent == true)
	{
		MeshVertexFormat.AddAttribute(VertexSemantic::TANGENT, MENGINE_R32G32B32_FLOAT);
	}

	_U32 VertexByteSize = MeshVertexFormat.GetByteSize();
	_U32 StrideForByte = VertexByteSize;
	_U32 StrideForFloat = VertexByteSize / sizeof(float);

	char* ChVertexSrcData = new char[VertexByteSize * NumVertices];
	memset(ChVertexSrcData, 0, VertexByteSize * NumVertices);
	_U32 Offset = 0;


	float* FVertexSrcData = (float*)(ChVertexSrcData);

	for (_U32 Index = 0; Index < NumVertices; ++Index)
	{
		_U32 Head = Index * StrideForFloat;

		FVertexSrcData[Head + POSITION_X] = a_Mesh->mVertices[Index].x;
		FVertexSrcData[Head + POSITION_Y] = a_Mesh->mVertices[Index].y;
		FVertexSrcData[Head + POSITION_Z] = a_Mesh->mVertices[Index].z;

		FVertexSrcData[Head + NORMAL_X] = a_Mesh->mNormals[Index].x;
		FVertexSrcData[Head + NORMAL_Y] = a_Mesh->mNormals[Index].y;
		FVertexSrcData[Head + NORMAL_Z] = a_Mesh->mNormals[Index].z;

		if (a_Mesh->mTextureCoords[0])
		{
			FVertexSrcData[Head + TEXCOORD_U] = a_Mesh->mTextureCoords[0][Index].x;
			FVertexSrcData[Head + TEXCOORD_V] = a_Mesh->mTextureCoords[0][Index].y;
		}
		else
		{
			FVertexSrcData[Head + TEXCOORD_U] = 0.0f;
			FVertexSrcData[Head + TEXCOORD_V] = 0.0f;
		}

		if (a_IsGenTangent == true)
		{
			FVertexSrcData[Head + TANGENT_X] = a_Mesh->mTangents[Index].x;
			FVertexSrcData[Head + TANGENT_Y] = a_Mesh->mTangents[Index].y;
			FVertexSrcData[Head + TANGENT_Z] = a_Mesh->mTangents[Index].z;



		}
	}

	std::shared_ptr<VertexBuffer> ReturnVertexBuffer = std::make_shared<VertexBuffer>(MeshVertexFormat, NumVertices);
	ReturnVertexBuffer->SetData(FVertexSrcData);
	return ReturnVertexBuffer;
}

std::shared_ptr<Miracle::IndexBuffer> Miracle::ModelLoader::GenerateIndexBuffer(aiMesh* a_Mesh)
{
	_U32 NumFaces = a_Mesh->mNumFaces;
	_U32 NumVerticesForOneFace = 3;
	_U32 NumIndices = NumFaces * NumVerticesForOneFace;

	_U32* IndexSrcData = new _U32[NumIndices];

	for (_U32 FaceIndex = 0; FaceIndex < NumFaces; ++FaceIndex)
	{
		aiFace face = a_Mesh->mFaces[FaceIndex];
		_U32 Head = FaceIndex * NumVerticesForOneFace;
		for (_U32 IndicesIndex = 0; IndicesIndex < face.mNumIndices; IndicesIndex++)
		{
			IndexSrcData[Head + IndicesIndex] = face.mIndices[IndicesIndex];
		}
	}
	std::shared_ptr<IndexBuffer> ReturnIndexBuffer = std::make_shared<IndexBuffer>(TRIMESH, NumFaces, sizeof(_U32));
	ReturnIndexBuffer->SetData(IndexSrcData);
	return ReturnIndexBuffer;
}

std::shared_ptr<Miracle::Texture2D> Miracle::ModelLoader::GenerateMaterial(aiMesh* a_Mesh, const aiScene* a_Scene, aiTextureType a_Type, const std::string& a_RootDic)
{
	std::shared_ptr<Miracle::Texture2D> ReturnTexture = nullptr;

	if (a_Mesh->mMaterialIndex >= 0)
	{
		aiMaterial* Material = a_Scene->mMaterials[a_Mesh->mMaterialIndex];
		aiString TextureName;
		Material->GetTexture(a_Type, 0, &TextureName);
		if (TextureName.length <= 0)
		{
			return nullptr;
		}
		auto Image = GameResourceSystem::Instance()->GetImage(HName(a_RootDic + TextureName.C_Str()));
		ReturnTexture = std::make_shared<Texture2D>(Image->GetFormat(), Image->GetImageWidth(), Image->GetImageHeight(), true);
		ReturnTexture->SetData(Image->GetData());
	}

	return ReturnTexture;
}

std::string Miracle::ModelLoader::GenerateRootDic(const std::string& a_FilePath)
{
	auto StrArray = StringUtils::Split(a_FilePath, '/');
	std::string RootDic;
	for (_U32 i = 0; i < StrArray.size() - 1; ++i)
	{
		RootDic = RootDic + StrArray[i] + '/';
	}
	return RootDic;
}

