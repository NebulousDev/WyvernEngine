#pragma once

#include "../common.h"

#define CONTEXT_WINDOWED		0x0
#define CONTEXT_FULLSCREEN		0x1
#define	CONTEXT_USE_SOFTWARE	0x2		//TODO: implement
#define CONTEXT_VSYNC			0x3

#define INVALID_CONTEXT			NULLPTR

//Re-definition
typedef WYVHANDLE WindowHandle;

struct	Window;
struct	Context;
struct	ContextInfo;
struct	RenderTarget;
struct	RenderTargetInfo;
struct	InputLayout;
struct	InputLayoutInfo;
struct	Buffer;
struct	BufferInfo;
struct	Shader;
struct	ShaderInfo;

enum	PrimitiveType;

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
	RenderTarget*			backBuffer;		// CONVERTED TO POINTER! FIX IT QUICK
	uint32					vSync;

	typedef	RESULT(*CreateContextFunc)(Context** ppContext, const Window* pWindow, const ContextInfo info);
	typedef	RESULT(*ReleaseContextFunc)(Context* pContext);
	typedef RESULT(*SetContextCurrentFunc)(Context* pContext);

	typedef RESULT(*CreateInputLayoutFunc)(InputLayout** ppLayout, const Context* pContext, const InputLayoutInfo info);
	typedef RESULT(*ReleaseInputLayoutFunc)(InputLayout** ppLayout, const Context* pContext);
	typedef RESULT(*BindInputLayoutFunc)(InputLayout* pLayout, const Context* pContext);
	typedef RESULT(*UnbindInputLayoutFunc)(InputLayout* pLayout, const Context* pContext);

	typedef RESULT(*CreateBufferFunc)(Buffer** ppBuffer, const Context* pContext, const BufferInfo info);
	typedef RESULT(*ReleaseBufferFunc)(Buffer** ppBuffer, const Context* pContext);
	typedef RESULT(*BindBufferFunc)(Buffer* pBuffer, const Context* pContext);
	typedef RESULT(*UnbindBufferFunc)(Buffer* pBuffer, const Context* pContext);

	typedef RESULT(*CreateShaderFunc)(Shader** ppShader, const Context* pContext, const ShaderInfo info);
	typedef RESULT(*ReleaseShaderFunc)(Shader** ppShader);
	typedef	RESULT(*BindShaderFunc)(Shader* pShader, const Context* pContext);
	typedef	RESULT(*UnbindShaderFunc)(const Context* pContext);

	typedef RESULT(*CreateRenderTargetFunc)(RenderTarget** ppTarget, const Context* pContext, const RenderTargetInfo info);
	typedef RESULT(*ClearRenderTargetFunc)(const RenderTarget* pTarget, const Context* pContext, const float32 color[4]);

	typedef RESULT(*SetPrimitiveTypeFunc)(const PrimitiveType type, const Context* pContext);
	typedef RESULT(*DrawIndexedFunc)(const Context* pContext, const uint32 idxStart, const uint32 idxCount);
	
	typedef	RESULT(*PresentFunc)(const Context* pContext);

	CreateContextFunc		fpCreateContext;
	ReleaseContextFunc		fpReleaseContext;
	SetContextCurrentFunc	fpSetContextCurrent;

	CreateInputLayoutFunc	fpCreateInputLayout;
	ReleaseInputLayoutFunc	fpReleaseInputLayout;
	BindInputLayoutFunc		fpBindInputLayout;
	UnbindInputLayoutFunc	fpUnbindInputLayout;

	CreateBufferFunc		fpCreateBuffer;
	ReleaseBufferFunc		fpReleaseBuffer;
	BindBufferFunc			fpBindBuffer;
	UnbindBufferFunc		fpUnbindBuffer;

	CreateShaderFunc		fpCreateShader;
	ReleaseShaderFunc		fpReleaseShader;
	BindShaderFunc			fpBindShader;
	UnbindShaderFunc		fpUnbindShader;

	CreateRenderTargetFunc	fpCreateRenderTarget;
	ClearRenderTargetFunc	fpClearRenderTarget;

	SetPrimitiveTypeFunc	fpSetPrimitiveType;
	DrawIndexedFunc			fpDrawIndexed;

	PresentFunc				fpPresent;
};

typedef WYVPTRHANDLE ContextHandle;
#define WYVHCONTEXT	ContextHandle;

WYVERN_CORE_API
const ContextHandle			CreateContext(const WindowHandle hWindow, const ContextInfo info);
WYVERN_CORE_API
RESULT						ReleaseContext(ContextHandle* phContext);
WYVERN_CORE_API
RESULT						SetContextCurrent(const ContextHandle hContext);
WYVERN_CORE_API
const ContextHandle			GetCurrentContextHandle();
WYVERN_CORE_API
const Context*				GetCurrentContext();
WYVERN_CORE_API
const Context*				GetContextFromHandle(const ContextHandle hContext);