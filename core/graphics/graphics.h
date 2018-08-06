#pragma once

#include "../common.h"
#include "context.h"
#include "layout.h"
#include "buffers.h"
#include "shaders.h"
#include "target.h"

enum PrimitiveType
{
	PRIMITIVE_TRIANGLE,
	PRIMITIVE_TRIANGLE_STRIP,
	PRIMITIVE_LINE,
	PRIMITIVE_LINE_STRIP,
	PRIMITIVE_POINT
};

enum CullSide
{
	CULL_SIDE_FRONT,
	CULL_SIDE_BACK
};

/* SHADER */

WYVERN_CORE_API
RESULT				SetShader(const ShaderHandle hShader);

/* STATE */

WYVERN_CORE_API
RESULT				SetInputLayout(const InputLayoutHandle hLayout);

WYVERN_CORE_API
RESULT				SetCullingEnabled(const bool8 culling);

WYVERN_CORE_API
RESULT				SetCullSide(const CullSide side);

WYVERN_CORE_API
RESULT				SetPrimitiveType(const PrimitiveType type);

/* BUFFER */

WYVERN_CORE_API
RESULT				EnableBuffer(const BufferHandle hBuffer);

WYVERN_CORE_API
RESULT				DisableBuffer(const BufferHandle hBuffer);

/* DRAW */

WYVERN_CORE_API
RESULT				DrawIndexed(const uint32 idxStart, const uint32 idxCount);

/* VIEWPORT */

WYVERN_CORE_API 
RESULT				Present();
