read -p "Press any key to continue" var
sshpass -p 'root' ssh -p 22 root@192.168.1.251 "echo ap_client:2345:respawn:/root/ap_client >> /etc/inittab"

var=1

