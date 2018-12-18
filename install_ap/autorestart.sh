#!/bin/sh

RC=1
cd /root/
while [ $RC -ne 0 ]; do
   sleep 3
   /root/ap_client
   RC=$?
done &
