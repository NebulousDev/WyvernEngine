#pragma once

#include <graphics\context.h>
#include <graphics\target.h>
#include <graphics\gfxapi.h>

WYVERN_GFX_API RESULT D3D11CreateRenderTarget(RenderTarget** target, const Context* context, const RenderTargetInfo info);

// TODO: delete render target?

WYVERN_GFX_API RESULT D3D11ClearRenderTarget(const RenderTarget* target, const Context* context, const float32 color[4]);