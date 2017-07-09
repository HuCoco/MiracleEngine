#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Core/Foundation/HObject.h>

NAMESPACE_MENGINE_BEGIN


enum
{
	ConstantBufferShaderDataIndex = 0,
	TextureBufferShaderDataIndex = 1,
	StructuredBufferShaderDataIndex = 2,
	RawBufferShaderDataIndex = 3,
	TextureSingleShaderDataIndex = 4,
	TextureArrayShaderDataIndex = 5,
	SamplerStateShaderDataIndex = 6,
	NUM_SHADER_DATA_INDEX
};

class GraphicsObject : public HObject
{
public:

	enum { UNKWON = -1 };

	enum
	{
		GRAPHICS_RESOURCE,
			RESOURCE,
				BUFFER,
					CONSTANT_BUFFER,
					TEXTURE_BUFFER,
					VERTEX_BUFFER,
					INDEX_BUFFER,
				TEXTURE,
					TEXTURE_SINGLE,
						TEXTURE1D,
						TEXTURE2D,
							TEXTURE_RENDER_TARGET,
							TEXTURE_DEPTH_STENCIL,
						TEXTURE3D,
					TEXTURE_ARRAY,
						TEXTURE1D_ARRAY,
						TEXTURE2D_ARRAY,
						TEXTURE_CUBE,
						TEXTURE_CUBE_ARRAY,
			SHADER,
				VERTEX_SHADER,
				GEOMETRY_SHADER,
				PIXEL_SHADER,
				COMPUTE_SHADER,
			STATE,
				SAMPLER_STATE,
				BLEND_STATE,
				DEPTH_STENCIL_STATE,
				RASTERIZER_STATE,
		NUM_GRAPHICS_OBJECT_TYPES
	};

	GraphicsObject(_U32 a_Type);
	~GraphicsObject();

	inline _U32 GetType() const;
	inline bool IsBuffer() const;
	inline bool IsTexture() const;
	inline bool IsTextureArray() const;
	inline bool IsShader() const;
	inline bool IsState() const;

private:
	_U32 m_GraphicsType;
};

inline _U32 GraphicsObject::GetType() const
{
	return m_GraphicsType;
}

inline bool GraphicsObject::IsBuffer() const
{
	return	(BUFFER <= m_GraphicsType) & (m_GraphicsType <= INDEX_BUFFER);
}

inline bool GraphicsObject::IsTexture() const
{
	return	(TEXTURE_SINGLE <= m_GraphicsType) && (m_GraphicsType <= TEXTURE3D);
}

inline bool GraphicsObject::IsTextureArray() const
{
	return	(TEXTURE_ARRAY <= m_GraphicsType) && (m_GraphicsType <= TEXTURE_CUBE_ARRAY);
}

inline bool GraphicsObject::IsShader() const
{
	return	(SHADER <= m_GraphicsType) && (m_GraphicsType <= COMPUTE_SHADER);
}

inline bool GraphicsObject::IsState() const
{
	return	(STATE <= m_GraphicsType) && (m_GraphicsType <= RASTERIZER_STATE);
}


NAMESPACE_MENGINE_END