#include "d3d11Shaders.h"
#include "d3d11.h"

#include <iostream>

RESULT D3D11CreateShader(Shader** ppShader, const Context* pContext, const ShaderInfo info)
{
	*ppShader = new Shader();
	Shader* pShader = *ppShader;
	ID3DBlob* pShaderBlob;

	if (info.hlslSources.pVertexShader)
	{
		ID3D11VertexShader* pVertexShader;

		if (D3DReadFileToBlob((LPCWSTR)info.hlslSources.pVertexShader, &pShaderBlob) != S_OK)
		{
			std::cout << "D3D11 Shader Error: Failed to locate shader '" << info.hlslSources.pVertexShader << "'." << std::endl;
			return FAILURE;
		}

		((ID3D11Device*)pContext->hDevice)->
			CreateVertexShader(pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize(), NULLPTR, &pVertexShader);

		pShader->hlslBuffers.hVertexBuffer = (WYVPTRHANDLE)pVertexShader;

		pShaderBlob->Release();
	}

	if (info.hlslSources.pPixelShader)
	{
		ID3D11PixelShader* pPixelShader;

		if (D3DReadFileToBlob((LPCWSTR)info.hlslSources.pPixelShader, &pShaderBlob) != S_OK)
		{
			std::cout << "D3D11 Shader Error: Failed to locate shader '" << info.hlslSources.pVertexShader << "'." << std::endl;
			return FAILURE;
		}

		((ID3D11Device*)pContext->hDevice)->
			CreatePixelShader(pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize(), NULLPTR, &pPixelShader);

		pShader->hlslBuffers.hPixelBuffer = (WYVPTRHANDLE)pPixelShader;

		pShaderBlob->Release();
	}

	return SUCCESS;
}

RESULT D3D11DisposeShader(Shader** pShader)
{
	delete *pShader;
	pShader = NULLPTR;
	return SUCCESS;
}

RESULT D3D11BindShader(Shader* pShader, const Context* pContext)
{
	if (!pShader)
	{
		//TODO: throw error
		return FAILURE;
	}

	ID3D11DeviceContext*	pDeviceContext = ((ID3D11DeviceContext*)pContext->hDeviceContext);
	HLSLShaderBuffers		buffers = pShader->hlslBuffers;

	if (pShader->hlslBuffers.hVertexBuffer)
		pDeviceContext->VSSetShader((ID3D11VertexShader*)buffers.hVertexBuffer, NULLPTR, 0);

	return SUCCESS;
}

RESULT D3D11UnbindShader(const Context* pContext)
{
	//TODO: Do nothing?
	return SUCCESS;
}