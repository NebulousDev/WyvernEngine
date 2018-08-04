#include "buffers.h"
#include "context.h"

const BufferHandle CreateBuffer(const BufferInfo info)
{
	Buffer* pBuffer = NULLPTR;
	GetCurrentContext()->fpCreateBuffer(&pBuffer, GetCurrentContext(), info);
	return (BufferHandle)pBuffer;
}

RESULT ReleaseBuffer(BufferHandle* phBuffer)
{
	if (phBuffer != NULLPTR && *phBuffer != NULLPTR)
		return GetCurrentContext()->fpReleaseBuffer((Buffer**)phBuffer, GetCurrentContext());
	return FAILURE;
}

RESULT BindBuffer(BufferHandle hBuffer)
{
	if (hBuffer != NULLPTR)
		return GetCurrentContext()->fpBindBuffer((Buffer*)hBuffer, GetCurrentContext());
	return FAILURE;
}

RESULT UnbindBuffer(BufferHandle hBuffer)
{
	if (hBuffer != NULLPTR)
		return GetCurrentContext()->fpUnbindBuffer((Buffer*)hBuffer, GetCurrentContext());
	return FAILURE;
}