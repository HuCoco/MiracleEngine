#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <ThirdParty/GraphicsKit/DirectXPreCompileHeader.h>
#include <ThirdParty/GraphicsKit/OpenGLPreCompileHeader.h>

NAMESPACE_MENGINE_BEGIN

enum DataFormat
{
	MENGINE_UNKNOWN = 0,
	MENGINE_R32G32B32A32_TYPELESS = 1,
	MENGINE_R32G32B32A32_FLOAT = 2,
	MENGINE_R32G32B32A32_UINT = 3,
	MENGINE_R32G32B32A32_SINT = 4,
	MENGINE_R32G32B32_TYPELESS = 5,
	MENGINE_R32G32B32_FLOAT = 6,
	MENGINE_R32G32B32_UINT = 7,
	MENGINE_R32G32B32_SINT = 8,
	MENGINE_R16G16B16A16_TYPELESS = 9,
	MENGINE_R16G16B16A16_FLOAT = 10,
	MENGINE_R16G16B16A16_UNORM = 11,
	MENGINE_R16G16B16A16_UINT = 12,
	MENGINE_R16G16B16A16_SNORM = 13,
	MENGINE_R16G16B16A16_SINT = 14,
	MENGINE_R32G32_TYPELESS = 15,
	MENGINE_R32G32_FLOAT = 16,
	MENGINE_R32G32_UINT = 17,
	MENGINE_R32G32_SINT = 18,
	MENGINE_R32G8X24_TYPELESS = 19,
	MENGINE_D32_FLOAT_S8X24_UINT = 20,
	MENGINE_R32_FLOAT_X8X24_TYPELESS = 21,
	MENGINE_X32_TYPELESS_G8X24_UINT = 22,
	MENGINE_R10G10B10A2_TYPELESS = 23,
	MENGINE_R10G10B10A2_UNORM = 24,
	MENGINE_R10G10B10A2_UINT = 25,
	MENGINE_R11G11B10_FLOAT = 26,
	MENGINE_R8G8B8A8_TYPELESS = 27,
	MENGINE_R8G8B8A8_UNORM = 28,
	MENGINE_R8G8B8A8_UNORM_SRGB = 29,
	MENGINE_R8G8B8A8_UINT = 30,
	MENGINE_R8G8B8A8_SNORM = 31,
	MENGINE_R8G8B8A8_SINT = 32,
	MENGINE_R16G16_TYPELESS = 33,
	MENGINE_R16G16_FLOAT = 34,
	MENGINE_R16G16_UNORM = 35,
	MENGINE_R16G16_UINT = 36,
	MENGINE_R16G16_SNORM = 37,
	MENGINE_R16G16_SINT = 38,
	MENGINE_R32_TYPELESS = 39,
	MENGINE_D32_FLOAT = 40,
	MENGINE_R32_FLOAT = 41,
	MENGINE_R32_UINT = 42,
	MENGINE_R32_SINT = 43,
	MENGINE_R24G8_TYPELESS = 44,
	MENGINE_D24_UNORM_S8_UINT = 45,
	MENGINE_R24_UNORM_X8_TYPELESS = 46,
	MENGINE_X24_TYPELESS_G8_UINT = 47,
	MENGINE_R8G8_TYPELESS = 48,
	MENGINE_R8G8_UNORM = 49,
	MENGINE_R8G8_UINT = 50,
	MENGINE_R8G8_SNORM = 51,
	MENGINE_R8G8_SINT = 52,
	MENGINE_R16_TYPELESS = 53,
	MENGINE_R16_FLOAT = 54,
	MENGINE_D16_UNORM = 55,
	MENGINE_R16_UNORM = 56,
	MENGINE_R16_UINT = 57,
	MENGINE_R16_SNORM = 58,
	MENGINE_R16_SINT = 59,
	MENGINE_R8_TYPELESS = 60,
	MENGINE_R8_UNORM = 61,
	MENGINE_R8_UINT = 62,
	MENGINE_R8_SNORM = 63,
	MENGINE_R8_SINT = 64,
	MENGINE_A8_UNORM = 65,
	MENGINE_R1_UNORM = 66,
	MENGINE_R9G9B9E5_SHAREDEXP = 67,
	MENGINE_R8G8_B8G8_UNORM = 68,
	MENGINE_G8R8_G8B8_UNORM = 69,
	MENGINE_BC1_TYPELESS = 70,
	MENGINE_BC1_UNORM = 71,
	MENGINE_BC1_UNORM_SRGB = 72,
	MENGINE_BC2_TYPELESS = 73,
	MENGINE_BC2_UNORM = 74,
	MENGINE_BC2_UNORM_SRGB = 75,
	MENGINE_BC3_TYPELESS = 76,
	MENGINE_BC3_UNORM = 77,
	MENGINE_BC3_UNORM_SRGB = 78,
	MENGINE_BC4_TYPELESS = 79,
	MENGINE_BC4_UNORM = 80,
	MENGINE_BC4_SNORM = 81,
	MENGINE_BC5_TYPELESS = 82,
	MENGINE_BC5_UNORM = 83,
	MENGINE_BC5_SNORM = 84,
	MENGINE_B5G6R5_UNORM = 85,
	MENGINE_B5G5R5A1_UNORM = 86,
	MENGINE_B8G8R8A8_UNORM = 87,
	MENGINE_B8G8R8X8_UNORM = 88,
	MENGINE_R10G10B10_XR_BIAS_A2_UNORM = 89,
	MENGINE_B8G8R8A8_TYPELESS = 90,
	MENGINE_B8G8R8A8_UNORM_SRGB = 91,
	MENGINE_B8G8R8X8_TYPELESS = 92,
	MENGINE_B8G8R8X8_UNORM_SRGB = 93,
	MENGINE_BC6H_TYPELESS = 94,
	MENGINE_BC6H_UF16 = 95,
	MENGINE_BC6H_SF16 = 96,
	MENGINE_BC7_TYPELESS = 97,
	MENGINE_BC7_UNORM = 98,
	MENGINE_BC7_UNORM_SRGB = 99,
	MENGINE_AYUV = 100,
	MENGINE_Y410 = 101,
	MENGINE_Y416 = 102,
	MENGINE_NV12 = 103,
	MENGINE_P010 = 104,
	MENGINE_P016 = 105,
	MENGINE_420_OPAQUE = 106,
	MENGINE_YUY2 = 107,
	MENGINE_Y210 = 108,
	MENGINE_Y216 = 109,
	MENGINE_NV11 = 110,
	MENGINE_AI44 = 111,
	MENGINE_IA44 = 112,
	MENGINE_P8 = 113,
	MENGINE_A8P8 = 114,
	MENGINE_B4G4R4A4_UNORM = 115,
	NUM_DIRECTX_FORMATS
};

