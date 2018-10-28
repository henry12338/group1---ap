mkdir ../back_up
mkdir ../back_up/config
mkdir ../back_up/dropbear
mkdir ../back_up/opkg
mkdir ../back_up/opkg/keys
mkdir ../back_up/ppp


cp ./config/dhcp ./config/dropbear ./config/firewall ./config/luci ./config/network ./config/rpcd ./config/system ./config/ucitrack ./config/uhttpd ./config/wireless ../back_up/config/

cp ./dropbear/dropbear_dss_host_key ./dropbear/dropbear_rsa_host_key ../back_up/dropbear/

cp ./opkg/keys/* ../back_up/opkg/keys/

cp ./opkg/customfeeds.conf ../back_up/opkg/

cp ./ppp/chap-secrets ./ppp/filter ./ppp/options ../back_up/ppp/

cp dnsmasq.conf firewall.user group hosts inittab opkg.conf passwd profile protocols rc.local services shadow shells sysctl.conf sysupgrade.conf  ../back_up/


tar -czvf ../backup.tar.gz ../back_up

rm -R ../back_up
