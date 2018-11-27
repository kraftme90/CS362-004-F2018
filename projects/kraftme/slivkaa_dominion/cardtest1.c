/*******************************************************************************
* Author: Riley Kraft (kraftme)
* Date: 10/28/2018
* Description: This program is a unit test suite for the Adventurer card of the 
* 				dominion.c file. When run, this will test for the correct
* 				outcome of this function in regards to the gameState, player,
* 				opponent, and supply cards. See test titles for more information.
* Sources:
* 	Assignment 3 Assistance (1) bst_assgn3.zip
* 	Assignment 3 Assistance (2) testUpdateCoins.c
* 	Assignment 3: Test something vs Testing for business rules cardtest4.c
* 	https://stackoverflow.com/questions/3585846/color-text-in-terminal-applications-in-unix
*******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

/*
#define RED   "\x1b[31m"
#define GRN   "\x1b[32m"
#define RESET "\x1b[0m"
*/

int main ()	{
    int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int currentPlayer = 0;
    int opponent = 1;
	struct gameState G;
	int k[10] = {adventurer, council_room, village, minion, mine, salvager,
			sea_hag, tribute, smithy, treasure_map};

	initializeGame(numPlayers, k, seed, &G);
	
	G.whoseTurn = opponent;
	G.hand[opponent][handPos] = adventurer;
	G.deck[opponent][G.deckCount[opponent]-1] = copper;
	G.deck[opponent][G.deckCount[opponent]-2] = estate;
	G.deck[opponent][G.deckCount[opponent]-3] = silver;
	int op_handCount = G.handCount[opponent];
	int op_deckCount = G.deckCount[opponent];
	int op_discardCount = G.discardCount[opponent];
	int op_deckCard_1 = G.deck[opponent][G.deckCount[opponent]-1];
	int op_deckCard_2 = G.deck[opponent][G.deckCount[opponent]-2];
	int op_deckCard_3 = G.deck[opponent][G.deckCount[opponent]-3];

	G.whoseTurn = currentPlayer;
	G.hand[currentPlayer][handPos] = adventurer;
	G.deck[currentPlayer][G.deckCount[currentPlayer]-1] = copper;
	G.deck[currentPlayer][G.deckCount[currentPlayer]-2] = estate;
	G.deck[currentPlayer][G.deckCount[currentPlayer]-3] = silver;
	int handCount = G.handCount[currentPlayer];
	int deckCount = G.deckCount[currentPlayer];
	int discardCount = G.discardCount[currentPlayer];
	int lastCard = G.hand[currentPlayer][G.handCount[currentPlayer] - 1];
	
	int curseCount = G.supplyCount[curse];
	
	int estateCount = G.supplyCount[estate];
	int duchyCount = G.supplyCount[duchy];
	int provinceCount = G.supplyCount[province];
		
	int copperCount = G.supplyCount[copper];
	int silverCount = G.supplyCount[silver];
	int goldCount = G.supplyCount[gold];
	
	int adventurerCount = G.supplyCount[adventurer];
	int council_roomCount = G.supplyCount[council_room];
	int villageCount = G.supplyCount[village];
	int minionCount = G.supplyCount[minion];
	int mineCount = G.supplyCount[mine];
	int salvagerCount = G.supplyCount[salvager];
	int sea_hagCount = G.supplyCount[sea_hag];
	int tributeCount = G.supplyCount[tribute];
	int smithyCount = G.supplyCount[smithy];	
	int treasure_mapCount = G.supplyCount[treasure_map];
	
	int phase = G.phase;
	int numActions = G.numActions;
	int numBuys = G.numBuys;
	int coins = G.coins;
	int playedCardCount = G.playedCardCount;
	
/*  Not part of game
	int embargoTokens[treasure_map+1];
	int outpostPlayed;
	int outpostTurn;
*/
	
	printf("\n--------------- Begin card-1-Adventurer Tests ---------------\n");
	 
	int returnValue = cardEffect(adventurer, choice1, choice2, choice3, &G, handPos, &bonus);

	printf("\nTEST-1: return value = 0\n");
	if(returnValue == 0)
		printf( "PASS" );
	else
		printf( "FAIL: return value = %d" , returnValue);
	
	printf("\nTEST-2: currentPlayer's handCount - Adventurer + 2 Treasures\n");
	if(G.handCount[currentPlayer] == handCount + 1)
		printf( "PASS" );
	else
		printf( "FAIL: handCount changed from %d to %d" , handCount, G.handCount[currentPlayer]);
	  
	printf("\nTEST-3: currentPlayer's deckCount - cards drawn until 2 Treasures found\n");
	if(G.deckCount[currentPlayer] == deckCount - 3)
		printf( "PASS" );
	else
		printf( "FAIL: deckCount changed from %d to %d" , deckCount, G.deckCount[currentPlayer]);
	
	printf("\nTEST-4: 2 new cards in currentPlayer's hand are Treasures gained from currentPlayer's deck\n");
	if((G.hand[currentPlayer][G.handCount[currentPlayer]-1] == copper || silver || gold) &&
	   (G.hand[currentPlayer][G.handCount[currentPlayer]-2] == copper || silver || gold)){
		printf( "PASS" );
	}
	else{
		printf( "FAIL: new cards in hand are not Treasures" );
	}
	
	printf("\nTEST-5: currentPlayer's discardCount + Non-Treasure drawn cards\n");
	if(G.discardCount[currentPlayer] == discardCount + 1)
		printf( "PASS" );
	else
		printf( "FAIL: discardCount changed from %d to %d" , discardCount, G.discardCount[currentPlayer]);
	
	printf("\nTEST-6: Adventurer set to be discarded at end of turn\n");
	if(G.hand[currentPlayer][3] == lastCard && G.hand[currentPlayer][G.handCount[currentPlayer]] == -1)
		printf( "PASS" );
	else
		printf( "FAIL: Adventurer is not set to be discarded at end of player's turn" );
	
	printf("\nTEST-7: Non-Treasure cards drawn were discarded\n");
	if(G.discard[currentPlayer][G.discardCount[currentPlayer]-1] == estate){
		printf( "PASS" );
	}
	else{
		printf( "FAIL: Non-Treasure drawn cards were not discarded" );
	}
	
	printf("\nTEST-8: playedCardCount + Adventurer; Non-Treasure drawn cards are not 'played', just discarded\n");
	if(G.playedCardCount == playedCardCount + 1)
		printf( "PASS" );
	else
		printf( "FAIL: playedCardCount changed from %d to %d" , playedCardCount, G.playedCardCount);
	
	printf("\nTEST-9: last played card was Adventurer\n");
	if(G.playedCards[G.playedCardCount-1] == adventurer)
		printf( "PASS" );
	else
		printf( "FAIL: last playedCard was not Adventurer" );
	
	printf("\nTEST-10: Last discarded card was the Non-Treasure drawn card\n");
	if(G.discard[currentPlayer][G.discardCount[currentPlayer]-1] == estate){
		printf( "PASS" );
	}
	else{
		printf( "FAIL: 2nd to last played card was not the Non-Treasure drawn card" );
	}
	
	printf("\nTEST-11: numPlayers didn't change\n");
	if(G.numPlayers == numPlayers)
		printf( "PASS" );
	else
		printf( "FAIL: numPlayers changed from %d to %d" , numPlayers, G.numPlayers);
	
	printf("\nTEST-12: still currentPlayer's turn\n");
	if(G.whoseTurn == currentPlayer)
		printf( "PASS" );
	else
		printf( "FAIL: whoseTurn changed from %d to %d" , currentPlayer, G.whoseTurn);
		
	printf("\nTEST-13: game phase didn't change\n");
	if(G.phase == phase)
		printf( "PASS" );
	else
		printf( "FAIL: game phase changed from %d to %d" , phase, G.phase);
		
	printf("\nTEST-14: numActions didn't change\n");
	if(G.numActions == numActions)
		printf( "PASS" );
	else
		printf( "FAIL: numActions changed from %d to %d" , numActions, G.numActions);
	
	printf("\nTEST-15: numBuys didn't change\n");
	if(G.numBuys == numBuys)
		printf( "PASS" );
	else
		printf( "FAIL: numBuys changed from %d to %d" , numBuys, G.numBuys);
	
	printf("\nTEST-16: currentPlayer's coins didn't change\n");
	if(G.coins == coins)
		printf( "PASS" );
	else
		printf( "FAIL: currentPlayer's coins changed from %d to %d" , coins, G.coins);
	
	printf("\nTEST-17: opponent's handCount didn't change\n");
	if(G.handCount[opponent] == op_handCount)
		printf( "PASS" );
	else
		printf( "FAIL: opponent's handCount changed from %d to %d" , op_handCount, G.handCount[opponent]);
	  
	printf("\nTEST-18: opponent's deckCount didn't change\n");
	if(G.deckCount[opponent] == op_deckCount)
		printf( "PASS" );
	else
		printf( "FAIL: opponent's deckCount changed from %d to %d" , op_deckCount, G.deckCount[opponent]);
	
	printf("\nTEST-19: 3 cards on top of opponent's deck didn't change\n");
	if(G.deck[opponent][G.deckCount[opponent]-1] == op_deckCard_1 &&
	   G.deck[opponent][G.deckCount[opponent]-2] == op_deckCard_2 &&
	   G.deck[opponent][G.deckCount[opponent]-3] == op_deckCard_3){
		printf( "PASS" );
	}
	else{
		printf( "FAIL: cards from top of opponent's deck changed" );
	}
	
	printf("\nTEST-20: opponent's discardCount didn't change\n");
	if(G.discardCount[opponent] == op_discardCount)
		printf( "PASS" );
	else
		printf( "FAIL: opponent's discardCount changed from %d to %d" , op_discardCount, G.discardCount[opponent]);
	
	printf("\nTEST-21: Curse supply didn't change\n");
	if(G.supplyCount[curse] == curseCount){
		printf( "PASS" );
	}
	else{
		printf( "FAIL: Curse supply changed" );
	}
	
	printf("\nTEST-22: Victory supplies didn't change\n");
	if(G.supplyCount[estate] == estateCount &&
	   G.supplyCount[duchy] == duchyCount &&
	   G.supplyCount[province] == provinceCount){
		printf( "PASS" );
	}
	else{
		printf( "FAIL: at least one Victory supply changed" );
	}
	
	printf("\nTEST-23: Treasure supplies didn't change\n");
	if(G.supplyCount[copper] == copperCount &&
	   G.supplyCount[silver] == silverCount &&
	   G.supplyCount[gold] == goldCount){
		printf( "PASS" );
	}
	else{
		printf( "FAIL: at least one Treasure supply changed" );
	}
	
	printf("\nTEST-24: Kingdom supplies didn't change\n");
	if(G.supplyCount[adventurer] == adventurerCount &&
	   G.supplyCount[council_room] == council_roomCount &&
	   G.supplyCount[village] == villageCount &&
	   G.supplyCount[minion] == minionCount &&
	   G.supplyCount[mine] == mineCount &&
	   G.supplyCount[salvager] == salvagerCount &&
	   G.supplyCount[sea_hag] == sea_hagCount &&
	   G.supplyCount[tribute] == tributeCount &&
	   G.supplyCount[smithy] == smithyCount &&
	   G.supplyCount[treasure_map] == treasure_mapCount){
		printf( "PASS" );
	}
	else{
		printf( "FAIL: at least one Kingdom supply changed" );
	}
	
	printf("\n\n---------------- End card-1-Adventurer Tests ----------------\n\n");
	
	return 0;
}