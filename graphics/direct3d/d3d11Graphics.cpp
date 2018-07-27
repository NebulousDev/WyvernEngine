#include <graphics\shaders.h>
#include "d3d11Graphics.h"
#include "d3d11Shaders.h"
#include "d3d11.h"

void D3D11SetupFunctions(Context* context)
{
	context->fpCreateContext		= D3D11CreateContext;
	context->fpSetContextCurrent	= D3D11SetContextCurrent;
	context->fpDisposeContext		= D3D11DisposeContext;

	context->fpCreateShader			= D3D11CreateShader;
	context->fpDisposeShader		= D3D11DisposeShader;
	context->fpBindShader			= D3D11BindShader;
	context->fpUnbindShader			= D3D11UnbindShader;

	context->fpCreateRenderTarget	= D3D11CreateRenderTarget;
	context->fpClearRenderTarget	= D3D11ClearRenderTarget;
	context->fpPresent				= D3D11Present;
}

RESULT D3D11CreateContext(Context** context, ContextInfo info, const Window* window)
{
	DXGI_SWAP_CHAIN_DESC swapChainDesc	= {};
	swapChainDesc.BufferCount			= info.bufferCount;
	swapChainDesc.BufferDesc.Format		= DXGI_FORMAT_R8G8B8A8_UNORM;				// TODO: auto-assign (hdr?)
	swapChainDesc.BufferUsage			= DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow			= (HWND)window->instance;
	swapChainDesc.SampleDesc.Count		= info.multisamples;						// MSAA
	swapChainDesc.SampleDesc.Quality	= 0;										// TODO: auto-assign CheckMultisampleQualityLevels
	swapChainDesc.Windowed				= !(info.flags & CONTEXT_FULLSCREEN);		// Windowed/Fullscreen
	swapChainDesc.Flags					= DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	IDXGISwapChain*			swapChain			= NULLPTR;
	ID3D11Device*			device				= NULLPTR;
	ID3D11DeviceContext*	deviceContext		= NULLPTR;

	HRESULT result = D3D11CreateDeviceAndSwapChain
	(
		0, D3D_DRIVER_TYPE_HARDWARE, 0, 0, 0, 0, 
		D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &device, 0, &deviceContext
	);

	if (result != S_OK)
	{
		//TODO: throw error?
		return FAILURE;
	}

	Context* contextImpl = *context;
	contextImpl = new Context;

	contextImpl->hDeviceContext		= (WYVPTRHANDLE)deviceContext;
	contextImpl->hSwapChain			= (WYVPTRHANDLE)swapChain;
	contextImpl->hDevice			= (WYVPTRHANDLE)device;
	contextImpl->hRenderDevice		= info.hRenderDevice;
	contextImpl->vSync				= info.flags & CONTEXT_VSYNC ? 1 : 0;

	RenderTargetInfo renderTargetInfo = {};	//TODO: I dont like this
	result = D3D11CreateRenderTarget(&contextImpl->backBuffer, renderTargetInfo, contextImpl);

	if (result != SUCCESS)
	{
		//TODO: throw error?
		return FAILURE;
	}

	D3D11SetupFunctions(contextImpl);

	*context = contextImpl;

	return SUCCESS;
}

RESULT D3D11DisposeContext(Context* context)
{
	((IDXGISwapChain*)context->hSwapChain)->Release();
	((ID3D11Device*)context->hDevice)->Release();
	((ID3D11DeviceContext*)context->hDeviceContext)->Release();
	((ID3D11RenderTargetView*)context->backBuffer.hTarget)->Release();		// D3D11DisposeRenderTarget

	context->hSwapChain	= NULLPTR;
	context->hDevice		= NULLPTR;
	context->hDeviceContext	= NULLPTR;

	delete context;

	return SUCCESS;
}

RESULT D3D11SetContextCurrent(Context* context)
{
	//TODO: do something on context creation?
	return SUCCESS;
}

RESULT D3D11CreateRenderTarget(RenderTarget* target, const RenderTargetInfo info, Context* context)
{
	ID3D11RenderTargetView* renderTarget	= NULLPTR;
	ID3D11Texture2D* backBuffer				= NULLPTR;

	IDXGISwapChain* swapChain	= (IDXGISwapChain*)context->hSwapChain;
	ID3D11Device*	device		= (ID3D11Device*)context->hDevice;

	HRESULT result = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);

	// TODO: replace these with asserts
	if (result != S_OK)
	{
		//TODO: throw error?
		return FAILURE;
	}

	result = device->CreateRenderTargetView(backBuffer, 0, &renderTarget);

	if (result != S_OK)
	{
		//TODO: throw error?
		return FAILURE;
	}

	backBuffer->Release();

	target->hTarget = (WYVPTRHANDLE)renderTarget;
	target->pContext = context;

	return SUCCESS;
}

RESULT D3D11ClearRenderTarget(const RenderTarget* target, const Context* context, const float32 color[4])
{
	((ID3D11DeviceContext*)context->hDeviceContext)->ClearRenderTargetView((ID3D11RenderTargetView*)target->hTarget, color);
	return SUCCESS;
}

RESULT D3D11Present(const Context* context)
{
	return ((IDXGISwapChain*)context->hSwapChain)->Present(context->vSync, 0) 
		== S_OK ? SUCCESS : FAILURE;
}

