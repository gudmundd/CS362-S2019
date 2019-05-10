CFLAGS = -Wall -fpic -coverage -lm -std=c99

testme: 
	gcc -o testme testme.c $(CFLAGS)
	-./testme > testme.out
	gcov -fb testme.c >> testme.out
	
testme_exe:
	-./testme > testme.out
	gcov -fb testme.c >> testme.out
	
clean:
	rm testme

cleanall: 
	rm testme testme.out *.gcda *.gcno *.gcov
