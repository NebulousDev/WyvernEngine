#include "platform.h"

static const Platform* sPlatform;

void InitPlaform(const Platform* platform)
{
	//TODO: assert platform already exists
	sPlatform = platform;
}

const Platform* GetPlatform()
{
	return sPlatform;
}

const PlatformInfo GetPlatformInfo()
{
	return sPlatform->platformInfo;
}

Runtime* CreateRuntime(const char* dll)
{
	return sPlatform->fpCreateRuntime(dll);
}

CoreRuntime* CreateCoreRuntime(const char* dll)
{
	return sPlatform->fpCreateCoreRuntime(dll);
}

void FreeRuntime(Runtime* runtime)
{
	sPlatform->fpFreeRuntime(runtime);
}