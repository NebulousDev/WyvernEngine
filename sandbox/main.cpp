#include <platform\platform.h>
#include <platform\window.h>
#include <iostream>

#include "graphics\graphics.h"
#include "graphics\shaders.h"
#include "graphics\buffers.h"
#include "graphics\layout.h"
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

	PlatformInfo info = GetPlatformInfo();

	WindowInfo windInfo = {};
	windInfo.title = "WyvernGame";
	windInfo.width = 1280;
	windInfo.height = 720;
	windInfo.posX = 20;
	windInfo.posY = 20;
	windInfo.flags = 0;

	ContextInfo contextInfo = {};
	contextInfo.bufferCount = 1;
	contextInfo.multisamples = 1;
	contextInfo.hRenderDevice = RENDER_DEVICE_DIRECT3D_11;
	contextInfo.flags = CONTEXT_WINDOWED;

	WindowHandle wind = CreateWindow(windInfo);
	RESULT show = ShowWindow(wind);

	ContextHandle context = CreateContext(wind, contextInfo);
	SetContextCurrent(context);

	HLSLShaderSources testShaderHLSLsources = {};
	testShaderHLSLsources.vertexShaderSource = L"assets\\shaders\\vertTestShader.cso";
	testShaderHLSLsources.pixelShaderSource = L"assets\\shaders\\pixelTestShader.cso";

	ShaderInfo testShaderInfo = {};
	testShaderInfo.name = "Test Shader";
	testShaderInfo.hlslSources = testShaderHLSLsources;

	ShaderHandle shader = CreateShader(context, testShaderInfo);

	uint8 bufferData[] = 
	{
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	};

	BufferInfo vertBufferInfo	= {};
	vertBufferInfo.bufferName	= "Test Vertex Buffer";
	vertBufferInfo.bufferType	= BUFFER_TYPE_VERTEX;
	vertBufferInfo.byteSize		= 10;
	vertBufferInfo.pData		= bufferData;
	vertBufferInfo.bufferUsage	= BUFFER_USAGE_IMMUTABLE;

	BufferHandle vertBuffer = CreateBuffer(vertBufferInfo);

	InputElement elements[2] =
	{
		{ "vertPosition", ELEMENT_USAGE_POSITION, 0, ELEMENT_FORMAT_FLOAT3, 0,  0, LAYOUT_TYPE_VERTEX, 0 },
		{ "vertColor",    ELEMENT_USAGE_COLOR, 0, ELEMENT_FORMAT_FLOAT4,    0, 12, LAYOUT_TYPE_VERTEX, 0 }
	};

	InputLayoutInfo inputLayoutInfo { elements, 2 };

	InputLayoutHandle inputLayout = CreateInputLayout(inputLayoutInfo);

	BindInputLayout(inputLayout);
	BindShader(shader);
	BindBuffer(vertBuffer);

	// DRAW

	//UnbindShader();
	//DisposeShader(&shader);
	//DisposeContext(&context);
}

WYVERN_DLL_API void Loop(const Application* app)
{
	ClearBackbuffer(colors);
	Present();
}