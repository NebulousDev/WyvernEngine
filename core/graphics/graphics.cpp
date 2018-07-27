#include "graphics.h"

static Context* sContext;

const ContextHandle CreateContext(const WindowHandle hWindow, const ContextInfo info)
{
	Context* pContext = NULLPTR;
	((Context::CreateContextFunc)info.hRenderDevice)(&pContext, info, GetWindow(hWindow));	// SUPER WONKY
	return (ContextHandle)pContext;
}

RESULT DisposeContext(ContextHandle* phContext)
{
	RESULT result = sContext->fpDisposeContext((Context*)*phContext);
	if (result == SUCCESS) *phContext = INVALID_CONTEXT;
	return result;
}

RESULT SetContextCurrent(const ContextHandle hContext)
{
	RESULT result = ((Context*)hContext)->fpSetContextCurrent((Context*)hContext);
	if(result) sContext = (Context*)hContext;
	return result;
}

const RenderTargetHandle CreateRenderTarget(const RenderTargetInfo info)
{
	RenderTarget* renderTarget = NULLPTR;
	sContext->fpCreateRenderTarget(renderTarget, info, sContext);
	return (RenderTargetHandle)renderTarget;
}

RESULT ClearRenderTarget(const RenderTargetHandle hTarget, const float32 color[4])
{
	return sContext->fpClearRenderTarget((RenderTarget*)hTarget, sContext, color);
}

RESULT ClearBackbuffer(const float32 color[4])
{
	return ClearRenderTarget((RenderTargetHandle)&sContext->backBuffer, color);
}

RESULT Present()
{
	return sContext->fpPresent(sContext);
}

const ContextHandle GetCurrentContextHandle()
{
	return (ContextHandle)sContext;
}

const Context* GetCurrentContext()
{
	return (Context*)sContext;
}

const Context* GetContextFromHandle(const ContextHandle context)
{
	return (Context*)context;
}
