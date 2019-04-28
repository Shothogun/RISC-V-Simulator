IDIR = ./include
ODIR = ./obj

CC=gcc
CFLAGS= -W -Wall -pedantic -I$(IDIR)
DEBUG = -g

_DEPS = $(patsubst $(IDIR)/%,%,$(DEPS))
DEPS = $(wildcard $(IDIR)/*.h)

_OBJ = $(patsubst %.c,%.o,$(wildcard *.c))
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUG)

test: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(DEBUG)

clean:
	rm -f $(wildcard $(ODIR)/*.o)