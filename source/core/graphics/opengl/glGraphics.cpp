#include "../graphics.h"
#include "../../platform/platform.h"
#include <GLEW/glew.h>

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
	glGenBuffers(1, &buffer->bufferID);
	return WYVERN_SUCCESS;
}

RESULT GLPutGraphicsBuffer(const GraphicsBufferType type, GraphicsBuffer* buffer, const uint8* data, const uint32 size)
{
	switch (type)
	{

		case VERTEX_BUFFER_DATA:
		{
			glBindBuffer(GL_ARRAY_BUFFER, buffer->bufferID);
			glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
			break;
		}

		case INDEX_BUFFER_DATA:
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->bufferID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
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
	glBindBuffer(GL_ARRAY_BUFFER, vbo.bufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo.bufferID);

	glDrawElements(GL_TRIANGLE_STRIP, ibo.size, GL_UNSIGNED_INT, NULL);

	//TODO: Dont unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GFXAPI_TEMPLATE_DEF RESULT Graphics::CreateGraphics<GFXAPI_OPENGL>()
{
	//TODO: Destroy previous context

	//TODO: Rename these with Platform prefix:
	if (OpenGLCreateContext() == WYVERN_ERROR) return WYVERN_ERROR;
	if (OpenGLMakeContextCurrent() == WYVERN_ERROR) return WYVERN_ERROR;

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