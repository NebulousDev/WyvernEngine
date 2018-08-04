#include "d3d11Layout.h"
#include "d3d11.h"

#define MAX_INPUT_LAYOUT_ELEMENTS 32

static ID3D11InputLayout* sD3D11InputLayouts[MAX_INPUT_LAYOUTS] = {};

// Move to D3D11 utilities?
const DXGI_FORMAT D3D11GetDXGIFormat(InputElementFormat format)
{
	switch (format)
	{
		case ELEMENT_FORMAT_INT:	return DXGI_FORMAT_R32_SINT;
		case ELEMENT_FORMAT_INT2:	return DXGI_FORMAT_R32G32_SINT;
		case ELEMENT_FORMAT_INT3:	return DXGI_FORMAT_R32G32B32_SINT;
		case ELEMENT_FORMAT_INT4:	return DXGI_FORMAT_R32G32B32A32_SINT;
		case ELEMENT_FORMAT_UINT:	return DXGI_FORMAT_R32_UINT;
		case ELEMENT_FORMAT_UINT2:	return DXGI_FORMAT_R32G32_UINT;
		case ELEMENT_FORMAT_UINT3:	return DXGI_FORMAT_R32G32B32_UINT;
		case ELEMENT_FORMAT_UINT4:	return DXGI_FORMAT_R32G32B32A32_UINT;
		case ELEMENT_FORMAT_FLOAT:	return DXGI_FORMAT_R32_FLOAT;
		case ELEMENT_FORMAT_FLOAT2:	return DXGI_FORMAT_R32G32_FLOAT;
		case ELEMENT_FORMAT_FLOAT3:	return DXGI_FORMAT_R32G32B32_FLOAT;
		case ELEMENT_FORMAT_FLOAT4:	return DXGI_FORMAT_R32G32B32A32_FLOAT;
		default:					return DXGI_FORMAT_UNKNOWN;
	}
}

const D3D11_INPUT_CLASSIFICATION D3D11GetInputClassification(InputLayoutType type)
{
	switch (type)
	{
		case LAYOUT_TYPE_VERTEX:	return D3D11_INPUT_PER_VERTEX_DATA;
		case LATOUT_TYPE_INSTACNE:	return D3D11_INPUT_PER_INSTANCE_DATA;
		default:					return D3D11_INPUT_PER_VERTEX_DATA;
	}
}

#include <vector>	//TODO: replace
#include <iostream>

#define DUMMY_MAX_BYTES 4096

RESULT D3D11CreateDummyShaderSignature(ID3DBlob** ppDummyShaderBlob, InputElement* pElements, const uint32 count, const Context* pContext)
{
	char* pShaderCodeBuffer = new char[DUMMY_MAX_BYTES]{};

	strcpy_s(pShaderCodeBuffer, DUMMY_MAX_BYTES, "struct VSInput\n{\n");

	for (uint32 i = 0; i < count; i++)
	{
		InputElement element = pElements[i];

		switch (element.format)
		{
			case ELEMENT_FORMAT_INT:	strcat_s(pShaderCodeBuffer, DUMMY_MAX_BYTES, "\tint ");		break;
			case ELEMENT_FORMAT_INT2:	strcat_s(pShaderCodeBuffer, DUMMY_MAX_BYTES, "\tint2 ");	break;
			case ELEMENT_FORMAT_INT3:	strcat_s(pShaderCodeBuffer, DUMMY_MAX_BYTES, "\tint3 ");	break;
			case ELEMENT_FORMAT_INT4:	strcat_s(pShaderCodeBuffer, DUMMY_MAX_BYTES, "\tint4 ");	break;
			case ELEMENT_FORMAT_UINT:	strcat_s(pShaderCodeBuffer, DUMMY_MAX_BYTES, "\tuint ");	break;
			case ELEMENT_FORMAT_UINT2:	strcat_s(pShaderCodeBuffer, DUMMY_MAX_BYTES, "\tuint2 ");	break;
			case ELEMENT_FORMAT_UINT3:	strcat_s(pShaderCodeBuffer, DUMMY_MAX_BYTES, "\tuint3 ");	break;
			case ELEMENT_FORMAT_UINT4:	strcat_s(pShaderCodeBuffer, DUMMY_MAX_BYTES, "\tuint4 ");	break;
			case ELEMENT_FORMAT_FLOAT:	strcat_s(pShaderCodeBuffer, DUMMY_MAX_BYTES, "\tfloat ");	break;
			case ELEMENT_FORMAT_FLOAT2:	strcat_s(pShaderCodeBuffer, DUMMY_MAX_BYTES, "\tfloat2 ");	break;
			case ELEMENT_FORMAT_FLOAT3:	strcat_s(pShaderCodeBuffer, DUMMY_MAX_BYTES, "\tfloat3 ");	break;
			case ELEMENT_FORMAT_FLOAT4:	strcat_s(pShaderCodeBuffer, DUMMY_MAX_BYTES, "\tfloat4 ");	break;

			default:
			{
				//TODO: throw error
				return FAILURE;
			}
		}

		if (strlen(element.name) > 200)
		{
			//TODO: throw error
			return FAILURE;
		}

		strcat_s(pShaderCodeBuffer, DUMMY_MAX_BYTES, element.name);
		strcat_s(pShaderCodeBuffer, DUMMY_MAX_BYTES, " : ");
		
		switch (element.usage)
		{
			case ELEMENT_USAGE_POSITION :	strcat_s(pShaderCodeBuffer, DUMMY_MAX_BYTES, "POSITION;\n");	break;
			case ELEMENT_USAGE_NORMAL:		strcat_s(pShaderCodeBuffer, DUMMY_MAX_BYTES, "NORMAL;\n");		break;
			case ELEMENT_USAGE_BINORMAL:	strcat_s(pShaderCodeBuffer, DUMMY_MAX_BYTES, "BINORMAL;\n");	break;
			case ELEMENT_USAGE_TANGENT:		strcat_s(pShaderCodeBuffer, DUMMY_MAX_BYTES, "TANGERT;\n");		break;
			case ELEMENT_USAGE_TEXCOORD:	strcat_s(pShaderCodeBuffer, DUMMY_MAX_BYTES, "TEXCOORD;\n");	break;
			case ELEMENT_USAGE_COLOR:		strcat_s(pShaderCodeBuffer, DUMMY_MAX_BYTES, "COLOR;\n");		break;

			default:
			{
				//TODO: throw error
				return FAILURE;
			}
		}
	}

	strcat_s(pShaderCodeBuffer, DUMMY_MAX_BYTES, "};\n\n");
	strcat_s(pShaderCodeBuffer, DUMMY_MAX_BYTES, "void DummyMain(VSInput input) {};");

	ID3DInclude* pInclude = D3D_COMPILE_STANDARD_FILE_INCLUDE;
	D3D_SHADER_MACRO macros[1];
	macros[0].Name = "TEST";
	macros[0].Definition = "1";

	ID3DBlob* pShaderCodeBlob = NULLPTR;
	ID3DBlob* pShaderErrorBlob = NULLPTR;

	HRESULT result = D3DCompile(pShaderCodeBuffer, strlen(pShaderCodeBuffer), "dummyShader", 0, 0,
		"DummyMain", "vs_4_1", 0, 0, &pShaderCodeBlob, &pShaderErrorBlob);

	if (pShaderErrorBlob)
	{
		std::cout << pShaderCodeBuffer;
		std::cout << (const char*)pShaderErrorBlob->GetBufferPointer() << std::endl;
		pShaderErrorBlob->Release();
	}

	*ppDummyShaderBlob = pShaderCodeBlob;

	return SUCCESS;
}

