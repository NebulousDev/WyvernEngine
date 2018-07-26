#pragma once
#include "../common.h"
#include "graphics.h"

enum WYVERN_CORE_API ShaderType
{
	SHADER_TYPE_VERTEX,
	SHADER_TYPE_PIXEL,
	SHADER_TYPE_GEOMETRY,
	SHADER_TYPE_TESSELATION,
	SHADER_TYPE_TESSELATION_CONTROL
};

enum WYVERN_CORE_API ShaderDataType
{
	SHADER_DATA_BINARY,
	SHADER_DATA_TEXT
};

enum WYVERN_CORE_API ShaderFormat
{
	SHADER_FORMAT_HLSL,
	SHADER_FORMAT_GLSL
};

struct WYVERN_CORE_API HLSLShaderResource
{
	const char* vertexShdader;
	const char* pixelShader;
};

struct WYVERN_CORE_API GLSLShaderResource
{
	const char* vertexShdader;
	const char* fragmentShader;
};

struct WYVERN_CORE_API ShaderInfo
{
	const char*		name;
	const char*		filepath;
	ShaderType		type;
	ShaderDataType	dataType;
	ShaderFormat	format;
};

struct WYVERN_CORE_API Shader
{
	const char*		name;
	WYVPTRHANDLE	buffer;
};

typedef WYVPTRHANDLE ShaderHandle;
#define SHADER ShaderHandle;

WYVERN_CORE_API
const ShaderHandle CreateShader(const ContextHandle context, const ShaderInfo info);
WYVERN_CORE_API
void DisposeShader(ShaderHandle* shader);