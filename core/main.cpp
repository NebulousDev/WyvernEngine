#include "common.h"
#include "platform.h"
#include <iostream>

EXPORT void Create(ApplicationInfo* info)
{
	info->appName			= "Wyvern Game";
	info->appVersion		= "1.0.0";
	info->appMemAllocSize	= MEGABYTES(64);
}

EXPORT void Start(const Application* app, const Platform* platform)
{
	InitPlaform(platform);

	PlatformInfo info = GetPlatformInfo();

	std::cout << info.platformName << std::endl;
	std::cout << info.platformVersion << std::endl;
}

EXPORT void Loop(const Application* app)
{

}