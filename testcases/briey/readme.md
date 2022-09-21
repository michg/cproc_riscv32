testcases for single precison floating point math running on [briey](https://github.com/SpinalHDL/VexRiscv)

* using hardware floating point instructions:

```
make -f makehf
make -C verilator
cd result
./vbriey
```

* using Berkeley software floating point package:

```
make -f makesf
make -C verilator
cd result
./vbriey
```
