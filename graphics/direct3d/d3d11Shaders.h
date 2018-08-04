#pragma once

#include <graphics\context.h>
#include <graphics\shaders.h>
#include <graphics\gfxapi.h>

WYVERN_GFX_API RESULT D3D11CreateShader(Shader** ppShader, const Context* pContext, const ShaderInfo info);

WYVERN_GFX_API RESULT D3D11DisposeShader(Shader** ppShader);

WYVERN_GFX_API RESULT D3D11BindShader(Shader* pShader, const Context* pContext);

WYVERN_GFX_API RESULT D3D11UnbindShader(const Context* pContext);