#include "../graphics.h"
#include "../../platform/platform.h"
#include <GLEW/GL/glew.h>

void GLClearBuffers()
{
	//TODO: Fix clear inputs
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // | GL_STENCIL_BUFFER_BIT);
}

void GLSetClearColor(const float32 r, const float32 g, const float32 b)
{
	glClearColor(r, g, b, 1.0f);
}

RESULT GLCreateGraphicsBuffer(GFXStaticBuffer* buffer)
{
	glGenBuffers(1, &buffer->bufferID);
	return WYVERN_SUCCESS;
}

RESULT GLPutGraphicsBuffer(GFXStaticBuffer buffer, const uint8* data, const uint32 size)
{
	glBufferData(buffer.bufferID, size, data, GL_STATIC_DRAW);
	return WYVERN_SUCCESS;
}

GFXAPI_TEMPLATE_DEF RESULT GraphicsDevice::InitGraphicsDevice<GFXAPI_OPENGL>()
{
	//TODO: Destroy previous context

	if (OpenGLCreateContext() == WYVERN_ERROR) return WYVERN_ERROR;
	if (OpenGLMakeContextCurrent() == WYVERN_ERROR) return WYVERN_ERROR;

	mClearBuffersFunc		= &GLClearBuffers;
	mSetClearColorFunc		= &GLSetClearColor;
	mCreateGraphicsBuffer	= &GLCreateGraphicsBuffer;
	mPutGraphicsBuffer		= &GLPutGraphicsBuffer;

	mInitialized = true;
		
	return WYVERN_SUCCESS;
}