enum MiracleChannels
{
	MENGINE_UNSUPPORTED,
	MENGINE_BYTE,
	MENGINE_UBYTE,
	MENGINE_SHORT,
	MENGINE_USHORT,
	MENGINE_INT,
	MENGINE_UINT,
	MENGINE_HALF_FLOAT,
	MENGINE_FLOAT,
	MENGINE_DOUBLE,
	MENGINE_INT_10_10_2,
	MENGINE_UINT_10_10_2,
	MENGINE_FLOAT_11_11_10,
	NUM_CHANNELS
};

enum PrimitiveType
{
	NONE = 0xFFFFFFFF,
	POLYPOINT = 0x00000001,
	POLYSEGMENT_DISJOINT = 0x00000002,
	POLYSEGMENT_CONTIGUOUS = 0x00000004,
	TRIMESH = 0x00000008,
	TRISTRIP = 0x00000010,
	POLYSEGMENT_DISJOINT_ADJ = 0x00000020,
	POLYSEGMENT_CONTIGUOUS_ADJ = 0x00000040,
	TRIMESH_ADJ = 0x00000080,
	TRISTRIP_ADJ = 0x00000100,

	HAS_POINTS = POLYPOINT,

	HAS_SEGMENTS = POLYSEGMENT_DISJOINT | POLYSEGMENT_CONTIGUOUS
	| POLYSEGMENT_DISJOINT_ADJ | POLYSEGMENT_CONTIGUOUS_ADJ,

	HAS_TRIANGLES = TRIMESH | TRISTRIP
	| TRIMESH_ADJ | TRISTRIP_ADJ,

	NUM_TYPES = 9
};



class DataFormatUtils
{
public:
	static _U32 GetChannels(DataFormat a_Format);
	static _U32 GetDataFormatBytes(DataFormat a_Format);
	static _U32 GetDataFormatChannles(DataFormat a_Format);
	static bool IsDepth(DataFormat a_Format);

	static GLenum GetOpenGLChannelType(DataFormat a_Format);
private:
	static const GLenum OpenGLDataFormat[];
	static const _U32 ChannelType[];
	static const _U32 NumBytesPerStruct[];
	static const _U32 NumChannles[];
};

NAMESPACE_MENGINE_END