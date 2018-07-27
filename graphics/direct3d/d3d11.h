#pragma once

#define WYVERN_DIRECT3D11

#ifdef WYVERN_DIRECT3D11

#define WIN32_LEAN_AND_MEAN
#include <d3d11.h>
#include <D3Dcompiler.h>

#pragma comment(lib, "dxgi.lib") 
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")
#define DIRECT_3D_INCLUDED

#endif // !WYVERN_DIRECT3D11

