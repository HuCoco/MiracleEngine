#pragma once

#if defined(_WIN32) | defined (WIN32)
#if defined(_WIN64)
#define 			ME_MSWINDOWS_X64
#else
#define 			ME_MSWINDOWS_X32
#endif
#elif defined (__APPLE__)
#define 			ME_MACOS
#else
#error Unkown Platfom!
#endif