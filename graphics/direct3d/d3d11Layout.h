#pragma once

#include <graphics\context.h>
#include <graphics\layout.h>
#include <graphics\gfxapi.h>

WYVERN_GFX_API RESULT D3D11CreateInputLayout(InputLayout** ppLayout, const Context* pContext, InputLayoutInfo info);

WYVERN_GFX_API RESULT D3D11ReleaseInputLayout(InputLayout** ppLayout, const Context* pContext);

WYVERN_GFX_API RESULT D3D11BindInputLayout(InputLayout* pLayout, const Context* pContext);

WYVERN_GFX_API RESULT D3D11UnbindInputLayout(InputLayout* pLayout, const Context* pContext);