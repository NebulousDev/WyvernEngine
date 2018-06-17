#pragma once
#include "platform.h"

class Application
{
private:
	const PlatformApplication* platform;

public:
	//TODO: Tidy up application creation
	void InitPlatform(const PlatformApplication* platform);

	INLINE void SetWindowTitle(const char* title) { platform->fpSetWindowTitle(title); }
	INLINE void SetWindowSize(const uint32 width, const uint32 height) { platform->fpSetWindowSize(width, height); }
	INLINE void SetWindowPosition(const uint32 x, const uint32 y) { platform->fpSetWindowPosition(x, y); }
	INLINE void SetWindowCentered() { platform->fpSetWindowCentered(); }
	INLINE void SetWindowVisible(const bool32 visible) { platform->fpSetWindowVisible(visible); }
};