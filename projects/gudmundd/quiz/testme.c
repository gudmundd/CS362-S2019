/*

File:			testme.c
Description:	Random Testing Quiz for CS362
Student:		David Gudmundson
Class: 			CS362 Spring 2019
		
Instructions
************

	To run the tests
		make testme	(output is redirected to testme.out)
		
				gcc -o testme testme.c $(CFLAGS)
				-./testme > testme.out
				gcov -fb testme.c >> testme.out
					
	To inspect the last few lines of output and the coverage summary
		tail -40 testme.out
						
	To inspect coverage details 
		cat testme.c.gcov

*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
							
// TODO: rewrite this function
char inputChar()
{
   char c;
   
   // The printable ASCII character set is from 
   // decimal char 32 to 126 which is 95 characters 
   c = 32 + (rand() % 95);	
   return c;
}

// TODO: rewrite this function
char *inputString()
{
	char * str;
	int strLength = 5;	
  	int i = 0;
	
	// allocate memory
	str = (char *) malloc (strLength);
	// initialize to null
	memset(str, '\0', strLength*sizeof(char));

   // The lowercase alphabet ASCII character set is from 
   // decimal char 97 to 122 which is a total of 26 characters 	
	for (i = 0; i < strLength; i++) 
	{
	  str[i] = 97 +(rand() % 26);
	}
	return str;
}

void testme()
{
  int tcCount = 0;		
  char *s;
  char c;
  int state = 0; 
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' ' && state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
