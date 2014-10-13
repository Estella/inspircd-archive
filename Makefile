PROGS     = inspircd

INSTDIR   = $(prefix)/bin/
INSTMODE  = 0755
INSTOWNER = root
INSTGROUP = root

OBJS = inspircd.o inspircd_io.o inspircd_util.o

all: $(PROGS)

$(PROGS): $(OBJS)
	$(CC) -o $@ $(OBJS)

.PHONY: clean
clean:
	rm -f *.o core
