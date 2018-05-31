#include "platform.h"

int32 GLOBAL LoadPlatformFunctions(PlatformFuncs funcs)
{
	sLoadDLLFunc = funcs.funcLoadDLL;
	sLoadFunctionFunc = funcs.funcLoadFunction;

	return WYVERN_SUCCESS;
}

FuncHandle GLOBAL GetEnteranceFunc()
{
	return NULL;
}