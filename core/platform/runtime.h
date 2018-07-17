#pragma once
#include "platform.h"

class Runtime
{
public:
	typedef void*(*GetFunctionFunc)(Runtime* runtime, const char* func);

protected:
	WYVPTRHANDLE		mInstance;
	GetFunctionFunc		fpGetFunction;

	Runtime() {}

public:
	template<typename Function>
	Function GetFunction(const char* func);

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
	RESULT Create(ApplicationInfo* info);
	RESULT Start(const Application* app, const Platform* platform);
	RESULT Loop(const Application* app);
};