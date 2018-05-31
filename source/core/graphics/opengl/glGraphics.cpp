#include "../graphics.h"
#include <GLEW/GL/glew.h>

template<>
INLINE void GraphicsDevice::ClearBuffers<API_OPENGL>(uint8 buffers)
{
	//TODO: Fix clear inputs
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // | GL_STENCIL_BUFFER_BIT);
}

template<>
INLINE void GraphicsDevice::SetClearColor<API_OPENGL>(float32 r, float32 g, float32 b)
{
	glClearColor(r, g, b, 1.0f);
}