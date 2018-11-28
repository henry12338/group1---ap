#include "help.h"
#include <stdio.h>
void Helper()
{
	printf("send <action> [content] \n");
	printf("	action = \n");
	printf("	0 		: Check if controller is alive\n"); 
	printf("	1 		: Register AP\n"); 
	printf("	6 [content] 	: Upload update file with content as description\n"); 
}
