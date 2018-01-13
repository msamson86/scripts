#!/bin/bash

#usage smtp-enum [target ip] [user list]

for user in $(cat $2); do echo VRFY $user  |nc  -nv -w 1 $1 25 2>/dev/null |grep ^"250";done
