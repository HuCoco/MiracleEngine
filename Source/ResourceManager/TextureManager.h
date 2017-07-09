#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Independent/DataStructure/MSet.h>
#include <Independent/File/Image/TexImage.h>
#include <Core/Foundation/HName.h>

NAMESPACE_MENGINE_BEGIN

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	TexImage* Load(const HName& a_Name);
	bool Find(const HName& a_Name, TexImage*& a_Image);

private:
	MSet<HName, TexImage*> m_Mananger;
};

NAMESPACE_MENGINE_END