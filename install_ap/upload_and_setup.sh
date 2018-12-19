#divide vlan to one for internal network, one for external network
sshpass -p 'root' ssh -p 22 root@192.168.1.251 'uci set network.@switch_vlan[0].ports="1 2 3 6t"'

sshpass -p 'root' ssh -p 22 root@192.168.1.251 'uci set network.@switch_vlan[1].ports="0 4 6t"'

sshpass -p 'root' ssh -p 22 root@192.168.1.251 'uci commit'

#upload firmware and md5sums to check intergrity
sshpass -p 'root' scp ./openwrt-ramips-mt7628-mt7628-squashfs-sysupgrade.bin root@192.168.1.251:/tmp

sshpass -p 'root' scp ./md5sums root@192.168.1.251:/tmp

#backup config
sshpass -p 'root' ssh -p 22 root@192.168.1.251 'awk "/^Package:/{PKG= \$2} /^Status: .*user installed/{print PKG}" /usr/lib/opkg/status'

echo "Now updating firmware, please reconnect to AP after updated firmware for further installation"
read -p "Press any key to continue..." var

#update firmware
sshpass -p 'root' ssh -p 22 root@192.168.1.251 'cd /tmp; md5sum -c md5sums > md5result ; cat md5result | head -3 | tail -1 | grep "OK" && sysupgrade -v /tmp/*.bin || exit 1'

echo "reconnected to AP, updated firmware, uploading AP program"

#upload AP program and wifidog.conf
sshpass -p 'root' ssh -p 22 root@192.168.1.251 'mkdir config'

sshpass -p 'root' scp -r ./config/* root@192.168.1.251:./config

sshpass -p 'root' scp ./ap_client root@192.168.1.251:

sshpass -p 'root' scp ./wifidog.conf root@192.168.1.251:/etc/wifidog.conf

echo "updated AP program, now run AP program"
#set ap_client to run when booted, run ap_client
sshpass -p 'root' scp ./APClient root@192.168.1.251:/etc/init.d
sshpass -p 'root' scp ./autorestart.sh root@192.168.1.251:/root
sshpass -p 'root' ssh -p 22 root@192.168.1.251 "chmod +x /etc/init.d/APClient;chmod +x /root/autorestart.sh"
sshpass -p 'root' ssh -p 22 root@192.168.1.251 '/etc/init.d/APClient enable'
sshpass -p 'root' ssh -p 22 root@192.168.1.251 'reboot'


var=1
