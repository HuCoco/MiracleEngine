#pragma once
#include <Independent/Platform/PlatfomDefine.h>

#if defined(ME_MSWINDOWS_X32) | defined(ME_MSWINDOWS_X64)
#define MENGINE_DRIECTX_SUPPORT
#endif

#ifdef MENGINE_DRIECTX_SUPPORT

#include <D3D11.h>
#include <D3Dcompiler.h>
#include <DXGI.h>

#include <Core/Assert/AssertUtils.h>

template <typename T>
inline ULONG SafeRelease(T*& a_Object)
{
	if (a_Object)
	{
		ULONG refs = a_Object->Release();
		a_Object = nullptr;
		return refs;
	}
	return 0;
}

template <typename T>
inline ULONG FinalRelease(T*& a_Object)
{
	if (a_Object)
	{
		ULONG refs = a_Object->Release();
		a_Object = nullptr;
		if (refs > 0)
		{
			MENGINE_ASSERT_MSG(false,"Reference count is not zero after release.");
			return refs;
		}
	}
	return 0;
}


#define CHECK_HR_RETURN_NONE(msg)\
if (FAILED(hr))\
{ \
    MENGINE_ASSERT_MSG(false,msg); \
}

#define CHECK_HR_RETURN_VOID(msg)\
if (FAILED(hr))\
{ \
    MENGINE_ASSERT_MSG(false,msg); \
    return; \
}

#define CHECK_HR_RETURN(msg, value)\
if (FAILED(hr))\
{ \
    MENGINE_ASSERT_MSG(false,msg); \
    return value; \
}

// D3D11_BIND_FLAG
#define D3D11_BIND_NONE 0

// D3D11_RESOURCE_MISC_FLAG
#define D3D11_RESOURCE_MISC_NONE 0

// D3D11_BUFFER_UAV_FLAG
#define D3D11_BUFFER_UAV_FLAG_BASIC 0

// D3D11_CPU_ACCESS_FLAG
#define D3D11_CPU_ACCESS_NONE 0
#define D3D11_CPU_ACCESS_READ_WRITE (D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE)

// D3D11_QUERY_MISC_FLAG
#define D3D11_QUERY_MISC_NONE 0



#endif