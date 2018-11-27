#include "JSON_action.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "config.h"

int Request_Controller_Alive(char * OutputBuf, int length)
{
	int ret_value = snprintf(OutputBuf, length, "{\n  \"Action\" : 0\n}\n");
	return ret_value>=0&&ret_value<length;
}
int Request_Register_AP(char * OutputBuf, int length)
{
	int ret_value = snprintf(OutputBuf, length, "{\n  \"Action\" : 1\n}\n");
	return ret_value>=0&&ret_value<length;
}
int Request_Upload_Config(const char * Content, char * OutputBuf, int length)
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

	char FTPFile[500];
	char FTPServerAddress[100];
	char UserName[50];
	char Password[50];
	ConfigQuery ConfigBuf;
	ConfigBuf = Load_Config_String("./config/connect_config", "FTP_Server_Address", FTPServerAddress, sizeof(FTPServerAddress));
	printf("Downloaded Filename: %s\n", Filename);

	if(ConfigBuf.DataType != 2)
	{
		puts("No proper config");
		return -1;
	}
	snprintf(FTPFile, sizeof(FTPFile), "ftp://%s/%s", FTPServerAddress, Filename);

	ConfigBuf = Load_Config_String("./config/connect_config", "FTP_Username", UserName, sizeof(UserName));
	if(ConfigBuf.DataType != 2)
	{
		puts("No proper config");
		return -1;
	}

	ConfigBuf = Load_Config_String("./config/connect_config", "FTP_Password", Password, sizeof(Password));
	if(ConfigBuf.DataType != 2)
	{
		puts("No proper config");
		return -1;
	}

	//UploadSettingPackage(FTPFile, UserName, Password, Filename);
        int ret_value = snprintf(OutputBuf, length, "{\n  \"Action\" : 6,\n  \"Content\" : \"%s\",\n  \"Config Archive File Name\" : \"%s\"\n}\n", Content, Filename);
	return ret_value>=0&&ret_value<length;
}
