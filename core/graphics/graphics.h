#pragma once
#include "../common.h"
#include "../platform/window.h"

#define CONTEXT_WINDOWED		0x0
#define CONTEXT_FULLSCREEN		0x1
#define	CONTEXT_USE_SOFTWARE	0x2		//TODO: implement
#define CONTEXT_VSYNC			0x3

#define INVALID_CONTEXT			NULLPTR

typedef WYVPTRHANDLE ContextHandle;
typedef WYVPTRHANDLE RenderTargetHandle;

struct Context;
struct ContextInfo;
struct Shader;
struct ShaderInfo;

struct WYVERN_CORE_API RenderTargetInfo
{
	//TODO: add more info
};

struct WYVERN_CORE_API RenderTarget
{
	WYVPTRHANDLE	instance;
	Context*		context;
};

struct WYVERN_CORE_API ContextInfo
{
	WYVPTRHANDLE	renderDevice;
	uint32			bufferCount;
	uint32			multisamples;
	BITS32			flags;
};

struct WYVERN_CORE_API Context
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

	typedef RESULT			(*CreateShaderFunc)(Shader** shader, const Context* context, const ShaderInfo info);
	typedef RESULT			(*DisposeShaderFunc)(Shader** shader);

	typedef RESULT			(*CreateRenderTargetFunc)(RenderTarget* target, const RenderTargetInfo info, Context* context);
	typedef RESULT			(*ClearRenderTargetFunc)(const RenderTarget* target, const Context* context, const float32 color[4]);
	typedef	RESULT			(*PresentFunc)(const Context* context);

	CreateContextFunc		fpCreateContext;
	DisposeContextFunc		fpDisposeContext;
	SetContextCurrentFunc	fpSetContextCurrent;

	CreateShaderFunc		fpCreateShader;
	DisposeShaderFunc		fpDisposeShader;

	CreateRenderTargetFunc	fpCreateRenderTarget;
	ClearRenderTargetFunc	fpClearRenderTarget;
	PresentFunc				fpPresent;
};

WYVERN_CORE_API 
const ContextHandle			CreateContext(const WindowHandle window, const ContextInfo info);
WYVERN_CORE_API 
RESULT						DisposeContext(ContextHandle* context);
WYVERN_CORE_API 
RESULT						SetContextCurrent(const ContextHandle context);

WYVERN_CORE_API 
const RenderTargetHandle	CreateRenderTarget(const RenderTargetInfo info);
WYVERN_CORE_API 
RESULT						ClearRenderTarget(const RenderTargetHandle target, const float32 color[4]);
WYVERN_CORE_API 
RESULT						ClearBackbuffer(const float32 color[4]);

WYVERN_CORE_API 
RESULT						Present();

WYVERN_CORE_API 
const ContextHandle			GetCurrentContext();
WYVERN_CORE_API 
const Context*				GetCurrentContextData();
WYVERN_CORE_API 
const Context*				GetContextData(const ContextHandle context);