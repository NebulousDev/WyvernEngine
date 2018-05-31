#pragma once

#include "../common.h"

#define API_OPENGL		0x1

#define COLOR_BUFFER	0x1
#define DEPTH_BUFFER	0x2
#define STENCIL_BUFFER	0x3

#define GFX_TEMPLATE	template<uint8 API>

struct GraphicsDevice
{
	GFX_TEMPLATE INLINE void ClearBuffers(uint8 buffers);
	GFX_TEMPLATE INLINE void SetClearColor(float32 r, float32 g, float32 b);
};
