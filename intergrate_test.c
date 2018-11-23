#include <stdio.h>
#include "update.h"
int main()
{
	DownloadSettingPackage("ftp://35.221.194.17/ftptest.txt", "uftp", "seg1", "here.txt");
	UploadSettingPackage("ftp://35.221.194.17/ggwp.c", "uftp", "seg1", "main.c");
}
