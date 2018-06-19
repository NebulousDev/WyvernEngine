#pragma once

#include "../../types.h"
#include <GLEW\glew.h>
#include <cstdio>

#ifdef _DEBUG

#define GL_CHECK(code) \
{ \
	code; \
	GLCheckError(#code, __FILE__, __LINE__); \
}
#else
#define GL_CHECK(code) code
#endif

string GLGetErrorEnumName(int32 err)
{
	switch (err)
	{
		case GL_INVALID_ENUM:
			return "GL_INVALID_ENUM";
		default:
			return STRINGIZE(err);
	}
}

void GLCheckError(string code, string file, int32 line)
{
	GLenum err = GL_NO_ERROR;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		string glErrorEnum = GLGetErrorEnumName(err);
		printf("[ERROR] An OpenGL error [%s:] occured at [%s:%i]! \n%s\n", glErrorEnum, file, line, code);
		//abort();	//TODO: end program?
	}
}