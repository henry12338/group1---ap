#include <stdio.h>
#include <sys/socket.h>
int main()
{
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_fd == -1)
	{
		puts("Socket Creation Failure");
	}
}
