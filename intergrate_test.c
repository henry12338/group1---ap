#include <stdio.h>
#include "update.h"
#include <time.h>
#include "JSON_request_handle.h"
#include "JSON_action.h"
int main()
{
	time_t cur_time = time(NULL);
	printf("Cur Time: %s\n", ctime(&cur_time));

	Handle_Action("{\n	\"Action\" : 7,\n	\"Config Archive File Name\" : \"helloworld.tar.gz\"\n}\n", 0);
	Handle_Action("{\"Action\" : 3,\"Config_1\":{\"Config file location\" : \"/etc/testconfig\",\"Config Category\" : \"config wifi-iface\",\"Config Keyword\" : \"option ssid\",\"Config Value\":\"SSID_Edge\"},\"Config_2\":{\"Config file location\" : \"/etc/testconfig\",\"Config Category\" : \"config wifi-test\",\"Config Keyword\" : \"option ggwp\",\"Config Value\":\"thks\"}}", 0);
	char OutputBuf[1000];
	Request_Upload_Config(OutputBuf, sizeof(OutputBuf));
	//DownloadSettingPackage("ftp://35.221.194.17/ggwp.c", "uftp", "seg1", "ggwp.c");
	//UploadSettingPackage("ftp://35.221.194.17/helloworld.tar.gz", "uftp", "seg1", "helloworld.tar.gz");
}