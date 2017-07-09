#pragma once
#include <Independent/Platform/PreCompileHeader.h>

NAMESPACE_MENGINE_BEGIN

class Model;
class TexImage;
class FileSystem
{
public:
	FileSystem();
	~FileSystem();
	static FileSystem* GetInstance();
	TexImage* LoadTexImage(const std::string& a_ImagePath);
	TexImage* LoadTexCubeImage(
		const std::string& a_RightCubeFace,
		const std::string& a_LeftCubeFace,
		const std::string& a_UpCubeFace,
		const std::string& a_DownCubeFace,
		const std::string& a_FrontCubeFace,
		const std::string& a_BackCubeFace);

	Model* LoadModel(const std::string& a_ModelPath);
private:
	static FileSystem* m_pInstance;
};

NAMESPACE_MENGINE_END