#pragma once

#include <graphics\context.h>
#include <graphics\gfxapi.h>

WYVERN_GFX_API RESULT D3D11CreateContext(Context** context, const Window* window, const ContextInfo info);

WYVERN_GFX_API RESULT D3D11DisposeContext(Context* context);

WYVERN_GFX_API RESULT D3D11SetContextCurrent(Context* context);