#include "testLib.h"

#define TESTCARD "adventurer"
int main(){

    /* Basic requirements for adventurer
    1. Player should have 2 treasure cards in his hand (handCount == 2)
    3. All cards from hand pile (except treasure cards) should be moved to discard pile
    4. No state change should occur to kingdom card piles.
    5. No state change should occur to other's players hand piles.

    void playAdventurer(struct gameState *state, int drawntreasure, int z, int currentPlayer, int cardDrawn, int *temphand){
    // Variables used: drawntreasure, state, currentPlayer, z, temphand
    //while(drawntreasure<2){   //Original line
    while(drawntreasure<4){   //Bug: allows adventurer to draw more treasure cards than intended, artem 181013
        if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
         shuffle(currentPlayer, state);
        }
        drawCard(currentPlayer, state);
        cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold){
            drawntreasure++; 
        }
        else{
            temphand[z]=cardDrawn;
            state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
            z++;
        }
    }
        while(z-1>=0){
            state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
            z=z-1;
        }
    }

     */  
    int actual, expected, numPasses = 0;
    int newCards = 0, card;
    int discarded = 1;
    //int xtraCoins = 0;
    //int shuffledCards = 0;
    int i, j;
    //int m;
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
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

    printf("player 1 deck count: %d\n", initG.deckCount[thisPlayer]);
	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	// ----------- TEST 1: player should have exactly 2 treasure cards in his deck --------------
    int numTreasures = 0;
    for(i = 0; i < testG.handCount[thisPlayer]; i++){
        card = testG.hand[thisPlayer][i];
        if(card == copper || card == silver || card == gold){
            numTreasures +=1;
        }
    }
    actual = numTreasures;
    expected = 2;
    if( (actual == expected) && testG.handCount[thisPlayer] == 2){
        printf("TEST 1: PASS player 1 has 2 treasure cards in his hand (hand count = %d, expected = %d)\n", actual, expected);
        numPasses++;
    }
    else{
        printf("TEST 1: FAIL player 1 has >2 or <2 treasure cards in his hand (hand count = %d, expected = %d)\n", actual, expected);
    }


    // ----------- TEST 2: All cards from hand pile (except treasure cards) should be moved to discard pile --------------
    // int actCount = testG.handCount[thisPlayer];
    // int expCount = 2;
    numTreasures = 0;
    for(i = 0; i < initG.handCount[thisPlayer]; i++){
        card = initG.hand[thisPlayer][i];
        if(card == copper || card == silver || card == gold){
            numTreasures +=1;
        }
    }
    expected = initG.handCount[thisPlayer] - numTreasures;
    actual = testG.discardCount[thisPlayer] - initG.discardCount[thisPlayer];
    if(expected == actual){
        printf("TEST 2: PASS all non-treasure cards in player's hand were moved to discard pile (discarded count = %d, expected = %d)\n", actual, expected);
        numPasses++;
    }
    else{
        printf("TEST 2: FAIL all non-treasure cards in player's hand were NOT moved to discard pile (discarded count = %d, expected = %d)\n", actual, expected);
    }


    if(numPasses == 2){
       printf("TEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("TEST FAILED\n");
    }

   return 0;
}