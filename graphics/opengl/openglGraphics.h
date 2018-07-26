#pragma once
#include <graphics\graphics.h>

#define WYVERN_D3D11_API __declspec(dllexport)

WYVERN_D3D11_API RESULT GLCreateContext(Context** context, ContextInfo info, const Window* window);

WYVERN_D3D11_API RESULT GLDisposeContext(Context* context);

WYVERN_D3D11_API RESULT GLSetContextCurrent(Context* context);

WYVERN_D3D11_API RESULT GLCreateRenderTarget(RenderTarget* target, const RenderTargetInfo info, Context* context);

WYVERN_D3D11_API RESULT GLClearRenderTarget(const RenderTarget* target, const Context* context, const float32 color[4]);

WYVERN_D3D11_API RESULT GLPresent(const Context* context);

// Define the function to create a D3D11 context (wonky, subject to change)
#define RENDER_DEVICE_OPENGL \
(WYVPTRHANDLE)(Context::CreateContextFunc)GLCreateContext