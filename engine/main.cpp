#include <platform\platform.h>
#include <platform\window.h>
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

	WindowInfo windInfo = {};
	windInfo.title		= "WyvernGame";
	windInfo.width		= 1280;
	windInfo.height		= 720;
	windInfo.posX		= 20;
	windInfo.posY		= 20;
	windInfo.flags		= 0;

	WindowHandle wind = CreateWindow(windInfo);
	RESULT show = ShowWindow(wind);
}

EXPORT void Loop(const Application* app)
{
	
}