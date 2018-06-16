#include "context.h"

RESULT GLCreateContext(GraphicsContext* context, GraphicsDevice device)
{
	PIXELFORMATDESCRIPTOR pixelFormatDesc = {};
	pixelFormatDesc.nSize		= sizeof(pixelFormatDesc);
	pixelFormatDesc.nVersion	= 1;
	pixelFormatDesc.dwFlags		= PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pixelFormatDesc.iPixelType	= PFD_TYPE_RGBA;
	pixelFormatDesc.cColorBits	= PIXEL_COLOR_BITS;
	pixelFormatDesc.cDepthBits	= PIXEL_DEPTH_BITS;
	pixelFormatDesc.iLayerType	= PFD_MAIN_PLANE;

	uint32 winPixelFormat;
	winPixelFormat = ChoosePixelFormat(device, &pixelFormatDesc);
	SetPixelFormat(device, winPixelFormat, &pixelFormatDesc);

	*context = wglCreateContext(device);

	if (!context)
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

RESULT GLDeleteContext(GraphicsContext context)
{
	return wglDeleteContext(context) ? WYVERN_SUCCESS : WYVERN_ERROR;
}