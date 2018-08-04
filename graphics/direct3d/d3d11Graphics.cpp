#include "d3d11Graphics.h"
#include "d3d11.h"

RESULT D3D11Present(const Context* context)
{
	return ((IDXGISwapChain*)context->hSwapChain)->Present(context->vSync, 0) 
		== S_OK ? SUCCESS : FAILURE;
}

