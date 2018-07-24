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

RESULT GetWorkingDirectory(char* path)
{
	return sPlatform->fpGetWorkingDirectory(path);
}

RESULT GetFileSize(uint64* size, const char* filepath)
{
	return sPlatform->fpGetFileSize(size, filepath);
}

RESULT ReadFileToBuffer(char* buffer, const uint64 bufferSize, const uint64 offset, const uint64 bytes, const char* filepath)
{
	return sPlatform->fpReadFileToBuffer(buffer, bufferSize, offset, bytes, filepath);
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