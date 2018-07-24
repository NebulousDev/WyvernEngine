#pragma once
#include "../common.h"

#define MAX_PATH_LENGTH	512

struct ApplicationInfo
{
	const char*		appName;
	const char*		appVersion;
	uint64			appMemAllocSize;
};

struct Application
{

};

struct Window;
struct WindowInfo;
class Runtime;
class CoreRuntime;

struct PlatformInfo
{
	const char* platformName;
	const char* platformVersion;
	// Add more fancy platform info
};

struct Platform
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

void				InitPlaform(const Platform* platform);
const Platform*		GetPlatform();
const PlatformInfo	GetPlatformInfo();

///////////////////////////////////////////////////////////////

RESULT				GetWorkingDirectory(char* path);

RESULT				GetFileSize(uint64* size, const char* filepath);
RESULT				ReadFileToBuffer(char* buffer, const uint64 bufferSize, 
										const uint64 offset, const uint64 bytes, const char* filepath);

///////////////////////////////////////////////////////////////

Runtime*			CreateRuntime(const char* dll);
CoreRuntime*		CreateCoreRuntime(const char* dll);
void				FreeRuntime(Runtime* runtime);