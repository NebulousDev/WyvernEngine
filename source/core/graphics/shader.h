#pragma once
#include "../types.h"
#include "graphics.h"

enum ShaderType
{
	SHADER_TYPE_VERTEX,
	SHADER_TYPE_FRAGMENT,
	SHADER_TYPE_GEOMETRY
};

struct ShaderCreationInfo
{
	//TODO: Auto-detect shader extention by active graphics type
	const char*			name;
	const ShaderType	type;
	//TODO: Add a compiled flag for vulkan pre-compiled shaders?
};

struct Shader
{
	uint32		id;
	const char*	name;
	ShaderType	type;
};

struct ShaderProgramCreationInfo
{
	const char*	name;
	Shader vertexShader;
	Shader fragmentShader;
	Shader geometryShader;
};

struct ShaderProgram
{

};

GFXAPI_TEMPLATE
INLINE RESULT CreateShader(const ShaderCreationInfo info, Shader* shader);

GFXAPI_TEMPLATE
INLINE void DestroyShader(Shader* shader);

GFXAPI_TEMPLATE
INLINE RESULT CreateShaderProgram(const ShaderCreationInfo info, ShaderProgram* program);

GFXAPI_TEMPLATE
INLINE RESULT BindShaderProgram(const ShaderProgram program);

GFXAPI_TEMPLATE
INLINE RESULT UnbindShaderProgram();