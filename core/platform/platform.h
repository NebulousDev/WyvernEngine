#pragma once
#include "../common.h"

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

typedef RESULT			(*CreateWindowFunc)(Window* window, const WindowInfo info);
typedef RESULT			(*FreeWindowFunc)(Window* window);
typedef RESULT			(*SetWindowSizeFunc)(Window* window, uint32 width, uint32 height);
typedef RESULT			(*ShowWindowFunc)(Window* window);
typedef RESULT			(*HideWindowFunc)(Window* window);

typedef Runtime*		(*CreateRuntimeFunc)(const char* dllname);
typedef CoreRuntime*	(*CreateCoreRuntimeFunc)(const char* dllname);
typedef	void			(*FreeRuntimeFunc)(Runtime* runtime);

struct PlatformInfo
{
	const char* platformName;
	const char* platformVersion;
	// Add more fancy platform info
};

struct Platform
{
	PlatformInfo			platformInfo;

	CreateWindowFunc		fpCreateWindow;
	FreeWindowFunc			fpFreeWindow;
	SetWindowSizeFunc		fpSetWindowSize;
	ShowWindowFunc			fpShowWindow;
	HideWindowFunc			fpHideWindow;

	CreateRuntimeFunc		fpCreateRuntime;
	CreateCoreRuntimeFunc	fpCreateCoreRuntime;
	FreeRuntimeFunc			fpFreeRuntime;
};

void				InitPlaform(const Platform* platform);
const Platform*		GetPlatform();
const PlatformInfo	GetPlatformInfo();

///////////////////////////////////////////////////////////////

Runtime*			CreateRuntime(const char* dll);
CoreRuntime*		CreateCoreRuntime(const char* dll);
void				FreeRuntime(Runtime* runtime);