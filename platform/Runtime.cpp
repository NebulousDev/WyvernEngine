#include "Runtime.h"

template<typename Function>
inline Function Runtime::GetFunction(const char* funcName)
{
	return (Function)fpGetFunction(funcName);
}