CC=gcc
CFLAGS= -W -Wall -g -pedantic -I.
DEPS = RISCV_mem.h
OBJ = test.o RISCV_mem.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f ./*.o 