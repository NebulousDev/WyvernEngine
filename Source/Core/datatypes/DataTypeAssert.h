#pragma once
#include <cstring>
#include "../Common.h"

#define DATA_TYPE_ASSERT

#if defined(DATA_TYPE_ASSERT)

#define ASSERT_NOT_NULL(pointer)\
	if((void*)pointer == NULL) AssertNotNull32((uint32)pointer, __LINE__, __FILE__);

#else

#define ASSERT_NOT_NULL(void* pointer)

#endif

// TODO: move to platform
static void ThrowAssert(const char* message)
{
	std::cout << "ASSERTION FAILED!:\n" << message << std::endl;
	throw std::exception();
}

static void PointerToString(const uint32 ptr)
{

}

static void AssertNotNull32(const uint32 ptr, const uint32 line, const char* file)
{
	char messageBuffer[128]; 
	char lineBuffer[16];

	_itoa_s(line, lineBuffer, 16);

	strcpy_s(messageBuffer, "ASSERT_NOT_NULL Failed with value ");
	strcat_s(messageBuffer, "TEST");//PointerToString(ptr));
	strcat_s(messageBuffer, " on line ");
	strcat_s(messageBuffer, lineBuffer);
	strcat_s(messageBuffer, " in ");
	strcat_s(messageBuffer, file);
	ThrowAssert(messageBuffer);
}