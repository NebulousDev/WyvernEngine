#pragma once
#include <glew\glew.h>

#define WYVERN_OPENGL

#ifdef WYVERN_OPENGL

#pragma comment(lib, "opengl32.lib") 

#ifdef _M_X64
#pragma comment(lib, "glew32s_x64.lib") 
#else
#pragma comment(lib, "glew32s_x86.lib") 
#endif

#define OPENGL_INCLUDED

#endif // !WYVERN_OPENGL
