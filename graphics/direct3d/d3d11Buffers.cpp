#include "d3d11Buffers.h"
#include "d3d11.h"

RESULT D3D11CreateBuffer(Buffer** ppBuffer, const Context* pContext, const BufferInfo info)
{
	ID3D11Buffer* pD3D11Buffer = NULLPTR;

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.ByteWidth = info.byteSize;

	switch (info.bufferUsage)
	{
		case BUFFER_USAGE_IMMUTABLE:	bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;	break;
		case BUFFER_USAGE_MUTABLE:		bufferDesc.Usage = D3D11_USAGE_DEFAULT;		break;
		case BUFFER_USAGE_DYNAMIC:		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;		break;

		default:
		{
			//TODO: unsupported usage error
			return FAILURE;
		}
	}
	
	switch (info.bufferType)
	{
		case BUFFER_TYPE_VERTEX:	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	break;

		default:
		{
			//TODO: unsupported type error
			return FAILURE;
		}
	}

	D3D11_SUBRESOURCE_DATA subResourceData = {};

	bool8	genData = false;
	uint8*	data	= NULLPTR;

	if (info.pData == NULLPTR)
	{
		data = new uint8[info.byteSize]{};
		subResourceData.pSysMem = data;
		genData = true;
	}

	else
	{
		subResourceData.pSysMem = info.pData;
	}

	ID3D11Device* pDevice = (ID3D11Device*)pContext->hDevice;

	if (pDevice->CreateBuffer(&bufferDesc, &subResourceData, &pD3D11Buffer) != S_OK)
	{
		//TODO: throw error?
		return FAILURE;
	}

	Buffer* pBuffer			= new Buffer;
	pBuffer->bufferName		= info.bufferName;
	pBuffer->hBuffer		= (WYVPTRHANDLE)pD3D11Buffer;
	pBuffer->byteSize		= info.byteSize;
	pBuffer->bufferUsage	= info.bufferUsage;
	pBuffer->bufferType		= info.bufferType;
	pBuffer->stride			= info.stride;
	pBuffer->offset			= info.offset;

	*ppBuffer = pBuffer;

	if(genData) delete[] data;

	return SUCCESS;
}

RESULT D3D11ReleaseBuffer(Buffer** ppBuffer, const Context* pContext)
{
	Buffer* pBuffer = *ppBuffer;
	((ID3D11Buffer*)pBuffer->hBuffer)->Release();
	delete pBuffer;
	*ppBuffer = NULLPTR;
	return SUCCESS;
}

RESULT D3D11BindBuffer(Buffer* pBuffer, const Context* pContext)
{
	ID3D11DeviceContext* pDeviceContext		= (ID3D11DeviceContext*)pContext->hDeviceContext;
	ID3D11Buffer* pD3D11Buffer				= (ID3D11Buffer*)pBuffer->hBuffer;

	switch (pBuffer->bufferType)
	{
		case BUFFER_TYPE_VERTEX:
		{
			pDeviceContext->IASetVertexBuffers(0, 1, &pD3D11Buffer, &pBuffer->stride, &pBuffer->offset);
			break;
		}

		default:
		{
			//TODO: unsupported type error
			return FAILURE;
		}
	}

	return SUCCESS;
}

RESULT D3D11UnbindBuffer(Buffer* pBuffer, const Context* pContext)
{
	//TODO: unbind d3d11 buffers
	return SUCCESS;
}