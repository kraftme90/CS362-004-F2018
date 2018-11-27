/*******************************************************************************
* Author: Riley Kraft (kraftme)
* Date: 10/28/2018
* Description: This program is a unit test suite for the Salvager card of the 
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
    int handPos = 0, choice1 = 1, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int currentPlayer = 0;
    int opponent = 1;
	struct gameState G;
	int k[10] = {adventurer, council_room, village, minion, mine, salvager,
			sea_hag, tribute, smithy, treasure_map};

	initializeGame(numPlayers, k, seed, &G);
	
	G.whoseTurn = opponent;
	G.hand[opponent][handPos] = salvager;
	G.hand[opponent][handPos+1] = village;
	int op_handCount = G.handCount[opponent];
	int op_deckCount = G.deckCount[opponent];
	int op_discardCount = G.discardCount[opponent];

	G.whoseTurn = currentPlayer;
	G.hand[currentPlayer][handPos] = salvager;
	G.hand[currentPlayer][handPos+1] = village;
	int handCount = G.handCount[currentPlayer];
	int deckCount = G.deckCount[currentPlayer];
	int discardCount = G.discardCount[currentPlayer];
	int lastCard_1 = G.hand[currentPlayer][G.handCount[currentPlayer] - 2];
	int lastCard_2 = G.hand[currentPlayer][G.handCount[currentPlayer] - 1];
	
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
	
/*
	int embargoTokens[treasure_map+1];
	int outpostPlayed;
	int outpostTurn;
*/
	
	printf("\n--------------- Begin card-3-Salvager Tests ---------------\n");
	 
	int returnValue = cardEffect(salvager, choice1, choice2, choice3, &G, handPos, &bonus);

	printf("\nTEST-1: return value = 0\n");
	if(returnValue == 0)
		printf( "PASS" );
	else
		printf( "FAIL: return value = %d" , returnValue);
	
	printf("\nTEST-2: currentPlayer's handCount - Salvager - trashed card\n");
	if(G.handCount[currentPlayer] == handCount - 2)
		printf( "PASS" );
	else
		printf( "FAIL: handCount changed from %d to %d" , handCount, G.handCount[currentPlayer]);
	  
	printf("\nTEST-3: currentPlayer's deckCount didn't change\n");
	if(G.deckCount[currentPlayer] == deckCount)
		printf( "PASS" );
	else
		printf( "FAIL: deckCount changed from %d to %d" , deckCount, G.deckCount[currentPlayer]);
	
	printf("\nTEST-4: currentPlayer's discardCount didn't change\n");
	if(G.discardCount[currentPlayer] == discardCount)
		printf( "PASS" );
	else
		printf( "FAIL: discardCount changed from %d to %d" , discardCount, G.discardCount[currentPlayer]);
	
	printf("\nTEST-5: choice1(Village) is set to be trashed, not discarded, at end of turn\n");
	if(G.hand[currentPlayer][1] == lastCard_1 && G.hand[currentPlayer][G.handCount[currentPlayer]] == -1 &&
	   G.playedCards[G.playedCardCount-2] != village){
		printf( "PASS" );
	}
	else{
		printf( "FAIL: choice1(Village) is not set to be trashed at end of player's turn" );
	}
	
	printf("\nTEST-6: Salvager set to be discarded at end of turn\n");
	if(G.hand[currentPlayer][0] == lastCard_2 && G.hand[currentPlayer][G.handCount[currentPlayer]+1] == -1)
		printf( "PASS" );
	else
		printf( "FAIL: Salvager is not set to be discarded at end of player's turn" );
	
	printf("\nTEST-7: playedCardCount + 1\n");
	if(G.playedCardCount == playedCardCount + 1)
		printf( "PASS" );
	else
		printf( "FAIL: playedCardCount changed from %d to %d" , playedCardCount, G.playedCardCount);
	
	printf("\nTEST-8: last played card was Salvager\n");
	if(G.playedCards[G.playedCardCount-1] == salvager)
		printf( "PASS" );
	else
		printf( "FAIL: last playedCard was not Salvager" );
	
	printf("\nTEST-9: numPlayers didn't change\n");
	if(G.numPlayers == numPlayers)
		printf( "PASS" );
	else
		printf( "FAIL: numPlayers changed from %d to %d" , numPlayers, G.numPlayers);
	
	printf("\nTEST-10: still currentPlayer's turn\n");
	if(G.whoseTurn == currentPlayer)
		printf( "PASS" );
	else
		printf( "FAIL: whoseTurn changed from %d to %d" , currentPlayer, G.whoseTurn);
		
	printf("\nTEST-11: game phase didn't change\n");
	if(G.phase == phase)
		printf( "PASS" );
	else
		printf( "FAIL: game phase changed from %d to %d" , phase, G.phase);
		
	printf("\nTEST-12: numActions didn't change\n");
	if(G.numActions == numActions)
		printf( "PASS" );
	else
		printf( "FAIL: numActions changed from %d to %d" , numActions, G.numActions);
	
	printf("\nTEST-13: numBuys + 1\n");
	if(G.numBuys == numBuys + 1)
		printf( "PASS" );
	else
		printf( "FAIL: numBuys changed from %d to %d" , numBuys, G.numBuys);
	
	printf("\nTEST-14: currentPlayer's coins increased by value of choice1(Village)\n");
	if(G.coins == coins + 3)
		printf( "PASS" );
	else
		printf( "FAIL: currentPlayer's coins changed from %d to %d" , coins, G.coins);
	
	printf("\nTEST-15: opponent's handCount didn't change\n");
	if(G.handCount[opponent] == op_handCount)
		printf( "PASS" );
	else
		printf( "FAIL: opponent's handCount changed from %d to %d" , op_handCount, G.handCount[opponent]);
	  
	printf("\nTEST-16: opponent's deckCount didn't change\n");
	if(G.deckCount[opponent] == op_deckCount)
		printf( "PASS" );
	else
		printf( "FAIL: opponent's deckCount changed from %d to %d" , op_deckCount, G.deckCount[opponent]);
	
	printf("\nTEST-17: opponent's discardCount didn't change\n");
	if(G.discardCount[opponent] == op_discardCount)
		printf( "PASS" );
	else
		printf( "FAIL: opponent's discardCount changed from %d to %d" , op_discardCount, G.discardCount[opponent]);
	
	printf("\nTEST-18: Curse supply didn't change\n");
	if(G.supplyCount[curse] == curseCount){
		printf( "PASS" );
	}
	else{
		printf( "FAIL: Curse supply changed" );
	}
	
	printf("\nTEST-19: Victory supplies didn't change\n");
	if(G.supplyCount[estate] == estateCount &&
	   G.supplyCount[duchy] == duchyCount &&
	   G.supplyCount[province] == provinceCount){
		printf( "PASS" );
	}
	else{
		printf( "FAIL: at least one Victory supply changed" );
	}
	
	printf("\nTEST-20: Treasure supplies didn't change\n");
	if(G.supplyCount[copper] == copperCount &&
	   G.supplyCount[silver] == silverCount &&
	   G.supplyCount[gold] == goldCount){
		printf( "PASS" );
	}
	else{
		printf( "FAIL: at least one Treasure supply changed" );
	}
	
	printf("\nTEST-21: Kingdom supplies didn't change\n");
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
	
	printf("\n\n---------------- End card-3-Salvager Tests ----------------\n\n");
	
	return 0;
}