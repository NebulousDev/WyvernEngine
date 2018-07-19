#include "graphics.h"

static Context* sContext;

const ContextHandle CreateContext(const WindowHandle window, const ContextInfo info)
{
	Context* context = NULLPTR;
	((Context::CreateContextFunc)info.renderDevice)(&context, info, GetWindow(window));	// SUPER WONKY
	return (ContextHandle)context;
}

RESULT DisposeContext(ContextHandle* context)
{
	RESULT result = sContext->fpDisposeContext((Context*)*context);
	if (result == SUCCESS) *context = INVALID_CONTEXT;
	return result;
}

RESULT SetContextCurrent(const ContextHandle context)
{
	RESULT result = ((Context*)context)->fpSetContextCurrent((Context*)context);
	if(result) sContext = (Context*)context;
	return result;
}

const RenderTargetHandle CreateRenderTarget(const RenderTargetInfo info)
{
	RenderTarget* renderTarget = NULLPTR;
	sContext->fpCreateRenderTarget(renderTarget, info, sContext);
	return (RenderTargetHandle)renderTarget;
}

RESULT ClearRenderTarget(const RenderTargetHandle target, const float32 color[4])
{
	return sContext->fpClearRenderTarget((RenderTarget*)target, sContext, color);
}

RESULT ClearBackbuffer(const float32 color[4])
{
	return ClearRenderTarget((RenderTargetHandle)&sContext->backBuffer, color);
}

RESULT Present()
{
	return sContext->fpPresent(sContext);
}

const ContextHandle GetCurrentContext()
{
	return (ContextHandle)sContext;
}

const Context* GetContext(const ContextHandle context)
{
	return (Context*)context;
}
