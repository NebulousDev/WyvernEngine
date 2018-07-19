#pragma once
#include <graphics\graphics.h>
#include <common.h>

RESULT D3D11CreateContext(Context** context, ContextInfo info, const Window* window);

RESULT D3D11DisposeContext(Context* context);

RESULT D3D11SetContextCurrent(Context* context);

RESULT D3D11CreateRenderTarget(RenderTarget* target, const RenderTargetInfo info, Context* context);

RESULT D3D11ClearRenderTarget(const RenderTarget* target, const Context* context, const float32 color[4]);

RESULT D3D11Present(const Context* context);

// Define the function to create a D3D11 context (wonky, subject to change)
#define RENDER_DEVICE_DIRECT3D_11 \
(WYVPTRHANDLE)(Context::CreateContextFunc)D3D11CreateContext