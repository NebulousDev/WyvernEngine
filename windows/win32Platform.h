#pragma once
#include <platform\platform.h>

void	Win32SetupPlatform(Platform* platform, PlatformInfo info);

RESULT	Win32GetWorkingDirectory(char* path);

RESULT	Win32GetFileSize(uint64* size, const char* filepath);

RESULT	Win32ReadFileToBuffer(char* buffer, const uint64 bufferSize, const uint64 offset, const uint64 bytes, const char* filepath);
