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
#include "config.h"
#include "update.h"
int main()
{
	char ip_address[100] = {};
	char DNS_address[200] = {};
	ConfigQuery ConfigBuf;
	ConfigBuf = Load_Config_String("./config/connect_config", "IP_Address");
	if(ConfigBuf.DataType == -1)
	{
		ConfigBuf = Load_Config_String("./config/connect_config", "DNS_Address");
		if(ConfigBuf.DataType == -1)
		{
			puts("No proper config");
			return -3;
		}
		strcpy(DNS_address, ConfigBuf.StringData);
		printf("Load DNS: %s\n", DNS_address);
		struct hostent* HostInfo;

		/* get IP address from name */
		HostInfo = gethostbyname(DNS_address);

		if(!HostInfo)
		{
		    printf("Could not resolve host name\n");
		    return -10;
		}
		sprintf(ip_address, "%hhu.%hhu.%hhu.%hhu", HostInfo->h_addr_list[0][0], HostInfo->h_addr_list[0][1], HostInfo->h_addr_list[0][2], HostInfo->h_addr_list[0][3]);
	}
	else
	{
		strcpy(ip_address, ConfigBuf.StringData);
		printf("Load IP: %s\n", ip_address);
	}
	ConfigBuf = Load_Config_IntData("./config/connect_config", "Port");
	int port = ConfigBuf.IntData;
	printf("Load Port: %d\n", port);


	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = PF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(ip_address);
	serveraddr.sin_port = htons(port);

	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_fd == -1)
	{
		puts("Socket Creation Failure");
		return -1;
	}
	int connect_fail = connect(socket_fd, (struct sockaddr *) &serveraddr, sizeof(serveraddr));
	if(connect_fail == -1)
	{
		printf("Connect to %s fail\n", ip_address);
		return -2;
	}
	char send_buf[1000];
	char send_buf_buf[1000];
	char recv_buf[1000];
	int send_fail;
	fd_set read_fd;
	int action;
	while(1)
	{
		struct timeval tv;
		tv.tv_sec = 5;
		tv.tv_usec = 0;
		FD_ZERO(&read_fd);		
		FD_SET(socket_fd, &read_fd);
		FD_SET(STDIN_FILENO, &read_fd);
		if(select(socket_fd+1, &read_fd, NULL, NULL, &tv) <= 0)
		{
			puts("select field failed");
			break;
		}
		if(FD_ISSET(STDIN_FILENO, &read_fd))
		{
			scanf("%d", &action);
			if(action == 0)
			{
				if(Request_Controller_Alive(send_buf) == 1)
				{
					sprintf(send_buf_buf, "%s", send_buf);
					printf("Send JSON to server:\n");				
					printf("%s", send_buf_buf);
				}
			}
			else if(action == 1)
			{
				
			}
			send_fail = send(socket_fd, send_buf_buf, strlen(send_buf_buf)+1, 0);
			if(send_fail < 0)
			{
				printf("Send JSON Failed\n");
				break;
			}
		}
		if(FD_ISSET(socket_fd, &read_fd))
		{
			if(recv(socket_fd, recv_buf, 1000, 0) > 0)
			{
				printf("Received result from server = %s\n", recv_buf);
			}
			else
			{
				break;
			}
		}
	}
	close(socket_fd);
}
