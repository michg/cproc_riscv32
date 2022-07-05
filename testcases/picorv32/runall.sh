CC=../../cproc/cproc
AS=../../elftools/minias/minias
LD=../../elftools//neatld/nld
AR=../../elftools/ar/ar
CFLAGS="-S -I."

rm -f -r result
mkdir result
for name in src/*/; do
	name=${name%/}
	name=${name#src/}
	SRCDIR=src/${name}
	RESDIR=result/${name}
	mkdir ${RESDIR}
	${CC} ${CFLAGS} ${SRCDIR}/${name}.c -o ${RESDIR}/${name}.s
	${CC} ${CFLAGS} io.c -o ${RESDIR}/io.s
	${AS} -o ${RESDIR}/start.o start.s
	${AS} -o ${RESDIR}/io.o ${RESDIR}/io.s
	${AS} -o ${RESDIR}/${name}.o ${RESDIR}/${name}.s
	${LD} -ns -ne -o ${RESDIR}/${name}.bin ${RESDIR}/start.o ${RESDIR}/io.o ${RESDIR}/${name}.o 
	python3 mkhex.py ${RESDIR}/${name}
        cp ${RESDIR}/${name}.hex firmware.mem
	./simv >> ${RESDIR}/${name}.log
	if cmp -s "${SRCDIR}/${name}.ref" "${RESDIR}/${name}.log"
	then
		echo "Testcase ${name} ok." >>result/results.log
	else
		echo "Testcase ${name} fail." >>result/results.log
	fi 
done



