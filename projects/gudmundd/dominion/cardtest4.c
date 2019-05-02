/*

	File:				cardtest4.c
	
	Description:		Performs unit tests for the dominion game per Assignment 3 of CS362
	
	Card Tested:		cardtest4 in dominion.c
	
	Makefile:			The following lines are added to the makefile provided in CS362
	
							cardtest4: cardtest4.c dominion.o rngs.o 
								gcc -o ct4 cardtest4.c -g dominion.o rngs.o $(CFLAGS)

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

void print_game_state(struct gameState G, struct gameState G_orig);

char CARD_UNDER_TEST[] = "village";	// string for printing the unit test name


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

	printf ("Starting Card Test 4 - %s.\n", CARD_UNDER_TEST);

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
			
		// Add the village card to the current player's hand
		G.hand[current_player][G.handCount[current_player]++] = village;
		// Execute the card function
		cardEffect(village, 0, 0, 0, &G, G.hand[current_player][G.handCount[current_player]-1], 0);
		
		if(PRINT_STATE)
			print_game_state(G, G_orig);
		
		// REQUIREMENT
		// Current player's number of actions should increase by 2
		if(G.numActions-2 != G_orig.numActions)
			printf("FAIL: Current player's number of actions should increase by 2\n");
		else
			printf("PASS - Current player's number of action increased by 2\n");

		// REQUIREMENT
		// Current player draws 1 cards, and discards 1, after already receiving village, so net add is 1
		for (i=0; i<G.numPlayers; i++){
			if (i==0){
				if ((G.handCount[i] - 1 != G_orig.handCount[i]) || FORCE_FAIL){
					printf("FAIL: Current player handCount Error: G.handCount[%d]=%d, G_orig.handCount[%d]=%d\n", i, G.handCount[i], i, G_orig.handCount[i]);
					errr_1 = 1;
				}
			}
		// REQUIREMENT
		// Other players receive NO cards
			if (i > 0){
				if ((G.handCount[i] != G_orig.handCount[i]) || FORCE_FAIL){
					printf("FAIL: Other player handCount Error: G.handCount[%d]=%d, G_orig.handCount[%d]=%d\n", i, G.handCount[i], i, G_orig.handCount[i]);
					errr_2 = 1;
				}
			}
		}
		if (errr_1 == 0)
			printf("PASS - Current player's handCount increases by 3 (+1 village, +1 drawn, -1 discard = 3)\n");
		if (errr_2 == 0)
			printf("PASS - Other players' handCounts remain unchanged\n");

		// REQUIREMENT
		// Current player's deck reduces by 1	
		errr_1 = errr_2 = 0;
		for (i=0; i<G.numPlayers; i++){
			if (i==0){
				if (G.deckCount[i] + 1 != G_orig.deckCount[i]){
					printf("FAIL: Current player deckCount Error: G.deckCount[%d]=%d, G_orig.deckCount[%d]=%d\n", i, G.deckCount[i], i, G_orig.deckCount[i]);
					errr_1 = 1;
				}
			}
		// REQUIREMENT
		// Other player's decks stay the same size
			if (i > 0){
				if (G.deckCount[i] != G_orig.deckCount[i]){
						printf("FAIL: Other player deckCount Error: G.deckCount[%d]=%d, G_orig.deckCount[%d]=%d\n", i, G.deckCount[i], i, G_orig.deckCount[i]);
						errr_2 = 1;
					}
				}
		}
		if (errr_1 == 0)
			printf("PASS - Current player's deck reduces by 3\n");
		if (errr_2 == 0)
			printf("PASS - Other players' decks remain unchanged\n");

		// REQUIREMENT
		// Current player's original cards don't change (only 3 new cards were added)
		// printf("G.discardCount[%d] = %d \n", player, G.discardCount[player]);
		errr_1 = 0;
		for (p = 0; p < G_orig.handCount[current_player]; p++){			// count to original hand count to exclude new cards
			if (G_orig.hand[current_player][p] != G.hand[current_player][p]){
				printf("FAIL: Current player's original cards should remain unchanged: G_orig.hand[%d]{%d] == %d != G.hand[%d][%d] = %d\n", current_player, p, G_orig.hand[current_player][p], current_player, p, G.hand[current_player][p]);
				errr_1 = 1;
			}
		}
		if (errr_1 == 0)
			printf("PASS - Current player's original hand remains unchanged\n");
		
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
		// Except for the Current Player's number of cards increasing by 3, 
		// and the Current Player's deck count decreasing by 30, no other state change should occur.
		// The following tests validate remaining state variables are unchanged
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



void print_game_state(struct gameState G, struct gameState G_orig)
{
		int i, j;
		printf("numPlayers=%d\n", G_orig.numPlayers);
		printf("numPlayers=%d\n", G.numPlayers);
		for (i=0; i<G_orig.numPlayers; i++)
			printf("handCount[%d]=%d ", i, G_orig.handCount[i]);
		printf("\n");
		for (i=0; i<G.numPlayers; i++)
			printf("handCount[%d]=%d ", i, G.handCount[i]);
		printf("\n");
		for (i=0; i<G_orig.numPlayers; i++)
			printf("deckCount[%d]=%d ", i, G_orig.deckCount[i]);
		printf("\n");
		for (i=0; i<G.numPlayers; i++)
			printf("deckCount[%d]=%d ", i, G.deckCount[i]);
		printf("\n");
		for (i=0; i<G_orig.numPlayers; i++)
			printf("discardCount[%d]=%d ", i, G_orig.discardCount[i]);
		printf("\n");
		for (i=0; i<G.numPlayers; i++)
			printf("discardCount[%d]=%d ", i, G.discardCount[i]);
		printf("\n");
		for (i=0; i<G_orig.playedCardCount; i++)
			printf("playedCards[%d]=%d ", i, G_orig.playedCards[i]);
		printf("\n");
		for (i=0; i<G.playedCardCount; i++)
			printf("playedCards[%d]=%d ", i, G.playedCards[i]);
		printf("\n");
		printf("playedCardCount=%d\n", G_orig.playedCardCount);
		printf("playedCardCount=%d\n", G.playedCardCount);
		for (i=0; i<G_orig.numPlayers; i++){
			for (j=0; j<G_orig.handCount[i]; j++)
			{
				printf("hand[%d,%d]=%d ", i, j, G_orig.hand[i][j]);
			}
			if (j != 0)
				printf("\n");
		}
		for (i=0; i<G.numPlayers; i++){
			for (j=0; j<G.handCount[i]; j++)
			{
				printf("hand[%d,%d]=%d ", i, j, G.hand[i][j]);
			}
			if (j != 0)
				printf("\n");
		}
		for (i=0; i<G_orig.numPlayers; i++){
			for (j=0; j<G_orig.deckCount[i]; j++)
			{
				printf("deck[%d,%d]=%d ", i, j, G_orig.deck[i][j]);
			}
			if (j != 0)
				printf("\n");
		}
		for (i=0; i<G.numPlayers; i++){
			for (j=0; j<G.deckCount[i]; j++)
			{
				printf("deck[%d,%d]=%d ", i, j, G.deck[i][j]);
			}
			if (j != 0)
				printf("\n");
		}
		for (i=0; i<G_orig.numPlayers; i++){
			for (j=0; j<G_orig.discardCount[i]; j++)
			{
				printf("discard[%d,%d]=%d ", i, j, G_orig.discard[i][j]);
			}
			if (j != 0)
				printf("\n");
		}
		for (i=0; i<G.numPlayers; i++){
			for (j=0; j<G.discardCount[i]; j++)
			{
				printf("discard[%d,%d]=%d ", i, j, G.discard[i][j]);
			}
			if (j != 0)
				printf("\n");
		}
		for (i=0; i<G_orig.numPlayers; i++){
			for (j=0; j<G_orig.discardCount[i]; j++)
			{
				printf("discard[%d,%d]=%d ", i, j, G_orig.discard[i][j]);
			}
			if (j != 0)
				printf("\n");
		}
}

