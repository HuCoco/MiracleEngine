#pragma once
#include <Independent/Platform/PlatfomDefine.h>

#ifdef  ME_MSWINDOWS_X32
typedef signed char					_I8;
typedef short						_I16;
typedef int							_I32;
typedef long long					_I64;
typedef unsigned char				_U8;
typedef unsigned short				_U16;
typedef unsigned int				_U32;
typedef unsigned long long			_U64;
typedef float						_F32;
typedef double						_D64;
typedef int							_Enum;
typedef unsigned int				GraphicsObjectID;
#elif ME_MSWINDOWS_X64
typedef signed char					_I8;
typedef short						_I16;
typedef int							_I32;
typedef long long					_I64;
typedef unsigned char				_U8;
typedef unsigned short				_U16;
typedef unsigned int				_U32;
typedef unsigned long long			_U64;
typedef float						_F32;
typedef double						_D64;
typedef int							_Enum;
typedef unsigned int				GraphicsObjectID;
#elif ME_MACOS

#endif
