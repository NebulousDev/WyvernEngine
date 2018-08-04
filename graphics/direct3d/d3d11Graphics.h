#pragma once

#include <graphics\graphics.h>
#include <graphics\gfxapi.h>

#include "d3d11Context.h"
#include "d3d11Layout.h"
#include "d3d11Buffers.h"
#include "d3d11Shaders.h"
#include "d3d11Target.h"

WYVERN_GFX_API RESULT D3D11Present(const Context* context);

// Define the function to create a D3D11 context (wonky, subject to change)
#define RENDER_DEVICE_DIRECT3D_11 \
(WYVPTRHANDLE)(Context::CreateContextFunc)D3D11CreateContext