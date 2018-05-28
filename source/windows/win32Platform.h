#pragma once

#define WIN32_LEAN_AND_MEAN	1
#define NOCOMM				1

#include <Windows.h>

#include <Core\platform\platform.h>

int32 GLOBAL Win32LoadDLL(const char* path);

int32 GLOBAL Win32ExitApplication(int32 code);

int32 GLOBAL Win32ForceKillApplication(int32 code);

void GLOBAL Win32DebugConsolePrint(const char* text);
