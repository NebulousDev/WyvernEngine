#pragma once
#include "common.h"

EXPORT_STRUCT ApplicationInfo
{
	const char*		appName;
	const char*		appVersion;
	uint64			appMemAllocSize;
};

EXPORT_STRUCT Application
{

};

class Window
{
	// TODO
};

struct WindowInfo
{
	// TODO
};

typedef Window(*CreateWindow)(const WindowInfo info);

EXPORT_STRUCT Platform
{
	CreateWindow fpCreateWindow;
};