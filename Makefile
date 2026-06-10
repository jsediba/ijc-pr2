CFLAGS=-std=c99 -pedantic -Wall -Wextra -O2
CPPFLAGS=-std=c++17 -pedantic -Wall -O2
LIBRARYOBJS=htab_hash_function.o htab_init.o htab_for_each.o htab_find.o htab_lookup_add.o htab_size.o htab_bucket_count.o htab_erase.o htab_move.o htab_clear.o htab_free.o

all: tail wordcount wordcount-dynamic libhtab.a libhtab.so cppwordcount

### LINKOVANIE ###

tail: tail.o
	gcc $(CFLAGS) $^ -o $@

cppwordcount: cppwordcount.cc
	g++ $(CPPFLAGS) $< -o $@

wordcount: wordcount.o io.o libhtab.a
	gcc $(CFLAGS) -static $^ -o $@

wordcount-dynamic:wordcount.o io.o libhtab.so
	gcc $(CFLAGS) -Wl,-R. $^ -o $@

### KNIZNICE ###

libhtab.a:$(LIBRARYOBJS)
	ar -r -c -s $@ $(LIBRARYOBJS)

libhtab.so:$(LIBRARYOBJS)
	gcc $(CFLAGS) -shared -fPIC  $(LIBRARYOBJS) -o $@

### OBJEKTOVE SUBORY ###

tail.o: tail.c
	gcc $(CFLAGS) -c $< -o $@

io.o: io.c io.h
	gcc $(CFLAGS) -c $< -o $@

wordcount.o: wordcount.c htab.h
	gcc $(CFLAGS) -c $< -o $@



htab_hash_function.o: htab_hash_function.c htab.h
	gcc $(CFLAGS) -fPIC -c $< -o $@

htab_init.o: htab_init.c htab_priv.h htab.h
	gcc $(CFLAGS) -fPIC -c $< -o $@

htab_for_each.o: htab_for_each.c htab_priv.h htab.h
	gcc $(CFLAGS) -fPIC -c $< -o $@

htab_find.o: htab_find.c htab_priv.h htab.h
	gcc $(CFLAGS) -fPIC -c $< -o $@

htab_lookup_add.o: htab_lookup_add.c htab_priv.h htab.h
	gcc $(CFLAGS) -fPIC -c $< -o $@

htab_size.o: htab_size.c htab_priv.h htab.h
	gcc $(CFLAGS) -fPIC -c $< -o $@

htab_bucket_count.o: htab_bucket_count.c htab_priv.h htab.h
	gcc $(CFLAGS) -fPIC -c $< -o $@

htab_erase.o: htab_erase.c htab_priv.h htab.h
	gcc $(CFLAGS) -fPIC -c $< -o $@

htab_move.o: htab_move.c htab_priv.h htab.h
	gcc $(CFLAGS) -fPIC -c $< -o $@

htab_clear.o: htab_clear.c htab_priv.h htab.h
	gcc $(CFLAGS) -fPIC -c $< -o $@

htab_free.o: htab_free.c htab_priv.h htab.h
	gcc $(CFLAGS) -fPIC -c $< -o $@



.PHONY: all clean pack
clean:
	rm -f tail wordcount wordcount-dynamic libhtab.a libhtab.so cppwordcount *.o
pack:
	zip xsedib00.zip *.c *.cc *.h Makefile