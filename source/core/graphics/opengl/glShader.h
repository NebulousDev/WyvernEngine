#pragma once
#include "../shader.h"
#include "glUtils.h"

INLINE int32 GetGLShaderType(const ShaderType type)
{
	switch (type)
	{
		case SHADER_TYPE_VERTEX: 
			return GL_VERTEX_SHADER;

		case SHADER_TYPE_FRAGMENT: 
			return GL_FRAGMENT_SHADER;

		case SHADER_TYPE_GEOMETRY: 
			return GL_GEOMETRY_SHADER;

		default:
			return -1;
	}
}

GFXAPI_TEMPLATE_DEF
RESULT CreateShader<GFXAPI_OPENGL>(const ShaderCreationInfo info, Shader* shader)
{
	GL_CHECK(shader->id = glCreateShader(GetGLShaderType(info.type));)

	if (shader->id == -1)
	{
		//TODO: Add error message
		return WYVERN_ERROR;
	}

	GL_CHECK(glShaderSource(shader->id, 1, &info.name, NULL);)

	shader->name = info.name;
	shader->type = info.type;

	return WYVERN_SUCCESS;
}

GFXAPI_TEMPLATE_DEF
void DestroyShader<GFXAPI_OPENGL>(Shader* shader)
{
	GL_CHECK(glDeleteShader(shader->id);)
	shader->id = -1;
}

GFXAPI_TEMPLATE_DEF 
RESULT CreateShaderProgram<GFXAPI_OPENGL>(const ShaderCreationInfo info, ShaderProgram * program)
{
	return WYVERN_SUCCESS;
}