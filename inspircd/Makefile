PROGS     = inspircd
OBJS = inspircd.o inspircd_io.o inspircd_util.o modules.o dynamic.o

CC = g++
CXXFLAGS = -fPIC -frtti -O
LDLIBS = -ldl

all : $(PROGS) m_foobar.so

$(PROGS): $(OBJS)
	$(CXX) -rdynamic $^ -o $@ $(LDLIBS)


m_foobar.so : m_foobar.o
	$(CXX) $(CXXFLAGS) -shared  $^ -o $@ && mv $@ `cat .modpath`

.PHONY: clean
clean:
	rm -f *.o core

