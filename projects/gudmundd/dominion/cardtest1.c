/*

	File:				cardtest1.c
	
	Description:		Performs unit tests for the dominion game per Assignment 3 of CS362
	
	Card Tested:		smithy in dominion.c
	
	Makefile:			The following lines are added to the makefile provided in CS362
	
							cardtest1: cardtest1.c dominion.o rngs.o 
								gcc -o ct1 cardtest1.c -g dominion.o rngs.o $(CFLAGS)

	Student:			David Gudmundson
	
	Class: 				CS362 Spring 2019
	

*/

#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <string.h>

#define PRINT_STATE 0
#define PRINT_DECKS 0
#define FORCE_FAIL 0

char CARD_UNDER_TEST[] = "smithy";	// string for printing the unit test name

int main (int argc, char** argv) {
	
	int current_player = 0;
	struct gameState G;
	struct gameState G_orig;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
		   sea_hag, tribute, smithy};

	printf ("Starting Card Test 1 - %s.\n", CARD_UNDER_TEST);
	
	int num_game_state_tests = 3;	// CHOOSE HIGHER VALUE FOR MORE GAME STATES
	int game_state_pass;
	for (game_state_pass = 1; game_state_pass <= num_game_state_tests; game_state_pass++)
	{
		printf("GAME STATE %d\n", game_state_pass);
		initializeGame(4, k, game_state_pass, &G);
		memcpy(&G_orig, &G, sizeof(struct gameState));

		// REQUIREMENT 
		// Invalid hand because player doesn't actually have Smithy to play
		initializeGame(4, k, game_state_pass, &G);
		memcpy(&G_orig, &G, sizeof(struct gameState));
		G.hand[current_player][G.handCount[current_player]++] = mine;
		int ret;
		// Execute the card function
		ret = cardEffect(smithy, 0, 0, 0, &G, G.hand[current_player][G.handCount[current_player]-1], 0);
		if (ret == 0)
			printf("FAIL: Invalid hand - player didn't have Smithy\n");
		else
			printf("PASSED: Invalid hand - player didn't have Smithy\n");	

		// REQUIREMENT 
		// Out of bounds current player should not be processed, and cause an error
		initializeGame(4, k, game_state_pass, &G);
		memcpy(&G_orig, &G, sizeof(struct gameState));
		G.hand[current_player][G.handCount[current_player]++] = smithy;
		int invalid_current_player = 5;
		// Execute the card function
		ret = cardEffect(smithy, 0, 0, 0, &G, G.hand[invalid_current_player][G.handCount[invalid_current_player]-1], 0);
		if (ret == 0)
			printf("FAIL: Invalid Current Player\n");
		else
			printf("PASSED: Invalid Current Player\n");
			
		// REQUIREMENT 
		// Out of bounds hand position should not be processed, and cause an error
		initializeGame(4, k, game_state_pass, &G);
		memcpy(&G_orig, &G, sizeof(struct gameState));
		G.hand[current_player][G.handCount[current_player]++] = smithy;
		int invalid_hand_pos = -1;
		// Execute the card function
		ret = cardEffect(smithy, 0, 0, 0, &G, invalid_hand_pos, 0);
		if (ret == 0)
			printf("FAIL: Invalid Hand Position\n");
		else
			printf("PASSED: Invalid Hand Position\n");
			
		// REQUIREMENT
		// Invalid card submitted to cardEffect should cause an error
		initializeGame(4, k, game_state_pass, &G);
		memcpy(&G_orig, &G, sizeof(struct gameState));
		G.hand[current_player][G.handCount[current_player]++] = smithy;
		int invalid_card = -1;
		// Execute the card function
		ret = cardEffect(invalid_card, 0, 0, 0, &G, G.hand[current_player][G.handCount[current_player]-1], 0);
		if (ret == 0)
			printf("FAIL: Invalid Hand Position \n");
		else
			printf("PASSED: Invalid Card\n");
			
		// REQUIREMENT
		// Invalid choice1, choice2, and choice3 - not required for Smithy, so should be zero and not be ignored by cardEffect
		initializeGame(4, k, game_state_pass, &G);
		memcpy(&G_orig, &G, sizeof(struct gameState));
		G.hand[current_player][G.handCount[current_player]++] = smithy;
		int invalid_choice_1 = 1;
		int invalid_choice_2 = 2;
		int invalid_choice_3 = 3;
		// Execute the card function
		ret = cardEffect(smithy, invalid_choice_1, invalid_choice_2, invalid_choice_3, &G, G.hand[current_player][G.handCount[current_player]-1], 0);
		if (ret == 0)
			printf("FAIL: Invalid Choice Inputs \n");
		else
			printf("PASSED: Invalid Choice Inputs (choice1, choice2, and choice3)\n");
		
		// REQUIREMENT
		// Invalid bonus - not required for Smithy, so should be zero and not be ignored by cardEffect
		initializeGame(4, k, 2, &G);
		memcpy(&G_orig, &G, sizeof(struct gameState));
		G.hand[current_player][G.handCount[current_player]++] = smithy;
		int invalid_bonus = 99;
		// Execute the card function
		ret = cardEffect(smithy, 0, 0, 0, &G, G.hand[current_player][G.handCount[current_player]-1], &invalid_bonus);
		if (ret == 0)
			printf("FAIL: Invalid Bonus input\n");
		else
			printf("PASSED: Invalid Bonus Input)\n");
	}
	// REQUIREMENT
	// Unitialized game state submitted as input
	// Does not depend on game state passes, so not in the below loop
	int ret;
	struct gameState Uninitialized_G;
	//memcpy(&G_orig, &G, sizeof(struct gameState));
	G.hand[current_player][G.handCount[current_player]++] = smithy;
	// Execute the card function
	ret = cardEffect(smithy, 0, 0, 0, &Uninitialized_G, G.hand[current_player][G.handCount[current_player]-1], 0);
	printf("*** the following test is longer in the game state loop***\n");
	if (ret == 0)
		printf("FAIL: Uninitialized game state \n");
	else
		printf("PASSED: Uninitialized game state)\n");

	return 0;
}


