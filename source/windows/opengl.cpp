#include "context.h"

RESULT GLCreateContext(GraphicsContext* context, GraphicsDevice device)
{
	PIXELFORMATDESCRIPTOR pixelFormatDesc = {};
	pixelFormatDesc.nSize		= sizeof(PIXELFORMATDESCRIPTOR);
	pixelFormatDesc.nVersion	= 1;
	pixelFormatDesc.dwFlags		= PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pixelFormatDesc.iPixelType	= PFD_TYPE_RGBA;
	pixelFormatDesc.cColorBits	= PIXEL_COLOR_BITS;
	pixelFormatDesc.cDepthBits	= PIXEL_DEPTH_BITS;
	pixelFormatDesc.iLayerType	= PFD_MAIN_PLANE;

	int32 winPixelFormat = ChoosePixelFormat(device, &pixelFormatDesc);
	BOOL res = SetPixelFormat(device, winPixelFormat, &pixelFormatDesc);

	*context = wglCreateContext(device);

	DWORD err = GetLastError();

	if (!*context)
	{
		MessageBoxA(0, "Critical Error! Failed to create glContext!", "GL CONTEXT CREATION FAILED", 0);
		return WYVERN_ERROR;
	}

	return WYVERN_SUCCESS;
}

RESULT GLMakeContextCurrent(GraphicsDevice device, GraphicsContext context)
{
	return wglMakeCurrent(device, context) ? WYVERN_SUCCESS : WYVERN_ERROR;
}

RESULT GLDeleteContext(GraphicsContext* context)
{
	BOOL res = wglDeleteContext(*context);
	*context = NULL;
	return res ? WYVERN_SUCCESS : WYVERN_ERROR;
}