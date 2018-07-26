#pragma once
#include "../common.h"

#define MAX_PATH_LENGTH	512

struct WYVERN_CORE_API ApplicationInfo
{
	const char*		appName;
	const char*		appVersion;
	uint64			appMemAllocSize;
};

struct WYVERN_CORE_API Application
{

};

struct Window;
struct WindowInfo;
class Runtime;
class CoreRuntime;

struct WYVERN_CORE_API PlatformInfo
{
	const char* platformName;
	const char* platformVersion;
	// Add more fancy platform info
};

struct WYVERN_CORE_API Platform
{
	typedef RESULT			(*CreateWindowFunc)(Window* window, const WindowInfo info);
	typedef RESULT			(*FreeWindowFunc)(Window* window);
	typedef RESULT			(*SetWindowSizeFunc)(Window* window, uint32 width, uint32 height);
	typedef RESULT			(*ShowWindowFunc)(Window* window);
	typedef RESULT			(*HideWindowFunc)(Window* window);

	typedef RESULT			(*GetWorkingDirectoryFunc)(char* path);

	typedef RESULT			(*GetFileSizeFunc)(uint64* size, const char* filepath);
	typedef RESULT			(*ReadFileToBuffer)(char* buffer, const uint64 bufferSize,
												const uint64 offset, const uint64 bytes, const char* filepath);

	typedef Runtime*		(*CreateRuntimeFunc)(const char* dllname);
	typedef CoreRuntime*	(*CreateCoreRuntimeFunc)(const char* dllname);
	typedef	void			(*FreeRuntimeFunc)(Runtime* runtime);

	PlatformInfo			platformInfo;

	CreateWindowFunc		fpCreateWindow;
	FreeWindowFunc			fpFreeWindow;
	SetWindowSizeFunc		fpSetWindowSize;
	ShowWindowFunc			fpShowWindow;
	HideWindowFunc			fpHideWindow;

	GetWorkingDirectoryFunc	fpGetWorkingDirectory;

	GetFileSizeFunc			fpGetFileSize;
	ReadFileToBuffer		fpReadFileToBuffer;

	CreateRuntimeFunc		fpCreateRuntime;
	CreateCoreRuntimeFunc	fpCreateCoreRuntime;
	FreeRuntimeFunc			fpFreeRuntime;
};

WYVERN_CORE_API
void				InitPlaform(const Platform* platform);
WYVERN_CORE_API
const Platform*		GetPlatform();
WYVERN_CORE_API
const PlatformInfo	GetPlatformInfo();

///////////////////////////////////////////////////////////////

WYVERN_CORE_API
RESULT				GetWorkingDirectory(char* path);

WYVERN_CORE_API
RESULT				GetFileSize(uint64* size, const char* filepath);
WYVERN_CORE_API
RESULT				ReadFileToBuffer(char* buffer, const uint64 bufferSize, 
										const uint64 offset, const uint64 bytes, const char* filepath);

///////////////////////////////////////////////////////////////

WYVERN_CORE_API
Runtime*			CreateRuntime(const char* dll);
WYVERN_CORE_API
CoreRuntime*		CreateCoreRuntime(const char* dll);
WYVERN_CORE_API
void				FreeRuntime(Runtime* runtime);