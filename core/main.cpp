#include "common.h"
#include "platform.h"

EXPORT void Create(ApplicationInfo* info)
{
	info->appName			= "Wyvern Game";
	info->appVersion		= "1.0.0";
	info->appMemAllocSize	= MEGABYTES(64);
}

EXPORT void Start(const Application* app, const Platform* platform)
{

}

EXPORT void Loop(const Application* app)
{

}