#include "common.h"
#include "graphics\graphics.h"
#include "graphics\primitives.h"
#include "GLEW\GL\glew.h"
#include "platform/platform.h"

static Graphics			graphics;	//TODO: MOVE ME
static GraphicsBuffer	planeVBO;
static GraphicsBuffer	planeIBO;

void InitTestPlane()
{
	graphics.CreateGraphicsBuffer(&planeVBO);
	graphics.PutGraphicsBuffer(VERTEX_BUFFER_DATA, &planeVBO, (uint8*)sPlaneVertsIP3C3, sizeof(sPlaneVertsIP3C3));

	graphics.CreateGraphicsBuffer(&planeIBO);
	graphics.PutGraphicsBuffer(INDEX_BUFFER_DATA, &planeIBO, (uint8*)sPlaneIdxsIP3C3, sizeof(sPlaneIdxsIP3C3));
}

void DrawTestPlane()
{
	graphics.DrawIndexedBuffers(planeVBO, planeIBO);
}

EXPORT RESULT Create()
{
	/*
	if (!graphics.IsInitialized())
	{
		graphics.CreateGraphics<GFXAPI_OPENGL>();
		graphics.SetClearColor(0.0f, 1.0f, 1.0f);

		InitTestPlane();
	}
	*/

	return WYVERN_SUCCESS;
}

EXPORT void Update()
{
	//graphics.ClearBuffers();
	//DrawTestPlane();
}


EXPORT void Destroy()
{
	//graphics.DestroyGraphics<GFXAPI_OPENGL>();
}
