#pragma once
#include "header.h"

class Runtime
{
private:
	typedef RESULT(*FuncTypeCreate)();
	typedef void(*FuncTypeUpdate)();
	typedef void(*FuncTypeDestroy)();

	FuncTypeCreate	fpCreate;
	FuncTypeUpdate	fpUpdate;
	FuncTypeDestroy fpDestroy;

	HMODULE mRuntime;

public:
	RESULT CreateRuntime(Win32State* state, const char* dll);
	RESULT DestroyRuntime();

	INLINE RESULT	Create() { return fpCreate(); }
	INLINE void		Update() { fpUpdate(); }
	INLINE void		Destroy() { fpDestroy(); }
};

RESULT RunApplication(Win32State* state, ApplicationInfo* appInfo, WindowInfo* windInfo);
