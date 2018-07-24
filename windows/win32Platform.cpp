#include "win32Platform.h"
#include "win32Runtime.h"
#include "win32Window.h"
#include "win32.h"
#include <cstdio>

void Win32SetupPlatform(Platform* platform, PlatformInfo info)
{
	platform->platformInfo			= info;
	platform->fpCreateWindow		= Win32CreateWindow;
	platform->fpFreeWindow			= Win32FreeWindow;
	platform->fpSetWindowSize		= Win32SetWindowSize;
	platform->fpShowWindow			= Win32ShowWindow;
	platform->fpHideWindow			= Win32HideWindow;

	platform->fpGetWorkingDirectory = Win32GetWorkingDirectory;

	platform->fpGetFileSize			= Win32GetFileSize;
	platform->fpReadFileToBuffer	= Win32ReadFileToBuffer;

	platform->fpCreateRuntime		= Win32CreateRuntime;
	platform->fpCreateCoreRuntime	= Win32CreateCoreRuntime;
	platform->fpFreeRuntime			= Win32FreeRuntime;
}

HANDLE Win32GetFileHandle(const char* filepath)
{
	HANDLE file = CreateFile(filepath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (file == INVALID_HANDLE_VALUE)
	{
		DWORD error = GetLastError();
		LPTSTR errorText = NULLPTR;
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&errorText, 0, NULL);

		char buffer[512];
		sprintf(buffer, "Error: Failed to locate file '%s'. \nReason: %s", filepath, errorText);
		MessageBox(0, buffer, "Error", MB_OK);

		return NULLPTR;
	}

	return file;
}

RESULT Win32CloseFileHandle(HANDLE handle)
{
	if (!CloseHandle(handle))
	{
		//TODO: throw warning?
		return FAILURE;
	}

	return SUCCESS;
}

RESULT Win32GetWorkingDirectory(char* path)
{
	DWORD bytes = GetCurrentDirectory(MAX_PATH_LENGTH, path);

	if (!bytes)
	{
		DWORD error = GetLastError();
		LPTSTR errorText = NULLPTR;
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&errorText, 0, NULL);

		char buffer[512];
		sprintf(buffer, "Error: Unable to get working directory. \nMessage: %s", errorText);
		MessageBox(0, buffer, "Error", MB_OK);

		return FAILURE;
	}

	if (bytes > MAX_PATH_LENGTH - 1)
		path[MAX_PATH_LENGTH] = '\0';

	return SUCCESS;
}

RESULT Win32GetFileSize(uint64* size, const char* filepath)
{
	LARGE_INTEGER filelength;
	HANDLE file = Win32GetFileHandle(filepath);
	
	if (!file) return FAILURE;

	if (!GetFileSizeEx(file, &filelength))
	{
		DWORD error = GetLastError();

		if (error)
		{
			LPTSTR errorText = NULLPTR;
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&errorText, 0, NULL);

			char buffer[512]; 
			sprintf(buffer, "Error: Failed to obtain file size of '%s'. \nReason: %s", filepath, errorText);
			MessageBox(0, buffer, "Error", MB_OK);
		}

		return FAILURE;
	}

	*size = filelength.QuadPart;

	if (!Win32CloseFileHandle(file)) return FAILURE;

	return SUCCESS;
}

RESULT Win32ReadFileToBuffer(char* buffer, const uint64 bufferSize, const uint64 offset, const uint64 bytes, const char* filepath)
{
	HANDLE file = CreateFile(filepath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	
	//TODO: make asserts?
	if (buffer == NULLPTR)
	{
		//TODO: error
		return FAILURE;
	}

	if (offset > bufferSize)
	{
		//TODO: error
		return FAILURE;
	}

	if(bytes > bufferSize)
	{
		//TODO: error
		return FAILURE;
	}

	if(offset + bytes > bufferSize)
	{
		//TODO: error
		return FAILURE;
	}

	DWORD bytesRead = 0;

	if (!ReadFile(file, buffer + offset, bytes, &bytesRead, NULL))
	{
		DWORD error = GetLastError();
		LPTSTR errorText = NULLPTR;
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&errorText, 0, NULL);

		char buffer[512];
		sprintf(buffer, "Error: Failed to read file '%s'. \nReason: %s", filepath, errorText);
		MessageBox(0, buffer, "Error", MB_OK);

		return FAILURE;
	}

	if (bytesRead != bytes)
	{
		//TODO: error
		return FAILURE;
	}

	return SUCCESS;
}
