#pragma once

#include "../common.h"

enum WYVERN_CORE_API BufferUsage
{
	BUFFER_USAGE_MUTABLE,
	BUFFER_USAGE_IMMUTABLE,
	BUFFER_USAGE_DYNAMIC
};

enum WYVERN_CORE_API BufferType
{
	BUFFER_TYPE_VERTEX,
	BUFFER_TYPE_UNIFORM
};

struct WYVERN_CORE_API BufferInfo
{
	const STRING	bufferName;
	uint32			byteSize;
	uint8*			pData;
	uint32			stride;
	uint32			offset;
	BufferUsage		bufferUsage;
	BufferType		bufferType;
};

struct WYVERN_CORE_API Buffer
{
	const STRING	bufferName;
	WYVPTRHANDLE	hBuffer;
	uint32			byteSize;
	BufferUsage		bufferUsage;
	BufferType		bufferType;
	uint32			stride;
	uint32			offset;
	bool8			isBound;
	uint32			bindSlot;
};

typedef WYVPTRHANDLE BufferHandle;
#define GFXBUFFER BufferHandle;

WYVERN_CORE_API
const BufferHandle	CreateBuffer(const BufferInfo info);
WYVERN_CORE_API
RESULT				BindBuffer(BufferHandle hBuffer);
WYVERN_CORE_API
RESULT				UnbindBuffer(BufferHandle hBuffer);
WYVERN_CORE_API
RESULT				ReleaseBuffer(BufferHandle* phBuffer);