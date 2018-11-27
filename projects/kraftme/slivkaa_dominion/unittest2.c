/*******************************************************************************
* Author: Riley Kraft (kraftme)
* Date: 10/28/2018
*  Description: This program is a unit test suite for the buyCard() function
* 				of the dominion.c file. When run, this will test for the correct
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
#define RED "\x1b[31m"
#define GRN "\x1b[32m"
#define RESET "\x1b[0m"
*/

/* GLOBALS */
const int supplyPos = province;
const int seed = 1000;
int numPlayers;
const int currentPlayer = 0;
const int opponent = 1;
struct gameState G;

int op_handCount, op_deckCount, op_discardCount,op_fullDeckCount;
int handCount, deckCount, discardCount, cp_fullDeckCount;
int curseCount;
int estateCount, duchyCount, provinceCount;
int copperCount, silverCount, goldCount;
int adventurerCount, council_roomCount, villageCount, minionCount, mineCount, salvagerCount, sea_hagCount, tributeCount, smithyCount, treasure_mapCount;
int phase, numActions, numBuys, coins, playedCardCount;
	
/*
int embargoTokens[treasure_map+1];
int outpostPlayed;
int outpostTurn;
*/

void noChange();

int main(){
	numPlayers = 2;
	int k[10] = {adventurer, council_room, village, minion, mine, salvager,
			sea_hag, tribute, smithy, treasure_map};

	initializeGame(numPlayers, k, seed, &G);
	
	op_handCount = G.handCount[opponent];
	op_deckCount = G.deckCount[opponent];
	op_discardCount = G.discardCount[opponent];
	op_fullDeckCount = G.deckCount[opponent] + G.handCount[opponent] + G.discardCount[opponent];
	
	G.whoseTurn = currentPlayer;
	handCount = G.handCount[currentPlayer];
	deckCount = G.deckCount[currentPlayer];
	discardCount = G.discardCount[currentPlayer];
	cp_fullDeckCount = G.deckCount[currentPlayer] + G.handCount[currentPlayer] + G.discardCount[currentPlayer];
	
	curseCount = G.supplyCount[curse];
	
	estateCount = G.supplyCount[estate];
	duchyCount = G.supplyCount[duchy];
	provinceCount = G.supplyCount[province];
		
	copperCount = G.supplyCount[copper];
	silverCount = G.supplyCount[silver];
	goldCount = G.supplyCount[gold];
	
	adventurerCount = G.supplyCount[adventurer];
	council_roomCount = G.supplyCount[council_room];
	villageCount = G.supplyCount[village];
	minionCount = G.supplyCount[minion];
	mineCount = G.supplyCount[mine];
	salvagerCount = G.supplyCount[salvager];
	sea_hagCount = G.supplyCount[sea_hag];
	tributeCount = G.supplyCount[tribute];
	smithyCount = G.supplyCount[smithy];	
	treasure_mapCount = G.supplyCount[treasure_map];
	
	phase = G.phase;
	numActions = G.numActions;
	numBuys = G.numBuys;
	playedCardCount = G.playedCardCount;
	
/*
	int embargoTokens[treasure_map+1];
	int outpostPlayed;
	int outpostTurn;
*/
	
 	printf("\n-------------------- Begin unit-2-buyCard() Tests --------------------\n");
 	
 	printf("\n--------------- Test Collection 1 ---------------\n");
 	G.numBuys = 0;
 	numBuys = G.numBuys;
 	G.coins = 8;
 	coins = G.coins;
 		
 	int returnValue = buyCard(supplyPos, &G);
	
	printf("\nTEST-1: numBuys < 1 returns -1\n");
	if(returnValue == -1)
		printf( "PASS" );
	else
		printf( "FAIL: buyCard() returned %d" , returnValue);

	noChange();
	
	printf("\n--------------- Test Collection 2 ---------------\n");
	G.numBuys = 1;
	numBuys = G.numBuys;
	G.supplyCount[province] = 0;
	provinceCount = G.supplyCount[province];
		
	returnValue = buyCard(supplyPos, &G);
	
	printf("\nTEST-1: card supplyCount < 1 returns -1\n");
	if(returnValue == -1)
		printf( "PASS" );
	else
		printf( "FAIL: buyCard() returned %d" , returnValue);
	
	noChange();
	
	printf("\n--------------- Test Collection 3 ---------------\n");
	G.coins = 4;
	coins = G.coins;
	G.supplyCount[province] = 8;
	provinceCount = G.supplyCount[province];
	
	returnValue = buyCard(supplyPos, &G);
	
	printf("\nTEST-1: coins < cost of card returns -1\n");	
 	if(returnValue == -1)
		printf( "PASS" );
	else
		printf( "FAIL: buyCard() returned %d" , returnValue);
 	
 	noChange();
 	
		
 	printf("\n--------------- Test Collection 4 ---------------\n");
	G.coins = 8;
	coins = G.coins;
	
	returnValue = buyCard(supplyPos, &G);
 	
 	printf("\nTEST-1: buyCard() returns 0\n");
	if(returnValue == 0)
		printf( "PASS" );
	else
		printf( "FAIL: buyCard() returned %d" , returnValue);
	
	printf("\nTEST-2: coins - cost of card(Province)\n");
	if(G.coins == coins - 8)
		printf( "PASS" );
	else
		printf( "FAIL: coins changed from %d to %d" , coins, G.coins);
	
	printf("\nTEST-3: currentPlayer's handCount didn't change\n");
	if(G.handCount[currentPlayer] == handCount)
		printf( "PASS" );
	else
		printf( "FAIL: handCount changed from %d to %d" , handCount, G.handCount[currentPlayer]);
		  
	printf("\nTEST-4: currentPlayer's deckCount didn't change\n");
	if(G.deckCount[currentPlayer] == deckCount)
		printf( "PASS" );
	else
		printf( "FAIL: deckCount changed from %d to %d" , deckCount, G.deckCount[currentPlayer]);
		
	printf("\nTEST-5: currentPlayer's discardCount + 1\n");
	if(G.discardCount[currentPlayer] == discardCount + 1)
		printf( "PASS" );
	else
		printf( "FAIL: discardCount changed from %d to %d" , discardCount, G.discardCount[currentPlayer]);
	
	printf("\nTEST-6: currentPlayer's fullDeckCount + 1\n");
	if(G.deckCount[currentPlayer] + G.handCount[currentPlayer] + G.discardCount[currentPlayer] == cp_fullDeckCount + 1)
		printf( "PASS" );
	else
		printf( "FAIL: currentPlayer's fullDeckCount changed from %d to %d" , cp_fullDeckCount, G.deckCount[currentPlayer] + G.handCount[currentPlayer] + G.discardCount[currentPlayer]);
	
	printf("\nTEST-7: opponent's handCount didn't change\n");
	if(G.handCount[opponent] == op_handCount)
		printf( "PASS" );
	else
		printf( "FAIL: handCount changed from %d to %d" , handCount, G.handCount[currentPlayer]);
				  
	printf("\nTEST-8: opponent's deckCount didn't change\n");
	if(G.deckCount[opponent] == op_deckCount)
		printf( "PASS" );
	else
		printf( "FAIL: deckCount changed from %d to %d" , deckCount, G.deckCount[currentPlayer]);
				
	printf("\nTEST-9: opponent's discardCount didn't change\n");
	if(G.discardCount[opponent] == op_discardCount)
		printf( "PASS" );
	else
		printf( "FAIL: discardCount changed from %d to %d" , discardCount, G.discardCount[currentPlayer]);
	
	printf("\nTEST-10: opponent's fullDeckCount didn't change\n");
	if(G.deckCount[opponent] + G.handCount[opponent] + G.discardCount[opponent] == op_fullDeckCount)
		printf( "PASS" );
	else
		printf( "FAIL: opponent's fullDeckCount changed from %d to %d" , op_fullDeckCount, G.deckCount[opponent] + G.handCount[opponent] + G.discardCount[opponent]);
		
	printf("\nTEST-11: playedCardCount didn't change\n");
	if(G.playedCardCount == playedCardCount)
		printf( "PASS" );
	else
		printf( "FAIL: playedCardCount changed from %d to %d" , playedCardCount, G.playedCardCount);
	
	printf("\nTEST-12: numPlayers didn't change\n");
	if(G.numPlayers == numPlayers)
		printf( "PASS" );
	else
		printf( "FAIL: numPlayers changed from %d to %d" , numPlayers, G.numPlayers);
	
	printf("\nTEST-13: still currentPlayer's turn\n");
	if(G.whoseTurn == currentPlayer)
		printf( "PASS" );
	else
		printf( "FAIL: whoseTurn changed from %d to %d" , currentPlayer, G.whoseTurn);
		
	printf("\nTEST-14: game phase = 1\n");
	if(G.phase == 1)
		printf( "PASS" );
	else
		printf( "FAIL: game phase changed from %d to %d" , phase, G.phase);
		
	printf("\nTEST-15: numActions didn't change\n");
	if(G.numActions == numActions)
		printf( "PASS" );
	else
		printf( "FAIL: numActions changed from %d to %d" , numActions, G.numActions);
	
	printf("\nTEST-16: numBuys - 1\n");
	if(G.numBuys == numBuys - 1)
		printf( "PASS" );
	else
		printf( "FAIL: numBuys changed from %d to %d" , numBuys, G.numBuys);
	
	printf("\nTEST-17: Curse supply didn't change\n");
	if(G.supplyCount[curse] == curseCount){
		printf( "PASS" );
	}
	else{
		printf( "FAIL: Curse supply changed" );
	}
	
	printf("\nTEST-18: Victory supplies, except Province, didn't change\n");
	if(G.supplyCount[estate] == estateCount &&
	   G.supplyCount[duchy] == duchyCount){
		printf( "PASS" );
	}
	else{
		printf( "FAIL: Estate and/or Duchy supply changed" );
	}
	
	printf("\nTEST-19: card (Province) supplyCount - 1\n");
	if(G.supplyCount[province] == provinceCount - 1)
		printf( "PASS" );
	else
		printf( "FAIL: Province supplyCount changed from %d to %d" , provinceCount, G.supplyCount[province]);
	
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
		
 	printf("\n\n---------------------- End unit-2-buyCard() Tests ----------------------\n\n"); 	
 	
 	return 0;
}


