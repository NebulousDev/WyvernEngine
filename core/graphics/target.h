#pragma once

#include "../common.h"

struct WYVERN_CORE_API RenderTargetInfo
{
	uint32			width;
	uint32			height;
	//TODO: add more info
};

struct WYVERN_CORE_API RenderTarget
{
	WYVPTRHANDLE	hTarget;
	uint32			width;
	uint32			height;
};

typedef WYVPTRHANDLE RenderTargetHandle;
#define RENDERTARGET RenderTargetHandle

WYVERN_CORE_API
const RenderTargetHandle	CreateRenderTarget(const RenderTargetInfo info);
WYVERN_CORE_API
RESULT						ClearRenderTarget(const RenderTargetHandle hTarget, const float32 color[4]);
WYVERN_CORE_API
RESULT						ClearBackbuffer(const float32 color[4]);