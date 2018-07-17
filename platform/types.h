#pragma once

typedef __int8					int8;
typedef __int16					int16;
typedef __int32					int32;
typedef __int64					int64;

typedef unsigned __int8			uint8;
typedef unsigned __int16		uint16;
typedef unsigned __int32		uint32;
typedef unsigned __int64		uint64;

typedef float					f32;
typedef double					d64;

typedef uint8					bool8;

typedef uint32*					ptr32;
typedef uint64*					ptr64;

#define WYVHANDLE				int32
#define WYVPTRHANDLE			ptr32

#ifdef COMPILE_64
#define HANDLE					uint64;
#define PTRHANDLE				ptr64
#endif // COMPILE_64
