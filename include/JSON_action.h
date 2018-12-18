#ifndef JSON_ACTION_H
	#define JSON_ACTION_H
	#include <stdint.h>

	/* AP Query Controller if Controller is alive
		Param:
	
		OutputBuf is the string to save JSON content
		length is OutputBuf's maximum length

		Return value:
		0 if the OutputBuf cannot contain large data
		1 if success
	*/
	int Request_Controller_Alive(char * OutputBuf, int length);

	/* AP Prompt Controller to register AP
		Param:
	
		OutputBuf is the string to save JSON content
		length is OutputBuf's maximum length

		Return value:
		0 if the OutputBuf cannot contain large data
		1 if success
	*/
	int Request_Register_AP(char * OutputBuf, int length);

	//---------Response------------
	//Response will let JSON_request_handle.c to handle
#endif
