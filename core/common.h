#pragma once
#include "types.h"

#define EXPORT				extern "C" __declspec(dllexport)
#define EXPORT_STRUCT		extern "C" struct __declspec(dllexport)

#define KILOBYTES(size)		1000 * size
#define MEGABYTES(size)		1000 * KILOBYTES(size)
#define GIGABYTES(size)		1000 * MEGABYTES(size)