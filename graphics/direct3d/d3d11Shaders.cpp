#include "d3d11Shaders.h"
#include "d3d11.h"

#include <iostream>

RESULT D3D11CreateShader(Shader** ppShader, const Context* pContext, const ShaderInfo info)
{
	*ppShader = new Shader();
	Shader* pShader = *ppShader;
	ID3DBlob* pShaderBlob;

	uint32 error = S_OK;

	if (info.hlslSources.vertexShaderSource)
	{
		ID3D11VertexShader* pVertexShader;

		if ((error = D3DReadFileToBlob((LPCWSTR)info.hlslSources.vertexShaderSource, &pShaderBlob)) != S_OK)
		{
			std::wcout << L"D3D11 Shader Error: Failed to load shader '" << info.hlslSources.vertexShaderSource << L"'." << std::endl;
			std::wcout << L"DXError Code: " << error << std::endl;
			return FAILURE;
		}

		((ID3D11Device*)pContext->hDevice)->
			CreateVertexShader(pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize(), NULLPTR, &pVertexShader);

		pShader->hlslBuffers.hVertexBuffer = (WYVPTRHANDLE)pVertexShader;

		pShaderBlob->Release();
	}

	if (info.hlslSources.pixelShaderSource)
	{
		ID3D11PixelShader* pPixelShader;

		if ((error = D3DReadFileToBlob((LPCWSTR)info.hlslSources.pixelShaderSource, &pShaderBlob)) != S_OK)
		{
			std::wcout << L"D3D11 Shader Error: Failed to load shader '" << info.hlslSources.pixelShaderSource << L"'." << std::endl;
			std::wcout << L"DXError Code: " << error << std::endl;
			return FAILURE;
		}

		((ID3D11Device*)pContext->hDevice)->
			CreatePixelShader(pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize(), NULLPTR, &pPixelShader);

		pShader->hlslBuffers.hPixelBuffer = (WYVPTRHANDLE)pPixelShader;

		pShaderBlob->Release();
	}

	return SUCCESS;
}

RESULT D3D11DisposeShader(Shader** ppShader)
{
	Shader* pShader = *ppShader;

	if (pShader->hlslBuffers.hVertexBuffer)
		((ID3D11VertexShader*)pShader->hlslBuffers.hVertexBuffer)->Release();

	if (pShader->hlslBuffers.hPixelBuffer)
		((ID3D11PixelShader*)pShader->hlslBuffers.hPixelBuffer)->Release();

	delete pShader;
	ppShader = NULLPTR;
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