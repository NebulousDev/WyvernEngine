#pragma once
#include "header.h"

class Runtime
{
typedef RESULT(*FuncTypeCreate)();
typedef void(*FuncTypeUpdate)();
typedef void(*FuncTypeDestroy)();

private:
	FuncTypeCreate	fpCreate;
	FuncTypeUpdate	fpUpdate;
	FuncTypeDestroy fpDestroy;

public:
	RESULT CreateRuntime(Win32State* state, const char* dll);

	INLINE RESULT	Create() { return fpCreate(); }
	INLINE void		Update() { fpUpdate(); }
	INLINE void		Destroy() { fpDestroy(); }
};

RESULT RunApplication(Win32State* state, ApplicationInfo* appInfo, WindowInfo* windInfo);
