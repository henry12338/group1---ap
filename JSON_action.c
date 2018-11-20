#include "JSON_action.h"
#include "mjson.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>

int Request_Controller_Alive(char * OutputBuf)
{
        const int length = 1000;
	snprintf(OutputBuf, length, "{\n  \"Action\" : 0\n}\n");
	return 1;
}
int Request_Register_AP(const char * ip, char * OutputBuf)
{
        const int lenght = 1000;
        snprintf(OutputBuf, length, "{\n  \"Action\" : 1,\n  \"AP out IP\" : \"%s\"\n}\n", ip);
	return 1;
    //neccessary register info
}
int Request_Return_AP_Info(uint32_t AP_Number, char * OutputBuf)
{
        const int length = 1000;
        snprintf(OutputBuf, length, "{\n  \"Action\" : 2,\n  \"AP Number\" : %u\n}\n", AP_Number);
	return 1;
}
int Request_User_IsRegistered(const char * Username, char * OutputBuf)
{
        const int length = 1000;
        snprintf(OutputBuf, length, "{\n  \"Action\" : 3,\n  \"Username\" : \"%s\"\n}\n", Username);
	return 1;
}
int Request_Check_User_Password(const char * Hashed_Password, char * OutputBuf)
{
        const int length = 1000;
        snprintf(OutputBuf, length, "{\n  \"Action\" : 4,\n  \"Password\" : \"%s\"\n}\n", Hashed_Password);
	return 1;
}
int Request_Send_User_Info(uint32_t AP_Number, char * OutputBuf)
{
        const int length = 1000;
        snprintf(OutputBuf, length, "{\n  \"Action\" : 5,\n  \"AP Number\" : %u\n}\n", AP_Number);
	return 1;
}
int Request_Upload_Config(uint32_t AP_Number, const char * ConfigLocation, char * OutputBuf)
{
        const int length = 1000;
        snprintf(OutputBuf, length, "{\n  \"Action\" : 6,\n  \"AP Number\" : \"%u\",\n  \"Config Archive Location\" : \"%s\"\n}\n", AP_Number, ConfigLocation);
	return 1;
}
int Request_Download_Config(const char * ConfigLocation, char * OutputBuf)
{
        const int length = 1000;
        snprintf(OutputBuf, length, "{\n  \"Action\" : 7,\n  \"Config Archive Location\" : \"%s\"\n}\n", ConfigLocation);
	return 1;
}
//---------Response------------
int Response_Controller_Alive(char * OutputBuf)
{
    const int length = 1000;
    snprintf(OutputBuf, length, "{\n  \"Action\" : 0,\n  \"State\" : 1\n}\n");
    return 1;
}
int Response_Register_AP(uint32_t AP_Number, char * OutputBuf)
{
    const int length = 1000;
    snprintf(OutputBuf, length, "{\n  \"Action\" : 1,\n  \"AP Number\" : %u\n}\n", AP_Number);
    return 1;
}
int Response_Return_AP_Info(uint32_t AP_Number, char * OutputBuf, uint32_t AP_Temperature, double AP_Usage_Percent, uint32_t AP_Device_Amount, uint32_t AP_Traffic)
{
    const int length = 1000;
    snprintf(OutputBuf, length, "{\n  \"Action\" : 2,\n  \"AP Number\" : %u,\n  \"AP CPU temperture\" : %u,\n  \"AP CPU Usage Percent\" : %.2f,\n  \"Connect Device Amount\" : %u,\n  \"Traffic(Kib)\" : %u\n}\n", AP_Number, AP_Temperature, AP_Usage_Percent, AP_Device_Amount, AP_Traffic);
    return 1;
}
int Response_User_IsRegistered(int IsRegistered, char * OutputBuf)
{
    const int length = 1000;
    snprintf(OutputBuf, length, "{\n  \"Action\" : 3,\n  \"Result\" :%d\n}\n", IsRegistered);
    return 1;
}
int Response_Check_User_Password(int CheckPassword, char * OutputBuf)
{
    const int length = 1000;
    snprintf(OutputBuf, length, "{\n  \"Action\" : 4,\n  \"Result\" : %d\n}\n", CheckPassword);
    return 1;
}
int Response_Send_User_Info(const char * ip, const char *Username, char * OutputBuf)
{
    const int length = 1000;
    snprintf(OutputBuf, length, "{\n  \"Action\" : 5,\n  \"User Out IP\" : \"%s\",\n  \"Username\" : \"%s\"\n}\n", ip, Username);
    return 1;
}
int Response_Upload_Config(uint32_t AP_Number, const char * ConfigLocation, char * OutputBuf)
{
    const int length = 1000;
    snprintf(OutputBuf, length, "{\n  \"Action\" : 6,\n  \"AP Number\" : %u,\n  \"Config Archive Location\" : \"%s\"\n}\n", AP_Number, ConfigLocation);
    return 1;
}
int Response_Download_Config(const char * ConfigLocation, char * OutputBuf)
{
    const int length = 1000;
    snprintf(OutputBuf, length, "{\n  \"Action\" : 7,\n  \"Config Archive Location\" : \"%s\"\n}\n", ConfigLocation);
    return 1;
}
