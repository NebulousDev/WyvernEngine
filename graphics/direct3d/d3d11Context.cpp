#include "d3d11Graphics.h"
#include "d3d11.h"

///////////////////////////////////////////////////////////

/* Required to prevent errors from including window.h */

struct WYVERN_CORE_API Window
{
	uint32			id;
	uint32			next;
	WYVPTRHANDLE	hInstance;
	STRING			title;
	uint32			width;
	uint32			height;
	uint32			posX;
	uint32			posY;
	BITS32			flags;
	bool8			valid;
};

//////////////////////////////////////////////////////////

void D3D11SetupFunctions(Context* context)
{
	context->fpCreateContext			= D3D11CreateContext;
	context->fpSetContextCurrent		= D3D11SetContextCurrent;
	context->fpReleaseContext			= D3D11DisposeContext;

	context->fpCreateInputLayout		= D3D11CreateInputLayout;
	context->fpReleaseInputLayout		= D3D11ReleaseInputLayout;
	context->fpBindInputLayout			= D3D11BindInputLayout;
	context->fpUnbindInputLayout		= D3D11UnbindInputLayout;

	context->fpCreateBuffer				= D3D11CreateBuffer;
	context->fpReleaseBuffer			= D3D11ReleaseBuffer;
	context->fpBindBuffer				= D3D11BindBuffer;
	context->fpUnbindBuffer				= D3D11UnbindBuffer;

	context->fpCreateShader				= D3D11CreateShader;
	context->fpReleaseShader			= D3D11DisposeShader;
	context->fpBindShader				= D3D11BindShader;
	context->fpUnbindShader				= D3D11UnbindShader;

	context->fpCreateRenderTarget		= D3D11CreateRenderTarget;
	context->fpClearRenderTarget		= D3D11ClearRenderTarget;

	context->fpSetPrimitiveType			= D3D11SetPrimitiveType;
	context->fpDrawIndexed				= D3D11DrawIndexed;

	context->fpPresent					= D3D11Present;
}

RESULT D3D11CreateContext(Context** ppContext, const Window* pWindow, const ContextInfo info)
{
	DXGI_SWAP_CHAIN_DESC swapChainDesc	= {};
	swapChainDesc.BufferCount			= info.bufferCount;
	swapChainDesc.BufferDesc.Format		= DXGI_FORMAT_R8G8B8A8_UNORM;				// TODO: auto-assign (hdr?)
	swapChainDesc.BufferUsage			= DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow			= (HWND)pWindow->hInstance;
	swapChainDesc.SampleDesc.Count		= info.multisamples;						// MSAA
	swapChainDesc.SampleDesc.Quality	= 0;										// TODO: auto-assign CheckMultisampleQualityLevels
	swapChainDesc.Windowed				= !(info.flags & CONTEXT_FULLSCREEN);		// Windowed/Fullscreen
	swapChainDesc.Flags					= DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	IDXGISwapChain*			pSwapChain			= NULLPTR;
	ID3D11Device*			pDevice				= NULLPTR;
	ID3D11DeviceContext*	pDeviceContext		= NULLPTR;

	HRESULT result = D3D11CreateDeviceAndSwapChain
	(
		0, D3D_DRIVER_TYPE_HARDWARE, 0, 0, 0, 0, 
		D3D11_SDK_VERSION, &swapChainDesc, &pSwapChain, &pDevice, 0, &pDeviceContext
	);

	if (result != S_OK)
	{
		//TODO: throw error?
		return FAILURE;
	}

	Context* pContext = *ppContext;
	pContext = new Context();

	pContext->hDeviceContext		= (WYVPTRHANDLE)pDeviceContext;
	pContext->hSwapChain			= (WYVPTRHANDLE)pSwapChain;
	pContext->hDevice				= (WYVPTRHANDLE)pDevice;
	pContext->hRenderDevice			= info.hRenderDevice;
	pContext->vSync					= info.flags & CONTEXT_VSYNC ? 1 : 0;

	RenderTargetInfo renderTargetInfo = {};
	renderTargetInfo.width	= pWindow->width;
	renderTargetInfo.height = pWindow->height;

	result = D3D11CreateRenderTarget(&pContext->backBuffer, pContext, renderTargetInfo);

	if (result != SUCCESS)
	{
		//TODO: throw error?
		return FAILURE;
	}

	D3D11SetupFunctions(pContext);

	*ppContext = pContext;

	return SUCCESS;
}

RESULT D3D11DisposeContext(Context* pContext)
{
	((IDXGISwapChain*)pContext->hSwapChain)->Release();
	((ID3D11Device*)pContext->hDevice)->Release();
	((ID3D11DeviceContext*)pContext->hDeviceContext)->Release();
	//((ID3D11RenderTargetView*)(()context->backBuffer).hTarget)->Release();		// D3D11DisposeRenderTarget
	// TODO: dispose render target!

	pContext->hSwapChain		= NULLPTR;
	pContext->hDevice		= NULLPTR;
	pContext->hDeviceContext	= NULLPTR;

	delete pContext;

	return SUCCESS;
}

RESULT D3D11SetContextCurrent(Context* context)
{
	//TODO: do something on context creation?
	return SUCCESS;
}