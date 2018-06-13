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

struct GFXBufferHandle
{
	uint32 bufferID;
	uint32 bufferSize;
};

class GraphicsDevice
{
private:
	RESULT(*mClearBuffersFunc)();
	RESULT(*mSetClearColorFunc)(const float32 r, const float32 g, const float32 b);
	RESULT(*mCreateGraphicsBuffer)(GFXBufferHandle* buffer, uint32 size);
	RESULT(*mPutVertexBuffer)(GFXBufferHandle buffer, uint8* data);

	bool mInitialized = false;

public:
	GFXAPI_TEMPLATE int32 InitGraphicsDevice();

	INLINE RESULT ClearBuffers() { return mClearBuffersFunc(); }
	INLINE RESULT SetClearColor(const float32 r, const float32 g, const float32 b) { return mSetClearColorFunc(r, g, b); }
	INLINE RESULT CreateGraphicsBuffer(GFXBufferHandle* buffer, uint32 size) { return mCreateGraphicsBuffer(buffer, size); };
	INLINE RESULT PutVertexBuffer(GFXBufferHandle buffer, uint8* data) { return mPutVertexBuffer(buffer, data); };

	INLINE bool32 IsInitialized() { return mInitialized; }
};