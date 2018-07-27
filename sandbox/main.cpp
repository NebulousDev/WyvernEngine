#include <platform\platform.h>
#include <platform\window.h>
#include <iostream>

#include "graphics\graphics.h"
#include "graphics\shaders.h"
#include <d3d11Graphics.h>
#include <openglGraphics.h>

WYVERN_DLL_API void Create(ApplicationInfo* info)
{
	info->appName			= "Wyvern Game";
	info->appVersion		= "1.0.0";
	info->appMemAllocSize	= MEGABYTES(64);
}

static float32 colors[4]{ 0.0f, 0.08f, 0.1f, 1.0f };

WYVERN_DLL_API void Start(const Application* app, const Platform* platform)
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
	contextInfo.hRenderDevice	= RENDER_DEVICE_DIRECT3D_11;
	contextInfo.flags			= CONTEXT_WINDOWED;

	WindowHandle wind = CreateWindow(windInfo);
	RESULT show = ShowWindow(wind);

	ContextHandle context = CreateContext(wind, contextInfo);
	SetContextCurrent(context);

	HLSLShaderSources testShaderHLSLsources = {};
	testShaderHLSLsources.pVertexShader		= "shaders/vertTestShader.hlsl";
	testShaderHLSLsources.pPixelShader		= "shaders/pixelTestShader.hlsl";

	ShaderInfo testShaderInfo	= {};
	testShaderInfo.pName		= "Test Shader";
	testShaderInfo.hlslSources	= testShaderHLSLsources;

	ShaderHandle shader = CreateShader(context, testShaderInfo);

}

WYVERN_DLL_API void Loop(const Application* app)
{
	ClearBackbuffer(colors);
	Present();
}