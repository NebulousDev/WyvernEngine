#pragma once
#include "common.h"

struct ApplicationInfo
{
	const char*		appName;
	const char*		appVersion;
	uint64			appMemAllocSize;
};

struct Application
{

};

class Window
{
private:
	const char*		mTitle;
	uint32			mWidth;
	uint32			mHeight;
	uint32			mPosX;
	uint32			mPosY;

public:
};

struct WindowInfo
{
	const char*		title;
	uint32			width;
	uint32			height;
	uint32			posX;
	uint32			posY;
};

class Runtime;
class CoreRuntime;

typedef Window*			(*CreateWindowFunc)(const WindowInfo info);
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
	CreateRuntimeFunc		fpCreateRuntime;
	CreateCoreRuntimeFunc	fpCreateCoreRuntime;
	FreeRuntimeFunc			fpFreeRuntime;
};

void				InitPlaform(const Platform* platform);
const PlatformInfo	GetPlatformInfo();

Runtime*			CreateRuntime(const char* dll);
CoreRuntime*		CreateCoreRuntime(const char* dll);
void				FreeRuntime(Runtime* runtime);