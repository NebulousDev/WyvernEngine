#include "platform.h"

int32 GLOBAL LoadPlatformFunctions(PlatformFuncs funcs)
{
	sTestPlatformFunc	= funcs.funcTestPlatform;
	sLoadDLLFunc		= funcs.funcLoadDLL;

	int32 result = TestPlatform(12);

	return WYVERN_SUCCESS;
}