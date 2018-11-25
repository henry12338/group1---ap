#include "JSON_action.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

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
int Request_Upload_Config(char * OutputBuf, int length)
{
	char Filename[100];
	char month[10];
	int year, day, hour, minute, sec;
	
	//Sun Nov 25 01:27:25 2018
	time_t cur_time = time(NULL);
	sscanf(ctime(&cur_time), "%*s %s %d %d:%d:%d %d", month, &day, &hour, &minute, &sec, &year);
	
	snprintf(Filename, sizeof(Filename), "Update_%d_%s_%d_%d_%d_%d.tar.gz", year, month, day, hour, minute, sec);
	char Command_To_Pack[1000];
	snprintf(Command_To_Pack, sizeof(Command_To_Pack), "tar cvzf %s ./", Filename); // ./ is compared different file
	printf("Command_To_Pack: %s\n", Command_To_Pack);
	//system(Command_To_Pack);
	//UploadSettingPackage("ftp://35.221.194.17/helloworld.tar.gz", "uftp", "seg1", "helloworld.tar.gz");
        int ret_value = snprintf(OutputBuf, length, "{\n  \"Action\" : 6,\n  \"Config Archive File Name\" : \"%s\"\n}\n", Filename);
	return ret_value>=0&&ret_value<length;
}
