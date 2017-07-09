#include <Independent/File/FileSystem.h>
#include <Independent/File/Image/TexImage.h>
#include <Independent/File/Model/Model.h> 
#include <Independent/File/ImageLoader.h>
#include <Independent/File/ModelLoader.h>


Miracle::FileSystem* Miracle::FileSystem::m_pInstance = nullptr;

Miracle::FileSystem::FileSystem()
{
}


Miracle::FileSystem::~FileSystem()
{
}

Miracle::FileSystem* Miracle::FileSystem::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new FileSystem;
	}
	return m_pInstance;
}


Miracle::TexImage* Miracle::FileSystem::LoadTexImage(const std::string& a_ImagePath)
{
	return ImageLoader::Load(a_ImagePath);
}


Miracle::TexImage* Miracle::FileSystem::LoadTexCubeImage(
	const std::string& a_RightCubeFace, 
	const std::string& a_LeftCubeFace, 
	const std::string& a_UpCubeFace, 
	const std::string& a_DownCubeFace, 
	const std::string& a_BackCubeFace,
	const std::string& a_FrontCubeFace)

{
	return ImageLoader::Load(
		a_RightCubeFace, a_LeftCubeFace,
		a_UpCubeFace, a_DownCubeFace,
		a_BackCubeFace, a_FrontCubeFace);
}

Miracle::Model* Miracle::FileSystem::LoadModel(const std::string& a_ModelPath)
{
	return ModelLoader::Load(a_ModelPath);
}

