#pragma once

#include "../common.h"
#include "colorFormat.h"
#include "shaders.h"

#define MAX_INPUT_LAYOUTS 128

enum WYVERN_CORE_API InputLayoutType
{
	LAYOUT_TYPE_VERTEX,
	LATOUT_TYPE_INSTACNE
};

enum WYVERN_CORE_API InputElementFormat
{
	ELEMENT_FORMAT_INT,
	ELEMENT_FORMAT_INT2,
	ELEMENT_FORMAT_INT3,
	ELEMENT_FORMAT_INT4,
	ELEMENT_FORMAT_UINT,
	ELEMENT_FORMAT_UINT2,
	ELEMENT_FORMAT_UINT3,
	ELEMENT_FORMAT_UINT4,
	ELEMENT_FORMAT_FLOAT,
	ELEMENT_FORMAT_FLOAT2,
	ELEMENT_FORMAT_FLOAT3,
	ELEMENT_FORMAT_FLOAT4,
	ELEMENT_FORMAT_MATRIX3,
	ELEMENT_FORMAT_MATRIX4
};

enum WYVERN_CORE_API InputElementUsage
{
	ELEMENT_USAGE_POSITION,
	ELEMENT_USAGE_NORMAL,
	ELEMENT_USAGE_BINORMAL,
	ELEMENT_USAGE_TANGENT,
	ELEMENT_USAGE_TEXCOORD,
	ELEMENT_USAGE_COLOR,
};

struct WYVERN_CORE_API InputElement
{
	const STRING		name;
	InputElementUsage	usage;
	uint32				index;
	InputElementFormat	format;
	uint32				slot;
	uint32				stride;
	InputLayoutType		type;
	uint32				instanceCount;
};

struct WYVERN_CORE_API InputLayout
{
	WYVHANDLE		hID;
	WYVHANDLE		hNext;
	InputElement*	pElements;
	uint32			elementCount;
	Shader*			pShaderSignature;
	bool8			valid;
};

struct WYVERN_CORE_API InputLayoutInfo
{
	InputElement*	pElements;
	uint32			elementCount;
};

typedef WYVHANDLE		InputLayoutHandle;
#define HINPUTLAYOUT	InputLayoutHandle

WYVERN_CORE_API
bool8					ValidateLayoutHandle(InputLayoutHandle hHandle);
WYVERN_CORE_API
const InputLayoutHandle CreateInputLayout(const InputLayoutInfo info);
WYVERN_CORE_API
RESULT					ReleaseInputLayout(InputLayoutHandle* phInputLayout);
WYVERN_CORE_API
RESULT					BindInputLayout(InputLayoutHandle hInputLayout);
WYVERN_CORE_API
RESULT					UnbindInputLayout(InputLayoutHandle hInputLayout);