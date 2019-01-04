echo "Welcome to first launch setup AP" 

echo "What method do you want to connect to Controller?"
echo "(1) by IP Address"
echo "(2) by DNS Address"
read -p "Input..>" choice

Config_To_Be_configure=../config/connect_config

case $choice in
1)
	echo "Setting up Controller's IP address..."
	read -p "Please input controller's IP address(default is 35.221.194.17)...>" ipaddr
	if [ -z "$ipaddr" ]
	then
		ipaddr=35.221.194.17
		echo "Use default IP"
	fi
	sed -i "/IP_Address = */ c\IP_Address = ${ipaddr}" $Config_To_Be_configure
	sed -i "/DNS_Address*/ c\#DNS_Address = " $Config_To_Be_configure;;
2)
	echo "Setting up Controller's DNS address..."
	read -p "Please input controller's DNS address(default is secontroller1st.ddns.net)...>" dnsaddr
	if [ -z "$dnsaddr" ]
	then
		dnsaddr=secontroller1st.ddns.net
		echo "Use default DNS"
	fi
	sed -i "/DNS_Address = */ c\DNS_Address = ${dnsaddr}" $Config_To_Be_configure
	sed -i "/IP_Address*/ c\#IP_Address = " $Config_To_Be_configure;;
*)
	echo "Input not valid"
	exit;;
esac

echo ""
echo "Setting up Controller's Port..."
read -p "Please input controller's port(default is 27015)...>" port
if [ -z "$port" ]
then
	port=27015
	echo "use default port"
fi
sed -i "/Port = */ c\Port = ${port}" $Config_To_Be_configure

echo ""
echo "Setting up Download update, upload log FTP address..."
read -p "Please input FTP address(default is 35.221.194.17)...>" ftpaddr
if [ -z "$ftpaddr" ]
then
	ftpaddr=35.221.194.17
	echo "use default FTP address"
fi
sed -i "/FTP_Server_Address = */ c\FTP_Server_Address = ${ftpaddr}" $Config_To_Be_configure

echo ""
echo "Setting up FTP username..."
read -p "Please input FTP username(default is uftp)...>" ftpusername
if [ -z "$ftpusername" ]
then
	ftpusername=uftp
	echo "use default FTP username"
fi
sed -i "/FTP_Username = */ c\FTP_Username = ${ftpusername}" $Config_To_Be_configure

echo ""
echo "Setting up FTP password..."
read -p "Please input FTP password(default is seg1)...>" ftppassword
if [ -z "$ftppassword" ]
then
	ftppassword=seg1
	echo "use default FTP password"
fi
sed -i "/FTP_Password = */ c\FTP_Password = ${ftppassword}" $Config_To_Be_configure
