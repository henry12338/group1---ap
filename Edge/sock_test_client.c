#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
int main()
{
	char ip_address[100] = "35.189.168.208";
	int port = 27015;
//	scanf("%s", ip_address);
//	scanf("%d", &port); // 27000


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
	printf("Send Message: ");
	while(fgets(send_buf, sizeof(send_buf), stdin))
	{
		send_fail = send(socket_fd, send_buf, sizeof(send_buf), 0);
		printf("Send Message %s to %s", send_buf, ip_address);
		if(send_fail == -1)
		{
			printf("Send Message %s fail\n", send_buf);
			return -3;
		}
		recv(socket_fd, recv_buf, sizeof(recv_buf), 0);
		printf("Receive: %s\n", recv_buf);
		printf("Send Message: ");
	}
	shutdown(socket_fd, 2);
}
