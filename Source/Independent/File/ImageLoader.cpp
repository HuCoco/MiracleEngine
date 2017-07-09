#include "ImageLoader.h"

Miracle::TexImage* Miracle::ImageLoader::Load(const std::string& a_FilePath)
{
	TexImage* ReturnTexImage = nullptr;
	FIBITMAP * FreeImageBitmap = LoadFreeImageBitmap(a_FilePath);;
	if (FreeImageBitmap == nullptr)
	{
		return ReturnTexImage;
	}

	FreeImageBitmap = FreeImage_ConvertTo32Bits(FreeImageBitmap);

	if (FreeImageBitmap == nullptr)
	{
		return ReturnTexImage;
	}

	BYTE* StandardBitmap = FreeImageBitmap2StandardBitmap(FreeImageBitmap);

	ReturnTexImage = CreateTexImage(StandardBitmap, FreeImageBitmap);

	MENGINE_ASSERT_MSG(ReturnTexImage, "Failed to create tex iamge.");

	FreeImage_Unload(FreeImageBitmap);

	return ReturnTexImage;
}

// Need Op!!!! Need Op!!!! Need Op!!!! Need Op!!!!
Miracle::TexImage* Miracle::ImageLoader::Load(
	const std::string& a_RightCubeFace, const std::string& a_LeftCubeFace,
	const std::string& a_UpCubeFace, const std::string& a_DownCubeFace,
	const std::string& a_FrontCubeFace, const std::string& a_BackCubeFace)
{
	TexImage* ReturnTexCubeImage = nullptr;

	TexImage* RightCubeFace = ImageLoader::Load(a_RightCubeFace);
	if (RightCubeFace == nullptr)
	{
		return ReturnTexCubeImage;
	}

	TexImage* LeftCubeFace = ImageLoader::Load(a_LeftCubeFace);
	if (LeftCubeFace == nullptr)
	{
		return ReturnTexCubeImage;
	}

	TexImage* UpCubeFace = ImageLoader::Load(a_UpCubeFace);
	if (UpCubeFace == nullptr)
	{
		return ReturnTexCubeImage;
	}

	TexImage* DownCubeFace = ImageLoader::Load(a_DownCubeFace);
	if (DownCubeFace == nullptr)
	{
		return ReturnTexCubeImage;
	}

	TexImage* FrontCubeFace = ImageLoader::Load(a_FrontCubeFace);
	if (FrontCubeFace == nullptr)
	{
		return ReturnTexCubeImage;
	}

	TexImage* BackCubeFace = ImageLoader::Load(a_BackCubeFace);
	if (BackCubeFace == nullptr)
	{
		return ReturnTexCubeImage;
	}


	_U32 Width = RightCubeFace->GetImageWidth();
	_U32 Height = RightCubeFace->GetImageHeight();
	_U32 NumCubeFaceBytes = Width * Height * 4;

	BYTE* TexCubeBits = new BYTE[NumCubeFaceBytes * 6];

	memcpy(TexCubeBits + NumCubeFaceBytes * 0, RightCubeFace->GetData(), NumCubeFaceBytes);
	memcpy(TexCubeBits + NumCubeFaceBytes * 1, LeftCubeFace->GetData(), NumCubeFaceBytes);
	memcpy(TexCubeBits + NumCubeFaceBytes * 2, UpCubeFace->GetData(), NumCubeFaceBytes);
	memcpy(TexCubeBits + NumCubeFaceBytes * 3, DownCubeFace->GetData(), NumCubeFaceBytes);
	memcpy(TexCubeBits + NumCubeFaceBytes * 4, FrontCubeFace->GetData(), NumCubeFaceBytes);
	memcpy(TexCubeBits + NumCubeFaceBytes * 5, BackCubeFace->GetData(), NumCubeFaceBytes);

	ReturnTexCubeImage = new TexImage(MENGINE_R8G8B8A8_UNORM, TexCubeBits, Width, Height);


	delete RightCubeFace;
	delete LeftCubeFace;
	delete UpCubeFace;
	delete DownCubeFace;
	delete FrontCubeFace;
	delete BackCubeFace;

	return ReturnTexCubeImage;
}

FIBITMAP* Miracle::ImageLoader::LoadFreeImageBitmap(const std::string& a_FilePath)
{
	FIBITMAP * ReturnFreeImageBitmap = nullptr;
	FREE_IMAGE_FORMAT ImageFormat = FIF_UNKNOWN;
	ImageFormat = FreeImage_GetFileType(a_FilePath.c_str());
	if (ImageFormat == FIF_UNKNOWN)
	{
		ImageFormat = FreeImage_GetFIFFromFilename(a_FilePath.c_str());
	}
	if (ImageFormat == FIF_UNKNOWN)
	{
		return ReturnFreeImageBitmap;
	}

	if (FreeImage_FIFSupportsReading(ImageFormat))
	{
		ReturnFreeImageBitmap = FreeImage_Load(ImageFormat, a_FilePath.c_str());
	}
	if (ReturnFreeImageBitmap == nullptr)
	{
		return ReturnFreeImageBitmap;
	}

	return ReturnFreeImageBitmap;
}

BYTE* Miracle::ImageLoader::FreeImageBitmap2StandardBitmap(FIBITMAP* a_FreeImageBitmap)
{
	uint32_t Pitch = FreeImage_GetPitch(a_FreeImageBitmap);
	BYTE* Bits = FreeImage_GetBits(a_FreeImageBitmap);
	uint32_t bbp = FreeImage_GetBPP(a_FreeImageBitmap);
	uint32_t Width = FreeImage_GetWidth(a_FreeImageBitmap);
	uint32_t Height = FreeImage_GetHeight(a_FreeImageBitmap);
	BYTE* StandardBitmap = nullptr;
	
	MENGINE_ASSERT_MSG(bbp == 32, "Bitmap isn't a 32 bits format");

	StandardBitmap = new BYTE[Width * Height * 4];
	if (StandardBitmap == nullptr)
	{
		return nullptr;
	}
	for (uint32_t i = 0; i < Height; ++i)
	{
		for (uint32_t j = 0; j < Width; ++j)
		{
			StandardBitmap[(i * Width + j) * 4 + 0] = Bits[(i * Pitch) + j * 4 + 2];
			StandardBitmap[(i * Width + j) * 4 + 1] = Bits[(i * Pitch) + j * 4 + 1];
			StandardBitmap[(i * Width + j) * 4 + 2] = Bits[(i * Pitch) + j * 4 + 0];
			StandardBitmap[(i * Width + j) * 4 + 3] = Bits[(i * Pitch) + j * 4 + 3];
		}
	}

	return StandardBitmap;
}

Miracle::TexImage* Miracle::ImageLoader::CreateTexImage(BYTE* a_SrcData, FIBITMAP* a_FreeImageBitmap)
{
	uint32_t Width = FreeImage_GetWidth(a_FreeImageBitmap);
	uint32_t Height = FreeImage_GetHeight(a_FreeImageBitmap);
	return new TexImage(Miracle::DataFormat::MENGINE_R8G8B8A8_UNORM,a_SrcData, Width,Height);
}

