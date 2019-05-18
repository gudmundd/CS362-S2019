/*
	File:			randomtestcard2.c
	Description:	Performs random unit tests for the dominion game per Assignment 4 of CS362
	Card Tested:	Village in dominion.c
	
	Makefile:		Type "make randomtestresults" to compile, run, anc generate coverage results 
					for all three tests, and to pipe the results to andomtestresults.out
	
					Type "make exe_all" to simply run the tests, and send test output to stdout
	
					Specific to this test, the following lines are added to the makefile provided in CS362
	
					rt2: randomtestcard2.c dominion.o rngs.o 
						gcc -o rt2 randomtestcard2.c -g dominion.o rngs.o $(CFLAGS)
						./rt2 >> randomtestresults.out
						gcov -fb dominion.c >> randomtestresults.out

	Student:		David Gudmundson
	Class: 			CS362 Spring 2019
*/

#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"

void rand_test_village() 
{
	// indexes
	int i;							// test iteration loops
	int x, y;						// random set up loops 	
	int a; 							// random index for action cards
	int z;							// general purpose index
	
	// test paramaters
	int num_random_tests = 10000;	// number of random test loops
	int game_seed = 30;				// the seed for the game initialization function
	char CARD_UNDER_TEST[] = "Village";	// string for printing the card under test
	int FORCE_FAIL = 0;
	
	// counters
	int num_tests_passed = 0;		
	int num_tests_failed = 0;		
	int num_failed_game_states = 0;	
	int failed_game_state_flag;
	
	// local game parameters
	int num_players;				
	int current_player;
	int current_player_handCount;
	struct gameState PRE;
	struct gameState POST;

	int k[10] = {adventurer, gardens, embargo, village, minion, mine, council_room,
		   sea_hag, tribute, smithy};

	printf ("Starting Random Test 2 - %s\n", CARD_UNDER_TEST);
	
	srand(time(NULL));
	
	// Begin random test loop
	for (i = 0; i < num_random_tests; i++)
	{
		//printf("test iteration = %d\n", i);
	
		//Randomly set number of players to either 2, 3, or 4 players (3 possible values)
		num_players = 2 + (rand() % 3);
		//Initialize game 
		initializeGame(num_players, k, game_seed, &PRE);
		
		//printf("PRE.numPlayers = %d\n", PRE.numPlayers);

		// Randomly set up all relevant game parameters for each player
		for (x = 0; x < num_players; x++) 
		{
			//	Set Deck Counts							MIN	MAX		RANGE
			// 	1. number of cards in hand 				3	12    	9
			//	2. number of cards in deck				5	25		20
			//  3. number of cards in discard pile		3	12  	9
			PRE.handCount[x] 	= 3 + (rand() % 9);
			PRE.deckCount[x] 	= 5 + (rand() % 20);
			PRE.discardCount[x] = 3 + (rand() % 9);	
			
			//printf("PRE.handCount[%d] = %d   PRE.deckCount[%d] = %d   PRE.discardCount[%d] = %d\n", x, PRE.handCount[x], x, PRE.deckCount[x], x, PRE.discardCount[x]);
		}
		
		//	SET CARD MAKEUP IN EACH HAND		
		// 	1. set each card in each hand 		
		//     to one of the 10 action cards	
		//	2. replace some of the cards in 
		//     each hand with treasure cards	
		for (x = 0; x < num_players; x++) 
		{
			for (y = 0; y < PRE.handCount[x]; y++) 
			{
				a = rand() % 10;
				PRE.hand[x][y] = k[a];
			}
			//	SET CARD MAKEUP IN EACH DECK	
			// 	1. set each card in each deck 
			//     to one of the 10 action cards
			//	2. replace some of the cards in
			//     each deck with treasure cards	 		
			for (y = 0; y < PRE.deckCount[x]; y++) 
			{
				a = rand() % 10;
				PRE.deck[x][y] = k[a];
			}
			//	SET CARD MAKEUP IN EACH DISCARD PILE	
			// 	1. set each card in each discard 
			//     pile to one of the 10 action cards 	 
			//	2. replace some of the cards in 
			//     each pile with treasure cards		
			for (y = 0; y < PRE.discardCount[x]; y++) 
			{
				a = rand() % 10;
				PRE.discard[x][y] = k[a];
			}
		}	

		// Establish the current player
		current_player = 0;
	    PRE.whoseTurn = current_player;
		
		// Guarantee the current player had an village card
		// by randomly seeding one
		current_player_handCount = PRE.handCount[current_player];
		z = rand() % current_player_handCount;
		PRE.hand[current_player][z] = village;	
		
		// BEGIN CARD TESTS
		failed_game_state_flag = 0;
		
		// REQUIREMENT
		// Verify current player begins with 1 action
		if (PRE.numActions != 1) {
			printf("FAIL INIT - Iteration %d: game should start with number of actions = 1\n", i);
			num_tests_failed++;
			failed_game_state_flag = 1;
		}
		else {
			num_tests_passed++;
		}
		
		// Random paramaters are now set 
		//print_PRE_Decks(PRE);
		
		//Create pre/post copy of game state
		memcpy(&POST, &PRE, sizeof(struct gameState));
		
		// Play village card
		
		// REQUIREMENT
		// cardEffect must return zero
		if (cardEffect(village, 0, 0, 0, &POST, POST.handCount[z], 0) || FORCE_FAIL) {
			printf("FAIL REQ 1 - Iteration %d: cardEffect returned return error\n", i);
			num_tests_failed++;
			failed_game_state_flag = 1;
		}
		else {
			num_tests_passed++;
		}
		
		
		// REQUIREMENT
		// Current player's number of actions should increase by 2
		if(POST.numActions - 2 != PRE.numActions || FORCE_FAIL) {
			printf("FAIL REQ 2 - Iteration %d: Current player's number of actions should increase by 2\n", i);
			num_tests_failed++;
			failed_game_state_flag = 1;
		}
		else {
			num_tests_passed++;
		}

		// REQUIREMENT
		// Current player draws 1 cards, and discards 1, so net in the current player's hand is 0 cards
		if ((POST.handCount[current_player] != PRE.handCount[current_player]) || FORCE_FAIL){
			printf("FAIL REQ 3 - Iteration %d: Current player handCount Error\n", i);
			//printf("POST.handCount[%d] = %d, PRE.handCount[%d] = %d\n", current_player, POST.handCount[current_player], current_player, PRE.handCount[current_player]);
			num_tests_failed++;
			failed_game_state_flag = 1;
		}
		else {
			num_tests_passed++;
		}
		
		// REQUIREMENT
		// Other players receive NO new cards in their hand
		for (x = 1; x < POST.numPlayers; x++){ 
			if ((POST.handCount[x] != PRE.handCount[x]) || FORCE_FAIL) {
				printf("FAIL REQ 4 - Iteration %d: Other player[%d] received additional cards in hand\n", i, x);
				num_tests_failed++;
				failed_game_state_flag = 1;
			}
			else {
				num_tests_passed++;
			}
		}
		
		// REQUIREMENT
		// Current player's deck reduces by 1	
		if (POST.deckCount[current_player] + 1 != PRE.deckCount[current_player] || FORCE_FAIL) {
			printf("FAIL REQ 5 - Iteration %d: Current player deckCount should decrease by 1\n", i);
			num_tests_failed++;
			failed_game_state_flag = 1;
		}
		else {
			num_tests_passed++;
		}
			
		// REQUIREMENT
		// Other player's decks stay the same size
		int other_fail_flag = 0;
		for (x = 1; x < num_players; x++)  // start loop at 1 for other players because 0 is current_player
		{
			if (PRE.deckCount[x] != POST.deckCount[x] || FORCE_FAIL){
				printf("FAIL REQ 6 - Iteration %d: Other player deckCount Error: PRE.deckCount[%d]=%d, POST.deckCount[%d]=%d\n", i, x, PRE.deckCount[x], x, POST.deckCount[x]);
				other_fail_flag = 1;
			}
			if (other_fail_flag != 0) {
				failed_game_state_flag = 1;
				num_tests_failed++;
			}
			else {
				num_tests_passed++;
			}
		}
		
		// REQUIREMENT
		// Victory card piles should remain unchanged (estate, duchy, and province)
		if (PRE.supplyCount[estate] != POST.supplyCount[estate] 
			||   
			PRE.supplyCount[duchy] != POST.supplyCount[duchy]
			|| 
			PRE.supplyCount[province] != POST.supplyCount[province] 
			||
			FORCE_FAIL) {
				printf("FAIL REQ 7 - Iteration %d: Victory card piles should remain unchanged\n", i);
				num_tests_failed++;
				failed_game_state_flag = 1;
		}
		else {
			num_tests_passed++;
		}
	
		// REQUIREMENT
		// The following tests validate the remaining state variables are unchanged
		int rest_of_game_state_err = 0;
		if(PRE.numPlayers != POST.numPlayers || FORCE_FAIL)
			rest_of_game_state_err = 1;
		if(PRE.outpostPlayed != POST.outpostPlayed || FORCE_FAIL)
			rest_of_game_state_err = 1;		
		if(PRE.outpostTurn != POST.outpostTurn || FORCE_FAIL)
			rest_of_game_state_err = 1;			
		if(PRE.whoseTurn != POST.whoseTurn || FORCE_FAIL)
			rest_of_game_state_err = 1;		
		if(PRE.phase != POST.phase)
			rest_of_game_state_err = 1;	
		if(PRE.coins != POST.coins || FORCE_FAIL)
			rest_of_game_state_err = 1;		
		if(PRE.numBuys != POST.numBuys || FORCE_FAIL)
			rest_of_game_state_err = 1;		

		if (rest_of_game_state_err != 0) {
			printf("FAIL REQ 8 - Iteration %d: Variables changed in game state that should have remained the same\n", i);
			num_tests_failed++;
			failed_game_state_flag = 1;
		}
		else {
			num_tests_passed++;
		}
		
		// Update failed_game_state counter
		if (failed_game_state_flag == 1)
			num_failed_game_states++;
	}
	
	printf("\n%s - Random Test Summary\n", CARD_UNDER_TEST);
	printf("Number of Tested Game States = %d\n", i);
	printf("Number of Failed Game States = %d\n", num_failed_game_states);
	printf("Number of Passed Tests = %d\n", num_tests_passed);
	printf("Number of Failed Tests = %d\n", num_tests_failed);
}

int main() 
{
  rand_test_village();
  return 0;
}






