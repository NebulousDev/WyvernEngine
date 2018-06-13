#include "../graphics.h"
#include "../../platform/platform.h"
#include <GLEW/GL/glew.h>

RESULT GLClearBuffers()
{
	//TODO: Fix clear inputs
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // | GL_STENCIL_BUFFER_BIT);
	return WYVERN_SUCCESS;
}

RESULT GLSetClearColor(const float32 r, const float32 g, const float32 b)
{
	glClearColor(r, g, b, 1.0f);
	return WYVERN_SUCCESS;
}

RESULT CreateGraphicsBuffer(GFXBufferHandle* buffer, uint32 size)
{
	//glGenBuffers(1, &buffer->bufferID);
	return WYVERN_SUCCESS;
}

RESULT PutVertexBuffer(GFXBufferHandle buffer, uint8 * data)
{
	return WYVERN_SUCCESS;
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