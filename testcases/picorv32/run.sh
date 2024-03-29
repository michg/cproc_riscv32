CC=../../cproc/cproc
AS=../../elftools/minias/minias
LD=../../elftools//neatld/nld
AR=../../elftools/ar/ar
CFLAGS="-S -I."  
SRCDIR=./src/$1
RESDIR=./result/$1

rm -f -r result
mkdir result 
mkdir ${RESDIR}
copts=$(<${SRCDIR}/copts.txt)
ldopts=$(<${SRCDIR}/ldopts.txt)
${CC} ${CFLAGS} ${copts} ${SRCDIR}/$1.c  -o ${RESDIR}/$1.s
${AS} -o ${RESDIR}/$1.o ${RESDIR}/$1.s
${AS} -o ${RESDIR}/start.o start.s
${CC} ${CFLAGS} io.c -o ${RESDIR}/io.s
${AS} -o ${RESDIR}/io.o ${RESDIR}/io.s
${LD} -mc=0 -t ${RESDIR}/map.txt -ns -ne -o ${RESDIR}/$1.bin ${RESDIR}/start.o ${RESDIR}/io.o ${RESDIR}/$1.o ${ldopts}
${LD} -mc=0 -o ${RESDIR}/$1.elf ${RESDIR}/start.o ${RESDIR}/io.o ${RESDIR}/$1.o ${ldopts}
python3 mkhex.py ${RESDIR}/$1
cp ${RESDIR}/$1.hex firmware.mem
./simv | head -n -1 >> ${RESDIR}/$1.log
if cmp -s "${SRCDIR}/$1.ref" "${RESDIR}/$1.log"
   then
      echo "Testcase $1 ok."
   else
      echo "Testcase $1 fail."
   fi 



