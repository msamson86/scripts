output = ""
a = 0
b = 256
for x in range(a,a+16):
    output += "\\x0" + hex(x)[2:4]
for x in range(16,256):
    output += "\\x" + hex(x)[2:4]
print output
