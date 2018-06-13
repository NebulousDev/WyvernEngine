#include "win32OpenGL.h"
#include <GLEW\GL\glew.h>
#include <GLEW\GL\wglew.h>

/*=================================================================
|	GLOBAL VARS                                                   |
=================================================================*/

static bool	sGLEWInitialized = false;

/*=================================================================
|	OPENGL FUNCS                                                  |
=================================================================*/

RESULT InitOpenGL()
{
	if (sGLEWInitialized) return WYVERN_SUCCESS;

	if (glewInit() == GLEW_OK)
	{
		sGLEWInitialized = true;
		return WYVERN_SUCCESS;
	}

	return WYVERN_ERROR;
}

RESULT GLCreateContext(GLContext* glContext, HDC device)
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

	*glContext = wglCreateContext(device);

	if (!glContext)
	{
		MessageBoxA(0, "Critical Error! Failed to create glContext!", "GL CONTEXT CREATION FAILED", 0);
		return WYVERN_ERROR;
	}
}

RESULT GLMakeContextCurrent(HDC device, GLContext context)
{
	return wglMakeCurrent(device, context) ? WYVERN_SUCCESS : WYVERN_ERROR;
}

RESULT GLDeleteContext(GLContext context)
{
	return wglDeleteContext(context) ? WYVERN_SUCCESS : WYVERN_ERROR;
}