#pragma once
#include "types.h"

#define GFXAPI_OPENGL_ENABLED
#define GFXAPI_D3D9_ENABLED
#define GFXAPI_D3D11_ENABLED
#define GFXAPI_D3D12_ENABLED
#define GFXAPI_VULKAN_ENABLED

enum PlatformOS
{
	OS_WINDOWS,
	OS_LINUX,
	OS_MACOS,
	OS_IOS,
	OS_ANDROID
};

enum PlatformGraphicsAPI
{
	GFX_API_OPENGL,
	GFX_API_D3D9,
	GFX_API_D3D11,
	GFX_API_D2D12,
	GFX_API_VULKAN
};

struct PlatformGraphics
{
	typedef bool32(*FuncGLIsContextCreated)();
	typedef RESULT(*FuncGLCreateContext)();
	typedef RESULT(*FuncGLDestroyContext)();
	typedef RESULT(*FuncGLEnableContext)();
	typedef RESULT(*FuncGLDisableContext)();
	typedef RESULT(*FuncGLSetContextCurrent)();

	FuncGLIsContextCreated	fpGLIsContextCreated;
	FuncGLCreateContext		fpGLCreateContext;
	FuncGLDestroyContext	fpGLDestroyContext;
	FuncGLEnableContext		fpGLEnableContext;
	FuncGLDisableContext	fpGLDisableContext;
	FuncGLSetContextCurrent fpGLSetContextCurrent;
};

struct PlatformApplication
{
	PlatformOS mPlatformOS;

	typedef void(*FuncSetWindowTitle)(const char* title);
	typedef void(*FuncSetWindowSize)(const uint32 width, const uint32 height);
	typedef void(*FuncSetWindowPosition)(const uint32 x, const uint32 y);
	typedef void(*FuncSetWindowCentered)();
	typedef void(*FuncSetWindowVisible)(const bool32 visible);

	FuncSetWindowTitle		fpSetWindowTitle;
	FuncSetWindowSize		fpSetWindowSize;
	FuncSetWindowPosition	fpSetWindowPosition;
	FuncSetWindowCentered	fpSetWindowCentered;
	FuncSetWindowVisible	fpSetWindowVisible;
};