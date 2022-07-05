EXDEBUG?=no
TRACE?=no
FST?=no
PRINT_PERF?=no
TRACE_START=0
#ADDCFLAGS += -CFLAGS -pthread -LDFLAGS "-pthread"



#VERILATOR_ARGS += --trace -trace-underscore -trace-structs --trace-depth 1000 --trace-max-array	1000 -trace-max-width 1000 --no-decoration
VERILATOR_ARGS += --trace -trace-underscore --no-decoration
ADDCFLAGS += -CFLAGS -DTRACE

ifeq ($(FST),yes)
    VERILATOR_ARGS += --trace-fst
    ADDCFLAGS += -CFLAGS "-DFST"
endif
ifeq ($(DEBUG),yes)
	ADDCFLAGS += -CFLAGS "-g3 -O0"
endif
ifneq ($(DEBUG),yes)
	ADDCFLAGS += -CFLAGS "-O3"
endif
ifeq ($(PRINT_PERF),yes)
	ADDCFLAGS += -CFLAGS -DPRINT_PERF
endif

ADDCFLAGS += -CFLAGS -DTRACE_START=${TRACE_START} -CFLAGS -fpermissive 



all: clean compile

run: compile
	./obj_dir/Vsystem

verilate:
	verilator -cc Briey.v -CFLAGS -std=gnu++11  ${ADDCFLAGS} ${VERILATOR_ARGS} -Wno-WIDTH -Wno-UNOPTFLAT  -Wno-CASEINCOMPLETE  -Wno-MULTIDRIVEN -Wno-IMPLICIT -Wno-LATCH -Wno-PINMISSING -Wno-COMBDLY --x-assign unique  --top-module Briey --exe  main.cpp

compile: verilate
	make  -j  -C obj_dir/ -f VBriey.mk VBriey
	cp obj_dir/VBriey ../result
 	
clean:
	rm -rf obj_dir
 	
