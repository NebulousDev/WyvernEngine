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

RESULT GLCreateGraphicsBuffer(GraphicsBuffer* buffer)
{
	glGenBuffers(1, buffer);
	return WYVERN_SUCCESS;
}

RESULT GLPutGraphicsBuffer(const GraphicsBufferType type, const GraphicsBuffer buffer, const uint8* data, const uint32 size)
{
	switch (type)
	{

	case VERTEX_BUFFER_DATA:
	{
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		break;
	}

	case INDEX_BUFFER_DATA:
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		break;
	}

	default:
		break;
	}

	return WYVERN_SUCCESS;
}

void GLDrawIndexedBuffers(const GraphicsBuffer vbo, const GraphicsBuffer ibo)
{

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
	mDrawIndexedBuffers		= &GLDrawIndexedBuffers;

	mInitialized = true;
		
	return WYVERN_SUCCESS;
}