#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utility.h"
void RecordLog(const char * message)
{
	time_t cur_time = time(NULL);
	char CurrentPath[200];
	char RecordPath[200];
	getcwd(CurrentPath, sizeof(CurrentPath));
	snprintf(RecordPath, sizeof(RecordPath), "%s/Record.log", CurrentPath);
	
	FILE * fp = fopen(RecordPath, "a");
	fseek(fp, 0L, SEEK_END);
	long int sz = ftell(fp);
	//if log is larget than 512KiB, then create new one
	if(sz >= 1024*512)
	{
		fclose(fp);
		fp = fopen(RecordPath, "w");
	}
	rewind(fp);
	char timestr[200];
	strncpy(timestr, ctime(&cur_time), sizeof(timestr)-1);
	int len = strlen(timestr);
	if(timestr[len-1] == '\n')
	{
		timestr[len-1] = 0;
	}
	printf("[%s] %s\n", timestr, message);
	fprintf(fp, "[%s] %s\n", timestr, message);
	fclose(fp);
}
int GetGatewayID()
{
	int gw_id;
	char logText[500];
	int success = -1;
	FILE * fp_read = fopen("/etc/wifidog.conf", "r");
	if(fp_read)
	{
		char FileBuf[200];
		while(fgets(FileBuf, sizeof(FileBuf), fp_read))
		{
			if(MatchFunc(FileBuf, "GatewayID") != -1)
			{
				sscanf(FileBuf, "%*s %d", &gw_id);
				success = 1;
				continue;
			}
		}
		fclose(fp_read);
		if(success == 1)
		{
			snprintf(logText, sizeof(logText), "[%s] get gateway id successed", __FILE__);
			RecordLog(logText);
			return gw_id;
		}
		else
		{
			snprintf(logText, sizeof(logText), "[%s] get gateway id failed, can't find GatewayID in /etc/wifidog.conf", __FILE__);
			RecordLog(logText);
			return -1;
		}
	}
	else
	{
		snprintf(logText, sizeof(logText), "[%s] get gateway id failed, can't open /etc/wifidog.conf", __FILE__);
		RecordLog(logText);
		return -1;
	}
}
