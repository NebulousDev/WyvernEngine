#include "platform.h"

#include "../runtime.h"

int32 LoadPlatformFunctions(PlatformFuncs funcs)
{
	sLoadDLLFunc = funcs.funcLoadDLL;
	sLoadFunctionFunc = funcs.funcLoadFunction;

	return WYVERN_SUCCESS;
}

/*
fUpdateAndRender GetUpdateAndRenderFunc()
{
	return &WyvernUpdateAndRender;
}
*/