void noChange(){
	printf("\nTEST-2: coins didn't change\n");
	if(G.coins == coins)
		printf( "PASS" );
	else
		printf( "FAIL: coins changed from %d to %d" , coins, G.coins);
	
	printf("\nTEST-3: currentPlayer's handCount didn't change\n");
	if(G.handCount[currentPlayer] == handCount)
		printf( "PASS" );
	else
		printf( "FAIL: handCount changed from %d to %d" , handCount, G.handCount[currentPlayer]);
		  
	printf("\nTEST-4: currentPlayer's deckCount didn't change\n");
	if(G.deckCount[currentPlayer] == deckCount)
		printf( "PASS" );
	else
		printf( "FAIL: deckCount changed from %d to %d" , deckCount, G.deckCount[currentPlayer]);
		
	printf("\nTEST-5: currentPlayer's discardCount didn't change\n");
	if(G.discardCount[currentPlayer] == discardCount)
		printf( "PASS" );
	else
		printf( "FAIL: discardCount changed from %d to %d" , discardCount, G.discardCount[currentPlayer]);
	
	printf("\nTEST-6: currentPlayer's fullDeckCount didn't change\n");
	if(G.deckCount[currentPlayer] + G.handCount[currentPlayer] + G.discardCount[currentPlayer] == cp_fullDeckCount)
		printf( "PASS" );
	else
		printf( "FAIL: currentPlayer's fullDeckCount changed from %d to %d" , cp_fullDeckCount, G.deckCount[currentPlayer] + G.handCount[currentPlayer] + G.discardCount[currentPlayer]);
	
	printf("\nTEST-7: opponent's handCount didn't change\n");
	if(G.handCount[opponent] == op_handCount)
		printf( "PASS" );
	else
		printf( "FAIL: handCount changed from %d to %d" , handCount, G.handCount[currentPlayer]);
				  
	printf("\nTEST-8: opponent's deckCount didn't change\n");
	if(G.deckCount[opponent] == op_deckCount)
		printf( "PASS" );
	else
		printf( "FAIL: deckCount changed from %d to %d" , deckCount, G.deckCount[currentPlayer]);
				
	printf("\nTEST-9: opponent's discardCount didn't change\n");
	if(G.discardCount[opponent] == op_discardCount)
		printf( "PASS" );
	else
		printf( "FAIL: discardCount changed from %d to %d" , discardCount, G.discardCount[currentPlayer]);
	
	printf("\nTEST-10: opponent's fullDeckCount didn't change\n");
	if(G.deckCount[opponent] + G.handCount[opponent] + G.discardCount[opponent] == op_fullDeckCount)
		printf( "PASS" );
	else
		printf( "FAIL: opponent's fullDeckCount changed from %d to %d" , op_fullDeckCount, G.deckCount[opponent] + G.handCount[opponent] + G.discardCount[opponent]);
	
	printf("\nTEST-11: playedCardCount didn't change\n");
	if(G.playedCardCount == playedCardCount)
		printf( "PASS" );
	else
		printf( "FAIL: playedCardCount changed from %d to %d" , playedCardCount, G.playedCardCount);
	
	printf("\nTEST-12: numPlayers didn't change\n");
	if(G.numPlayers == numPlayers)
		printf( "PASS" );
	else
		printf( "FAIL: numPlayers changed from %d to %d" , numPlayers, G.numPlayers);
	
	printf("\nTEST-13: still currentPlayer's turn\n");
	if(G.whoseTurn == currentPlayer)
		printf( "PASS" );
	else
		printf( "FAIL: whoseTurn changed from %d to %d" , currentPlayer, G.whoseTurn);
		
	printf("\nTEST-14: game phase didn't change\n");
	if(G.phase == phase)
		printf( "PASS" );
	else
		printf( "FAIL: game phase changed from %d to %d" , phase, G.phase);
		
	printf("\nTEST-15: numActions didn't change\n");
	if(G.numActions == numActions)
		printf( "PASS" );
	else
		printf( "FAIL: numActions changed from %d to %d" , numActions, G.numActions);
	
	printf("\nTEST-16: numBuys didn't change\n");
	if(G.numBuys == numBuys)
		printf( "PASS" );
	else
		printf( "FAIL: numBuys changed from %d to %d" , numBuys, G.numBuys);
	
	printf("\nTEST-17: Curse supply didn't change\n");
	if(G.supplyCount[curse] == curseCount){
		printf( "PASS" );
	}
	else{
		printf( "FAIL: Curse supply changed" );
	}
	
	printf("\nTEST-18: Victory supplies didn't change\n");
	if(G.supplyCount[estate] == estateCount &&
	   G.supplyCount[duchy] == duchyCount &&
	   G.supplyCount[province] == provinceCount){
		printf( "PASS" );
	}
	else{
		printf( "FAIL: at least one Victory supply changed" );
	}
	
	printf("\nTEST-19: Treasure supplies didn't change\n");
	if(G.supplyCount[copper] == copperCount &&
	   G.supplyCount[silver] == silverCount &&
	   G.supplyCount[gold] == goldCount){
		printf( "PASS" );
	}
	else{
		printf( "FAIL: at least one Treasure supply changed" );
	}
	
	printf("\nTEST-20: Kingdom supplies didn't change\n");
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
}