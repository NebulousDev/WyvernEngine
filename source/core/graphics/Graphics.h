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

#define GFXAPI_TEMPLATE			template<uint8 GFXAPI>
#define GFXAPI_TEMPLATE_DEF		template<>

struct GFXStaticBuffer
{
	uint32 bufferID;
	uint32 bufferSize;
};

class GraphicsDevice
{
private:
	void(*mClearBuffersFunc)();
	void(*mSetClearColorFunc)(const float32 r, const float32 g, const float32 b);
	RESULT(*mCreateGraphicsBuffer)(GFXStaticBuffer* buffer);
	RESULT(*mPutGraphicsBuffer)(GFXStaticBuffer buffer, const uint8* data, const uint32 size);

	bool mInitialized = false;

public:
	GFXAPI_TEMPLATE RESULT InitGraphicsDevice();

	INLINE void ClearBuffers() { mClearBuffersFunc(); }
	INLINE void SetClearColor(const float32 r, const float32 g, const float32 b) { mSetClearColorFunc(r, g, b); }
	INLINE RESULT CreateGraphicsBuffer(GFXStaticBuffer* buffer) { return mCreateGraphicsBuffer(buffer); };
	INLINE RESULT PutGraphicsBuffer(GFXStaticBuffer buffer, const uint8* data, const uint32 size) { return mPutGraphicsBuffer(buffer, data, size); };

	INLINE bool32 IsInitialized() { return mInitialized; }
};