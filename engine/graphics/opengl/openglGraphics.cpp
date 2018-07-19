#include "openglGraphics.h"

RESULT GLCreateContext(Context** context, ContextInfo info, const Window* window)
{
	return SUCCESS;
}

RESULT GLDisposeContext(Context* context)
{
	return SUCCESS;
}

RESULT GLSetContextCurrent(Context* context)
{
	return SUCCESS;
}

RESULT GLCreateRenderTarget(RenderTarget* target, const RenderTargetInfo info, Context* context)
{
	return SUCCESS;
}

RESULT GLClearRenderTarget(const RenderTarget* target, const Context* context, const float32 color[4])
{
	return SUCCESS;
}

RESULT GLPresent(const Context* context)
{
	return SUCCESS;
}