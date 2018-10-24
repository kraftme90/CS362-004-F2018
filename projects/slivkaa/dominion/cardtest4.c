
#include "testLib.h"

#define TESTCARD "village"
int main(){

    /* Basic testing for village
    1. +1 card draw from deck/discard pile 
    2. add +2 actions to game state
    3. village card discarded from hand, playedCardCount+1
    4. check state changes to other player's decks/hands
     case village:
      //+1 Card
      drawCard(currentPlayer, state);
			
      //+2 Actions
      state->numActions = state->numActions + 2;
			
      //discard played card from hand
      discardCard(handPos, currentPlayer, state, 0);
      return 0;
     
     */  
    int actual, expected, numPasses = 0;
    int expHandCount, actHandCount, expDeckCount, actDeckCount;
    int newCards = 0, card;
    int discarded = 1;
    int i, j;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2, thisPlayer = 0;
	struct gameState initG, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &initG);  
    // copy the game state to a test case
    memcpy(&testG, &initG, sizeof(struct gameState));
    //Playing card
    choice3 = thisPlayer;
	cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	// ----------- TEST 1: player gains +1 card draw from deck  --------------
    expected = initG.deckCount[thisPlayer] - 1;
    actual = testG.deckCount[thisPlayer];
    if( (expected == actual)  ){ 
        printf("TEST 1: PASS player 1 draws +1 card from deck\n");
        printf("\tdeck card count = %d, expected = %d\n", actual, expected);
        numPasses++;
    }
    else{
        printf("TEST 1: FAIL player 1 doesn't draw +1 card from deck\n");
        printf("\tdeck card count = %d, expected = %d\n", actual, expected);
    }

	// ----------- TEST 2: player 1 gains +2 actions --------------
    expected = initG.numActions + 2;
    actual = testG.numActions;
    if(expected == actual){ 
        printf("TEST 2: PASS player 1 gains +2 actions\n");
        printf("\tnum of actions = %d, expected = %d\n", actual, expected);
        numPasses++;
    }
    else{
        printf("TEST 2: FAIL player 1 gains +2 actions\n");
        printf("\tnum of actions = %d, expected = %d\n", actual, expected);
    }

    // ----------- TEST 3: player 1 discards village card from hand --------------
    int numPCards[2], handChange[2];
    numPCards[0] = initG.playedCardCount + 1;
    numPCards[1] = testG.playedCardCount;
    handChange[0] = 0;
    handChange[1]= (initG.handCount[thisPlayer] - testG.handCount[thisPlayer]);

    if( (numPCards[0] == numPCards[1]) && (handChange[0] == handChange[1])){ 
        printf("TEST 3: PASS player 1 discards village card from hand\n");
        printf("\tnum of playedCards = %d, expected = %d\n", numPCards[1], numPCards[0]);
        printf("\tchange of cards in hand = %d, expected = %d\n", handChange[1], handChange[0]);
        numPasses++;
    }
    else{
        printf("TEST 3: FAIL player 1 doesn't discard village card from hand\n");
        printf("\tnum of playedCards = %d, expected = %d\n", numPCards[1], numPCards[0]);
        printf("\tchange of cards in hand = %d, expected = %d\n", handChange[1], handChange[0]);
    }

    // ----------- TEST 4: check state changes to other player's decks/hands --------------
    int p2DeckCount[2], p2HandCount[2];
    p2DeckCount[0] = initG.deckCount[thisPlayer+1];
    p2DeckCount[1] = testG.deckCount[thisPlayer+1];
    p2HandCount[0] = initG.handCount[thisPlayer+1];
    p2HandCount[1] = testG.handCount[thisPlayer+1];

    if((p2DeckCount[0] == p2DeckCount[1]) && (p2HandCount[0] == p2HandCount[1])){
        printf("TEST 4: PASS player 1 discards village card from hand\n");
        printf("\thand count = %d, expected = %d\n", p2HandCount[1], p2HandCount[0]);
        printf("\tdeck count = %d, expected = %d\n", p2DeckCount[1], p2DeckCount[0]);
        numPasses++;
    }
    else{
        printf("TEST 3: FAIL player 1 doesn't discard village card from hand\n");
        printf("\thand count = %d, expected = %d\n", p2HandCount[1], p2HandCount[0]);
        printf("\tdeck count = %d, expected = %d\n", p2DeckCount[1], p2DeckCount[0]);
    }

    if(numPasses == 4){
       printf("TEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("TEST FAILED\n");
    }

   return 0;
}