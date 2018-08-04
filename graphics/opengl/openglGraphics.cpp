#include "openglGraphics.h"
#include "opengl.h"

#include <iostream>

void GLSetupFunctions(Context* context)
{
	/*
	context->fpCreateContext		= GLCreateContext;
	context->fpSetContextCurrent	= GLSetContextCurrent;
	context->fpReleaseContext		= GLDisposeContext;
	context->fpCreateRenderTarget	= GLCreateRenderTarget;
	context->fpClearRenderTarget	= GLClearRenderTarget;
	context->fpPresent				= GLPresent;
	*/
}

RESULT GLCreateContext(Context** context, ContextInfo info, const Window* window)
{
	std::cout << "GLCONTEXT" << std::endl;
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