#include "context.h"
#include "../platform/window.h"

static Context* sContext;

const ContextHandle CreateContext(const WindowHandle hWindow, const ContextInfo info)
{
	Context* pContext = NULLPTR;
	((Context::CreateContextFunc)info.hRenderDevice)(&pContext, GetWindow(hWindow), info);	// SUPER WONKY
	return (ContextHandle)pContext;
}

RESULT ReleaseContext(ContextHandle* phContext)
{
	RESULT result = sContext->fpReleaseContext((Context*)*phContext);
	if (result == SUCCESS) *phContext = INVALID_CONTEXT;
	return result;
}

RESULT SetContextCurrent(const ContextHandle hContext)
{
	RESULT result = ((Context*)hContext)->fpSetContextCurrent((Context*)hContext);
	if (result) sContext = (Context*)hContext;
	return result;
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
