#pragma once
/* OpenGL */
#include <Independent/Platform/PlatfomDefine.h>

#if defined(ME_MSWINDOWS_X32) | defined(ME_MSWINDOWS_X64) | defined(ME_MACOS)
#define MENGINE_OPENGL_SUPPORT
#endif

#ifdef MENGINE_OPENGL_SUPPORT

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#endif