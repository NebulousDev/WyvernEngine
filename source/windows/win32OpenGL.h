#pragma once

#include "core\common.h"

#define WIN32_LEAN_AND_MEAN	1
#define NOCOMM				1

#include <Windows.h>

//TODO: Make color depth display dependent
#define PIXEL_COLOR_BITS 32
#define PIXEL_DEPTH_BITS 32

typedef HGLRC GLContext;

int32		InitOpenGL();

GLContext	GLCreateContext(HDC device);

int32		GLMakeContextCurrent(HDC device, GLContext context);

int32		GLDeleteContext(GLContext context);