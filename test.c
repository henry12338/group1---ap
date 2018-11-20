#include <stdio.h>
#include <string.h>
#include "JSON_request_handle.h"
int main()
{
	char InputBuf[1000];
	strcpy(InputBuf, "{\n	\"Action\" : 2,\n	\"AP Number\" : 4\n}\n");
	Handle_Action(InputBuf, 0);
	printf("%s\n", InputBuf);
}
