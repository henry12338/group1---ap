#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

int main()
{
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = PF_INET;
	serveraddr.sin_addr.s_addr = INADDR_ANY;
	serveraddr.sin_port = htons(27015);
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
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
	int addr_len = sizeof(clientaddr);
	clientsocket_fd = accept(socket_fd, (struct sockaddr *) &clientaddr, &addr_len);		
	char recv_buffer[1000];
	char send_buf[1000];
	int send_fail;
	while(1)
	{
		recv(clientsocket_fd, recv_buffer, sizeof(recv_buffer), 0);
	        printf("Get: %s\n", recv_buffer);
		printf("Send Message: ");
		fgets(send_buf, sizeof(send_buf), stdin);
		if(strcmp(send_buf, "Shut the fuck up\n") == 0)
		{
			break;
		}
		send_fail = send(clientsocket_fd, send_buf, sizeof(send_buf), 0);
		if(send_fail == -1)
		{
			printf("Send Fail\n");
		}
		printf("Send %s\n", send_buf);
	}
	shutdown(clientsocket_fd, 2);
	shutdown(socket_fd, 2);
}
