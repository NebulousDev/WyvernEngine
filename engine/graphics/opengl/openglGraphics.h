#pragma once
#include <graphics\graphics.h>

RESULT GLCreateContext(Context** context, ContextInfo info, const Window* window);

RESULT GLDisposeContext(Context* context);

RESULT GLSetContextCurrent(Context* context);

RESULT GLCreateRenderTarget(RenderTarget* target, const RenderTargetInfo info, Context* context);

RESULT GLClearRenderTarget(const RenderTarget* target, const Context* context, const float32 color[4]);

RESULT GLPresent(const Context* context);

// Define the function to create a D3D11 context (wonky, subject to change)
#define RENDER_DEVICE_OPENGL \
(WYVPTRHANDLE)(Context::CreateContextFunc)GLCreateContext