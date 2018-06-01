#pragma once

#include "../common.h"

#define GFXAPI_OPENGL			0x1
#define GFXAPI_VULKAN			0x2		// Not supported (yet)
#define GFXAPI_DIRECT3D_9		0x3		// Not supported (yet)
#define GFXAPI_DIRECT3D_11		0x4		// Not supported (yet)
#define GFXAPI_DIRECT3D_12		0x5		// Not supported (yet)

#define COLOR_BUFFER			0x1
#define DEPTH_BUFFER			0x2
#define STENCIL_BUFFER			0x3

#define GFXAPI_TEMPLATE_DECL	template<uint8 GFXAPI>
#define GFXAPI_TEMPLATE_DEF		template<>

class GraphicsDevice
{
private:
	void(*mClearBuffersFunc)();
	void(*mSetClearColorFunc)(const float32 r, const float32 g, const float32 b);

public:
	GFXAPI_TEMPLATE_DECL void InitGraphicsDevice();

	INLINE void ClearBuffers() { return mClearBuffersFunc(); }
	INLINE void SetClearColor(const float32 r, const float32 g, const float32 b) { return mSetClearColorFunc(r, g, b); }
};