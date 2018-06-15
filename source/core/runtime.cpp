#include "common.h"
#include "graphics\graphics.h"
#include "graphics\primitives.h"
#include "GLEW\GL\glew.h"
#include "platform/platform.h"

static GraphicsDevice gfxDevice;	//TODO: MOVE ME
static GraphicsBuffer planeVBO;
static GraphicsBuffer planeIBO;

void InitTestPlane()
{
	gfxDevice.CreateGraphicsBuffer(&planeVBO);
	gfxDevice.PutGraphicsBuffer(VERTEX_BUFFER_DATA, &planeVBO, (uint8*)sPlaneVertsIP3C3, sizeof(sPlaneVertsIP3C3));

	gfxDevice.CreateGraphicsBuffer(&planeIBO);
	gfxDevice.PutGraphicsBuffer(INDEX_BUFFER_DATA, &planeIBO, (uint8*)sPlaneIdxsIP3C3, sizeof(sPlaneIdxsIP3C3));
}

void DrawTestPlane()
{
	gfxDevice.DrawIndexedBuffers(planeVBO, planeIBO);
}

EXPORT void UpdateAndRender()
{
	if (!gfxDevice.IsInitialized())
	{
		gfxDevice.InitGraphicsDevice<GFXAPI_OPENGL>();
		gfxDevice.SetClearColor(0.0f, 1.0f, 1.0f);

		InitTestPlane();
	}

	gfxDevice.ClearBuffers();

	DrawTestPlane();
}

