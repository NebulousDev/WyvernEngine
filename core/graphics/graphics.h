#pragma once
#include "../platform/window.h"
#include "../common.h"

#define CONTEXT_WINDOWED		0x0
#define CONTEXT_FULLSCREEN		0x1
#define	CONTEXT_USE_SOFTWARE	0x2		//TODO: implement
#define CONTEXT_VSYNC			0x3

#define INVALID_CONTEXT			NULLPTR

typedef WYVPTRHANDLE ContextHandle;
typedef WYVPTRHANDLE RenderTargetHandle;

struct Context;

/*
enum RenderDevice
{
	RENDER_DEVICE_OPENGL,
	RENDER_DEVICE_OPENGL2,
	RENDER_DEVICE_DIREXT3D_9,
	RENDER_DEVICE_DIREXT3D_11,
	RENDER_DEVICE_DIREXT3D_12,
	RENDER_DEVICE_VULKAN
};
*/

struct RenderTargetInfo
{
	//TODO: add more info
};

struct RenderTarget
{
	WYVPTRHANDLE	instance;
	Context*		context;
};

struct ContextInfo
{
	WYVPTRHANDLE	renderDevice;
	uint32			bufferCount;
	uint32			multisamples;
	BITS32			flags;
};

struct Context
{
	WYVPTRHANDLE			instance;
	WYVPTRHANDLE			swapChain;
	WYVPTRHANDLE			device;
	WYVPTRHANDLE			renderDevice;
	RenderTarget			backBuffer;
	uint32					vSync;

	typedef	RESULT			(*CreateContextFunc)(Context** context, ContextInfo info, const Window* window);
	typedef	RESULT			(*DisposeContextFunc)(Context* context);
	typedef RESULT			(*SetContextCurrentFunc)(Context* context);
	typedef RESULT			(*CreateRenderTargetFunc)(RenderTarget* target, const RenderTargetInfo info, Context* context);
	typedef RESULT			(*ClearRenderTargetFunc)(const RenderTarget* target, const Context* context, const float32 color[4]);
	typedef	RESULT			(*PresentFunc)(const Context* context);

	CreateContextFunc		fpCreateContext;
	DisposeContextFunc		fpDisposeContext;
	SetContextCurrentFunc	fpSetContextCurrent;
	CreateRenderTargetFunc	fpCreateRenderTarget;
	ClearRenderTargetFunc	fpClearRenderTarget;
	PresentFunc				fpPresent;
};

const ContextHandle			CreateContext(const WindowHandle window, const ContextInfo info);

RESULT						DisposeContext(ContextHandle* context);

RESULT						SetContextCurrent(const ContextHandle context);

const RenderTargetHandle	CreateRenderTarget(const RenderTargetInfo info);

RESULT						ClearRenderTarget(const RenderTargetHandle target, const float32 color[4]);

RESULT						ClearBackbuffer(const float32 color[4]);

RESULT						Present();

const ContextHandle			GetCurrentContext();

const Context*				GetContext(const ContextHandle context);