RESULT D3D11CreateInputLayout(InputLayout** ppLayout, const Context* pContext, InputLayoutInfo info)
{
	InputLayout* pLayout = *ppLayout;

	D3D11_INPUT_ELEMENT_DESC layoutElements[MAX_INPUT_LAYOUT_ELEMENTS]{};

	for (uint32 i = 0; i < pLayout->elementCount; i++)
	{
		InputElement element = pLayout->pElements[i];

		switch (element.usage)
		{
			case ELEMENT_USAGE_POSITION:	layoutElements[i].SemanticName = "POSITION";	break;
			case ELEMENT_USAGE_NORMAL:		layoutElements[i].SemanticName = "NORMAL";		break;
			case ELEMENT_USAGE_BINORMAL:	layoutElements[i].SemanticName = "BINORMAL";	break;
			case ELEMENT_USAGE_TANGENT:		layoutElements[i].SemanticName = "TANGENT";		break;
			case ELEMENT_USAGE_TEXCOORD:	layoutElements[i].SemanticName = "TEXCOORD";	break;
			case ELEMENT_USAGE_COLOR:		layoutElements[i].SemanticName = "COLOR";		break;

			default:
			{
				//TODO: throw error
				return FAILURE;
			}
		}

		layoutElements[i].SemanticIndex			= element.index;
		layoutElements[i].Format				= D3D11GetDXGIFormat(element.format);
		layoutElements[i].InputSlot				= element.slot;
		layoutElements[i].AlignedByteOffset		= element.stride;
		layoutElements[i].InputSlotClass		= D3D11GetInputClassification(element.type);
		layoutElements[i].InstanceDataStepRate	= element.instanceCount;
	}

	ID3DBlob* pShaderBytecode = NULLPTR;
	ID3D11Device* pDevice = (ID3D11Device*)pContext->hDevice;

	if (!D3D11CreateDummyShaderSignature(&pShaderBytecode, pLayout->pElements, pLayout->elementCount, pContext))
	{
		if (pShaderBytecode) pShaderBytecode->Release();

		// TODO: throw error
		return FAILURE;
	}

	HRESULT result = pDevice->CreateInputLayout(layoutElements, pLayout->elementCount, 
		pShaderBytecode->GetBufferPointer(), pShaderBytecode->GetBufferSize(), &sD3D11InputLayouts[pLayout->hID]);

	if (result != S_OK)
	{
		std::cout << result << std::endl;
		
		if (pShaderBytecode) pShaderBytecode->Release();

		// TODO: throw error
		return FAILURE;
	}

	if(pShaderBytecode) pShaderBytecode->Release();

	return SUCCESS;
}

RESULT D3D11ReleaseInputLayout(InputLayout** ppLayout, const Context* pContext)
{
	//TODO: implement
	return SUCCESS;
}

RESULT D3D11BindInputLayout(InputLayout* pLayout, const Context* pContext)
{
	ID3D11DeviceContext* pDeviceContext = (ID3D11DeviceContext*)pContext->hDeviceContext;

	if (pLayout->valid)
	{
		pDeviceContext->IASetInputLayout(sD3D11InputLayouts[pLayout->hID]);
		return SUCCESS;
	}

	return FAILURE;
}

RESULT D3D11UnbindInputLayout(InputLayout* pLayout, const Context* pContext)
{
	//TODO: implement
	return SUCCESS;
}