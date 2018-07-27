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
	WYVPTRHANDLE	hTarget;
	Context*		pContext;		// convert to handle?
};

struct WYVERN_CORE_API ContextInfo
{
	WYVPTRHANDLE	hRenderDevice;
	uint32			bufferCount;
	uint32			multisamples;
	BITS32			flags;
};

struct WYVERN_CORE_API Context
{
	WYVPTRHANDLE			hDevice;
	WYVPTRHANDLE			hDeviceContext;
	WYVPTRHANDLE			hSwapChain;
	WYVPTRHANDLE			hRenderDevice;
	RenderTarget			backBuffer;
	uint32					vSync;

	typedef	RESULT			(*CreateContextFunc)(Context** ppContext, ContextInfo info, const Window* pWindow);
	typedef	RESULT			(*DisposeContextFunc)(Context* pContext);
	typedef RESULT			(*SetContextCurrentFunc)(Context* pContext);

	typedef RESULT			(*CreateShaderFunc)(Shader** ppShader, const Context* pContext, const ShaderInfo info);
	typedef RESULT			(*DisposeShaderFunc)(Shader** ppShader);
	typedef	RESULT			(*BindShaderFunc)(Shader* pShader, const Context* pContext);
	typedef	RESULT			(*UnbindShaderFunc)(const Context* pContext);

	typedef RESULT			(*CreateRenderTargetFunc)(RenderTarget* pTarget, const RenderTargetInfo info, Context* pContext);		// move params
	typedef RESULT			(*ClearRenderTargetFunc)(const RenderTarget* pTarget, const Context* pContext, const float32 color[4]);
	typedef	RESULT			(*PresentFunc)(const Context* pContext);

	CreateContextFunc		fpCreateContext;
	DisposeContextFunc		fpDisposeContext;
	SetContextCurrentFunc	fpSetContextCurrent;

	CreateShaderFunc		fpCreateShader;
	DisposeShaderFunc		fpDisposeShader;
	BindShaderFunc			fpBindShader;
	UnbindShaderFunc		fpUnbindShader;

	CreateRenderTargetFunc	fpCreateRenderTarget;
	ClearRenderTargetFunc	fpClearRenderTarget;
	PresentFunc				fpPresent;
};

WYVERN_CORE_API 
const ContextHandle			CreateContext(const WindowHandle hWindow, const ContextInfo info);
WYVERN_CORE_API 
RESULT						DisposeContext(ContextHandle* phContext);
WYVERN_CORE_API 
RESULT						SetContextCurrent(const ContextHandle hContext);

WYVERN_CORE_API 
const RenderTargetHandle	CreateRenderTarget(const RenderTargetInfo info);
WYVERN_CORE_API 
RESULT						ClearRenderTarget(const RenderTargetHandle hTarget, const float32 color[4]);
WYVERN_CORE_API 
RESULT						ClearBackbuffer(const float32 color[4]);

WYVERN_CORE_API 
RESULT						Present();

WYVERN_CORE_API 
const ContextHandle			GetCurrentContextHandle();
WYVERN_CORE_API 
const Context*				GetCurrentContext();
WYVERN_CORE_API 
const Context*				GetContextFromHandle(const ContextHandle hContext);