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
	G.hand[opponent][handPos] = sea_hag;
	int op_handCount = G.handCount[opponent];
	int op_deckCount = G.deckCount[opponent];
	int op_discardCount = G.discardCount[opponent];
	int op_deckCard_1 = G.deck[opponent][G.deckCount[opponent]-1];
	int op_fullDeckCount = G.deckCount[opponent] + G.handCount[opponent] + G.discardCount[opponent];

	G.whoseTurn = currentPlayer;
	G.hand[currentPlayer][handPos] = sea_hag;
	int handCount = G.handCount[currentPlayer];
	int deckCount = G.deckCount[currentPlayer];
	int discardCount = G.discardCount[currentPlayer];
	int fullDeckCount = G.deckCount[currentPlayer] + G.handCount[currentPlayer] + G.discardCount[currentPlayer];
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
	
	printf("\n--------------- Begin card-4-Sea Hag Tests ---------------\n");
	 
	int returnValue = cardEffect(sea_hag, choice1, choice2, choice3, &G, handPos, &bonus);

	printf("\nTEST-1: return value = 0\n");
	if(returnValue == 0)
		printf( "PASS" );
	else
		printf( "FAIL: return value = %d" , returnValue);
	
	printf("\nTEST-2: currentPlayer's handCount - Sea Hag\n");
	if(G.handCount[currentPlayer] == handCount - 1)
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
	
	printf("\nTEST-5: Sea Hag set to be discarded at end of turn\n");
	if(G.hand[currentPlayer][0] == lastCard && G.hand[currentPlayer][G.handCount[currentPlayer]] == -1)
		printf( "PASS" );
	else
		printf( "FAIL: Sea Hag is not set to be discarded at end of player's turn" );
	
	printf("\nTEST-6: currentPlayer's fullDeckCount didn't change\n");
	if(G.deckCount[currentPlayer] + G.handCount[currentPlayer] + 1 + G.discardCount[currentPlayer] == fullDeckCount)
		printf( "PASS" );
	else
		printf( "FAIL: currentPlayer's fullDeckCount changed from %d to %d" , fullDeckCount, G.deckCount[currentPlayer] + G.handCount[currentPlayer] + 1 + G.discardCount[currentPlayer]);
	
	printf("\nTEST-7: playedCardCount + 1\n");
	if(G.playedCardCount == playedCardCount + 1)
		printf( "PASS" );
	else
		printf( "FAIL: playedCardCount changed from %d to %d" , playedCardCount, G.playedCardCount);
	
	printf("\nTEST-8: last played card was Sea Hag\n");
	if(G.playedCards[G.playedCardCount-1] == sea_hag)
		printf( "PASS" );
	else
		printf( "FAIL: last playedCard was not Sea Hag" );
	
	printf("\nTEST-9: numPlayers stayed the same\n");
	if(G.numPlayers == numPlayers)
		printf( "PASS" );
	else
		printf( "FAIL: numPlayers changed from %d to %d" , numPlayers, G.numPlayers);
	
	printf("\nTEST-10: still currentPlayer's turn\n");
	if(G.whoseTurn == currentPlayer)
		printf( "PASS" );
	else
		printf( "FAIL: whoseTurn changed from %d to %d" , currentPlayer, G.whoseTurn);
		
	printf("\nTEST-11: game phase stayed the same\n");
	if(G.phase == phase)
		printf( "PASS" );
	else
		printf( "FAIL: game phase changed from %d to %d" , phase, G.phase);
		
	printf("\nTEST-12: numActions stayed the same\n");
	if(G.numActions == numActions)
		printf( "PASS" );
	else
		printf( "FAIL: numActions changed from %d to %d" , numActions, G.numActions);
	
	printf("\nTEST-13: numBuys didn't change\n");
	if(G.numBuys == numBuys)
		printf( "PASS" );
	else
		printf( "FAIL: numBuys changed from %d to %d" , numBuys, G.numBuys);
	
	printf("\nTEST-14: currentPlayer's coins stayed the same\n");
	if(G.coins == coins)
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
	
	printf("\nTEST-17: opponent's fullDeckCount + 1\n");
	if(G.deckCount[opponent] + G.handCount[opponent] + G.discardCount[opponent] == op_fullDeckCount + 1)
		printf( "PASS" );
	else
		printf( "FAIL: opponent's fullDeckCount changed from %d to %d" , op_fullDeckCount, G.deckCount[opponent] + G.handCount[opponent] + G.discardCount[opponent]);
	
	printf("\nTEST-18: top card of opponent's deck is a Curse\n");
	if(G.deck[opponent][G.deckCount[opponent]-1] == curse){
		printf( "PASS" );
	}
	else{
		printf( "FAIL: opponent's top deck card is not a Curse" );
	}
	
	printf("\nTEST-19: opponent's discardCount + 1\n");
	if(G.discardCount[opponent] == op_discardCount + 1)
		printf( "PASS" );
	else
		printf( "FAIL: opponent's discardCount changed from %d to %d" , op_discardCount, G.discardCount[opponent]);
	
	printf("\nTEST-20: opponent's last discard is same as card taken from top of deck\n");
	if(G.discard[opponent][G.discardCount[opponent]-1] == op_deckCard_1)
		printf( "PASS" );
	else
		printf( "FAIL: opponent's last discard is not same as card taken from top of deck" );
	
	printf("\nTEST-21: Curse supply - 1\n");
	if(G.supplyCount[curse] == curseCount - 1){
		printf( "PASS" );
	}
	else{
		printf( "FAIL: Curse supply changed from %d to %d" , curseCount, G.supplyCount[curse]);
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
	
	printf("\n\n---------------- End card-4-Sea Hag Tests ----------------\n\n");
	
	return 0;
}