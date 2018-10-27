#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <errno.h>

#include "config.h"
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
	char recv_buf[1000];
	int send_fail;
	while(fgets(send_buf, sizeof(send_buf), stdin))
	{
		//send and recv simultaneously
		fd_set read_fd, write_fd;
		struct timeval tv;
		tv.tv_sec = 0;
		tv.tv_usec = 0;
		FD_ZERO(&read_fd);
		FD_ZERO(&write_fd);		
		FD_SET(socket_fd, &read_fd);
		//FD_SET( socket_fd, &write_fd);
		FD_SET(0, &write_fd);
		
		if(select(socket_fd+1, &read_fd, &write_fd, NULL, &tv) < 0)
		{
			puts("select() failed");
			return -4;
		}
		if(FD_ISSET(socket_fd, &read_fd))
		{
			recv(socket_fd, recv_buf, 1000, 0);
			printf("Received result from server = %s\n", recv_buf);
		}
		if( FD_ISSET( 0, &write_fd)) {
			fgets(send_buf, sizeof(send_buf), stdin);
			send_fail = send(socket_fd, send_buf, strlen(send_buf), 0);
			printf("-------------Sent %d bytes to server--------------\n", send_buf);
		}
	}
	shutdown(socket_fd, 2);
}
