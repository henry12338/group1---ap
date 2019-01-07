#upload AP program and wifidog.conf
sshpass -p 'root' ssh -p 22 root@192.168.1.251 'mkdir config'

sshpass -p 'root' scp -r ./config/* root@192.168.1.251:./config

sshpass -p 'root' scp ./ap_client root@192.168.1.251:

sshpass -p 'root' scp ./wifidog.conf root@192.168.1.251:/etc/wifidog.conf

sshpass -p 'root' ssh -p 22 root@192.168.1.251 '/etc/init.d/wifidog enable'

sshpass -p 'root' ssh -p 22 root@192.168.1.251 '/etc/init.d/wifidog start'

echo "updated AP program, now run AP program"
#set ap_client to run when booted, run ap_client
sshpass -p 'root' scp ./APClient root@192.168.1.251:/etc/init.d
sshpass -p 'root' scp ./autorestart.sh root@192.168.1.251:/root
sshpass -p 'root' ssh -p 22 root@192.168.1.251 "chmod +x /etc/init.d/APClient;chmod +x /root/autorestart.sh"
sshpass -p 'root' ssh -p 22 root@192.168.1.251 '/etc/init.d/APClient enable'
sshpass -p 'root' ssh -p 22 root@192.168.1.251 'reboot'

