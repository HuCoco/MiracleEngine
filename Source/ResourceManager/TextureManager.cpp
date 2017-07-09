#include "TextureManager.h"
#include <Independent/File/FileSystem.h>


Miracle::TextureManager::TextureManager()
{
}


Miracle::TextureManager::~TextureManager()
{
}

Miracle::TexImage* Miracle::TextureManager::Load(const HName& a_Name)
{
	TexImage* img = nullptr;
	Find(a_Name, img);
	if (img == nullptr)
	{
		img = FileSystem::GetInstance()->LoadTexImage(a_Name.GetString());
		if (img != nullptr)
		{
			m_Mananger.Insert(a_Name, img);
			return img;
		}
		else
		{
			return nullptr;
		}
	}
	return img;
}

bool Miracle::TextureManager::Find(const HName& a_Name, TexImage*& a_Image)
{
	auto node = m_Mananger.Find(a_Name);
	if (node == nullptr)
	{
		return nullptr;
	}
	a_Image = node->Value;
	return true;
}
