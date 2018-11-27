#include "JSON_request_handle.h"
#include "mjson.h"
#include "config.h"
#include "update.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

int Handle_Action(const char * InputBuf, int socket_fd, int * State)
{
	double action = mjson_find_number(InputBuf, strlen(InputBuf), "$.Action", -1);
	printf("Action is %d\n", (int)action);
	if(action == 0)
	{
		return Handle_Controller_Alive(InputBuf, State);
	}
	else if(action == 1)
	{
		return Handle_Register_AP(InputBuf);
	}
	else if(action == 2)
	{
		return Handle_Return_AP_Info(InputBuf, socket_fd);
	}
	else if(action == 3)
	{
		return Handle_Change_Config(InputBuf, socket_fd);
	}
	else if(action == 7)
	{
		return Handle_Download_Config(InputBuf, socket_fd);
	}
	else
	{
		return -1;
	}
}
//KMP
void ConstructFailFunc(const char * needle, int * Fail, int len)
{
	Fail[0] = 0;
	for(int q = 1,k = 0;q < len;q++)
	{
		while(k > 0 && needle[q] != needle[k])
		{
			k = Fail[k-1];
		}
		// ensure the needle privious one is the same as needle match one is equal
		if(needle[q] == needle[k])
		{
			k++;
		}
		Fail[q] = k;
	}
}
int MatchFunc(const char * Origin, const char * needle)
{
	int Fail[200];
	int len = strlen(Origin);
	int len_n = strlen(needle);
	ConstructFailFunc(needle, Fail, len_n);
	for(int q = 0,k = 0;q < len;q++)
	{
		while(k > 0 && Origin[q] != needle[k])
		{
			k = Fail[k-1];
		}
		// ensure the needle privious one is the same as needle match one is equal
		if(Origin[q] == '#')
		{
			return -1;
		}
		if(Origin[q] == needle[k])
		{
			k++;
		}
		if(k == len_n)
		{
			return q;
		}
	}
	return -1;
}
int Handle_Controller_Alive(const char * InputBuf, int * State)
{
	double buf = mjson_find_number(InputBuf, strlen(InputBuf), "$.State", -1);
	*State = (int)buf;
	return 1;
}
int Handle_Register_AP(const char * InputBuf)
{
	char gw_id[200];
	mjson_find_string(InputBuf, strlen(InputBuf), "$.Gateway_ID", gw_id, sizeof(gw_id));
	FILE * fp_read = fopen("/etc/wifidog.conf", "r");
	FILE * fp_write = fopen("/etc/wifidog.conf_tmp", "a+");
	int success = 0;
	if(fp_read && fp_write)
	{
		char FileBuf[200];
		while(fgets(FileBuf, sizeof(FileBuf), fp_read))
		{
			if(MatchFunc(FileBuf, "GatewayID") != -1)
			{
				fprintf(fp_write, "GatewayID %s\n", gw_id);
				success = 1;
				continue;
			}
			else
			{
				fprintf(fp_write, "%s", FileBuf);
			}
		}
		if(!success)
		{
			fprintf(fp_write, "GatewayID %s\n", gw_id);
		}
		fclose(fp_read);
		fclose(fp_write);
		remove("/etc/wifidog.conf");
		rename("/etc/wifidog.conf_tmp", "/etc/wifidog.conf");
		return 1;
	}
	else
	{
		return 0;
	}
}
int Handle_Return_AP_Info(const char * InputBuf, int socket_fd)
{
	uint32_t AP_Traffic_Received, AP_Traffic_Transmit, AP_Gateway_ID;
	double AP_Usage_Percent;

	system("mkdir APRecord");
	system("cat /proc/stat | grep 'cpu ' /proc/stat | awk '{usage=($2+$4)*100/($2+$4+$5)} END {print usage}' > ./APRecord/cpu_usage_record");
	FILE * fp = fopen("./APRecord/cpu_usage_record", "r");
	if(!fp)
	{
		return -1;
	}
	fscanf(fp, "%lf", &AP_Usage_Percent);
	fclose(fp);

	char buf[500];
	fp = fopen("/proc/net/dev", "r");
	if(!fp)
	{
		return -1;
	}
	while(fscanf(fp, "%s", buf) == 1)
	{
		if(strncmp(buf, "eth0:", sizeof("eth0:")) == 0)
		{
			fscanf(fp, "%u %*u %*u %*u %*u %*u %*u %*u %u", &AP_Traffic_Received, &AP_Traffic_Transmit);
		}
	}
	const unsigned int KiB = 1024;
	printf("AP Received Traffic is %u(KiB)\n", AP_Traffic_Received/KiB);
	printf("AP Transmit Traffic is %u(KiB)\n", AP_Traffic_Transmit/KiB);
	printf("AP Usage Percent is %.2f\n", AP_Usage_Percent);

	char OutputBuf[1000];
        snprintf(OutputBuf, sizeof(OutputBuf), "{\n  \"Action\" : 2,\n  \"AP CPU Usage Percent\" : %.2f,\n  \"Network Received Traffic(KiB)\" : %u,\n  \"Network Transmit Traffic(KiB)\" : %u\n}\n", AP_Usage_Percent, AP_Traffic_Received/KiB, AP_Traffic_Transmit/KiB);

	return send(socket_fd, OutputBuf, strlen(OutputBuf)+1, 0);
}
int Handle_Change_Config(const char * InputBuf, int socket_fd)
{
	printf("InputBuf: %s\n", InputBuf);

	char OutputBuf[1000];
        snprintf(OutputBuf, sizeof(OutputBuf), "{\n	\"Action\" : 3");

	char Query_Config[100];
	char FileLoc[100], FileLoc_write[100];
	char ConfigCategory[100];
	char ConfigKeyword[100];
	char ConfigValue[100];
	int ConfigAppend;
	const char * Buf;
	int len;
	int counter = 1;
	int success;
	int Find_Category, Find_Keyword;
	snprintf(Query_Config, sizeof(Query_Config), "$.Config_%d", counter);
	while(mjson_find(InputBuf, strlen(InputBuf), Query_Config, &Buf, &len) == MJSON_TOK_OBJECT)
	{
		success = 0;
		snprintf(Query_Config, sizeof(Query_Config), "$.Config_%d.Config file location", counter);
		mjson_find_string(InputBuf, strlen(InputBuf), Query_Config, FileLoc, sizeof(FileLoc));
		snprintf(Query_Config, sizeof(Query_Config), "$.Config_%d.Config Category", counter);
		mjson_find_string(InputBuf, strlen(InputBuf), Query_Config, ConfigCategory, sizeof(ConfigCategory));
		snprintf(Query_Config, sizeof(Query_Config), "$.Config_%d.Config Keyword", counter);
		mjson_find_string(InputBuf, strlen(InputBuf), Query_Config, ConfigKeyword, sizeof(ConfigKeyword));
		snprintf(Query_Config, sizeof(Query_Config), "$.Config_%d.Config Value", counter);
		mjson_find_string(InputBuf, strlen(InputBuf), Query_Config, ConfigValue, sizeof(ConfigValue));

		Find_Category = Find_Keyword = 0;

		FILE * fp_read = fopen(FileLoc, "r");
		if(fp_read == NULL)
		{
			fp_read = fopen(FileLoc, "a+");
			fclose(fp_read);
			fp_read = fopen(FileLoc, "r");
		}
		snprintf(FileLoc_write, sizeof(FileLoc_write), "%s_tmp", FileLoc);
		FILE * fp_write = fopen(FileLoc_write, "a+");
		if(fp_read && fp_write)
		{
			char FileBuf[200];
			while(fgets(FileBuf, sizeof(FileBuf), fp_read))
			{
				printf("1: %s\n", FileBuf);
				fprintf(fp_write, "%s", FileBuf);
				if(MatchFunc(FileBuf, ConfigCategory) != -1)
				{
					Find_Category = 1;
					while(fgets(FileBuf, sizeof(FileBuf), fp_read))
					{
						if(MatchFunc(FileBuf, "config") != -1 && !Find_Keyword)
						{
							printf("2: %s %s %s\n", FileBuf, ConfigKeyword, ConfigValue);

							fprintf(fp_write, "	%s %s\n", ConfigKeyword, ConfigValue);
							fprintf(fp_write, "%s", FileBuf);
							success = 1;
							continue;
						}
						if(MatchFunc(FileBuf, ConfigKeyword) != -1 && !Find_Keyword)
						{
							Find_Keyword = 1;
							printf("3: %s %s %s\n", ConfigCategory, ConfigKeyword, ConfigValue);

							fprintf(fp_write, "	%s %s\n", ConfigKeyword, ConfigValue);
							success = 1;
							continue;
						}
						fprintf(fp_write, "%s", FileBuf);
					}
					if(!Find_Keyword)
					{
						printf("4: %s %s\n", ConfigKeyword, ConfigValue);
						fprintf(fp_write, "	%s %s\n", ConfigKeyword, ConfigValue);
					}
				}
			}
			if(!Find_Category)
			{
				printf("5: %s %s %s\n", ConfigCategory, ConfigKeyword, ConfigValue);
				fprintf(fp_write, "%s\n", ConfigCategory);
				fprintf(fp_write, "	%s %s\n", ConfigKeyword, ConfigValue);
			}

			fclose(fp_read);
			fclose(fp_write);
			remove(FileLoc);
			rename(FileLoc_write, FileLoc);
		}
		else
		{
			printf("[JSON_request_handle.c] %s open error\n", FileLoc);
		}
		char ConCat[1000];
		snprintf(ConCat, sizeof(ConCat), "%s,\n	\"Config_%d\" : %d", OutputBuf, counter, success);
		strncpy(OutputBuf, ConCat, sizeof(OutputBuf));
		

		counter++;
		snprintf(Query_Config, sizeof(Query_Config), "$.Config_%d", counter);
		printf("Query_config : %s\n", Query_Config);
	}
	char ConCat[1000];
	snprintf(ConCat, sizeof(ConCat), "%s\n}\n", OutputBuf, counter, success);
	strncpy(OutputBuf, ConCat, sizeof(OutputBuf));
	printf("%s", OutputBuf);
	return send(socket_fd, OutputBuf, strlen(OutputBuf)+1, 0);
}

