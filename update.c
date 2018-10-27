#include <stdio.h>
#include <stdlib.h>
#include "update.h"
void UpdateAllPackage()
{
	system("opkg update; opkg upgrade;");
}
