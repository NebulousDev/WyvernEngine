#pragma once

typedef void*(GetFunctionFunc)(const char* funcName);

class Runtime
{
private:

	void*			mInstance;

	GetFunctionFunc fpGetFunction;

public:
	template<typename Function>
	Function GetFunction(const char* funcName);
};