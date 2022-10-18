import io
from sys import argv
    
with open(argv[1]+".bin", "rb") as f:
    bindata = bytearray(f.read())

size =  32768
padcnt = 4 - len(bindata) % 4
if padcnt != 0:
    print("Padding: %d bytes!" %padcnt)
    for pad in range(padcnt):
        bindata.append(0) 
assert len(bindata) % 4 == 0

f = open(argv[1]+".hex","w")
for i in range(size):
    if i < len(bindata) // 4:
        w = bindata[4*i : 4*i+4]
        print("%02x%02x%02x%02x" % (w[3], w[2], w[1], w[0]),file=f)
    else:
        print("00000000",file=f)
f.close()