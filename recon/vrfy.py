#usage: vrfy.py [ip] [username]

import socket
import sys

if len(sys.argv) != 3:
    print "Usage: vrfy.py <ip> <username>"
    sys.exit(0)

s=socket.socket(socket.AF_INET, socket.SOCK_STREAM) # Create a socket
connect=s.connect((sys.argv[1],25)) # Connect to the server
banner=s.recv(1024)
print banner
userlist = open(sys.argv[2],'r')
for user in userlist:
    #print "USERNAME: " + user
    s.send('VRFY ' + user) # VRFY a user
    result = s.recv(1024)
    if result[0:3] != "550":
        print "SUCCESS! --> " + result
userlist.close()
s.close() #close the socket
