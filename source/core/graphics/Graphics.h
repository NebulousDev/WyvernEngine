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

struct GraphicsBuffer
{
	uint32 bufferID;
	uint32 size;
};

enum GraphicsBufferType
{
	VERTEX_BUFFER_DATA,
	INDEX_BUFFER_DATA
};

class GraphicsDevice
{
private:
	void(*mClearBuffersFunc)();
	void(*mSetClearColorFunc)(const float32 r, const float32 g, const float32 b);
	RESULT(*mCreateGraphicsBuffer)(GraphicsBuffer* buffer);
	RESULT(*mPutGraphicsBuffer)(const GraphicsBufferType type,
		GraphicsBuffer* buffer, const uint8* data, const uint32 size);
	void(*mDrawIndexedBuffers)(const GraphicsBuffer vbo, const GraphicsBuffer ibo);

	bool mInitialized = false;

public:
	GFXAPI_TEMPLATE RESULT InitGraphicsDevice();

	INLINE void ClearBuffers() { mClearBuffersFunc(); }
	INLINE void SetClearColor(const float32 r, const float32 g, const float32 b) { mSetClearColorFunc(r, g, b); }
	
	INLINE RESULT CreateGraphicsBuffer(GraphicsBuffer* buffer) { return mCreateGraphicsBuffer(buffer); };
	INLINE RESULT PutGraphicsBuffer(const GraphicsBufferType type, GraphicsBuffer* buffer,
		const uint8* data, const uint32 size) { return mPutGraphicsBuffer(type, buffer, data, size); };

	INLINE void DrawIndexedBuffers(const GraphicsBuffer vbo, const GraphicsBuffer ibo) { mDrawIndexedBuffers(vbo, ibo); };

	INLINE bool32 IsInitialized() { return mInitialized; }
};