/*******************************************************************************
* Author: Riley Kraft (kraftme)
* Date: 11/14/2018
* Description: This program is a random test suite for the Salvager card of the 
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
    int handPos, choice1, choice2=0, choice3=0, bonus;
    int numPlayers, currentPlayer;
	struct gameState G, testG;
	int k[10] = {adventurer, council_room, village, minion, mine, salvager,
			sea_hag, tribute, smithy, treasure_map};
	
	//int lastCard_1, lastCard_2;

	int i, j, m, it;
	int iteration = 1;
	int trashedCard;
	int trashedCost;
	int index = -1;
	
	printf("\n--------------- Begin Salvager Random Tests ---------------\n");
	
	for(it = 0; it < 100; it++){
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
		G.supplyCount[copper] = randNum(1,60 - (7 * numPlayers));
		G.supplyCount[silver] = randNum(1,40);
		G.supplyCount[gold] = randNum(1,30);

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
		  G.deckCount[i] = randNum(7,25);
		  for (j = 0; j < randNum(0,G.deckCount[i]); j++){
			  G.deck[i][j] = randNum(0, 6);  // curse to gold
		  }
		  for(m = j; m < G.deckCount[i]; m++){
			  G.deck[i][m] = k[randNum(0,9)];
		  }
	  	}

	  	//shuffle player decks
	  	for (i = 0; i < numPlayers; i++){
		  if(shuffle(i, &G) < 0){
			  printf("check 'shuffle player decks' test code");
			  return -1;
		  }
	  	}

	  	//draw player hands
	  	for (i = 0; i < numPlayers; i++){  
		  G.handCount[i] = 0;      // Must at least have a Salvager card and a card to trash
		  G.discardCount[i] = randNum(0,5);
		  
		  //printf("Player %d hand: ", i);
		  for (j = 0; j < randNum(2,10); j++){
			  drawCard(i, &G);
			  //printf("%d, ", G.hand[i][j]);
		  }
		  //printf("\n");
	  	}
	  
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
		G.hand[currentPlayer][handPos] = 24;
		//printf("handPos(24): %d   ", handPos);
		do{
			choice1 = randNum(0, G.handCount[currentPlayer]-1); // rand between 0 and hand count
		}while(choice1 == handPos);
		trashedCard = G.hand[currentPlayer][choice1];
		//printf("choice1: %d   trashedCard: %d   ", choice1, trashedCard);
		trashedCost = getCost(trashedCard);
		//printf("trashedCost: %d\n", trashedCost);
		
		memcpy(&testG,&G,sizeof(struct gameState));
		
		int returnValue = cardEffect(salvager, choice1, choice2, choice3, &testG, handPos, &bonus);
	
		//printf("\nTEST-1: return value = 0\n");
		if(returnValue != 0){
			++index;
			printf( "TEST-1 FAIL: return value supposed to be 0, but = %d\n" , returnValue);
		}
		
		//printf("\nTEST-2: currentPlayer's handCount - Salvager - trashed card\n");
		if(testG.handCount[currentPlayer] != G.handCount[currentPlayer] - 2){
			++index;
			printf( "TEST-2 FAIL: handCount changed from %d to %d\n" , G.handCount[currentPlayer], testG.handCount[currentPlayer]);
		}
		  
		//printf("\nTEST-3: currentPlayer's deckCount didn't change\n");
		if(testG.deckCount[currentPlayer] != G.deckCount[currentPlayer]){
			++index;
			printf( "TEST-3 FAIL: deckCount changed from %d to %d\n" , G.deckCount[currentPlayer], testG.deckCount[currentPlayer]);
		}
		
		//printf("\nTEST-4: currentPlayer's discardCount didn't change\n");
		if(testG.discardCount[currentPlayer] != G.discardCount[currentPlayer]){
			++index;
			printf( "TEST-4 FAIL: discardCount changed from %d to %d\n" , G.discardCount[currentPlayer], testG.discardCount[currentPlayer]);
		}
		
		//printf("\nTEST-5: choice1 is set to be trashed, not discarded, at end of turn\n");
		if(testG.hand[currentPlayer][testG.handCount[currentPlayer]+1] != -1){
			++index;
			printf( "TEST-5 FAIL: choice1 is not set to be trashed at end of player's turn\n" );
			//printf("Player %d last card in hand: %d\n", currentPlayer, testG.hand[currentPlayer][testG.handCount[currentPlayer]+1]);
		}
		
		//printf("\nTEST-6: Salvager set to be discarded at end of turn\n");
		if(testG.hand[currentPlayer][testG.handCount[currentPlayer]] != -1 || testG.playedCards[testG.playedCardCount-1] != salvager){
			++index;
			printf( "TEST-6 FAIL: Salvager is not set to be discarded at end of player's turn\n" );
			//printf("Player %d last card in hand: %d\n", currentPlayer, testG.hand[currentPlayer][testG.handCount[currentPlayer]]);
			//printf("Last played card (24): %d\n", testG.playedCards[testG.playedCardCount-1]);
		}
		
		//printf("\nTEST-7: playedCardCount + 1\n");
		if(testG.playedCardCount != G.playedCardCount + 1){
			++index;
			printf( "TEST-7 FAIL: playedCardCount changed from %d to %d\n" , G.playedCardCount, testG.playedCardCount);
		}
		
		//printf("\nTEST-8: last played card was Salvager\n");
		if(testG.playedCards[testG.playedCardCount-1] != salvager){
			++index;
			printf( "TEST-8 FAIL: last playedCard was not Salvager\n" );
			//printf("Last played card (24): %d\n", testG.playedCards[testG.playedCardCount-1]);
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
		
		//printf("\nTEST-13: numBuys + 1\n");
		if(testG.numBuys != G.numBuys + 1){
			++index;
			printf( "TEST-13 FAIL: numBuys changed from %d to %d\n" , G.numBuys, testG.numBuys);
		}
		
		//printf("\nTEST-14: currentPlayer's coins increased by value of choice1, %d\n", trashedCost);
		if(testG.coins != G.coins + trashedCost){
			++index;
			printf( "TEST-14 FAIL: currentPlayer's coins changed from %d to %d\n" , G.coins, testG.coins);
		}
		
		for(i = 0; i < G.numPlayers; i++){
			if(i != G.whoseTurn){
				//printf("\nTEST-15: opponent %d handCount didn't change\n", i);
				if(testG.handCount[i] != G.handCount[i]){
					++index;
					printf( "T$EST-15 FAIL: opponent %d's handCount changed from %d to %d" , i, G.handCount[i], testG.handCount[i]);
				}
		  
				//printf("\nTEST-16: opponent's deckCount didn't change\n");
				if(testG.deckCount[i] != G.deckCount[i]){
					++index;
					printf( "TEST-16 FAIL: opponent %d's deckCount changed from %d to %d" , i, G.deckCount[i], testG.deckCount[i]);
				}
				
				//printf("\nTEST-17: opponent's discardCount didn't change\n");
				if(testG.discardCount[i] != G.discardCount[i]){
					++index;
					printf( "TEST-17 FAIL: opponent %d's discardCount changed from %d to %d" , i, G.discardCount[i], testG.discardCount[i]);
				}
			}
		}
		
		//printf("\nTEST-18: Curse supply didn't change\n");
		if(testG.supplyCount[curse] != G.supplyCount[curse]){
			++index;
			printf( "TEST-18 FAIL: Curse supply changed from %d to %d\n", G.supplyCount[curse], testG.supplyCount[curse]);
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
			printf( "TEST-21 FAIL: at least one Kingdom supply changed\n" );
		}
		
		if(index == -1)
			printf("All tests PASSED\n");
		printf("\n");
		index = -1;
	}
	
	printf("---------------- End Salvager Random Tests ----------------\n\n");
		
	return 0;
}