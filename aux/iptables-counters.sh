#!/bin/bash

#usage: iptables-counters.sh [target IP]

#reset all counters and iptables rules
iptables -Z && iptables -F
#measure incoming traffic to [target ip]
iptables -I INPUT 1 -s $1 -j ACCEPT
# measure outgoing traffic to [target ip]
iptables -I OUTPUT 1 -d $1 -j ACCEPT
