#include "config.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
ConfigQuery Load_Config_Character(const char * FileName, const char * Key)
{
	ConfigQuery buf;
	FILE * fp = fopen(FileName, "r");
	if(!fp)
	{
		buf.DataType = -1;
		return buf;
	}
	buf.DataType = 1;
	//seek Key and obtain value
	char Line[500];
	char LineKey[500], LineValue[500];
	int gotcha = 0;
	while(fgets(Line, sizeof(Line), fp))
	{
		if(Line[strlen(Line)-1] == '\n')
		{
			Line[strlen(Line)-1] = 0;
		}
		
		sscanf(Line, "%s = %c", LineKey, LineValue);
		if(strcmp(Key, LineKey) == 0)
		{
			gotcha = 1;
			break;
		}
	}
	if(!gotcha)
	{
		buf.DataType = -1;
		return buf;
	}
	else
	{
		buf.CharacterData = LineValue[0];
	}
	return buf;
}
ConfigQuery Load_Config_String(const char * FileName, const char * Key)
{
	ConfigQuery buf;
	FILE * fp = fopen(FileName, "r");
	if(!fp)
	{
		buf.DataType = -1;
		return buf;
	}
	buf.DataType = 2;
	//seek Key and obtain value
	char Line[500];
	char LineKey[500], LineValue[500];
	int gotcha = 0;
	while(fgets(Line, sizeof(Line), fp))
	{
		if(Line[strlen(Line)-1] == '\n')
		{
			Line[strlen(Line)-1] = 0;
		}
		
		sscanf(Line, "%s = %s", LineKey, LineValue);
		if(strcmp(Key, LineKey) == 0)
		{
			gotcha = 1;
			break;
		}
	}
	if(!gotcha)
	{
		buf.DataType = -1;
		return buf;
	}
	else
	{
		buf.StringData = malloc(sizeof(char) * (strlen(LineValue)+1));
		strcpy(buf.StringData, LineValue);
	}
	return buf;
}
ConfigQuery Load_Config_IntData(const char * FileName, const char * Key)
{
	ConfigQuery buf;
	FILE * fp = fopen(FileName, "r");
	if(!fp)
	{
		buf.DataType = -1;
		return buf;
	}
	buf.DataType = 3;
	//seek Key and obtain value
	char Line[500];
	char LineKey[500], LineValue[500];
	int gotcha = 0;
	while(fgets(Line, sizeof(Line), fp))
	{
		if(Line[strlen(Line)-1] == '\n')
		{
			Line[strlen(Line)-1] = 0;
		}
		
		sscanf(Line, "%s = %s", LineKey, LineValue);
		if(strcmp(Key, LineKey) == 0)
		{
			gotcha = 1;
			break;
		}
	}
	if(!gotcha)
	{
		buf.DataType = -1;
		return buf;
	}
	else
	{
		sscanf(LineValue, "%d", &buf.IntData);
	}
	return buf;
}
ConfigQuery Load_Config_UIntData(const char * FileName, const char * Key)
{
	ConfigQuery buf;
	FILE * fp = fopen(FileName, "r");
	if(!fp)
	{
		buf.DataType = -1;
		return buf;
	}
	buf.DataType = 3;
	//seek Key and obtain value
	char Line[500];
	char LineKey[500], LineValue[500];
	int gotcha = 0;
	while(fgets(Line, sizeof(Line), fp))
	{
		if(Line[strlen(Line)-1] == '\n')
		{
			Line[strlen(Line)-1] = 0;
		}
		
		sscanf(Line, "%s = %s", LineKey, LineValue);
		if(strcmp(Key, LineKey) == 0)
		{
			gotcha = 1;
			break;
		}
	}
	if(!gotcha)
	{
		buf.DataType = -1;
		return buf;
	}
	else
	{
		sscanf(LineValue, "%u", &buf.UIntData);
	}
	return buf;
}