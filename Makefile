CC = g++
CFLAGS = -Wall -Werror -Wpedantic -g
LFLAGS =

.PHONY: all
all: test test_fst

.PHONY: clean
clean:
	rm -f *.o test test_fst

filter.o: filter.cpp filter.hpp
	$(CC) -c $(CFLAGS) -o $@ $<

fitler_fst.o: fitler_fst.cpp fitler_fst.hpp
	$(CC) -c $(CFLAGS) -o $@ $<

utils.o: utils.cpp utils.hpp
	$(CC) -c $(CFLAGS) -o $@ $<

test.o: test.cpp filter.hpp utils.hpp
	$(CC) -c $(CFLAGS) -o $@ $<

test_fst.o: test_fst.cpp filter_fst.hpp utils.hpp
	$(CC) -c $(CFLAGS) -o $@ $<

test: test.o filter.o utils.o
	$(CC) -o $@ $^ $(LFLAGS)

test_fst: test_fst.o filter_fst.o utils.o
	$(CC) -o $@ $^ $(LFLAGS)
