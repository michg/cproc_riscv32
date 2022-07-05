import io
from sys import argv
    
with open(argv[1], "rb") as f:
    bindata = bytearray(f.read())

padcnt = 4 - len(bindata) % 4
if padcnt != 0:
    print("Padding: %d bytes!" %padcnt)
    for pad in range(padcnt):
        bindata.append(0)
        
assert len(bindata) % 4 == 0

name = "result/Briey.v_toplevel_axi_ram_ram_symbol"
f0 = open(name + "0.bin","w")
f1 = open(name + "1.bin","w")
f2 = open(name + "2.bin","w")
f3 = open(name + "3.bin","w")
for i in range(len(bindata)//4):
    w = bindata[4*i : 4*i+4]
    print("{0:08b}".format(w[0]),file=f0)
    print("{0:08b}".format(w[1]),file=f1)
    print("{0:08b}".format(w[2]),file=f2)
    print("{0:08b}".format(w[3]),file=f3)
f0.close()
f1.close()
f2.close()
f3.close()
