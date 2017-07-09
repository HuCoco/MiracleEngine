#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Independent/File/Model/Model.h>
#include <Independent/DataStructure/MSet.h>
#include <Core/Foundation/HName.h>

NAMESPACE_MENGINE_BEGIN

class ModelManager
{
public:
	ModelManager();
	~ModelManager();
	Model* Load(const HName& a_Name);
	bool Find(const HName& a_Name, Model*& a_Image);

private:
	MSet<HName, Model*> m_Mananger;
};

NAMESPACE_MENGINE_END