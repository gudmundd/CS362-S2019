
This file contains instructions pertaining to Assignment 5


To compile and run the unit tests to test ONLY my teammate's (Nikita Mattingly) refactored code, type:

	make compile_mattingn_refactored_tests
	make run_mattingn_refactored_tests


To get coverage results, execute each compile separately, followed by running gcov.
For example:

	make ut1
	./ut1
	gcov -fb dominion.c 
	
	
To compile and run all unit tests, regardless of whether they relate to my teammates refactored code, type:
	
	make compile_all_tests
	make run_all_tests
	
