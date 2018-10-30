#ifndef JSON_ACTION_H
	#define JSON_ACTION_H
	#include <stdint.h>
	int Request_Controller_Alive(char * OutputBuf);
	int Request_Register_AP(const char * ip, char * OutputBuf);
	int Request_Return_AP_Info(uint32_t AP_Number, char * OutputBuf);
	int Request_User_IsRegistered(const char * Username, char * OutputBuf);
	int Request_Check_User_Password(const char * Hashed_Password, char * OutputBuf);
	int Request_Send_User_Info(uint32_t AP_Number, char * OutputBuf);
	int Request_Upload_Config(uint32_t AP_Number, const char * ConfigLocation, char * OutputBuf);
	int Request_Download_Config(const char * ConfigLocation, char * OutputBuf);

	int Response_Controller_Alive(char * OutputBuf);
	int Response_Register_AP(uint32_t AP_Number, char * OutputBuf);
	int Response_Return_AP_Info(uint32_t AP_Number, char * OutputBuf, uint32_t AP_Temperature, double AP_Usage_Percent, uint32_t AP_Device_Amount, uint32_t AP_Traffic);
	int Response_User_IsRegistered(int IsRegistered, char * OutputBuf);
	int Response_Check_User_Password(int CheckPassword, char * OutputBuf);
	int Response_Send_User_Info(const char * ip, const char *Username, char * OutputBuf);
	int Response_Upload_Config(uint32_t AP_Number, const char * ConfigLocation, char * OutputBuf);
	int Response_Download_Config(const char * ConfigLocation, char * OutputBuf);
#endif