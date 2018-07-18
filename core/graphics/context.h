#pragma once
#include "platform/window.h"
#include "common.h"

#define	CONTEXT_USE_SOFTWARE	0x1
#define CONTEXT_FULLSCREEN		0x2

enum RenderDevice
{
	RENDER_DEVICE_OPENGL,
	RENDER_DEVICE_OPENGL2,
	RENDER_DEVICE_DIREXT3D_9,
	RENDER_DEVICE_DIREXT3D_11,
	RENDER_DEVICE_DIREXT3D_12,
	RENDER_DEVICE_VULKAN
};

struct ContextCreationInfo
{
	RenderDevice	renderDevice;
	uint32			bufferCount;
	uint32			multisamples;
	BITS32			flags;
};

struct Context
{
	WindowHandle	window;
	WYVPTRHANDLE	swapChain;
	WYVPTRHANDLE	device;
	WYVPTRHANDLE	context;
	RenderDevice	renderDevice;
};