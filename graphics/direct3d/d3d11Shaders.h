#pragma once
#include "graphics\shaders.h"

RESULT D3D11CreateShader(Shader** ppShader, const Context* pContext, const ShaderInfo info);

RESULT D3D11DisposeShader(Shader** ppShader);

RESULT D3D11BindShader(Shader* pShader, const Context* pContext);

RESULT D3D11UnbindShader(const Context* pContext);