int Handle_Download_Config(const char * InputBuf, int socket_fd)
{
	char FileName[50];
	printf("InputBuf: %s\n", InputBuf);
	mjson_find_string(InputBuf, strlen(InputBuf), "$.Config Archive File Name", FileName, sizeof(FileName));

	char FTPServerAddress[100];
	char UserName[50];
	char Password[50];
	char FTPFile[500];
	char Config_Extract_Loc[100];

	ConfigQuery ConfigBuf;
	ConfigBuf = Load_Config_String("./config/connect_config", "FTP_Server_Address", FTPServerAddress, sizeof(FTPServerAddress));
	printf("Downloaded Filename: %s\n", FileName);

	if(ConfigBuf.DataType != 2)
	{
		puts("No proper config");
		return -1;
	}
	snprintf(FTPFile, sizeof(FTPFile), "ftp://%s/%s", FTPServerAddress, FileName);

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

	DownloadSettingPackage(FTPFile, UserName, Password, FileName);

	ConfigBuf = Load_Config_String("./config/connect_config", "Config_Extract_Location", Config_Extract_Loc, sizeof(Config_Extract_Loc));
	if(ConfigBuf.DataType != 2)
	{
		puts("No proper config");
		return -1;
	}

	char Command_To_Extract[200];
	snprintf(Command_To_Extract, sizeof(Command_To_Extract), "tar -xvzf %s -C %s", FileName, Config_Extract_Loc);
	system("mkdir testdir");
	printf("Command: %s\n", Command_To_Extract);
	system(Command_To_Extract);

	int Applied = 1;

	char OutputBuf[1000];
        snprintf(OutputBuf, sizeof(OutputBuf), "{\n  \"Action\" : 7,\n  \"Applied\" : %d\n}\n", Applied);
	return send(socket_fd, OutputBuf, strlen(OutputBuf)+1, 0);
}
