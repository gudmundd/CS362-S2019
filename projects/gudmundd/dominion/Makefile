CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
	
rt1: randomtestcard1.c dominion.o rngs.o 
	gcc -o rt1 randomtestcard1.c -g dominion.o rngs.o $(CFLAGS)
	./rt1 > randomtestresults.out
	gcov -fb dominion.c >> randomtestresults.out

rt2: randomtestcard2.c dominion.o rngs.o 
	gcc -o rt2 randomtestcard2.c -g dominion.o rngs.o $(CFLAGS)
	./rt2 >> randomtestresults.out
	gcov -fb dominion.c >> randomtestresults.out
	
rt3: randomtestcard3.c dominion.o rngs.o 
	gcc -o rt3 randomtestcard3.c -g dominion.o rngs.o $(CFLAGS)
	./rt3 >> randomtestresults.out
	gcov -fb dominion.c >> randomtestresults.out
	
randomtestresults: rt1 rt2 rt3

exe_all: 
	./rt1
	./rt2
	./rt3

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe rt1 rt2 rt3

