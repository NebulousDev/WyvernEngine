#include "common.h"
#include "graphics\graphics.h"

static GraphicsDevice gfxDevice;	//TODO: MOVE ME

EXPORT void UpdateAndRender()
{
	if(!gfxDevice.IsInitialized())
		gfxDevice.InitGraphicsDevice<GFXAPI_OPENGL>();

	gfxDevice.SetClearColor(0.0f, 1.0f, 1.0f);
	gfxDevice.ClearBuffers();
}

