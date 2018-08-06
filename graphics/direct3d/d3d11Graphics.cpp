#include "d3d11Graphics.h"
#include "d3d11.h"

const D3D_PRIMITIVE_TOPOLOGY D3D11GetTopologyFromPrimitiveType(const PrimitiveType type)
{
	switch (type)
	{
	case PRIMITIVE_TRIANGLE:			return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	case PRIMITIVE_TRIANGLE_STRIP:		return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
	case PRIMITIVE_LINE:				return D3D10_PRIMITIVE_TOPOLOGY_LINELIST;
	case PRIMITIVE_LINE_STRIP:			return D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
	case PRIMITIVE_POINT:				return D3D10_PRIMITIVE_TOPOLOGY_POINTLIST;
	default:							return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	}
}

RESULT D3D11SetPrimitiveType(const PrimitiveType type, const Context* pContext)
{
	ID3D11DeviceContext* pDeviceContext = (ID3D11DeviceContext*)pContext->hDeviceContext;
	pDeviceContext->IASetPrimitiveTopology(D3D11GetTopologyFromPrimitiveType(type));
	return SUCCESS;
}

RESULT D3D11DrawIndexed(const Context* pContext, const uint32 idxStart, const uint32 idxCount)
{
	ID3D11DeviceContext* pDeviceContext = (ID3D11DeviceContext*)pContext->hDeviceContext;
	pDeviceContext->DrawIndexed(idxCount, idxStart, 0); // TODO: allow vertex specification
	return SUCCESS;
}

#include <iostream>

RESULT D3D11Present(const Context* pContext)
{
	///////////////////////////////////////////////////////////////////////////////////////

	ID3D11RenderTargetView* pRenderTarget = (ID3D11RenderTargetView*)pContext->backBuffer->hTarget;
	ID3D11DeviceContext* pDeviceContext = (ID3D11DeviceContext*)pContext->hDeviceContext;
	pDeviceContext->OMSetRenderTargets(1, &pRenderTarget, NULL);

	D3D11_VIEWPORT viewport{};

	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.Width = 1280.0f;
	viewport.Height = 720.0f;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	pDeviceContext->RSSetViewports(1, &viewport);

	///////////////////////////////////////////////////////////////////////////////////////

	HRESULT result = ((IDXGISwapChain*)pContext->hSwapChain)->Present(pContext->vSync, 0);

	if (result)
	{
		std::cout << result << std::endl;
		return FAILURE;
	}

	return SUCCESS;
}

