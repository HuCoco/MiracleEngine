#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/Resource/DataFormat.h>

NAMESPACE_MENGINE_BEGIN
class TexImage
{
public:

	TexImage(DataFormat a_Format,BYTE* a_pData, _U32 a_Width = 0, _U32 a_Height = 0);
	~TexImage();

	void SetImageSize(_U32 a_Width, _U32 a_Height);
	inline _U32 GetImageWidth();
	inline _U32 GetImageHeight();
	inline BYTE* GetData();
	inline DataFormat GetFormat();
private:
	BYTE* m_pData;
	_U32 m_Width;
	_U32 m_Height;
	DataFormat m_DataFormat;
};


inline _U32 TexImage::GetImageWidth()
{
	return m_Width; 
}

inline _U32 TexImage::GetImageHeight() 
{
	return m_Height; 
}

inline BYTE* TexImage::GetData() 
{
	return m_pData; 
}

inline DataFormat TexImage::GetFormat() 
{
	return m_DataFormat; 
}

NAMESPACE_MENGINE_END