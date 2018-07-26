#pragma once
#include "graphics\shaders.h"

RESULT D3D11CreateShader(Shader** shader, const Context* context, const ShaderInfo info);

RESULT D3D11DisposeShader(Shader* shader);