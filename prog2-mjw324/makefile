AFLAGS=-g -o
FLAGS=-g -o
CFLAGS=-g -c -Wall -Wextra -Wwrite-strings
LFLAGS=-g -o prog2

prog2: prog2.o abs.o sum_diff.o gcd.o sum_squares.o max.o sort.o
	gcc ${LFLAGS} prog2.o abs.o sum_diff.o gcd.o sum_squares.o max.o sort.o

prog2.o: prog2.c 
	gcc ${CFLAGS} prog2.c

abs.o: abs.S
	as ${AFLAGS} abs.o abs.S

sum_diff.o: sum_diff.S
	as ${AFLAGS} sum_diff.o sum_diff.S

gcd.o: gcd.S
	as ${AFLAGS} gcd.o gcd.S

sum_squares.o: sum_squares.S
	as ${AFLAGS} sum_squares.o sum_squares.S

max.o: max.S
	as ${AFLAGS} max.o max.S

sort.o: sort.S
	as ${AFLAGS} sort.o sort.S

clean:
	rm -rf prog2
	rm -rf *.o