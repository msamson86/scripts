#usage: ./ping X.X.X.
#OSCP Exercise: 1.3.1.3 question 2

import subprocess,sys,thread

cmdping = "ping -c1 "

i = 0

def geti():
    global i
    i = i+1
    return i

def pingsweep():

    while i < 255:
	value = geti()
        proc = subprocess.Popen(cmdping+sys.argv[1]+str(value), shell=True, stdout=subprocess.PIPE, )
        output = proc.communicate()[0]

        if "Unreachable" in output:
            continue
        else:
            print sys.argv[1] + str(value) + " responded to ping"

try:
    thread.start_new_thread(pingsweep,())
    thread.start_new_thread(pingsweep,())
    thread.start_new_thread(pingsweep,())
    thread.start_new_thread(pingsweep,())
    thread.start_new_thread(pingsweep,())
except:
    print "Error: unable to start thread"

while 1:
    pass
