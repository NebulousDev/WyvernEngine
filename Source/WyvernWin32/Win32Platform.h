#pragma once

#include <Core\platform\Platform.h>

int32 GLOBAL Win32AllocPage(const uint32 pages);

int32 GLOBAL Win32FreePages();

int32 GLOBAL Win32LoadDLL(const char* path);

int32 GLOBAL ExitApplication(int32 code);

int32 GLOBAL ForceKillApplication(int32 code);

void GLOBAL DebugConsolePrint(const char* text);
