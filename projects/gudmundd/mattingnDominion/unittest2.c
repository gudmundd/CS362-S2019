/*

	File:				unittest2.c
	
	Description:		Performs unit tests for the dominion game per Assignment 3 of CS362
	
	Card Tested:		sea_hag in dominion.c
	
	Makefile:			The following lines are added to the makefile provided in CS362
	
							unittest2: unittest2.c dominion.o rngs.o 
								gcc -o ct2 unittest2.c -g dominion.o rngs.o $(CFLAGS)

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

char CARD_UNDER_TEST[] = "sea_hag";	// string for printing the unit test name

int main (int argc, char** argv) {
	int current_player = 0;
	struct gameState G;
	struct gameState G_orig;
	int p;
	int i;
	int errr_1 = 0;
	int errr_2 = 0;
	int errr_3 = 0;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
		   sea_hag, tribute, smithy};

	printf ("Starting Unit Test 2 - %s.\n", CARD_UNDER_TEST);

	int num_game_state_tests = 3;	// CHOOSE HIGHER VALUE FOR MORE GAME STATES
	int game_state_pass;
	for (game_state_pass = 1; game_state_pass <= num_game_state_tests; game_state_pass++)
	{
		printf("GAME STATE %d\n", game_state_pass);
		initializeGame(4, k, game_state_pass, &G);
		memcpy(&G_orig, &G, sizeof(struct gameState));
		
		if (PRINT_DECKS){
			for (p = 0; p < G_orig.handCount[current_player]; p++){
				printf("G.hand before [%d][%d] = %d\n", current_player, p, G_orig.hand[current_player][p]);
				printf("G.hand after  [%d][%d] = %d\n", current_player, p, G.hand[current_player][p]);
				printf("\n");
			}
		}
		if (PRINT_DECKS){
			for (p = 0; p < G.deckCount[current_player]; p++){
				printf("G.deck before [%d][%d] = %d\n", current_player, p, G_orig.deck[current_player][p]);
				printf("G.deck after  [%d][%d] = %d\n", current_player, p, G.deck[current_player][p]);
				printf("\n");
			}
		} 

		G.hand[current_player][G.handCount[current_player]++] = sea_hag;
		// Execute the card function
		cardEffect(sea_hag, 0, 0, 0, &G, G.hand[current_player][G.handCount[current_player]-1], 0);
			
		// REQUIREMENT 1
		// Each other player (not the current player) gains a Curse card 
		errr_1 = 0;
		for (i = 0; i < G.numPlayers; i++){		
			//printf("G.deck[%d][%d]=%d\n", i, G.deckCount[i]-1, G.deck[i][G.deckCount[i]-1]);
			if (i != 0) {
				if( G.deck[i][G.deckCount[i]-1] != curse) {
					printf("FAIL - Other players gain Curse card: G.deck[%d][%d]=%d\n", i, G.deckCount[i]-1, G.deck[i][G.deckCount[i]-1]);
					errr_1 = 1;
				}
			}
		}
		if (errr_1 == 0) printf("PASS - Other Players gain Curse card\n");		

		// REQUIREMENT 2
		// Each other player's deck size stays the same because 
		//    other players discard a card and gain a card
		errr_1 = 0;
		for (i=0; i<G.numPlayers; i++) {
			if (G.deckCount[i] != G_orig.deckCount[i]) {
				printf("FAIL - G.deckCount[%d] != G_orig.deckout[%d]\n", i, i);
				errr_1 = 1;
			}
		}
		if (errr_1 == 0) printf("PASS - Other player discard a card and gain a card\n");

		// REQUIREMENT 3
		// Each other player's discard deck increases in size by 1
		// Current player's discard deck is unchanged
		errr_1 = 0;
		for (i=0; i<G_orig.numPlayers; i++) {
			if (i != 0) {
				if (G.discardCount[i]-1 != G_orig.discardCount[i]) {
					printf("FAIL - Other Player: G.discardCount[%d] - 1 != G_orig.discardCount[%d] - 1\n", i, i);
					errr_1 = 1;
				}
			}
		}
		if (errr_1 == 0) printf("PASS - Other players discard a card\n");

		// REQUIREMENT 4
		// Current player's deck remains unchanged
		int j;
		i = 0;
		errr_1 = 0;
		for (j = 0; j < G_orig.deckCount[i]; j++){
			if(G_orig.deck[i][j] != G.deck[i][j]){
				printf("FAIL - Current Player's Deck Remains Unchanged: G_orig.deck[%d][%d]=%d --- G.deck[%d][%d]=%d\n", i, j, G_orig.deck[i][j], i, j, G.deck[i][j]);
				errr_1 = 1;
			}
		}
		if (errr_1 == 0) printf("PASS - Current Player's Deck Remains Unchanged\n");
		
		// REQUIREMENT
		// Victory card piles should remain unchanged (estate, duchy, and province)
		errr_1 = errr_2 = errr_3 = 0;
		if (G_orig.supplyCount[estate] != G.supplyCount[estate]) {
		   printf("FAIL: Estate card count should remain unchanged\n");
		   errr_1 = 1;
		}

		  if (G_orig.supplyCount[duchy] != G.supplyCount[duchy]) {
		   printf("FAIL: Duchy card count should remain unchanged\n");
		   errr_2 = 1;
		}

		if (G_orig.supplyCount[province] != G.supplyCount[province]) {
		   printf("FAIL: Province card count should remain unchanged\n");
		   errr_3 = 1;
		}
		if (errr_1 == 0 && errr_2 == 0 && errr_3 == 0)
			printf("PASS - Victory card piles (estate, duchy, province) remain unchanged \n");
		
		// REQUIREMENT
		// The size of the curse pile should reduce by n-1, where n is the number of players
		errr_1 = 1;
		if ((G_orig.supplyCount[curse] -(G_orig.numPlayers-1)) != G.supplyCount[curse]){
			printf("FAIL: size of curse pile should decrease by n-1, where n is the number of players\n");
			errr_1 = 0;
		}
		else
			printf("PASS - Curse pile reduced by the correct amount \n");
			
		// REQUIREMENT
		// The size of the discard pile for the other players should increase by 1
		errr_1 = 1;
		for (i=1; i<G_orig.numPlayers; i++) { // only cycle through other players
			if ((G_orig.discardCount[i] + 1) != G.discardCount[i])
			{
				printf("FAIL: discard pile for other player %d did not increase by 1\n", i);
				errr_1 = 0;
			}
		}
		if (errr_1 == 1)
			printf("PASS - Discard piles for other players all increased by 1 \n");
		
		// GENERAL REQUIREMENT
		// The following tests validate the remaining state variables are unchanged
		errr_1 = 0;
		if(G.numPlayers != G_orig.numPlayers)
			errr_1 = 1;
		if(G.outpostPlayed != G_orig.outpostPlayed)
			errr_1 = 1;		
		if(G.outpostTurn != G_orig.outpostTurn)
			errr_1 = 1;			
		if(G.whoseTurn != G_orig.whoseTurn)
			errr_1 = 1;		
		if(G.phase != G_orig.phase)
			errr_1 = 1;	
		if(G.numActions != G_orig.numActions)
			errr_1 = 1;		
		if(G.coins != G_orig.coins)
			errr_1 = 1;		
		if(G.numBuys != G_orig.numBuys)
			errr_1 = 1;		
		// Print result
		if (errr_1 == 0)
			printf("PASS - Remaining game state variables unchanged\n");
		else
			printf("FAIL - Remaining game state variables should not change\n");	
	}
		
	return 0;
}
