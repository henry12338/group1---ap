#include "JSON_request_handle.h"
#include "mjson.h"
#include <stdint.h>
#include <string.h>
#include <sys/socket.h>

int Handle_Action(const char * InputBuf, int socket_fd)
{
	double action = mjson_find_number(InputBuf, strlen(InputBuf), "$.Action", -1);
	printf("Go To Action %d\n", (int)action);
	if(action == 2)
	{
		return Handle_Return_AP_Info(InputBuf, socket_fd);
	}
	else if(action == 5)
	{
		return Handle_Send_Connected_User_Number(InputBuf, socket_fd);
	}
	else if(action == 6)
	{
		return Handle_Send_User_Info(InputBuf, socket_fd);
	}
	else if(action == 8)
	{
		return Handle_Download_Config(InputBuf, socket_fd);
	}
	else
	{
		return -1;
	}
}
int Handle_Return_AP_Info(const char * InputBuf, int socket_fd)
{
	double AP_Number = mjson_find_number(InputBuf, strlen(InputBuf), "$.AP Number", -1);
	uint32_t AP_Temperature, AP_Device_Amount, AP_Traffic;
	double AP_Usage_Percent;

	//go get the infoooooo
	printf("AP Number is %u\n", (uint32_t)AP_Number);
	printf("AP Temperature is %u\n", AP_Temperature);
	printf("AP Connected Device Amount is %u\n", AP_Device_Amount);
	printf("AP Traffic is %u(KiB)\n", AP_Traffic);
	printf("AP Usage Percent is %.2f\n", AP_Usage_Percent);


	char OutputBuf[1000];
        const int length = 1000;
        snprintf(OutputBuf, length, "{\n  \"Action\" :2,\n  \"AP Number\" : %u,\n  \"AP CPUT temperature(Celcius)\" : %u,\n  \"AP CPU Usage Percent\" :%.2f,\n  \"Connect Device Amount\" :%u,\n  \"Network Traffic(KiB)\" : %u\n}\n", (uint32_t)AP_Number, AP_Temperature, AP_Usage_Percent, AP_Device_Amount, AP_Traffic);
	return send(socket_fd, OutputBuf, strlen(OutputBuf)+1, 0);
}
int Handle_Send_Connected_User_Number(const char * InputBuf, int socket_fd)
{
	double AP_Number = mjson_find_number(InputBuf, strlen(InputBuf), "$.AP Number", -1);
	uint32_t Connected_User_Number;

	printf("AP Number is %u\n", (uint32_t)AP_Number);
	//go get the infoooooo
	printf("AP Connected Device Amount is %u\n", Connected_User_Number);


	char OutputBuf[1000];
        const int length = 1000;
        snprintf(OutputBuf, length, "{\n  \"Action\" : 5,\n  \"AP Number\" : %u,\n  \"Connected User Number\" : %u\n}\n", (uint32_t)AP_Number,Connected_User_Number);
	return send(socket_fd, OutputBuf, strlen(OutputBuf)+1, 0);

}
int Handle_Send_User_Info(const char * InputBuf, int socket_fd)
{
	char User_External_IP[20], Username[100];
	double AP_Number = mjson_find_number(InputBuf, strlen(InputBuf), "$.AP Number", -1);
	printf("AP Number is %u\n", (uint32_t)AP_Number);

	printf("User's External IP is %s\n", User_External_IP);
	printf("Username is %s\n", Username);

	char OutputBuf[1000];
        const int length = 1000;
        snprintf(OutputBuf, length, "{\n  \"Action\" : 6,\n  \"AP Number\" : %u,\n  \"User Out IP\" : %s,\n  \"Username\" : %s\n}\n", (uint32_t)AP_Number, User_External_IP, Username);
	return send(socket_fd, OutputBuf, strlen(OutputBuf)+1, 0);
}
int Handle_Download_Config(const char * InputBuf, int socket_fd)
{
	char Config_Location[200];
	printf("Config Archive Location is in %s\n", Config_Location);

	char OutputBuf[1000];
        const int length = 1000;
        snprintf(OutputBuf, length, "{\n  \"Action\" : 8,\n  \"Config Archive Location\" : %s\n}\n", Config_Location);
	return send(socket_fd, OutputBuf, strlen(OutputBuf)+1, 0);
}
