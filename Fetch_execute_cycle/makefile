EDIR = ./exec
IDIR = ./include
ODIR = ./obj

CC=gcc
CFLAGS= -W -Wall -pedantic  -I$(IDIR) 
DEBUG = -g

_DEPS = $(patsubst $(IDIR)/%,%,$(DEPS))
DEPS = $(wildcard $(IDIR)/*.h)

_OBJ = $(patsubst %.c,%.o,$(wildcard *.c))
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUG)

all: test assembly_code

test: test.o fec.o RISCV_mem.o
	$(CC) -o $(EDIR)/$@ $^ $(CFLAGS) $(DEBUG)

assembly_code: assembly_code.o fec.o RISCV_mem.o
	$(CC) -o $(EDIR)/$@ $^ $(CFLAGS) $(DEBUG)

clean:
	rm -f $(wildcard $(ODIR)/*.o)
