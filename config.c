#include "config.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
int Save_Config_Character(const char * FileName, const char * Key, char Value)
{
	char FileName_Tmp[500];
	snprintf(FileName_Tmp, sizeof(FileName_Tmp), "%s_tmp", FileName);
	FILE * fp_read = fopen(FileName, "r");
	FILE * fp_write = fopen(FileName_Tmp, "w");
	if(!fp_read || !fp_write)
	{
		return 0;
	}
	//seek Key and change value
	char Line[500];
	char LineKey[500], LineValue[500];
	int gotcha = 0;
	while(fgets(Line, sizeof(Line), fp_read))
	{
		if(gotcha)
		{
			fprintf(fp_write, "%s", Line);
		}
		else
		{
			if(Line[strlen(Line)-1] == '\n')
			{
				Line[strlen(Line)-1] = 0;
			}		
			sscanf(Line, "%s = %c", LineKey, LineValue);
			if(strcmp(Key, LineKey) == 0)
			{
				gotcha = 1;
				fprintf(fp_write, "%s = %c\n", Key, Value);
			}
			else
			{
				fprintf(fp_write, "%s\n", Line);
			}
			
		}		
	}
	fclose(fp_read);
	fclose(fp_write);
	remove(FileName);
	rename(FileName_Tmp, FileName);
	return 1;
}
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
	fclose(fp);
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
ConfigQuery Load_Config_String(const char * FileName, const char * Key, char * Output, int OutputLength)
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
	fclose(fp);
	if(!gotcha)
	{
		buf.DataType = -1;
		return buf;
	}
	else
	{
		strncpy(Output, LineValue, OutputLength);
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
	fclose(fp);
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
	fclose(fp);
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
