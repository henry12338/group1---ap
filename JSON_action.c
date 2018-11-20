#include "JSON_action.h"
#include "mjson.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>

int Request_Controller_Alive(char * OutputBuf, int length)
{
	int ret_value = snprintf(OutputBuf, length, "{\n  \"Action\" : 0\n}\n");
	return ret_value>=0&&ret_value<length;
}
int Request_Register_AP(const char * mac, const char * SSID, char * OutputBuf, int length)
{
	int ret_value = snprintf(OutputBuf, length, "{\n  \"Action\" : 1,\n  \"AP Mac\" : \"%s\",\n  \"AP SSID\" : \"%s\"\n}\n", mac, SSID);
	return ret_value>=0&&ret_value<length;
    //neccessary register info
}
int Request_Upload_Config(uint32_t AP_Number, const char * ConfigLocation, char * OutputBuf, int length)
{
        int ret_value = snprintf(OutputBuf, length, "{\n  \"Action\" : 6,\n  \"AP Number\" : \"%u\",\n  \"Config Archive Location\" : \"%s\"\n}\n", AP_Number, ConfigLocation);
	return ret_value>=0&&ret_value<length;
}
