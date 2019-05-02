CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
	
ut1: unittest1.c dominion.o rngs.o 
	gcc -o ut1 unittest1.c -g dominion.o rngs.o $(CFLAGS)
	./ut1 > unittestresults.out
	gcov -fb dominion.c >> unittestresults.out

ut2: unittest2.c dominion.o rngs.o 
	gcc -o ut2 unittest2.c -g dominion.o rngs.o $(CFLAGS)
	./ut2 >> unittestresults.out
	gcov -fb dominion.c >> unittestresults.out
	
ut3: unittest3.c dominion.o rngs.o 
	gcc -o ut3 unittest3.c -g dominion.o rngs.o $(CFLAGS)
	./ut3 >> unittestresults.out
	gcov -fb dominion.c >> unittestresults.out
	
ut4: unittest4.c dominion.o rngs.o 
	gcc -o ut4 unittest4.c -g dominion.o rngs.o $(CFLAGS)
	./ut4 >> unittestresults.out
	gcov -fb dominion.c >> unittestresults.out
	
ct1: cardtest1.c dominion.o rngs.o 
	gcc -o ct1 cardtest1.c -g dominion.o rngs.o $(CFLAGS)
	./ct1 >> unittestresults.out
	gcov -fb dominion.c >> unittestresults.out

ct2: cardtest2.c dominion.o rngs.o 
	gcc -o ct2 cardtest2.c -g dominion.o rngs.o $(CFLAGS)
	./ct2 >> unittestresults.out
	gcov -fb dominion.c >> unittestresults.out
	
ct3: cardtest3.c dominion.o rngs.o 
	gcc -o ct3 cardtest3.c -g dominion.o rngs.o $(CFLAGS)
	./ct3 >> unittestresults.out
	gcov -fb dominion.c >> unittestresults.out

ct4: cardtest4.c dominion.o rngs.o 
	gcc -o ct4 cardtest4.c -g dominion.o rngs.o $(CFLAGS)
	./ct4 >> unittestresults.out
	gcov -fb dominion.c >> unittestresults.out
	
unittestresults: ut1 ut2 ut3 ut4 ct1 ct2 ct3 ct4
	
exe_all: 
	./ut1
	./ut2
	./ut3
	./ut4
	./ct1
	./ct2
	./ct3
	./ct4

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
