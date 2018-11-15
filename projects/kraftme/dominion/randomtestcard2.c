/*******************************************************************************
* Author: Riley Kraft (kraftme)
* Date: 11/14/2018
* Description: This program is a random test suite for the Smithy card of the 
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

	int i, m, j, it;
	int iteration = 1;
	int index = -1;
	
	printf("\n--------------- Begin Smithy Random Tests ---------------\n");
	
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
		  G.deckCount[i] = randNum(8,25);        // have at least 3 cards to draw
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
		  for (j = 0; j < randNum(1,5); j++){
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
		G.hand[currentPlayer][handPos] = smithy;
		//printf("handPos(13): %d   \n", handPos);
		
		memcpy(&testG,&G,sizeof(struct gameState));
	 
		int returnValue = cardEffect(smithy, choice1, choice2, choice3, &testG, handPos, &bonus);
	
		//printf("\nTEST-1: return value = 0\n");
		if(returnValue != 0){
			++index;
			printf(  "TEST-1 FAIL: return value = %d\n"  , returnValue);
		}
		
		//printf("\nTEST-2: currentPlayer's handCount - Smithy + 3 cards\n");
		if(testG.handCount[currentPlayer] != G.handCount[currentPlayer] + 2){
			++index;
			printf(  "TEST-2 FAIL: handCount changed from %d to %d\n"  , G.handCount[currentPlayer], testG.handCount[currentPlayer]);
		}
		  
		//printf("\nTEST-3: currentPlayer's deckCount - 3 cards\n");
		if(testG.deckCount[currentPlayer] != G.deckCount[currentPlayer] - 3){
			++index;
			printf(  "TEST-3 FAIL: deckCount changed from %d to %d\n"  , G.deckCount[currentPlayer], testG.deckCount[currentPlayer]);
		}
		
		//printf("\nTEST-4: 3 new cards in currentPlayer's hand are same as 3 cards removed from currentPlayer's deck\n");
		if(testG.hand[currentPlayer][testG.handCount[currentPlayer]-1] != G.deck[currentPlayer][G.deckCount[currentPlayer]-3] ||
		   testG.hand[currentPlayer][testG.handCount[currentPlayer]-2] != G.deck[currentPlayer][G.deckCount[currentPlayer]-2] ||
		   testG.hand[currentPlayer][testG.handCount[currentPlayer]-3] != G.deck[currentPlayer][G.deckCount[currentPlayer]-1]){
			++index;
			printf(  "TEST-4 FAIL: new cards in hand did not come from top of deck\n"  );
		}
		
		//printf("\nTEST-5: currentPlayer's discardCount didn't change\n");
		if(testG.discardCount[currentPlayer] != G.discardCount[currentPlayer]){
			++index;
			printf(  "TEST-5 FAIL: discardCount changed from %d to %d\n", G.discardCount[currentPlayer], testG.discardCount[currentPlayer]);
		}
		
		//printf("\nTEST-6: Smithy set to be discarded at end of turn\n");
		if(testG.hand[currentPlayer][testG.handCount[currentPlayer]] != -1 && testG.hand[currentPlayer][testG.handCount[currentPlayer]] != smithy){
			++index;
			printf(  "TESt-6 FAIL: Smithy is not set to be discarded at end of player's turn\n"  );
		}
		
		//printf("\nTEST-7: playedCardCount + 1\n");
		if(testG.playedCardCount != G.playedCardCount + 1){
			++index;
			printf(  "TEST-7 FAIL: playedCardCount changed from %d to %d\n"  , G.playedCardCount, testG.playedCardCount);
		}
		
		//printf("\nTEST-8: last played card was Smithy\n");
		if(testG.playedCards[testG.playedCardCount-1] != smithy){
			++index;
			printf(  "TEST-8 FAIL: last playedCard was not Smithy\n"  );
			//printf("last played card was(13): %d\n", testG.playedCards[testG.playedCardCount-1]);
		}
		
		//printf("\nTEST-9: numPlayers didn't change\n");
		if(testG.numPlayers != G.numPlayers){
			++index;
			printf(  "TEST-9 FAIL: numPlayers changed from %d to %d\n"  , G.numPlayers, testG.numPlayers);
		}
		
		//printf("\nTEST-10: still currentPlayer's turn\n");
		if(testG.whoseTurn != G.whoseTurn){
			++index;
			printf(  "TEST-10 FAIL: whoseTurn changed from %d to %d\n", G.whoseTurn, testG.whoseTurn);
		}
			
		//printf("\nTEST-11: game phase didn't change\n");
		if(testG.phase != G.phase){
			++index;
			printf(  "TEST-11 FAIL: game phase changed from %d to %d\n", G.phase, testG.phase);
		}
			
		//printf("\nTEST-12: numActions didn't change\n");
		if(testG.numActions != G.numActions){
			++index;
			printf(  "TEST-12 FAIL: numActions changed from %d to %d\n", G.numActions, testG.numActions);
		}
		
		//printf("\nTEST-13: numBuys didn't change\n");
		if(testG.numBuys != G.numBuys){
			++index;
			printf(  "TEST-13 FAIL: numBuys changed from %d to %d\n", G.numBuys, testG.numBuys);
		}
		
		//printf("\nTEST-14: currentPlayer's coins didn't change\n");
		if(testG.coins != G.coins){
			++index;
			printf(  "TEST-14 FAIL: currentPlayer's coins changed from %d to %d\n", G.coins, testG.coins);
		}
		
		for(i = 0; i < G.numPlayers; i++){
			if(i != G.whoseTurn){
				//printf("\nTEST-15: opponent's handCount didn't change\n");
				if(testG.handCount[i] != G.handCount[i]){
					++index;
					printf(  "TEST-15 FAIL: opponent %d's handCount changed from %d to %d\n", i, G.handCount[i], testG.handCount[i]);
				}
				  
				//printf("\nTEST-16: opponent's deckCount didn't change\n");
				if(testG.deckCount[i] != G.deckCount[i]){
					++index;
					printf(  "TEST-16 FAIL: opponent %d's deckCount changed from %d to %d\n", i, G.deckCount[i], testG.deckCount[i]);
				}
				
				//printf("\nTEST-17: 3 cards on top of opponent's deck didn't change\n");
				if(testG.deck[i][testG.deckCount[i]-1] != G.deck[i][G.deckCount[i]-1] ||
				   testG.deck[i][testG.deckCount[i]-2] != G.deck[i][G.deckCount[i]-2] ||
				   testG.deck[i][testG.deckCount[i]-3] != G.deck[i][G.deckCount[i]-3]){
					++index;
					printf(  "TEST-17 FAIL: cards from top of opponent %d's deck changed\n", i  );
					//printf("top of deck: %d, %d, %d", testG.deck[i][testG.deckCount[i]-1], testG.deck[i][testG.deckCount[i]-2], testG.deck[i][testG.deckCount[i]-3]);
				}
				
				//printf("\nTEST-18: opponent's discardCount didn't change\n");
				if(testG.discardCount[i] != G.discardCount[i]){
					++index;
					printf(  "TEST-18 FAIL: opponent %d's discardCount changed from %d to %d\n"  , i, G.discardCount[i], testG.discardCount[i]);
				}
			}
		}
		
		//printf("\nTEST-19: Curse supply didn't change\n");
		if(testG.supplyCount[curse] != G.supplyCount[curse]){
			++index;
			printf(  "TEST-19 FAIL: Curse supply changed\n"  );
		}
		
		//printf("\nTEST-20: Victory supplies didn't change\n");
		if(testG.supplyCount[estate] != G.supplyCount[estate] ||
		   testG.supplyCount[duchy] != G.supplyCount[duchy] ||
		   testG.supplyCount[province] != G.supplyCount[province]){
			++index;
			printf(  "TEST-20 FAIL: at least one Victory supply changed\n"  );
		}
		
		//printf("\nTEST-21: Treasure supplies didn't change\n");
		if(testG.supplyCount[copper] != G.supplyCount[copper] ||
		   testG.supplyCount[silver] != G.supplyCount[silver] ||
		   testG.supplyCount[gold] != G.supplyCount[gold]){
			++index;
			printf(  "TEST-21 FAIL: at least one Treasure supply changed\n"  );
		}
		
		//printf("\nTEST-22: Kingdom supplies didn't change\n");
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
			printf(  "TEST-22 FAIL: at least one Kingdom supply changed\n"  );
		}
		
		if(index == -1){
			printf("All tests PASSED\n");
		}
		printf("\n");
		index = -1;
	}
	
	printf("---------------- End Smithy Random Tests ----------------\n\n");
	
	return 0;
}