#include "../graphics.h"
#include <GLEW/GL/glew.h>
#include "../../platform/platform.h"

void GLClearBuffers()
{
	//TODO: Fix clear inputs
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // | GL_STENCIL_BUFFER_BIT);
}

void GLSetClearColor(const float32 r, const float32 g, const float32 b)
{
	glClearColor(r, g, b, 1.0f);
}

GFXAPI_TEMPLATE_DEF int32 GraphicsDevice::InitGraphicsDevice<GFXAPI_OPENGL>()
{
	//TODO: Destroy previous context

	if (OpenGLCreateContext() == WYVERN_ERROR) return WYVERN_ERROR;
	if (OpenGLMakeContextCurrent() == WYVERN_ERROR) return WYVERN_ERROR;

	mClearBuffersFunc	= &GLClearBuffers;
	mSetClearColorFunc	= &GLSetClearColor;

	mInitialized = true;
		
	return WYVERN_SUCCESS;
}