#ifndef CONFIG_H
	#define CONFIG_H
	#include <stdint.h>
	typedef struct CFQuery
	{
		int DataType;// -1 == ERROR, 1 == char CharacterData, 2 == StringData, 3 == IntData, 4 = UIntData
		char CharacterData;
		int IntData;
		uint32_t UIntData;
	}ConfigQuery;

	int Save_Config_Character(const char * FileName, const char * Key, char Value);
	ConfigQuery Load_Config_Character(const char * FileName, const char * Key);
	ConfigQuery Load_Config_String(const char * FileName, const char * Key, char * Output, int OutputLength);
	ConfigQuery Load_Config_IntData(const char * FileName, const char * Key);
	ConfigQuery Load_Config_UIntData(const char * FileName, const char * Key);
#endif
