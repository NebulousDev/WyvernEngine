#pragma once

#include "../Common.h"
#include "../memory/Memory.h"

struct StringType
{
	const char*		data;
	const uint32	length;

	string operator=(char* cstr);
	string operator=(const char* cstr);
};

typedef StringType string;

uint32 GLOBAL StrLength(const char* str);

string GLOBAL StrConcat(string str1, string str2);

string GLOBAL operator+(string str1, string str2);

