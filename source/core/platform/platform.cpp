#include "platform.h"

/*=================================================================
|	FUNCTIONS                                                     |
=================================================================*/

fLoadDLL						sLoadDLLFunc					= NULL;
fLoadFunction					sLoadFunctionFunc				= NULL;

fAllocateBytes					sAllocateBytesFunc				= NULL;

#if defined(GFXAPI_OPENGL_ENABLED)
fOpenGLCreateContext			sOpenGLCreateContextFunc		= NULL;
fOpenGLMakeContextCurrent		sOpenGLMakeContextCurrentFunc	= NULL;
#endif

int32 LoadPlatformFunctions(PlatformFuncs funcs)
{
	sLoadDLLFunc					= funcs.funcLoadDLL;
	sLoadFunctionFunc				= funcs.funcLoadFunction;

	sAllocateBytesFunc				= funcs.funcAllocateBytes;

#if defined(GFXAPI_OPENGL_ENABLED)
	sOpenGLCreateContextFunc		= funcs.funcOpenGLCreateContext;
	sOpenGLMakeContextCurrentFunc	= funcs.funcOpenGLMakeContextCurrent;
#endif

	return WYVERN_SUCCESS;
}