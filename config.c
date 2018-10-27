#include "config.h"
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
}
ConfigQuery Load_Config_String(const char * FileName, const char * Key)
{
}
ConfigQuery Load_Config_Int(const char * FileName, const char * Key)
{
}
ConfigQuery Load_Config_UIntData(const char * FileName, const char * Key)
{
}
