#pragma once

#include "../common.h"

typedef WYVPTRHANDLE ContextHandle;

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

struct WYVERN_CORE_API HLSLShaderSources
{
	ShaderDataType	dataType;
	const WSTRING	vertexShaderSource;
	const WSTRING	pixelShaderSource;
};

struct WYVERN_CORE_API GLSLShaderSources
{
	ShaderDataType	dataType;
	const WSTRING	vertexShaderSource;
	const WSTRING	fragmentShaderSource;
};

struct WYVERN_CORE_API HLSLShaderBuffers
{
	WYVPTRHANDLE	hVertexBuffer;
	WYVPTRHANDLE	hPixelBuffer;
};

struct WYVERN_CORE_API GLSLShaderBuffers
{
	WYVPTRHANDLE	hVertexBuffer;
	WYVPTRHANDLE	hFragmentBuffer;
};

struct WYVERN_CORE_API ShaderInfo
{
	const STRING		name;
	HLSLShaderSources	hlslSources;
	GLSLShaderSources	glslSources;
};

struct WYVERN_CORE_API Shader
{
	const STRING		name;
	HLSLShaderBuffers	hlslBuffers;
	GLSLShaderBuffers	glslBuffers;
};

typedef WYVPTRHANDLE	ShaderHandle;
#define SHADER			ShaderHandle

WYVERN_CORE_API 
const SHADER		CreateShader(const ContextHandle context, const ShaderInfo info);
WYVERN_CORE_API 
void				ReleaseShader(ShaderHandle* phShader);
WYVERN_CORE_API	
RESULT				BindShader(ShaderHandle hShader);
WYVERN_CORE_API	
RESULT				UnbindShader();