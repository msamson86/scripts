#!/bin/bash

#usage: ./ping X.X.X.

for ((i=2;i<=254;i++)); do
    ping -c 1 $1$i | grep "bytes from" | cut -d " " -f 4 | cut -d ":" -f 1
done
