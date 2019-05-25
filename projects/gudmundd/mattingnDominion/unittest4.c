/*

	File:				unittest4.c
	
	Description:		Performs unit tests for the dominion game per Assignment 3 of CS362
	
	Card Tested:		remodel in dominion.c
	
	Makefile:			The following lines are added to the makefile provided in CS362
	
							unittest4: unittest4.c dominion.o rngs.o 
								gcc -o ct4 unittest4.c -g dominion.o rngs.o $(CFLAGS)

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

char CARD_UNDER_TEST[] = "remodel";	// string for printing the unit test name


int main (int argc, char** argv) {
	
	int current_player = 0;
	struct gameState G;
	struct gameState G_orig;
	int p;
	int i;
	int errr_1 = 0;
	int k[10] = {adventurer, gardens, embargo, village, minion, great_hall, remodel,  // change add remodel and great_hall
		   sea_hag, tribute, smithy};
	


	printf ("Starting Unit Test 4 - %s.\n", CARD_UNDER_TEST);
	
	int num_game_state_tests = 5;	// CHOOSE HIGHER VALUE FOR MORE GAME STATES
	int game_state_pass;
	for (game_state_pass = 1; game_state_pass <= num_game_state_tests; game_state_pass++)
	{
	
		int trashedCost;
		int gainedCost;
		int shouldPass = -99;
		int trashedCard;  // this is the index of the card in the current player's hand: valid values range from 0 to 4
		int gainedCard;	  // this is the actual card to be gained, such as province, or duchy
	
		printf("GAME STATE %d\n", game_state_pass);

		// REQUIREMENT
		// Current player's card that was gained costs up to 2 more than the trashed card
		
		// Card 1
		// ******************************
		initializeGame(4, k, game_state_pass, &G);
		memcpy(&G_orig, &G, sizeof(struct gameState));
		// Add the remodel card to the current player's hand
		G.hand[current_player][G.handCount[current_player]++] = remodel;
		
		// Set the trashed card (choice1) and gained card (choice2)
		int ret = -99;
		trashedCard = 3;      		
		trashedCost = getCost(G.hand[current_player][trashedCard]);
		gainedCard = gardens;
		gainedCost = getCost(gainedCard);
		//printf("trashedCost:%d  gainedCost:%d\n", trashedCost, gainedCost);
		if(trashedCost + 2 >= gainedCost)
			shouldPass = 1;
		else
			shouldPass = 0;
		// Execute the card function
		ret = cardEffect(remodel, trashedCard, gainedCard, 0, &G, G.hand[current_player][G.handCount[current_player]-1], 0);
		//printf("shouldPass:%d  ret:%d\n", shouldPass, ret);
		if ( shouldPass && ret == -1)
			printf("FAIL: gained card rejected, but cost was within bounds\n");
		else if (!shouldPass && ret == 0)
			printf("FAIL: gained card was accepted, but cost was too high\n");
		else if ( shouldPass && ret == 0)
			printf("PASS - gained card was accepted, and cost was within bounds\n");
		else if ( !shouldPass && ret == -1)
			printf("PASS - gained card rejected, because cost was too high\n");
		
 		// Card 2
		initializeGame(4, k, game_state_pass, &G);
		memcpy(&G_orig, &G, sizeof(struct gameState));
		// Add the remodel card to the current player's hand
		G.hand[current_player][G.handCount[current_player]++] = remodel;
		
		// Set the trashed card (choice1) and gained card (choice2)
		ret = -99;
		trashedCard = 3;      		
		trashedCost = getCost(G.hand[current_player][trashedCard]);
		gainedCard = embargo;
		gainedCost = getCost(gainedCard);
		//printf("trashedCost:%d  gainedCost:%d\n", trashedCost, gainedCost);
		if(trashedCost + 2 >= gainedCost)
			shouldPass = 1;
		else
			shouldPass = 0;
		// Execute the card function
		ret = cardEffect(remodel, trashedCard, gainedCard, 0, &G, G.hand[current_player][G.handCount[current_player]-1], 0);
		//printf("shouldPass:%d  ret:%d\n", shouldPass, ret);
		if ( shouldPass && ret == -1)
			printf("FAIL: gained card rejected, but cost was within bounds\n");
		else if (!shouldPass && ret == 0)
			printf("FAIL: gained card was accepted, but cost was too high\n");
		else if ( shouldPass && ret == 0)
			printf("PASS - gained card was accepted, and cost was within bounds\n");
		else if ( !shouldPass && ret == -1)
			printf("PASS - gained card rejected, because cost was too high\n");
			
 		// Card 3
		// ******************************
		initializeGame(4, k, game_state_pass, &G);
		memcpy(&G_orig, &G, sizeof(struct gameState));
		// Add the remodel card to the current player's hand
		G.hand[current_player][G.handCount[current_player]++] = remodel;
		
		// Set the trashed card (choice1) and gained card (choice2)
		ret = -99;
		trashedCard = 3;      		
		trashedCost = getCost(G.hand[current_player][trashedCard]);
		gainedCard = adventurer;
		gainedCost = getCost(gainedCard);
		//printf("trashedCost:%d  gainedCost:%d\n", trashedCost, gainedCost);
		if(trashedCost + 2 >= gainedCost)
			shouldPass = 1;
		else
			shouldPass = 0;
		// Execute the card function
		ret = cardEffect(remodel, trashedCard, gainedCard, 0, &G, G.hand[current_player][G.handCount[current_player]-1], 0);
		//printf("shouldPass:%d  ret:%d\n", shouldPass, ret);
		if ( shouldPass && ret == -1)
			printf("FAIL: gained card rejected, but cost was within bounds\n");
		else if (!shouldPass && ret == 0)
			printf("FAIL: gained card was accepted, but cost was too high\n");
		else if ( shouldPass && ret == 0)
			printf("PASS - gained card was accepted, and cost was within bounds\n");
		else if ( !shouldPass && ret == -1)
			printf("PASS - gained card rejected, because cost was too high\n");
			
		
		// END OF COST COMPARISON TESTS
		// Proceed to remaining requirements
		
		// Re-initialize game and continue with other requirements
		initializeGame(4, k, game_state_pass, &G);
		memcpy(&G_orig, &G, sizeof(struct gameState));
		// Add the remodel card to the current player's hand
		G.hand[current_player][G.handCount[current_player]++] = remodel;
		// Set the trashed card (choice1) and gained card (choice2)
		ret = -99;
		trashedCard = 3;
		gainedCard = embargo;  // cost = 2, so will always be gained relative to cost of trashed card
		// Execute the card function
		cardEffect(remodel, trashedCard, gainedCard, 0, &G, G.hand[current_player][G.handCount[current_player]-1], 0);
		
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
			
		// REQUIREMENT
		// The correct card is gained from the current player's hand, by verifying top card in discard pile
		i = 0;
		if (gainedCard != G.discard[i][G.discardCount[i]-1])
			printf("FAIL: not able to verify gained card\n");
		else
			printf("PASS - verified gained card is correct\n");
			
/* 		printf("top card of discard pile: %d\n", G.discard[i][G.discardCount[i]-1]);
		printf("gainedCard %d\n", gainedCard); */

	/* 	printf("G.discardCount[%d] = %d\n", i, G.discardCount[i]);
		printf("G_orig.discard[%d][%d] = %d\n", i, 0, G_orig.discard[i][0]);
		printf("G.discard[%d][%d] = %d\n", i, G.discardCount[i]-1, G.discard[i][G.discardCount[i]-1]);
		printf("G.discard[%d][%d] = %d\n", i, G.discardCount[i], G.discard[i][G.discardCount[i]]); */

		// REQUIREMENT
		// The current player actually trashed a card
		if (G_orig.handCount[i] != G.handCount[i] +1)
			printf("FAIL: not able to verify current player trashed a card\n");
		else
			printf("PASS - verified current player trashed a card\n");	
		
		// REQUIREMENT
		// The discard pile increases by 1 (due to gained card being discarded)
		if (G_orig.discardCount[i] +1 != G.discardCount[i])
			printf("FAIL: not able to verify current player discarded a card\n");
		else
			printf("PASS - verified current player's discard pile increased by 1\n");	
			
		// REQUIREMENT
		// Other player's decks are unchanged
		errr_1 = 1;
		for (i = 1; i < G.numPlayers; i++) {
			for (p = 0; p < G.deckCount[i]; p++) {
				if (G.deck[i][p] != G_orig.deck[i][p]) {
					printf("FAIL: Other player's deck changed: [%d][%d]\n", i, p);
					errr_1 = 0;
				}
			}
		}
		if (errr_1 == 1)
				printf("PASS - verified other player's decks remain unchanged\n");	
		
		// GENERAL REQUIREMENT
		// Except for the Current Player's number of cards increasing by 3, 
		// and the Current Player's deck count decreasing by 30, no other state change should occur.
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

