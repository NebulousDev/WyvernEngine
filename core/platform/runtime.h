#pragma once
#include "platform.h"

class WYVERN_CORE_API Runtime
{
public:
	typedef void*(*GetFunctionFunc)(Runtime* runtime, const char* func);

protected:
	WYVPTRHANDLE		mInstance;
	GetFunctionFunc		fpGetFunction;

	Runtime() {}

public:
	template<typename Function>
	WYVERN_CORE_API Function GetFunction(const char* func);

	INLINE const void* GetInstance() { return mInstance; }
};

class CoreRuntime : public Runtime
{
public:
	typedef RESULT(*CreateFunc)(ApplicationInfo* info);
	typedef RESULT(*StartFunc)(const Application* app, const Platform* platform);
	typedef RESULT(*LoopFunc)(const Application* app);

protected:
	CreateFunc			fpCreate;
	StartFunc			fpStart;
	LoopFunc			fpLoop;

	CoreRuntime() : Runtime() {}

public:
	WYVERN_CORE_API RESULT Create(ApplicationInfo* info);
	WYVERN_CORE_API RESULT Start(const Application* app, const Platform* platform);
	WYVERN_CORE_API RESULT Loop(const Application* app);
};