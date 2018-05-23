#pragma once

#include "../Platform.h"

int32 GLOBAL SDLCreateApplication(ApplicationInfo info)
{
	return WYVERN_SUCCESS;
}

int32 GLOBAL SDLCreateWindow(WindowInfo info)
{
	return WYVERN_SUCCESS;
}

int32 GLOBAL SDLAllocPage(const uint32 pages)
{
	return WYVERN_SUCCESS;
}

int32 GLOBAL SDLFreePages()
{
	return WYVERN_SUCCESS;
}