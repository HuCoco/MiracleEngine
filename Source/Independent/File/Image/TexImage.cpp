#include <Independent/File/Image/TexImage.h>



Miracle::TexImage::TexImage(DataFormat a_Format, BYTE* a_pData, _U32 a_Width, _U32 a_Height)
	: m_DataFormat(a_Format)
	, m_pData(a_pData)
	, m_Width(a_Width)
	, m_Height(a_Height)
{

}

Miracle::TexImage::~TexImage()
{
}

void Miracle::TexImage::SetImageSize(_U32 a_Width, _U32 a_Height)
{
	m_Width = a_Width;
	m_Height = a_Height;
}
