#pragma once

#include <graphics\context.h>
#include <graphics\buffers.h>
#include <graphics\gfxapi.h>

WYVERN_GFX_API RESULT D3D11CreateBuffer(Buffer** ppBuffer, const Context* pContext, const BufferInfo info);

WYVERN_GFX_API RESULT D3D11ReleaseBuffer(Buffer** ppBuffer, const Context* pContext);

WYVERN_GFX_API RESULT D3D11BindBuffer(Buffer* pBuffer, const Context* pContext);

WYVERN_GFX_API RESULT D3D11UnbindBuffer(Buffer* pBuffer, const Context* pContext);