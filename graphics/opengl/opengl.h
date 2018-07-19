#pragma once
#include <glew\glew.h>

#ifndef OPENGL_INCLUDED

#pragma comment(lib, "opengl32.lib") 

#ifdef _M_X64
#pragma comment(lib, "glew32s_x64.lib") 
#else
#pragma comment(lib, "glew32s_x86.lib") 
#endif

#define OPENGL_INCLUDED

#endif // !OPENGL_INCLUDED
