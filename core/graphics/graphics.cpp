#include "graphics.h"

/* SHADER */

RESULT SetShader(const ShaderHandle hShader)
{
	return SUCCESS;
}

/* STATE */

RESULT SetInputLayout(const InputLayoutHandle hLayout)
{
	return SUCCESS;
}
	   
RESULT SetCullingEnabled(const bool8 culling)
{
	return SUCCESS;
}
	   
RESULT SetCullSide(const CullSide side)
{
	return SUCCESS;
}
	   
RESULT SetPrimitiveType(const PrimitiveType type)
{
	return GetCurrentContext()->fpSetPrimitiveType(type, GetCurrentContext());
}

/* BUFFER */

RESULT EnableBuffer(const BufferHandle hBuffer)
{
	return SUCCESS;
}
	   
RESULT DisableBuffer(const BufferHandle hBuffer)
{
	return SUCCESS;
}

RESULT DrawIndexed(const uint32 idxStart, const uint32 idxCount)
{
	return GetCurrentContext()->fpDrawIndexed(GetCurrentContext(), idxStart, idxCount);
}

/* VIEWPORT */

RESULT Present()
{
	return GetCurrentContext()->fpPresent(GetCurrentContext());
}