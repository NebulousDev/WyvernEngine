#include <platform\platform.h>
#include <platform\window.h>
#include <iostream>

#include "graphics\graphics.h"
#include "graphics\d3d11\d3d11Graphics.h"

EXPORT void Create(ApplicationInfo* info)
{
	info->appName			= "Wyvern Game";
	info->appVersion		= "1.0.0";
	info->appMemAllocSize	= MEGABYTES(64);
}

static float32 colors[4]{ 0.0f, 0.08f, 0.1f, 1.0f };

EXPORT void Start(const Application* app, const Platform* platform)
{
	InitPlaform(platform);	// Call from platform?

	PlatformInfo info			= GetPlatformInfo();

	WindowInfo windInfo			= {};
	windInfo.title				= "WyvernGame";
	windInfo.width				= 1280;
	windInfo.height				= 720;
	windInfo.posX				= 20;
	windInfo.posY				= 20;
	windInfo.flags				= 0;

	ContextInfo contextInfo		= {};
	contextInfo.bufferCount		= 1;
	contextInfo.multisamples	= 1;
	contextInfo.renderDevice	= RENDER_DEVICE_DIRECT3D_11;
	contextInfo.flags			= CONTEXT_WINDOWED;

	WindowHandle wind = CreateWindow(windInfo);
	RESULT show = ShowWindow(wind);

	ContextHandle context = CreateContext(wind, contextInfo);
	SetContextCurrent(context);
}

EXPORT void Loop(const Application* app)
{
	ClearBackbuffer(colors);
	Present();
}