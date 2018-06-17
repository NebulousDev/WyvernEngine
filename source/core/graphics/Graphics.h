#pragma once

#include "../common.h"
#include "../platform/platform.h"

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

// TODO: Possible remake graphics to use GraphicsCreationInfo struct

class Graphics
{
private:
	const PlatformGraphics* platformGFX;

	void	(*fpClearBuffers)();
	void	(*fpSetClearColor)(const float32 r, const float32 g, const float32 b);
	RESULT	(*fpCreateGraphicsBuffer)(GraphicsBuffer* buffer);
	RESULT	(*fpPutGraphicsBuffer)(const GraphicsBufferType type,
				GraphicsBuffer* buffer, const uint8* data, const uint32 size);
	void	(*fpDrawIndexedBuffers)(const GraphicsBuffer vbo, const GraphicsBuffer ibo);

	bool	mInitialized = false;

public:
	GFXAPI_TEMPLATE RESULT CreateGraphics(const PlatformGraphics* graphics);
	GFXAPI_TEMPLATE RESULT DestroyGraphics();

	INLINE void		ClearBuffers() { fpClearBuffers(); }
	INLINE void		SetClearColor(const float32 r, const float32 g, const float32 b) { fpSetClearColor(r, g, b); }
	
	INLINE RESULT	CreateGraphicsBuffer(GraphicsBuffer* buffer) { return fpCreateGraphicsBuffer(buffer); };
	INLINE RESULT	PutGraphicsBuffer(const GraphicsBufferType type, GraphicsBuffer* buffer,
						const uint8* data, const uint32 size) { return fpPutGraphicsBuffer(type, buffer, data, size); };

	INLINE void		DrawIndexedBuffers(const GraphicsBuffer vbo, const GraphicsBuffer ibo) { fpDrawIndexedBuffers(vbo, ibo); };

	INLINE bool32	IsInitialized() { return mInitialized; }
};