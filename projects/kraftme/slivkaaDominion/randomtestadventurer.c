/*******************************************************************************
* Author: Riley Kraft (kraftme)
* Date: 11/14/2018
* Description: This program is a random test suite for the Adventurer card of the 
* 				dominion.c file. When run, this will test for the correct
* 				outcome of this function in regards to the gameState, player,
* 				opponent, and supply cards. See test titles for more information.
* Sources:
* 	kraftme's OSU-CS-362-400 Assignment 3 unit test source code
* 	https://www.geeksforgeeks.org/generating-random-number-range-c/
* 	OSU-CS362-400 course provided dominion.c initializeGame() function
*******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <time.h>

// Generates random numbers in range [min, max]. 
int randNum(int min, int max){  
	return rand() % (max - min + 1) + min;
}

int main ()	{
	srand(time(NULL));
	int handPos, choice1=0, choice2=0, choice3=0, bonus;
	int numPlayers, currentPlayer;
	struct gameState G, testG;
	int k[10] = {adventurer, council_room, village, minion, mine, salvager,
			sea_hag, tribute, smithy, treasure_map};

	int i, m, j, p, it;
	int iteration = 1;
	int index = -1;
	int deckTreasure, handTreasure;
	
	printf("\n--------------- Begin Adventurer Random Tests ---------------\n");
	
	for(it = 0; it < 100; it++){
		deckTreasure = 0;
		handTreasure = 0;

		printf("Iteration - %d\n", iteration++);
		
		numPlayers = randNum(2,4); 					// random between 2 and 4
		G.numPlayers = numPlayers; 					// set number of players
		//printf("numPlayers: %d   ", G.numPlayers);
		
		currentPlayer = randNum(0, numPlayers-1);  	// get a player
		G.whoseTurn = currentPlayer;				// set whose turn it is
		//printf("whoseTurn: %d   ", G.whoseTurn);
		
		bonus = randNum(0,5);  						// random between 0 and 5
		//printf("bonus: %d   ", bonus);

		//set number of Curse cards
		if (numPlayers == 2){                         // numPlayers is 2
		  G.supplyCount[curse] = randNum(0,10);         // random between 0 and 10
		}
		else if (numPlayers == 3){                    // numPlayers is 3
		  G.supplyCount[curse] = randNum(0,20);         // random between 0 and 20
		}
		else{                                         // numPlayers is 4
		  G.supplyCount[curse] = randNum(0,30);         // random between 0 and 30
		}

		//set number of Victory cards
		if (numPlayers == 2){                         // numPlayers is 2
		  G.supplyCount[estate] = randNum(1,8);         // Victory card counts random between 1 and 8
		  G.supplyCount[duchy] = randNum(1,8);          // Cannot be 0, or game would not be in progress
		  G.supplyCount[province] = randNum(1,8);
		}
		else{                                        // numPlayers is 3 or 4
		  G.supplyCount[estate] = randNum(1,12);       // Victory card counts random between 1 and 12
		  G.supplyCount[duchy] = randNum(1,12);        // Cannot be 0, or game would not be in progress
		  G.supplyCount[province] = randNum(1,12);
		}

		//set number of Treasure cards
		G.supplyCount[copper] = randNum(2,60 - (7 * numPlayers));
		G.supplyCount[silver] = randNum(2,40);
		G.supplyCount[gold] = randNum(2,30);

		//set number of Kingdom cards
		for (i = adventurer; i <= treasure_map; i++){   		// loop all cards
		  for (j = 0; j < 10; j++){           						// loop chosen cards
			  if (k[j] == i){
				  G.supplyCount[i] = randNum(1,10);
				  break;
			  }
			  else{    //card is not in the set choosen for the game
				  G.supplyCount[i] = -1;
			  }
		  }
		}

		//set player decks
		for (i = 0; i < numPlayers; i++){
		  G.deckCount[i] = randNum(2,20);
		  int first = randNum(2, G.deckCount[i]);
		  for (j = 0; j < first; j++){
			  G.deck[i][j] = randNum(4, 6);  // copper to gold
			  if(i == currentPlayer){
				  deckTreasure++;
			  }
		  }
		  int second = randNum(0, G.deckCount[i] - first);
		  for(m = j; m < second; m++){
			  G.deck[i][m] = k[randNum(0,3)]; // curse to province
		  }
		  for(p = m; p < G.deckCount[i]; p++){
			  G.deck[i][p] = k[randNum(0,9)];
		  }
		}
		//printf("deckCount: %d\n", G.deckCount[currentPlayer]);

		//shuffle player decks
		for (i = 0; i < numPlayers; i++){
		  if(shuffle(i, &G) < 0){
			  printf("check 'shuffle player decks' test code");
			  return -1;
		  }
		}

		//draw player hands
		for (i = 0; i < numPlayers; i++){  
		  G.handCount[i] = 0;
		  G.discardCount[i] = 0;
		  
		  //printf("Player %d hand: ", i);
		  for (j = 0; j < randNum(1,G.deckCount[i]); j++){
			  drawCard(i, &G);
			  if(i == currentPlayer && (G.hand[i][j] == copper || G.hand[i][j] == silver || G.hand[i][j] == gold)){
				  handTreasure++;
			  }
			  //printf("%d, ", G.hand[i][j]);
		  }
		}

		deckTreasure -= handTreasure;
	  
		//set embargo tokens to 0 for all supply piles
		for (i = 0; i <= treasure_map; i++){
		  G.embargoTokens[i] = randNum(0,5);
		}

		//initialize first player's turn
		G.outpostPlayed = randNum(0,5);
		G.phase = 0;
		G.numActions = randNum(0,5);
		G.numBuys = randNum(0,5);
		G.playedCardCount = randNum(0,5);

		updateCoins(G.whoseTurn, &G, bonus);
		
		handPos = randNum(0, G.handCount[currentPlayer]-1);
		G.hand[currentPlayer][handPos] = adventurer;
		//printf("handPos(7): %d   \n", handPos);
		
		memcpy(&testG,&G,sizeof(struct gameState));
		 
		int returnValue = cardEffect(adventurer, choice1, choice2, choice3, &testG, handPos, &bonus);
	
		//printf("\nTEST-1: return value = 0\n");
		if(returnValue != 0){
			++index;
			printf( "TEST-1 FAIL: return value = %d\n" , returnValue);
		}
		
		//printf("\nTEST-2: currentPlayer's handCount - Adventurer + 2 Treasures\n");
		if(deckTreasure < 2){
			if(testG.handCount[currentPlayer] != G.handCount[currentPlayer] + deckTreasure -1){
				++index;
				printf( "TEST-2 FAIL: there were %d Treasures in player's deck, but handCount changed from %d to %d\n" , deckTreasure, G.handCount[currentPlayer], testG.handCount[currentPlayer]);
			}
		}
		else{
			if(testG.handCount[currentPlayer] != G.handCount[currentPlayer] + 1){
				++index;
				printf( "TEST-2 FAIL: handCount changed from %d to %d\n" , G.handCount[currentPlayer], testG.handCount[currentPlayer]);
			}
		}
		 
		//printf("\nTEST-3: currentPlayer's deckCount - cards drawn until 2 Treasures found\n");
		if(testG.deckCount[currentPlayer] == G.deckCount[currentPlayer]){
			++index;
			printf( "TEST-3 FAIL: no cards were drawn from the currentPlayer's deck");
		}
		
		//printf("\nTEST-4: 2 new cards in currentPlayer's hand are Treasures gained from currentPlayer's deck\n");
		if(deckTreasure >= 2){
			if((testG.hand[currentPlayer][testG.handCount[currentPlayer]-1] != copper &&
					testG.hand[currentPlayer][testG.handCount[currentPlayer]-1] != silver &&
					testG.hand[currentPlayer][testG.handCount[currentPlayer]-1] != gold) ||
			   ((testG.hand[currentPlayer][handPos] != copper &&
					   testG.hand[currentPlayer][handPos] != silver &&
					   testG.hand[currentPlayer][handPos] != gold)  &&
				(testG.hand[currentPlayer][testG.handCount[currentPlayer]-2] != copper &&
						testG.hand[currentPlayer][testG.handCount[currentPlayer]-2] != silver &&
						testG.hand[currentPlayer][testG.handCount[currentPlayer]-2] != gold))){
				++index;
				printf( "TEST-4 FAIL: new cards in hand are not Treasures\n" );
			}
		}
		
		//printf("\nTEST-5: Adventurer set to be discarded at end of turn\n");
		if(testG.hand[currentPlayer][testG.handCount[currentPlayer]] != -1 && testG.hand[currentPlayer][testG.handCount[currentPlayer]] != adventurer){
			++index;
			printf( "TEST-5 FAIL: Adventurer is not set to be discarded at end of player's turn\n" );
		}
		
		//printf("\nTEST-6: playedCardCount + Adventurer; Non-Treasure drawn cards are not 'played', just discarded\n");
		if(testG.playedCardCount != G.playedCardCount + 1){
			++index;
			printf( "TEST-6 FAIL: playedCardCount changed from %d to %d\n" , G.playedCardCount, testG.playedCardCount);
		}
		
		//printf("\nTEST-7: last played card was Adventurer\n");
		if(testG.playedCards[testG.playedCardCount-1] != adventurer){
			++index;
			printf( "TEST-7 FAIL: last playedCard was not Adventurer\n" );
		}
		
		//printf("\nTEST-8: a drawn Treasure card was discarded\n");
		if(testG.discardCount[currentPlayer] > G.discardCount[currentPlayer]){
			int discard = testG.discardCount[currentPlayer] - G.discardCount[currentPlayer];
			//printf("discards: %d\n", discard);
			for(i = 1; i <= discard; i++){
				//printf("%d, ", testG.discard[currentPlayer][testG.discardCount[currentPlayer]-i]);
				if(testG.discard[currentPlayer][testG.discardCount[currentPlayer]-i] == copper ||
				testG.discard[currentPlayer][testG.discardCount[currentPlayer]-i] == silver ||
				testG.discard[currentPlayer][testG.discardCount[currentPlayer]-i] == gold){
					++index;
					printf( "\nTEST-8 FAIL: a Treasure card was discarded\n" );
					
				}
			}
		}
		
		//printf("\nTEST-9: numPlayers didn't change\n");
		if(testG.numPlayers != G.numPlayers){
			++index;
			printf( "TEST-9 FAIL: numPlayers changed from %d to %d\n" , G.numPlayers, testG.numPlayers);
		}
		
		//printf("\nTEST-10: still currentPlayer's turn\n");
		if(testG.whoseTurn != G.whoseTurn){
			++index;
			printf( "TEST-10 FAIL: whoseTurn changed from %d to %d\n" , G.whoseTurn, testG.whoseTurn);
		}
			
		//printf("\nTEST-11: game phase didn't change\n");
		if(testG.phase != G.phase){
			++index;
			printf( "TEST-11 FAIL: game phase changed from %d to %d\n" , G.phase, testG.phase);
		}
			
		//printf("\nTEST-12: numActions didn't change\n");
		if(testG.numActions != G.numActions){
			++index;
			printf( "TEST-12 FAIL: numActions changed from %d to %d\n" , G.numActions, testG.numActions);
		}
		
		//printf("\nTEST-13: numBuys didn't change\n");
		if(testG.numBuys != G.numBuys){
			++index;
			printf( "TEST-13 FAIL: numBuys changed from %d to %d\n" , G.numBuys, testG.numBuys);
		}
		
		//printf("\nTEST-14: currentPlayer's coins didn't change\n");
		if(testG.coins != G.coins){
			++index;
			printf( "TEST-14 FAIL: currentPlayer's coins changed from %d to %d\n" , G.coins, testG.coins);
		}
	
		for(i = 0; i < G.numPlayers; i++){
			if(i != G.whoseTurn){
				//printf("\nTEST-15: opponent's handCount didn't change\n");
				if(testG.handCount[i] != G.handCount[i]){
					++index;
					printf( "TEST-15 FAIL: opponent %d's handCount changed from %d to %d\n" , i, G.handCount[i], testG.handCount[i]);
				}
				  
				//printf("\nTEST-16: opponent's deckCount didn't change\n");
				if(testG.deckCount[i] != G.deckCount[i]){
					++index;
					printf( "TEST-16 FAIL: opponent %d's deckCount changed from %d to %d\n" , i, G.deckCount[i], testG.deckCount[i]);
				}
				
				//printf("\nTEST-17: opponent's discardCount didn't change\n");
				if(testG.discardCount[i] != G.discardCount[i]){
					++index;
					printf( "TEST-17 FAIL: opponent %d's discardCount changed from %d to %d\n" , i, G.discardCount[i], testG.discardCount[i]);
				}
			}
		}
		
		//printf("\nTEST-18: Curse supply didn't change\n");
		if(testG.supplyCount[curse] != G.supplyCount[curse]){
			++index;
			printf( "TEST-18 FAIL: Curse supply changed\n" );
		}
		
		//printf("\nTEST-19: Victory supplies didn't change\n");
		if(testG.supplyCount[estate] != G.supplyCount[estate] ||
		   testG.supplyCount[duchy] != G.supplyCount[duchy] ||
		   testG.supplyCount[province] != G.supplyCount[province]){
			++index;
			printf( "TEST-19 FAIL: at least one Victory supply changed\n" );
		}
		
		//printf("\nTEST-20: Treasure supplies didn't change\n");
		if(testG.supplyCount[copper] != G.supplyCount[copper] ||
		   testG.supplyCount[silver] != G.supplyCount[silver] ||
		   testG.supplyCount[gold] != G.supplyCount[gold]){
			++index;
			printf( "TEST-20 FAIL: at least one Treasure supply changed\n" );
		}
		
		//printf("\nTEST-21: Kingdom supplies didn't change\n");
		if(testG.supplyCount[adventurer] != G.supplyCount[adventurer] ||
		   testG.supplyCount[council_room] != G.supplyCount[council_room] ||
		   testG.supplyCount[village] != G.supplyCount[village] ||
		   testG.supplyCount[minion] != G.supplyCount[minion] ||
		   testG.supplyCount[mine] != G.supplyCount[mine] ||
		   testG.supplyCount[salvager] != G.supplyCount[salvager] ||
		   testG.supplyCount[sea_hag] != G.supplyCount[sea_hag] ||
		   testG.supplyCount[tribute] != G.supplyCount[tribute] ||
		   testG.supplyCount[smithy] != G.supplyCount[smithy] ||
		   testG.supplyCount[treasure_map] != G.supplyCount[treasure_map]){
			++index;
			printf( "TESTS-21 FAIL: at least one Kingdom supply changed\n" );
		}
		
		/*for (i = 0; i < numPlayers; i++){  
			printf("Player %d hand: ", i);
			for (j = 0; j < testG.handCount[i]; j++){
				printf("%d, ", testG.hand[i][j]);
			}
			printf("\n");
		}*/
		
		if(index == -1){
			printf("All tests PASSED\n");
		}
		printf("\n");
		index = -1;
	}
	
	printf("---------------- End Adventurer Random Tests ----------------\n\n");
	
	return 0;
}
