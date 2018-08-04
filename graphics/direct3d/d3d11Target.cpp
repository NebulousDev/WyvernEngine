#include "d3d11Target.h"
#include "d3d11.h"
#include <graphics\context.h>

RESULT D3D11CreateRenderTarget(RenderTarget** ppTarget, const Context* pContext, const RenderTargetInfo info)
{
	RenderTarget* pTarget = new RenderTarget();

	ID3D11RenderTargetView* pRenderTarget = NULLPTR;
	ID3D11Texture2D* pBackBuffer = NULLPTR;

	IDXGISwapChain* pSwapChain = (IDXGISwapChain*)pContext->hSwapChain;
	ID3D11Device*	pDevice = (ID3D11Device*)pContext->hDevice;

	HRESULT result = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);

	// TODO: replace these with asserts
	if (result != S_OK)
	{
		//TODO: throw error?
		return FAILURE;
	}

	result = pDevice->CreateRenderTargetView(pBackBuffer, 0, &pRenderTarget);

	if (result != S_OK)
	{
		//TODO: throw error?
		return FAILURE;
	}

	pBackBuffer->Release();

	pTarget->hTarget	= (WYVPTRHANDLE)pRenderTarget;
	pTarget->width		= info.width;
	pTarget->height		= info.height;

	*ppTarget = pTarget;

	return SUCCESS;
}

RESULT D3D11ClearRenderTarget(const RenderTarget* target, const Context* context, const float32 color[4])
{
	((ID3D11DeviceContext*)context->hDeviceContext)->ClearRenderTargetView((ID3D11RenderTargetView*)target->hTarget, color);
	return SUCCESS;
}