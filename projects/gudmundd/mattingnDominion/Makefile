CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
	
ut1: unittest1.c dominion.o rngs.o 
	gcc -o ut1 unittest1.c -g dominion.o rngs.o $(CFLAGS)

ut2: unittest2.c dominion.o rngs.o 
	gcc -o ut2 unittest2.c -g dominion.o rngs.o $(CFLAGS)
	
ut3: unittest3.c dominion.o rngs.o 
	gcc -o ut3 unittest3.c -g dominion.o rngs.o $(CFLAGS)
	
ut4: unittest4.c dominion.o rngs.o 
	gcc -o ut4 unittest4.c -g dominion.o rngs.o $(CFLAGS)
	
ct1: cardtest1.c dominion.o rngs.o 
	gcc -o ct1 cardtest1.c -g dominion.o rngs.o $(CFLAGS)

ct2: cardtest2.c dominion.o rngs.o 
	gcc -o ct2 cardtest2.c -g dominion.o rngs.o $(CFLAGS)
	
ct3: cardtest3.c dominion.o rngs.o 
	gcc -o ct3 cardtest3.c -g dominion.o rngs.o $(CFLAGS)

ct4: cardtest4.c dominion.o rngs.o 
	gcc -o ct4 cardtest4.c -g dominion.o rngs.o $(CFLAGS)

rt1: randomtestcard1.c dominion.o rngs.o 
	gcc -o rt1 randomtestcard1.c -g dominion.o rngs.o $(CFLAGS)

rt2: randomtestcard2.c dominion.o rngs.o 
	gcc -o rt2 randomtestcard2.c -g dominion.o rngs.o $(CFLAGS)
	
rt3: randomtestcard3.c dominion.o rngs.o 
	gcc -o rt3 randomtestcard3.c -g dominion.o rngs.o $(CFLAGS)
	
compile_mattingn_refactored_tests: ut1 ut3 ct2

run_mattingn_refactored_tests: 
	./ut1
	./ut3
	./ct2
	
compile_all_tests: ut1 ut2 ut3 ut4 ct1 ct2 ct3 ct4 rt1 rt2 rt3

run_all_tests: 
	./ut1
	./ut2
	./ut3
	./ut4
	./ct1
	./ct2
	./ct3
	./ct4
	./rt1
	./rt2
	./rt3
	
clean:
	rm -f *.o playdom.exe playdom *.gcov *.gcda *.gcno *.so *.out rt1 rt2 rt3 ut1 ut2 ut3 ut4 ct1 ct2 ct3 ct4

