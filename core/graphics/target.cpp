#include "target.h"
#include "context.h"

const RenderTargetHandle CreateRenderTarget(const RenderTargetInfo info)
{
	RenderTarget* renderTarget = NULLPTR;
	GetCurrentContext()->fpCreateRenderTarget(&renderTarget, GetCurrentContext(), info);
	return (RenderTargetHandle)renderTarget;
}

RESULT ClearRenderTarget(const RenderTargetHandle hTarget, const float32 color[4])
{
	return GetCurrentContext()->fpClearRenderTarget((RenderTarget*)hTarget, GetCurrentContext(), color);
}

RESULT ClearBackbuffer(const float32 color[4])
{
	return ClearRenderTarget((RenderTargetHandle)GetCurrentContext()->backBuffer, color);
}