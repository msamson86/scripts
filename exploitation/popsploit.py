#!/usr/bin/python

#usage: popsploit [ip]

import socket
import sys

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
try:
  print "\nSending evil buffer..."
  print sys.argv[1]
  s.connect((sys.argv[1],110))
  data = s.recv(1024)
  print data

  s.send('USER test' +'\r\n')
  data = s.recv(1024)
  print data

  s.send('PASS test\r\n')
  data = s.recv(1024)
  print data

  s.close()
  print "\nDone!"
except:
  print "Could not connect to POP3!"
