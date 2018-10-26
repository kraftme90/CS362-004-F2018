CFLAGS= -Wall -lm -std=c99

run: testme.c 
	gcc -o testme testme.c -g  $(CFLAGS)
	./testme

all: testme.c
	gcc -o testme testme.c -g  $(CFLAGS)

clean:
	rm -f *.o  *.gcov *.gcda *.gcno *.so *.out testme
