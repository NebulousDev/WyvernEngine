#pragma once
#include <graphics\context.h>
#include <common.h>

struct RenderTargetInfo
{

};

struct RenderTarget
{

};

RESULT D3D11CreateContext(Context* context, ContextCreationInfo info, const Window* window);

RESULT D3D11DisposeContext(Context* context);

RESULT D3D11CreateRenderTarget(RenderTarget* target, RenderTargetInfo info);