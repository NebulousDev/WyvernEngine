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

	// SHADERS ////////////////////////////////////////////////////////////////

	HLSLShaderSources testShaderHLSLsources = {};
	testShaderHLSLsources.vertexShaderSource = L"assets\\shaders\\vertTestShader.cso";
	testShaderHLSLsources.pixelShaderSource = L"assets\\shaders\\pixelTestShader.cso";

	ShaderInfo testShaderInfo = {};
	testShaderInfo.name = "Test Shader";
	testShaderInfo.hlslSources = testShaderHLSLsources;

	ShaderHandle shader = CreateShader(context, testShaderInfo);

	// VERTEX BUFFERS /////////////////////////////////////////////////////////

	float32 vertexData[] = 
	{
		 0.0f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f, 1.0f,
	};

	BufferInfo vertBufferInfo	= {};
	vertBufferInfo.bufferName	= "VertBuffer";
	vertBufferInfo.bufferType	= BUFFER_TYPE_VERTEX;
	vertBufferInfo.count		= sizeof(vertexData);
	vertBufferInfo.stride		= 7 * 4;
	vertBufferInfo.pData		= vertexData;
	vertBufferInfo.bufferUsage	= BUFFER_USAGE_IMMUTABLE;

	BufferHandle vertBuffer = CreateBuffer(vertBufferInfo);

	uint32 indexData[] =
	{ 0, 1, 2 };

	BufferInfo indexBufferInfo	= {};
	indexBufferInfo.bufferName	= "IdxBuffer";
	indexBufferInfo.bufferType	= BUFFER_TYPE_INDEX;
	indexBufferInfo.count		= sizeof(indexData);
	indexBufferInfo.stride		= 1 * 4;
	indexBufferInfo.pData		= indexData;
	indexBufferInfo.bufferUsage = BUFFER_USAGE_IMMUTABLE;

	BufferHandle idxBuffer = CreateBuffer(indexBufferInfo);

	// INPUT LAYOUT ////////////////////////////////////////////////////////////

	InputElement elements[2] =
	{
		{ "vertPosition", ELEMENT_USAGE_POSITION, 0, ELEMENT_FORMAT_FLOAT3, 0,  0, LAYOUT_TYPE_VERTEX, 0 },
		{ "vertColor",    ELEMENT_USAGE_COLOR,    0, ELEMENT_FORMAT_FLOAT4, 0, 12, LAYOUT_TYPE_VERTEX, 0 }
	};

	InputLayoutInfo inputLayoutInfo { elements, 2 };
	InputLayoutHandle inputLayout = CreateInputLayout(inputLayoutInfo);

	// BIND DATA ///////////////////////////////////////////////////////////////

	BindInputLayout(inputLayout);
	BindShader(shader);
	BindBuffer(vertBuffer);
	BindBuffer(idxBuffer);

	// DRAW

	SetPrimitiveType(PRIMITIVE_TRIANGLE);

	//UnbindShader();
	//DisposeShader(&shader);
	//DisposeContext(&context);
}

WYVERN_DLL_API void Loop(const Application* app)
{
	ClearBackbuffer(colors);
	DrawIndexed(0, 3);
	Present();
}