#pragma once
#include "assert.h"

typedef const char*	string;

#define STRINGIZE(obj) #obj

#define CONCAT(str1, str2) str1##str2

//TODO: check for better solutions to strlen
static const uint32 StrLen(string str)
{
	uint32 length = 0;
	while (str[length++] != '\0') {}
	return length;
}

//TODO: add error checking / assertions
static void StrAppend(char* buffer, string str1, string str2)
{
	uint32 str1len = StrLen(str1);
	//TODO: complete
}