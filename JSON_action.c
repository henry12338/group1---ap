#include "JSON_action.h"
//#include "mjson.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>

int Request_Controller_Alive(char * OutputBuf)
{
	char buf[200];
	sprintf(OutputBuf, "{\n");
	sprintf(buf, "	\"Action\" : 0\n");
	strcat(OutputBuf, buf);
	sprintf(buf, "}\n");
	strcat(OutputBuf, buf);
	return 1;
}
int Request_Register_AP(const char * ip, char * OutputBuf)
{
	char buf[200];
	sprintf(OutputBuf, "{\n");
	sprintf(buf, "	\"Action\" : 1,\n");
	strcat(OutputBuf, buf);
	sprintf(buf, "	\"AP out IP\" : \"%s\"\n", ip);
	strcat(OutputBuf, buf);
	sprintf(buf, "}\n");
	strcat(OutputBuf, buf);
	return 1;
    //neccessary register info
}
int Request_Return_AP_Info(uint32_t AP_Number, char * OutputBuf)
{
	char buf[200];
	sprintf(OutputBuf, "{\n");
	sprintf(buf, "	\"Action\" : 2,\n");
	strcat(OutputBuf, buf);
	sprintf(buf, "	\"AP Number\" : %u\n", AP_Number);
	strcat(OutputBuf, buf);
	sprintf(buf, "}\n");
	strcat(OutputBuf, buf);
	return 1;
}
int Request_User_IsRegistered(const char * Username, char * OutputBuf)
{
	char buf[200];
	sprintf(OutputBuf, "{\n");
	sprintf(buf, "	\"Action\" : 3,\n");
	strcat(OutputBuf, buf);
	sprintf(buf, "	\"Username\" : \"%s\"\n", Username);
	strcat(OutputBuf, buf);
	sprintf(buf, "}\n");
	strcat(OutputBuf, buf);
	return 1;
}
int Request_Check_User_Password(const char * Hashed_Password, char * OutputBuf)
{
	char buf[200];
	sprintf(OutputBuf, "{\n");
	sprintf(buf, "	\"Action\" : 4,\n");
	strcat(OutputBuf, buf);
	sprintf(buf, "	\"Password\" : \"%s\"\n", Hashed_Password);
	strcat(OutputBuf, buf);
	sprintf(buf, "}\n");
	strcat(OutputBuf, buf);
	return 1;
}
int Request_Send_User_Info(uint32_t AP_Number, char * OutputBuf)
{
	char buf[200];
	sprintf(OutputBuf, "{\n");
	sprintf(buf, "	\"Action\" : 5,\n");
	strcat(OutputBuf, buf);
	sprintf(buf, "	\"AP Number\" : %d\n", AP_Number);
	strcat(OutputBuf, buf);
	sprintf(buf, "}\n");
	strcat(OutputBuf, buf);
	return 1;
}
int Request_Upload_Config(uint32_t AP_Number, const char * ConfigLocation, char * OutputBuf)
{
	char buf[200];
	sprintf(OutputBuf, "{\n");
	sprintf(buf, "	\"Action\" : 6,\n");
	strcat(OutputBuf, buf);
	sprintf(buf, "	\"AP Number\" : \"%d\",\n", AP_Number);
	strcat(OutputBuf, buf);
	sprintf(buf, "	\"Config Archive Location\" : \"%s\"\n", ConfigLocation);
	strcat(OutputBuf, buf);
	sprintf(buf, "}\n");
	strcat(OutputBuf, buf);
	return 1;
}
int Request_Download_Config(const char * ConfigLocation, char * OutputBuf)
{
	char buf[200];
	sprintf(OutputBuf, "{\n");
	sprintf(buf, "	\"Action\" : 7,\n");
	strcat(OutputBuf, buf);
	sprintf(buf, "	\"Config Archive Location\" : \"%s\"\n", ConfigLocation);
	strcat(OutputBuf, buf);
	sprintf(buf, "}\n");
	strcat(OutputBuf, buf);
	return 1;
}
//---------Response------------
int Response_Controller_Alive(char * OutputBuf)
{
    char buf[200];
    sprintf(OutputBuf,"{\n");
    sprintf(buf, "	\"Action\" : 0,\n");
    strcat(OutputBuf, buf);
    sprintf(buf, "	\"State\" : 1\n");
    strcat(OutputBuf, buf);
    sprintf(buf, "}\n");
    strcat(OutputBuf, buf);
    return 1;
}
int Response_Register_AP(uint32_t AP_Number, char * OutputBuf)
{
    char buf[200];
    sprintf(OutputBuf,"{\n");
    sprintf(buf, "	\"Action\" : 1,\n");
    strcat(OutputBuf, buf);
    sprintf(buf, "	\"AP Number\" : %d\n", AP_Number);
    strcat(OutputBuf, buf);
	sprintf(buf, "}\n");
	strcat(OutputBuf, buf);
	return 1;
}
int Response_Return_AP_Info(uint32_t AP_Number, char * OutputBuf, uint32_t AP_Temperature, double AP_Usage_Percent, uint32_t AP_Device_Amount, uint32_t AP_Traffic)
{
    char buf[200];
    sprintf(OutputBuf,"{\n");
    sprintf(buf, "	\"Action\" : 2,\n");
    strcat(OutputBuf, buf);
    sprintf(buf, "	\"AP Number\" : %u,\n", AP_Number);
    strcat(OutputBuf, buf);
    sprintf(buf, "	\"AP CPU temperature(Celcius)\" : %u,\n", AP_Temperature);
    strcat(OutputBuf, buf);
    sprintf(buf, "	\"AP CPU Usage Percent\" : %.2f,\n", AP_Usage_Percent);
    strcat(OutputBuf, buf);
    sprintf(buf, "	\"Connect Device Amount\" : %u,\n", AP_Device_Amount);
    strcat(OutputBuf, buf);
    sprintf(buf, "	\"Traffic(KiB)\" : %u\n", AP_Traffic);
    strcat(OutputBuf, buf);
    sprintf(buf, "}\n");
	strcat(OutputBuf, buf);
	return 1;
}
int Response_User_IsRegistered(int IsRegistered, char * OutputBuf)
{
    char buf[200];
    sprintf(OutputBuf,"{\n");
    sprintf(buf, "	\"Action\" : 3,\n");
    strcat(OutputBuf, buf);
    sprintf(buf, "	\"Result\" : %d\n", IsRegistered);
    strcat(OutputBuf, buf);
    sprintf(buf, "}\n");
	strcat(OutputBuf, buf);
	return 1;
}
int Response_Check_User_Password(int CheckPassword, char * OutputBuf)
{
    char buf[200];
    sprintf(OutputBuf,"{\n");
    sprintf(buf, "	\"Action\" : 4,\n");
    strcat(OutputBuf, buf);
    sprintf(buf, "	\"Result\" : %d\n", CheckPassword);
    strcat(OutputBuf, buf);
    sprintf(buf, "}\n");
	strcat(OutputBuf, buf);
	return 1;
}
int Response_Send_User_Info(const char * ip, const char *Username, char * OutputBuf)
{
    char buf[200];
    sprintf(OutputBuf,"{\n");
    sprintf(buf, "	\"Action\" : 5,\n");
    strcat(OutputBuf, buf);
    sprintf(buf, "	\"User Out IP\" : \"%s\",\n", ip);
    strcat(OutputBuf, buf);
    sprintf(buf, "	\"Username\" : \"%s\"\n", Username);
    strcat(OutputBuf, buf);
    sprintf(buf, "}\n");
	strcat(OutputBuf, buf);
	return 1;
}
int Response_Upload_Config(uint32_t AP_Number, const char * ConfigLocation, char * OutputBuf)
{
    char buf[200];
    sprintf(OutputBuf,"{\n");
    sprintf(buf, "	\"Action\" : 6,\n");
    strcat(OutputBuf, buf);
    sprintf(buf, "	\"AP Number\" : %u,\n", AP_Number);
    strcat(OutputBuf, buf);
    sprintf(buf, "	\"Config Archive Location\" : \"%s\"\n", ConfigLocation);
    strcat(OutputBuf, buf);
    sprintf(buf, "}\n");
	strcat(OutputBuf, buf);
	return 1;
}
int Response_Download_Config(const char * ConfigLocation, char * OutputBuf)
{
    char buf[200];
    sprintf(OutputBuf,"{\n");
    sprintf(buf, "	\"Action\" : 7,\n");
    strcat(OutputBuf, buf);
    sprintf(buf, "	\"Config Archive Location\" : \"%s\"\n", ConfigLocation);
    strcat(OutputBuf, buf);
    sprintf(buf, "}\n");
	strcat(OutputBuf, buf);
	return 1;
}
