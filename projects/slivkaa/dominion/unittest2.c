/* -----------------------------------------------------------------------
 * To compile this file include the following lines in your makefile:
 *
 * testUpdateCoins: unittest2.c dominion.o rngs.o testLib.o
 *      	gcc -o unittest2 -g unittest2.c dominion.o rngs.o testLib.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "testLib.h"
#define TESTFUNC "numHandCards()"

int main(){

    struct gameState states[5];
    int i, actual, expected, numPasses = 0;

    for(i = 0; i < MAX_PLAYERS; i++){
        states[0].handCount[i] = 0;
        states[1].handCount[i] = 0;
        states[2].handCount[i] = 0;
        states[3].handCount[i] = 0;
        states[4].handCount[i] = 0;
    }

    states[0].whoseTurn = 0;
    states[0].handCount[states[0].whoseTurn] = 1;

    states[1].whoseTurn = 4;
    states[1].handCount[states[1].whoseTurn] = 1;

    states[2].whoseTurn = 0;
    states[2].handCount[states[2].whoseTurn] = 20;

    initGameState(&states[3]);
    initGameState(&states[4]);

    states[3].whoseTurn = 0;
    states[3].handCount[states[3].whoseTurn] = 1;

    states[4].whoseTurn = 0;
    states[4].handCount[states[4].whoseTurn] = 1;
  
  	printf("----------------- Testing function: %s ----------------\n", TESTFUNC);  
    
    /* Test 1 */
    actual = numHandCards(&states[0]);
    expected = 1;
    if(actual == expected){
        printf("TEST 1: PASS player 0's handcount = 1\n");
        printf("\thand count = %d, expected = %d\n", actual, expected);
        numPasses++;
    }
    else{
        printf("TEST 1: FAIL player 0's handcount != 1\n");
        printf("\thand count = %d, expected = %d\n", actual, expected);
    }

    /* Test 2 */
    actual = numHandCards(&states[1]);
    expected = 1;
    if(actual == expected){
        printf("TEST 2: PASS player 4's handcount = 1\n");
        printf("\thand count = %d, expected = %d\n", actual, expected);
        numPasses++;
    }
    else{
        printf("TEST 2: FAIL player 4's handcount != 1\n");
        printf("\thand count = %d, expected = %d\n", actual, expected);
    }

    /* Test 3 */
    actual = numHandCards(&states[2]);
    expected = 20;
    if(actual == expected){
        printf("TEST 3: PASS player 1's handcount = 20\n");
        printf("\thand count = %d, expected = %d\n", actual, expected);
        numPasses++;
    }
    else{
        printf("TEST 3: FAIL player 1's handcount != 20\n");
        printf("\thand count = %d, expected = %d\n", actual, expected);
    }

    /* Test 4 */
    numHandCards(&states[3]);
    actual = compareGameStates(&states[3], &states[4]);
    expected = 0;
    if(actual == expected){
        printf("TEST 4: PASS game state doesn't change after numHandCards() call\n");
        printf("\tgame state changed? = %d, expected = %d\n", actual, expected);
        numPasses++;
    }
    else{
        printf("TEST 4: FAIL game state does change after numHandCards() call\n");
        printf("\tgame state changed? = %d, expected = %d\n", actual, expected);
    }

    if(numPasses == 4){
       printf("TEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("TEST FAILED\n");
    }

    return 0;
}

