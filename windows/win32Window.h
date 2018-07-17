#pragma once
#include <platform\window.h>

RESULT Win32CreateWindow(Window* window, const WindowInfo info);

RESULT Win32FreeWindow(Window* window);

RESULT Win32SetWindowSize(Window* window, uint32 width, uint32 height);

RESULT Win32ShowWindow(Window* window);

RESULT Win32HideWindow(Window* window);