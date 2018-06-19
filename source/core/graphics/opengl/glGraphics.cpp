#include "../graphics.h"
#include "../../platform/platform.h"
#include "glUtils.h"

void GLClearBuffers()
{
	//TODO: Fix clear inputs
	GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);) // | GL_STENCIL_BUFFER_BIT);
}

void GLSetClearColor(const float32 r, const float32 g, const float32 b)
{
	GL_CHECK(glClearColor(r, g, b, 1.0f);)
}

RESULT GLCreateGraphicsBuffer(GraphicsBuffer* buffer)
{
	GL_CHECK(glGenBuffers(1, &buffer->bufferID);)
	return WYVERN_SUCCESS;
}

RESULT GLPutGraphicsBuffer(const GraphicsBufferType type, GraphicsBuffer* buffer, const uint8* data, const uint32 size)
{
	switch (type)
	{
		case VERTEX_BUFFER:
		{
			GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, buffer->bufferID);)
			GL_CHECK(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);)
			break;
		}

		case INDEX_BUFFER:
		{
			GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->bufferID);)
			GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);)
			break;
		}

		default:
			break;
	}

	buffer->size = size;

	return WYVERN_SUCCESS;
}

void GLDrawIndexedBuffers(const GraphicsBuffer vbo, const GraphicsBuffer ibo)
{
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo.bufferID);)
	GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo.bufferID);)

	GL_CHECK(glDrawElements(GL_TRIANGLE_STRIP, ibo.size, GL_UNSIGNED_INT, NULL);)

	//TODO: Dont unbind
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0);)
	GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);)
}

GFXAPI_TEMPLATE_DEF RESULT Graphics::CreateGraphics<GFXAPI_OPENGL>(const PlatformGraphics* graphics)
{
	//TODO: Destroy previous context

	platformGFX = graphics;

	if (graphics->fpGLCreateContext() == WYVERN_ERROR) return WYVERN_ERROR;
	if (graphics->fpGLSetContextCurrent() == WYVERN_ERROR) return WYVERN_ERROR;

	glewInit(); // Is this the best place to init GLEW?

	fpClearBuffers			= &GLClearBuffers;
	fpSetClearColor			= &GLSetClearColor;
	fpCreateGraphicsBuffer	= &GLCreateGraphicsBuffer;
	fpPutGraphicsBuffer		= &GLPutGraphicsBuffer;
	fpDrawIndexedBuffers	= &GLDrawIndexedBuffers;

	mInitialized = true;
		
	return WYVERN_SUCCESS;
}

GFXAPI_TEMPLATE_DEF RESULT Graphics::DestroyGraphics<GFXAPI_OPENGL>()
{
	return WYVERN_SUCCESS;
}