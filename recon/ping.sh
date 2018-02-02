#!/bin/bash

#usage: ./ping X.X.X.
#OSCP Exercise 1.3.1.3

for ((i=2;i<=254;i++)); do
    ping -c 1 $1$i | grep "bytes from" | cut -d " " -f 4 | cut -d ":" -f 1
done
