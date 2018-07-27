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

struct WYVERN_CORE_API HLSLShaderSources
{
	ShaderDataType	dataType;
	const char*		pVertexShader;
	const char*		pPixelShader;
};

struct WYVERN_CORE_API GLSLShaderSources
{
	ShaderDataType	dataType;
	const char*		pVertexShdader;
	const char*		pFragmentShader;
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
	const char*			pName;
	HLSLShaderSources	hlslSources;
	GLSLShaderSources	glslSources;
};

struct WYVERN_CORE_API Shader
{
	const char*			pName;
	HLSLShaderBuffers	hlslBuffers;
	GLSLShaderBuffers	glslBuffers;
};

typedef WYVPTRHANDLE	ShaderHandle;
#define HSHADER			ShaderHandle
#define PHSHADER		ShaderHandle*

WYVERN_CORE_API 
const ShaderHandle	CreateShader(const ContextHandle context, const ShaderInfo info);
WYVERN_CORE_API 
void				DisposeShader(ShaderHandle* phShader);
WYVERN_CORE_API	
RESULT				BindShader(ShaderHandle hShader);
WYVERN_CORE_API	
RESULT				UnbindShader();