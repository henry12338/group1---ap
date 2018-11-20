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


int main()
{
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = PF_INET;
	serveraddr.sin_addr.s_addr = INADDR_ANY;
	serveraddr.sin_port = htons(27015);
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	int yes = 1;
	setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
	if(socket_fd == -1)
	{
		puts("Socket Creation Failure");
		return -1;
	}
	int bind_fail = bind(socket_fd, (struct sockaddr *) &serveraddr, sizeof(serveraddr));
	if(bind_fail == -1)
	{
		puts("Socket Bind Failure");
		printf("%s\n", strerror(errno));
		return -2;
	}

	int listen_fail = listen(socket_fd, 10);
	if(listen_fail == -1)
	{
		puts("Socket listen Failure");
		return -3;
	}
	struct sockaddr_in clientaddr;
	int clientsocket_fd;
	size_t addr_len = sizeof(clientaddr);
	clientsocket_fd = accept(socket_fd, (struct sockaddr *) &clientaddr, &addr_len);
	printf("Client IP is %s\n", inet_ntoa(clientaddr));
	char recv_buf[1000];
	char send_buf[1000];
	int send_fail;
	fd_set read_fd;
	while(1)
	{
		FD_ZERO(&read_fd);
		FD_SET(clientsocket_fd, &read_fd);
		FD_SET(STDIN_FILENO, &read_fd);
		struct timeval tv;
		tv.tv_sec = 5;
		tv.tv_usec = 0;
		if(select(clientsocket_fd + 1, &read_fd, NULL, NULL, &tv) < 0)
		{
			puts("select() fail");
			break;
		}
		if(FD_ISSET(clientsocket_fd, &read_fd))
		{
			if(recv(clientsocket_fd, recv_buf, 1000, 0) > 0)
			{
			        printf("Receive from client: %s\n", recv_buf);
			}
			else
			{
				printf("Receive Fail, client close\n");
				break;
			}
		}
		if(FD_ISSET(STDIN_FILENO, &read_fd))
		{
			scanf("%s", send_buf);
			printf("Send Message: %s\n", send_buf);
			if(strcmp(send_buf, "Shut the fuck up\n") == 0)
			{
				break;
			}
			send_fail = send(clientsocket_fd, send_buf, strlen(send_buf)+1, 0);
			if(send_fail == -1)
			{
				printf("Send Fail\n");
				break;
			}
		}
	}
	close(clientsocket_fd);
	close(socket_fd);
	return -1;
}
