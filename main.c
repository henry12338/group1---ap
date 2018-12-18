#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>

#include "JSON_action.h"
#include "JSON_request_handle.h"
#include "config.h"
#include "update.h"
#include "help.h"
#include "utility.h"
int main(int argc, char ** argv)
{
	char logText[500];
	char ip_address[100] = {};
	char DNS_address[200] = {};
	ConfigQuery ConfigBuf;
	char ConfigPath[200];
	char CurrentPath[200];
	getcwd(CurrentPath, sizeof(CurrentPath));
	snprintf(ConfigPath, sizeof(ConfigPath), "%s/config/connect_config", CurrentPath);
	ConfigBuf = Load_Config_String(ConfigPath, "IP_Address", ip_address, sizeof(ip_address));
	if(ConfigBuf.DataType == -1)
	{
		ConfigBuf = Load_Config_String(ConfigPath, "DNS_Address", DNS_address, sizeof(DNS_address));
		if(ConfigBuf.DataType == -1)
		{
			snprintf(logText, sizeof(logText), "[%s] No proper config", __FILE__);
			RecordLog(logText);
			return -3;
		}
		snprintf(logText, sizeof(logText), "[%s] Load DNS: %s", __FILE__, DNS_address);
		RecordLog(logText);
		struct hostent* HostInfo;

		/* get IP address from name */
		HostInfo = gethostbyname(DNS_address);

		if(!HostInfo)
		{
			snprintf(logText, sizeof(logText), "[%s] Could not resolve host name", __FILE__);
			RecordLog(logText);
			return -10;
		}
		sprintf(ip_address, "%hhu.%hhu.%hhu.%hhu", HostInfo->h_addr_list[0][0], HostInfo->h_addr_list[0][1], HostInfo->h_addr_list[0][2], HostInfo->h_addr_list[0][3]);
	}
	else
	{
		snprintf(logText, sizeof(logText), "[%s] Load IP: %s", __FILE__, ip_address);
		RecordLog(logText);
	}
	ConfigBuf = Load_Config_IntData(ConfigPath, "Port");
	int port = ConfigBuf.IntData;
	snprintf(logText, sizeof(logText), "[%s] Load Port: %d", __FILE__, port);
	RecordLog(logText);


	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = PF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(ip_address);
	serveraddr.sin_port = htons(port);

	while(1)
	{
		int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
		if(socket_fd == -1)
		{
			snprintf(logText, sizeof(logText), "[%s] Socket Creation Failure", __FILE__);
			RecordLog(logText);
			return -1;
		}
		int connect_fail = connect(socket_fd, (struct sockaddr *) &serveraddr, sizeof(serveraddr));
		while(connect_fail == -1)
		{
			sleep(2);			
			connect_fail = connect(socket_fd, (struct sockaddr *) &serveraddr, sizeof(serveraddr));
			snprintf(logText, sizeof(logText), "[%s] Trying to connect to %s...", __FILE__, ip_address);
			RecordLog(logText);
			fflush(stdout);
		}
		snprintf(logText, sizeof(logText), "[%s] Connected to %s", __FILE__, ip_address);
		RecordLog(logText);


		char send_buf[1000];
		char send_buf_buf[1000];

		char command[1000];
		char recv_buf[1000];
		int send_fail;
		fd_set read_fd;
		int action;
		int Controller_State = -1;

		int Message_pop = 0;


		ConfigBuf = Load_Config_Character(ConfigPath, "AP_Registered");

		if(ConfigBuf.DataType == -1)
		{
			snprintf(logText, sizeof(logText), "[%s] Can't know whether this AP is registered, please check config.", __FILE__);
			RecordLog(logText);
			return -11;
		}
		if(ConfigBuf.CharacterData == '0')
		{
			snprintf(logText, sizeof(logText), "[%s] Trying to register AP", __FILE__);
			RecordLog(logText);
			if(Request_Register_AP(send_buf, 1000) == 1)
			{
				sprintf(send_buf_buf, "%s", send_buf);
				snprintf(logText, sizeof(logText), "[%s] Send Action 1 to server.", __FILE__);
				RecordLog(logText);
				printf("%s", send_buf_buf);
			}
			send_fail = send(socket_fd, send_buf_buf, strlen(send_buf_buf)+1, 0);
			if(send_fail < 0)
			{
				snprintf(logText, sizeof(logText), "[%s] Send JSON Failed.", __FILE__);
				RecordLog(logText);
			}
		}
		else
		{
			snprintf(logText, sizeof(logText), "[%s] AP is registered.", __FILE__);
			RecordLog(logText);
		}
		while(1)
		{
			if(!Message_pop)
			{
				printf("Enter Command (h for help)...>");
				fflush(stdout);
			}
			Message_pop = 1;

			struct timeval tv;
			tv.tv_sec = 2;
			tv.tv_usec = 0;
			FD_ZERO(&read_fd);		
			FD_SET(socket_fd, &read_fd);
			FD_SET(STDIN_FILENO, &read_fd);
			if(select(socket_fd+1, &read_fd, NULL, NULL, &tv) <= 0)
			{
			}
			if(FD_ISSET(STDIN_FILENO, &read_fd))
			{
/*
				scanf("%s", command);
				if(strncmp(command, "h", strlen("h")) == 0)
				{
					Helper();
				}
				else if(strncmp(command, "send", strlen("send")) == 0)
				{
					scanf("%d", &action);
					if(action == 0)
					{
						if(Request_Controller_Alive(send_buf, 1000) == 1)
						{
							snprintf(send_buf_buf, sizeof(send_buf_buf), "%s", send_buf);
							snprintf(logText, sizeof(logText), "[%s] Send Action 0 to server.", __FILE__);
							RecordLog(logText);
						}
					}
					else
					{
						snprintf(logText, sizeof(logText), "[%s] Invalid action.", __FILE__);
						RecordLog(logText);
					}
					send_fail = send(socket_fd, send_buf_buf, strlen(send_buf_buf)+1, 0);
					if(send_fail < 0)
					{
						snprintf(logText, sizeof(logText), "[%s] Send JSON Failed.", __FILE__);
						RecordLog(logText);
						break;
					}
				}
				else
				{
					snprintf(logText, sizeof(logText), "[%s] Invalid command.", __FILE__);
					RecordLog(logText);
				}
				Message_pop = 0;
*/
			}
			if(FD_ISSET(socket_fd, &read_fd))
			{
				if(recv(socket_fd, recv_buf, 1000, 0) > 0)
				{
					puts("");
					snprintf(logText, sizeof(logText), "[%s] Received JSON from server:\n%s", __FILE__, recv_buf);
					RecordLog(logText);
					Handle_Action(recv_buf, socket_fd, &Controller_State);
				}
				else
				{
					puts("");
					snprintf(logText, sizeof(logText), "[%s] Server Disconnect", __FILE__);
					RecordLog(logText);
					break;
				}
				Message_pop = 0;
			}
		}
		close(socket_fd);

	}
}
