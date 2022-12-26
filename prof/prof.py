import sys
import json
import subprocess
import pylibfst
from Verilog_VCD import parse_vcd
from bisect import bisect
from types import SimpleNamespace as New


vcddata = {}
alias = {}
fbeg = {}
fend = {}
ACODE = 1


def getfuncs(elfname):
    res = []
    outs = subprocess.check_output(['nm','-S'] + [elfname])
    outs = outs.decode("ascii")
    for line in outs.split('\n'):
        cols = line.split()
        if len(cols) == 4:
            f_name = cols[3]
            if(f_name[-3:]!="end"):
                val = int(cols[0], 16)
                fbeg[val] = f_name
                size = int(cols[1], 16)
                fend[val+size-4] = f_name
                res.append([f_name])
    return res

def b2w(bits):
    if  bits != 'x':
        word = int(bits, 2)
        return word
    else:
        return -1

def posedge(old, new):
    if not old and new:
        return True
    return False

def getsigfst(time, code):
    global fst
    buf = pylibfst.ffi.new("char[256]")
    res = pylibfst.helpers.string(
    pylibfst.lib.fstReaderGetValueFromHandleAtTime(fst, time, code, buf))
    return b2w(res)

def getsigvcd(time, code):
    global vcddata
    curtime = bisect(vcddata[code].tarr, time, lo=vcddata[code].lasttime) - 1
    vcddata[code].lasttime = curtime
    return vcddata[code].varr[curtime]


class Sig():
    def __init__(self, code, getfunc):
        self.code = code
        self.old = 0
        self.new = 0
        self.getval = getfunc
       
    def get(self, time):
        self.old = self.new
        self.new = self.getval(time, self.code)
        return self.old, self.new




if __name__ == '__main__':
    if len(sys.argv) < 3:
        print('Usage:')
        print('  prof.py elf vcd')
        sys.exit(1) 
    ELF = sys.argv[1]
    VCD = sys.argv[2]
    f = open('alias.jsn','r')
    alias = json.load(f)

    if VCD[-3:] == "vcd":
        isvcd = True
        print("Using vcd")
        slist = []
        for k in alias:
            alias[k][0] = alias[k][0].replace(" ","")
        for i in alias.values():
            slist.append(i[0])
        table =  parse_vcd(VCD, siglist=slist)
        codes = list(table.keys())
        for i, key in enumerate(alias.keys()):
            code = codes[i]
            alias[key].append(code)
            vals = []
            times = []
            for time, val in table[code]['tv']:
                vals.append(b2w(val))
                times.append(time)
            vcddata[code] = New(tarr=times, varr=vals, lasttime=0)
        get = getsigvcd
        timerange = range(len(vcddata[alias['CLK'][ACODE]].tarr))
        timevals = vcddata[alias['CLK'][ACODE]].tarr
    else:
        isvcd = False
        print("Using fst")
        fst = pylibfst.lib.fstReaderOpen(VCD.encode("UTF-8"))
        (scopes, signals) = pylibfst.get_scopes_signals(fst)
        for key in alias.keys():
            alias[key].append(signals[alias[key][0]])
        pylibfst.lib.fstReaderSetFacProcessMaskAll(fst)
        timestamps = pylibfst.lib.fstReaderGetTimestamps(fst)
        get = getsigfst
        timerange = range(timestamps.nvals)
        timevals = timestamps.val
    print(alias)
    funcs = getfuncs(ELF)
    print(funcs)
    clk = Sig(alias['CLK'][ACODE], get)
    pc = Sig(alias['PC'][ACODE], get)
    a0 = Sig(alias['X10'][ACODE], get)
    tabs = 0
    for ts in timerange:
        time = timevals[ts]
        old, new = clk.get(time)
        if posedge(old, new):
            old, new = pc.get(time)
            if(new!=old):
                if new in fbeg:
                    tabs += 1
                    arg0old, arg0new = a0.get(time)
                    print("time:%10d" %time,"\t"*tabs,"-->",fbeg[new], ":%08x" %arg0new)                    
                if new in fend:
                    rvold, rvnew = a0.get(time)
                    print("time:%10d" %time,"\t"*tabs,"<--",fend[new], ":%08x" %rvnew)
                    tabs -= 1



