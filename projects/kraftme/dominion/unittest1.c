/*******************************************************************************
* Author: Riley Kraft (kraftme)
* Date: 10/28/2018
* Desccription:
* Sources:
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

int main(){
 	int bonus = 1;
	int seed = 1000;
	int numPlayers = 2;
	int currentPlayer = 0;
	int opponent = 1;
	struct gameState G;
	int k[10] = {adventurer, council_room, village, minion, mine, salvager,
			sea_hag, tribute, smithy, treasure_map};

	initializeGame(numPlayers, k, seed, &G);
	
	G.whoseTurn = opponent;
	G.handCount[opponent] = 5;
	G.hand[opponent][0] = copper;
	G.hand[opponent][1] = copper;
	G.hand[opponent][2] = copper;
	G.hand[opponent][3] = copper;
	G.hand[opponent][4] = copper;
	int op_handCount = G.handCount[opponent];
	int op_deckCount = G.deckCount[opponent];
	int op_discardCount = G.discardCount[opponent];
	
	G.whoseTurn = currentPlayer;
	G.handCount[currentPlayer] = 5;
	G.hand[currentPlayer][0] = copper;
	G.hand[currentPlayer][1] = copper;
	G.hand[currentPlayer][2] = silver;
	G.hand[currentPlayer][3] = province;
	G.hand[currentPlayer][4] = gold;
	int handCount = G.handCount[currentPlayer];
	int deckCount = G.deckCount[currentPlayer];
	int discardCount = G.discardCount[currentPlayer];
	
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
	int coins = 0;
	int playedCardCount = G.playedCardCount;
	
/*
	int embargoTokens[treasure_map+1];
	int outpostPlayed;
	int outpostTurn;
*/
	
	printf("\n--------------- Begin unit-1-updateCoins() Tests ---------------\n");
	 
	int returnValue = updateCoins(currentPlayer, &G, bonus);

	printf("\nTEST-1: return value = 0\n");
	if(returnValue == 0)
		printf( "PASS" );
	else
		printf( "FAIL: return value = %d" , returnValue);
	
	printf("\nTEST-2: coins = 8\n");
	if(G.coins == coins + 8)
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
	
	printf("\nTEST-6: opponent's handCount didn't change\n");
	if(G.handCount[opponent] == op_handCount)
		printf( "PASS" );
	else
		printf( "FAIL: handCount changed from %d to %d" , handCount, G.handCount[currentPlayer]);
				  
	printf("\nTEST-7: opponent's deckCount didn't change\n");
	if(G.deckCount[opponent] == op_deckCount)
		printf( "PASS" );
	else
		printf( "FAIL: deckCount changed from %d to %d" , deckCount, G.deckCount[currentPlayer]);
				
	printf("\nTEST-8: opponent's discardCount didn't change\n");
	if(G.discardCount[opponent] == op_discardCount)
		printf( "PASS" );
	else
		printf( "FAIL: discardCount changed from %d to %d" , discardCount, G.discardCount[currentPlayer]);
	
	printf("\nTEST-9: playedCardCount didn't change\n");
	if(G.playedCardCount == playedCardCount)
		printf( "PASS" );
	else
		printf( "FAIL: playedCardCount changed from %d to %d" , playedCardCount, G.playedCardCount);
	
	printf("\nTEST-10: numPlayers didn't change\n");
	if(G.numPlayers == numPlayers)
		printf( "PASS" );
	else
		printf( "FAIL: numPlayers changed from %d to %d" , numPlayers, G.numPlayers);
	
	printf("\nTEST-11: still currentPlayer's turn\n");
	if(G.whoseTurn == currentPlayer)
		printf( "PASS" );
	else
		printf( "FAIL: whoseTurn changed from %d to %d" , currentPlayer, G.whoseTurn);
		
	printf("\nTEST-12: game phase didn't change\n");
	if(G.phase == phase)
		printf( "PASS" );
	else
		printf( "FAIL: game phase changed from %d to %d" , phase, G.phase);
		
	printf("\nTEST-13: numActions didn't change\n");
	if(G.numActions == numActions)
		printf( "PASS" );
	else
		printf( "FAIL: numActions changed from %d to %d" , numActions, G.numActions);
	
	printf("\nTEST-14: numBuys didn't change\n");
	if(G.numBuys == numBuys)
		printf( "PASS" );
	else
		printf( "FAIL: numBuys changed from %d to %d" , numBuys, G.numBuys);
	
	printf("\nTEST-15: Curse supply didn't change\n");
	if(G.supplyCount[curse] == curseCount){
		printf( "PASS" );
	}
	else{
		printf( "FAIL: Curse supply changed" );
	}
	
	printf("\nTEST-16: Victory supplies didn't change\n");
	if(G.supplyCount[estate] == estateCount &&
	   G.supplyCount[duchy] == duchyCount &&
	   G.supplyCount[province] == provinceCount){
		printf( "PASS" );
	}
	else{
		printf( "FAIL: at least one Victory supply changed" );
	}
	
	printf("\nTEST-17: Treasure supplies didn't change\n");
	if(G.supplyCount[copper] == copperCount &&
	   G.supplyCount[silver] == silverCount &&
	   G.supplyCount[gold] == goldCount){
		printf( "PASS" );
	}
	else{
		printf( "FAIL: at least one Treasure supply changed" );
	}
	
	printf("\nTEST-18: Kingdom supplies didn't change\n");
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
	
	printf("\n\n---------------- End unit-1-updateCoins() Tests ----------------\n\n");
	
	return 0;
}