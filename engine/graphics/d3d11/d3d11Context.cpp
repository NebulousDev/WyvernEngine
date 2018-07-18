#include "d3d11Context.h"
#include <d3d11.h>

RESULT D3D11CreateContext(Context* context, ContextCreationInfo info, const Window* window)
{
	DXGI_SWAP_CHAIN_DESC swapChainDesc	= {};
	swapChainDesc.BufferCount			= info.bufferCount;
	swapChainDesc.BufferDesc.Format		= DXGI_FORMAT_R8G8B8A8_UNORM;				// TODO: auto-assign (hdr?)
	swapChainDesc.BufferUsage			= DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow			= (HWND)window->instance;
	swapChainDesc.SampleDesc.Count		= info.multisamples;						// MSAA
	swapChainDesc.SampleDesc.Quality	= 0;										// TODO: auto-assign CheckMultisampleQualityLevels
	swapChainDesc.Windowed				= true;										// Windowed/Fullscreen
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

	context->renderDevice	= info.renderDevice;
	context->swapChain		= (WYVPTRHANDLE)swapChain;
	context->device			= (WYVPTRHANDLE)device;
	context->context		= (WYVPTRHANDLE)deviceContext;

	return SUCCESS;
}

RESULT D3D11DisposeContext(Context* context)
{

}

RESULT D3D11CreateRenderTarget(RenderTarget * target, RenderTargetInfo info)
{
	return RESULT();
}
