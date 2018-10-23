#include "testLib.h"

#define TESTCARD "smithy"
int main(){

    // struct gameState states[2];
    int actual, expected, numPasses = 0;

    /* Basic requirements for smithy
    1. Current player should receive exact 3 cards.
    2. 3 cards should come from his own pile.
    3. No state change should occur for other players.
    4. No state change should occur to the victory card piles and kingdom card piles.

        void playSmithy(struct gameState *state, int handPos, int currentPlayer){
    // Variables used:  currentPlayer, handPos, state
    //+3 Cards
    int i;
    for (i = 0; i < 3; i++){
        drawCard(currentPlayer, state);
        }		
    //discard card from hand
    //discardCard(handPos, currentPlayer, state, 0); //Bug: discardCard line commented out, artem 181013
    }

     */  
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;
    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    //int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState initG, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &initG);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	// ----------- TEST 1: player should receive exactly 3 cards --------------
    newCards = 3;
    /*       deckCounter = state->deckCount[player];//Create holder for the deck count
    state->hand[player][count] = state->deck[player][deckCounter - 1];//Add card to the hand
    state->deckCount[player]--;
    state->handCount[player]++;//Increment hand count
     */
	// copy the game state to a test case
	memcpy(&testG, &initG, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
    actual = testG.handCount[thisPlayer];
    expected = initG.handCount[thisPlayer] + newCards;
    if(actual == expected){
        printf("TEST 1: PASS player 1 received exactly 3 cards (hand count = %d, expected = %d)\n", actual, expected);
    }
    else{
        printf("TEST 1: FAIL current player didnt' receive exactly 3 cards (hand count = %d, expected = %d)\n", actual, expected);
    }

    actual = testG.deckCount[thisPlayer];
    expected = initG.deckCount[thisPlayer] - newCards;
    if(actual == expected){
        printf("TEST 2: PASS drawn 3 cards came from player's own deck (deck count = %d, expected = %d)\n", actual, expected);
    }
    else{
        printf("TEST 2: FAIL drawn 3 cards didn't come from player's own deck (deck count = %d, expected = %d)\n", actual, expected);
    }

    actual = testG.deckCount[thisPlayer+1] + testG.handCount[thisPlayer+1];
    expected = initG.deckCount[thisPlayer+1] + initG.handCount[thisPlayer+1];
    if(actual == expected){
        printf("TEST 3: PASS player 2's deck and hand count didn't change (deck+hand count = %d, expected = %d)\n", actual, expected);
    }
    else{
        printf("TEST 3: FAIL player 2's deck and hand count didn't change (deck+hand count = %d, expected = %d)\n", actual, expected);
    }

    
    /* Test 1 */
    // retVal = handCard(smithy, &states[0]);
    // expVal = smithy;
    // if(compareInts(expVal, retVal) == 0){
    //     printf("handCard(): PASS smithy in hand when player 1 plays smithy\n");
    //     numPasses++;
    // }
    // else{
    //     printf("handCard(): FAIL smithy not in hand when player 1 plays smithy\n");
    // }


    // if(numPasses == 4){
    //    printf("TEST SUCCESSFULLY COMPLETED\n");
    // }
    // else{
    //     printf("TEST FAILED\n");
    // }

   return 0;
}
