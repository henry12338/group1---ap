all: main.c update.o JSON_action.o config.o update_local.o JSON_action_local.o config_local.o
	mipsel-openwrt-linux-gcc -std=c99 -I./include main.c update.o JSON_action.o config.o -o ap_client
	gcc -std=c99 -I./include main.c update_local.o JSON_action_local.o config_local.o -o ap_client_local
	rm *.o
update.o: update.c
	mipsel-openwrt-linux-gcc -std=c99 -I./include -c update.c -o update.o
	gcc -std=c99 -I./include -c update.c -o update_local.o
JSON_action.o: JSON_action.c
	mipsel-openwrt-linux-gcc -std=c99 -I./include -c JSON_action.c -o JSON_action.o
	gcc -std=c99 -I./include -c JSON_action.c -o JSON_action_local.o
config.o: config.c
	mipsel-openwrt-linux-gcc -std=c99 -I./include -c config.c -o config.o
	gcc -std=c99 -I./include -c config.c -o config_local.o

SELF_DIR := ${CURDIR}
