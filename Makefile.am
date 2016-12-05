.PHONY: all clean

SOURCES = src/mruby_mdbm.c

# support mrbgems
MRUBY_MAK_FILE = $(MRUBY_PREFIX)/build/host/lib/libmruby.flags.mak
-include $(MRUBY_MAK_FILE)

CC      = gcc
AR      = ar

# configure settings related to mdbm and mruby
CFLAGS  =  -I$(MDBM_PREFIX)/include -I$(MRUBY_PREFIX)/include
LDFLAGS += -L$(MDBM_PREFIX)/lib $(MRUBY_LDFLAGS)
LIBS    =  -lmdbm $(MRUBY_LIBS)


all: libmruby_mdbm.o libmruby_mdbm.a

libmruby_mdbm.o:
	$(CC) -c -fPIC $(CFLAGS) $(LDFLAGS) $(LIBS) -o libmruby_mdbm.o $(SOURCES)

libmruby_mdbm.a:
	$(AR) -r libmruby_mdbm.a libmruby_mdbm.o

mdbm:
	cd $(MDBM_PREFIX)/src/lib/
	make
	ar -r libmdbm.a object/*.o
	cd ../../../

clean:
	rm -f **/*.lo
	rm -f **.o
	rm -f **.a
