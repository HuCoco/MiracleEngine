#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/GraphicsObject.h>

NAMESPACE_MENGINE_BEGIN

class GraphicsResource : public GraphicsObject
{
protected:
	GraphicsResource(_U32 a_NumElements,size_t a_ElementSize,_U32 a_Type = GraphicsObject::GRAPHICS_RESOURCE);

public:
	virtual ~GraphicsResource();

	inline _U32 GetNumElements() const;
	inline _U32 GetElementSize() const;
	inline _U32 GetNumBytes() const;

	enum class Usage
	{
		DEFAULT,
		IMMUTABLE,
		DYNAMIC
	};

	inline void SetUsage(Usage a_Usage);
	inline Usage GetUsage() const;

	enum class AccessFlag
	{
		NONE,
		READ_ONLY,
		WRITE_ONLY,
		READ_WIRTE
	};


	inline void	SetAccessFlag(AccessFlag a_AccessFlag);
	inline AccessFlag GetAccessFlag() const;

	void SetOffset(_U32 a_Offset);
	inline _U32 GetOffset() const;

	inline _U32 GetNumActiveElements() const;
	inline void SetNumActiveElements(_U32 a_NumActiveElements);
	inline _U32 GetNumActiveBytes() const;

	inline void* GetData() const;
	inline void SetData(void* a_Data);
protected:
	_U32 m_NumElements;
	_U32 m_ElementSize;
	_U32 m_NumBytes;
	_U32 m_NumActiveElements;
	Usage m_Usage;
	AccessFlag m_AccessFlag;
	_U32 m_Offset;
	void* m_pData;

};

inline _U32 GraphicsResource::GetNumElements() const
{
	return m_NumElements;
}

inline _U32 GraphicsResource::GetElementSize() const
{
	return m_ElementSize;
}

inline _U32 GraphicsResource::GetNumBytes() const
{
	return m_NumBytes;
}

inline void GraphicsResource::SetUsage(Usage a_Usage)
{
	m_Usage = a_Usage;
}

inline GraphicsResource::Usage GraphicsResource::GetUsage() const
{
	return m_Usage;
}

inline void	GraphicsResource::SetAccessFlag(AccessFlag a_AccessFlag)
{
	m_AccessFlag = a_AccessFlag;
}

inline GraphicsResource::AccessFlag GraphicsResource::GetAccessFlag() const
{
	return m_AccessFlag;
}

inline _U32 GraphicsResource::GetOffset() const
{
	return m_Offset;
}

inline _U32 GraphicsResource::GetNumActiveElements() const
{
	return m_NumActiveElements;
}

inline void GraphicsResource::SetNumActiveElements(_U32 a_NumActiveElements)
{
	m_NumActiveElements = a_NumActiveElements;
}

inline _U32 GraphicsResource::GetNumActiveBytes() const
{
	return m_NumActiveElements * m_ElementSize;
}

inline void* GraphicsResource::GetData() const
{
	return m_pData;
}

inline void GraphicsResource::SetData(void* a_Data)
{
	m_pData = a_Data;
}

NAMESPACE_MENGINE_END