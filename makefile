all: main.c update.o JSON_action.o JSON_request_handle.o config.o update_local.o help.o CheckFile.o JSON_action_local.o config_local.o JSON_request_handle_local.o help_local.o CheckFile_local.o
	mipsel-openwrt-linux-gcc -std=c99 -I./include main.c update.o JSON_action.o JSON_request_handle.o config.o help.o CheckFile.o -Wl,-rpath-link=$(TOOLCHAIN_DIR)lib -lcurl -o ap_client
	gcc -std=c99 -I./include main.c update_local.o JSON_action_local.o JSON_request_handle_local.o config_local.o help_local.o CheckFile_local.o -lcurl -o ap_client_local
#	gcc -std=c99 -I./include test.c JSON_request_handle_local.o -lcurl -o testpro
	gcc -std=c99 -I./include intergrate_test.c JSON_action_local.o JSON_request_handle_local.o config_local.o update_local.o CheckFile_local.o -lcurl -o intergrate_test
	mipsel-openwrt-linux-gcc -std=c99 -I./include intergrate_test.c JSON_action.o JSON_request_handle.o config.o update.o CheckFile.o -Wl,-rpath-link=$(TOOLCHAIN_DIR)lib -lcurl -o intergrate_test_ap
	rm *.o
update.o: update.c
	mipsel-openwrt-linux-gcc -std=c99 -I./include -c update.c -o update.o
	gcc -std=c99 -I./include -c update.c -o update_local.o
JSON_action.o: JSON_action.c CheckFile.o
	mipsel-openwrt-linux-gcc -std=c99 -I./include -c JSON_action.c -o JSON_action.o
	gcc -std=c99 -I./include -c JSON_action.c -o JSON_action_local.o
config.o: config.c
	mipsel-openwrt-linux-gcc -std=c99 -I./include -c config.c -o config.o
	gcc -std=c99 -I./include -c config.c -o config_local.o
JSON_request_handle.o: JSON_request_handle.c
	mipsel-openwrt-linux-gcc -std=c99 -I./include -c JSON_request_handle.c  -o JSON_request_handle.o
	gcc -std=c99 -I./include -c JSON_request_handle.c  -o JSON_request_handle_local.o
help.o: help.c
	mipsel-openwrt-linux-gcc -std=c99 -I./include -c help.c  -o help.o
	gcc -std=c99 -I./include -c help.c  -o help_local.o
CheckFile.o: CheckFile.c
	mipsel-openwrt-linux-gcc  -I./include -c CheckFile.c  -o CheckFile.o
	gcc -I./include -c CheckFile.c  -o CheckFile_local.o

TOOLCHAIN_DIR := /home/se-group1/openwrt_toolchain/OpenWrt-Toolchain-ramips-mt7628_gcc-4.8-linaro_uClibc-0.9.33.2.Linux-i686/toolchain-mipsel_24kec+dsp_gcc-4.8-linaro_uClibc-0.9.33.2/
