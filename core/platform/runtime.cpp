#include "runtime.h"

template<typename Function>
Function Runtime::GetFunction(const char* funcName)
{
	return (Function)fpGetFunction(this, funcName);
}

RESULT CoreRuntime::Create(ApplicationInfo* info)
{
	return fpCreate(info);
}

RESULT CoreRuntime::Start(const Application* app, const Platform* platform)
{
	return fpStart(app, platform);
}

RESULT CoreRuntime::Loop(const Application* app)
{
	return fpLoop(app);
}
