#include "win32OpenGL.h"
#include <GL\glew.h>
#include <GL\wglew.h>

#include "win32Platform.h"

int32 Win32InitOpenGL()
{
	return (glewInit() == GLEW_OK ? WYVERN_SUCCESS : WYVERN_ERROR);
}

GLContext Win32CreateOpenGLContext(HDC device)
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

	HGLRC glContext = wglCreateContext(device);
	wglMakeCurrent(device, glContext);

	if (!glContext)
	{
		MessageBoxA(0, "Critical Error! Failed to create glContext!", "GL CONTEXT CREATION FAILED", 0);
		return WYVERN_ERROR;
	}

	return (GLContext)glContext;
}

int32 Win32DeleteOpenGLContext(GLContext context)
{
	return wglDeleteContext(context) ? WYVERN_SUCCESS : WYVERN_ERROR;
}