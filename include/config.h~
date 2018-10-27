#ifndef CONFIG_H
	#define CONFIG_H
	#include <stdint.h>
	typedef struct CFQuery
	{
		int DataType;// -1 == ERROR, 1 == char CharacterData, 2 == StringData, 3 == IntData, 4 = UIntData
		char CharacterData;
		char * StringData;
		int IntData;
		uint32_t UIntData;
	}ConfigQuery;
	ConfigQuery Load_Config_Character(const char * FileName, const char * Key);
	ConfigQuery Load_Config_String(const char * FileName, const char * Key);
	ConfigQuery Load_Config_Int(const char * FileName, const char * Key);
	ConfigQuery Load_Config_UIntData(const char * FileName, const char * Key);
#endif
