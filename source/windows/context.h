#pragma once

#include "header.h"
#include "types.h"

typedef HDC		GraphicsDevice;
typedef HGLRC	GraphicsContext;

#define GFXAPI_OPENGL_ENABLED
#define GFXAPI_D3D9_ENABLED
#define GFXAPI_D3D11_ENABLED
#define GFXAPI_D3D12_ENABLED
#define GFXAPI_VULKAN_ENABLED

//TODO: Make color depth display dependent
#define PIXEL_COLOR_BITS 32
#define PIXEL_DEPTH_BITS 24

#define GFXAPI_OPENGL			0x1
#define GFXAPI_VULKAN			0x2		// Not supported (yet)
#define GFXAPI_DIRECT3D_9		0x3		// Not supported (yet)
#define GFXAPI_DIRECT3D_11		0x4		// Not supported (yet)
#define GFXAPI_DIRECT3D_12		0x5		// Not supported (yet)

#define GFXAPI_TEMPLATE			template<uint8 GFXAPI>
#define GFXAPI_TEMPLATE_DEF		template<>

#if defined(GFXAPI_OPENGL_ENABLED)

EXPORT RESULT GLCreateContext(GraphicsContext* glContext, GraphicsDevice device);

EXPORT RESULT GLMakeContextCurrent(GraphicsDevice device, GraphicsContext context);

EXPORT RESULT GLDeleteContext(GraphicsContext* context);

#endif