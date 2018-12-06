#include <stdio.h>
#include "update.h"
#include <time.h>
#include "JSON_request_handle.h"
#include "JSON_action.h"
int main()
{
	int state = -1;
	time_t cur_time = time(NULL);
	printf("Cur Time: %s\n", ctime(&cur_time));


	/*
{
	"Action" : 3,
	"Config_1":
	{
		"Config file location" : "/etc/config/wireless",
		"Config Category" : "config wifi-iface",
		"Config Keyword" : "option ssid",
		"Config Value":"SSID_Edge"
	},
	"Config_2":
	{
		"Config file location" : "/etc/config/wireless",
		"Config Category" : "config wifi-test",
		"Config Keyword" : "option ggwp",
		"Config Value" : "thks"
	},
	"Config_3":
	{
		"Config file location" : "/etc/config/wireless",
		"Config Category" : "config wifi-test",
		"Config Keyword" : "option damn",
		"Config Value" : ""
	}
}
	*/
	Handle_Action("{\"Action\" : 3,\"Config_1\":{\"Config file location\" : \"/etc/config/wireless\",\"Config Category\" : \"config wifi-iface\",\"Config Keyword\" : \"option ssid\",\"Config Value\":\"SSID_Edge\"},\"Config_2\":{\"Config file location\" : \"/etc/config/wireless\",\"Config Category\" : \"config wifi-test\",\"Config Keyword\" : \"option ggwp\",\"Config Value\":\"thks\"},\"Config_3\":{\"Config file location\" : \"/etc/config/wireless\",\"Config Category\" : \"config wifi-test\",\"Config Keyword\" : \"option damn\",\"Config Value\":\"\"}}", 0, &state);

	Handle_Action("{\n	\"Action\" : 1,\n	\"Gateway_ID\" : \"1234\"\n}\n", 0, &state);

	//Handle_Action("{\n	\"Action\" : 1,\n	\"Gateway_ID\" : \"1234\"\n}\n", 0, &state);





	char OutputBuf[1000];
	//Handle_Action("{\n	\"Action\" : 7,\n	\"Config Archive File Name\" : \"helloworld.tar.gz\"\n}\n", 0, &state);
	//Request_Upload_Config("Test content", OutputBuf, sizeof(OutputBuf));
	//DownloadSettingPackage("ftp://35.221.194.17/ggwp.c", "uftp", "seg1", "ggwp.c");
	//UploadSettingPackage("ftp://35.221.194.17/helloworld.tar.gz", "uftp", "seg1", "helloworld.tar.gz");
}
