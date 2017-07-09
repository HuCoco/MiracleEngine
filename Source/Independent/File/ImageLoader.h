#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Independent/File/Image/TexImage.h>
#include <freeimage.h>

NAMESPACE_MENGINE_BEGIN

class ImageLoader
{
public:
	static TexImage* Load(const std::string& a_FilePath);
	static TexImage* Load(
		const std::string& a_RightCubeFace,
		const std::string& a_LeftCubeFace,
		const std::string& a_UpCubeFace,
		const std::string& a_DownCubeFace,
		const std::string& a_FrontCubeFace,
		const std::string& a_BackCubeFace);

private:
	static FIBITMAP* LoadFreeImageBitmap(const std::string& a_FilePath);
	static BYTE* FreeImageBitmap2StandardBitmap(FIBITMAP* a_FreeImageBitmap);
	static TexImage* CreateTexImage(BYTE* a_SrcData,FIBITMAP* a_FreeImageBitmap);

};

NAMESPACE_MENGINE_END