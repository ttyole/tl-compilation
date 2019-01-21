# Compiler flags
CFLAGS := -Wall -O3 -m64 -D'main(a,b)=main(int argc, char** argv)' -Duint64_t='unsigned long long' -fno-builtin
CSTAR.X86=./cstar.x86
MIPSTER.X86=./mipster.x86
HEADERS=$(shell ls -1 *.h)
CFILES=$(shell ls -1 *.c | grep -v main )
OBJS=$(CFILES:.c=.o)

all: cstar

%.o: %.c
	$(CC) $(CFLAGS) $? -c $<

cstar: ${OBJS} main-cstar.o 
	$(CC) $(CFLAGS) $^ -o $@

test.cstar: ${CFILES} main-cstar.c
	${CSTAR.X86} -c $^ -o $@

# Clean up
clean:
	rm -rf *.o
	rm -rf *.m
	rm -rf *.s
	rm -rf cstar
	rm -rf cstar.rv
