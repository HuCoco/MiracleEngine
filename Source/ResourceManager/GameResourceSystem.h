#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <ResourceManager/ModelManager.h>
#include <ResourceManager/TextureManager.h>
NAMESPACE_MENGINE_BEGIN

class GameResourceSystem
{
public:
	GameResourceSystem();
	~GameResourceSystem();
	static void StartUp();
	static void ShutDown();
	static GameResourceSystem* Instance();


	Model* GetModel(const HName& a_Name);
	Model* GetModel(const std::string& a_Name); 
	TexImage* GetImage(const HName& a_Name);

private:
	TextureManager m_TextureManager;
	ModelManager m_ModelManager;
	static GameResourceSystem* s_pInstance;
};

NAMESPACE_MENGINE_END