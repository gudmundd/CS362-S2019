/*

	File:				unittest3.c
	
	Description:		Performs unit tests for the dominion game per Assignment 3 of CS362
	
	Card Tested:		adventurer in dominion.c
	
	Makefile:			The following lines are added to the makefile provided in CS362
	
							unittest3: unittest3.c dominion.o rngs.o 
								gcc -o ct3 unittest3.c -g dominion.o rngs.o $(CFLAGS)

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

char CARD_UNDER_TEST[] = "adventurer";	// string for printing the unit test name

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

	printf ("Starting Unit Test 3 - %s.\n", CARD_UNDER_TEST);

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
		// Add the adventurer card to the current player's hand
		G.hand[current_player][G.handCount[current_player]++] = adventurer;
		
		int handCount_before_playing_adventurer;
		handCount_before_playing_adventurer = G.handCount[current_player];
		
		// Execute the card function
		//cardEffect(adventurer, 0, 0, 0, &G, G.hand[current_player][G.handCount[current_player]-1], 0);	// REQUIRED CHANGE for Assignment 5
		playAdventurer(&G, G.hand[current_player][G.handCount[current_player]-1]);						    // REQUIRED CHANGE for Assignment 5
			
		// REQUIREMENT
		// Current player's hand should increase by 2
		if (handCount_before_playing_adventurer + 2 != G.handCount[current_player]){
			printf("FAIL: Current player's hand should increase by 2 \n");
		}
		else
			printf("PASS - Current player's hand increased by 2 \n");

		// REQUIREMENT
		// The 2 additional cards in the current player's hand are treasure cards
		int added_treasure_card_1;
		int added_treasure_card_2;
		added_treasure_card_1 = G.hand[current_player][G.handCount[current_player]-1];
		added_treasure_card_2 = G.hand[current_player][G.handCount[current_player]-2];
		if ((added_treasure_card_1 != copper && added_treasure_card_1 != silver && added_treasure_card_1 != gold) 
		   &&
			(added_treasure_card_2 != copper && added_treasure_card_2 != silver && added_treasure_card_2 != gold))
		{
			printf("FAIL: Additional 2 cards in current player's hand must be treasure cards\n");
		}
		else
			printf("PASS - Additional 2 cards in current player's hand are treasure cards\n");
		
		// REQUIREMENT
		// The Current player's discard pile should increase by:
		// 	      current players's original deck size
		//        - (minus)
		//        current player's after deck size
		//        - (minus)
		//        2
		// This reflects the current player discarding all revealed cards that are not treasury cards
		if ((G_orig.deckCount[current_player] - G.deckCount[current_player] - 2) != G.discardCount[current_player])
			printf("FAIL: Current player should discard all revealed cards that are not treasury cards\n");
		else
			printf("PASS - Current player discarded all revealed cards that were not treasury cards\n");
		
		// REQUIREMENT
		// Other player's decks stay the same size
		errr_2 = 0;
		for (i=1; i<G.numPlayers; i++){
			if (G.deckCount[i] != G_orig.deckCount[i]){
				printf("FAIL: Other player deckCount Error: G.deckCount[%d]=%d, G_orig.deckCount[%d]=%d\n", i, G.deckCount[i], i, G_orig.deckCount[i]);
				errr_2 = 1;
			}
		}
		if (errr_2 == 0)
			printf("PASS - Other players' decks remain unchanged\n");
			
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
