/* -----------------------------------------------------------------------
 * To compile this file include the following lines in your makefile:
 *
 * testUpdateCoins: unittest2.c dominion.o rngs.o testLib.o
 *      	gcc -o unittest2 -g unittest2.c dominion.o rngs.o testLib.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "testLib.h"

int main(){

    struct gameState states[5];
    int i, retVal, expVal, numPasses = 0;

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
  
    retVal = numHandCards(&states[0]);
    expVal = 1;
    if(compareInts(expVal, retVal) == 0){
        printf("numHandCards(): PASS player 0's handcount = 1\n");
        numPasses++;
    }
    else{
        printf("numHandCards(): FAIL player 0's handcount != 1\n");
    }

    retVal = numHandCards(&states[1]);
    expVal = 1;
    if(compareInts(expVal, retVal) == 0){
        printf("numHandCards(): PASS player 4's handcount = 1\n");
        numPasses++;
    }
    else{
        printf("numHandCards(): FAIL player 4's handcount != 1\n");
    }

    retVal = numHandCards(&states[2]);
    expVal = 20;
    if(compareInts(expVal, retVal) == 0){
        printf("numHandCards(): PASS player 1's handcount = 20\n");
        numPasses++;
    }
    else{
        printf("numHandCards(): FAIL player 1's handcount != 20\n");
    }

    numHandCards(&states[3]);
    retVal = compareGameStates(&states[3], &states[4]);
    expVal = 0;
    if(compareInts(expVal, retVal) == 0){
        printf("numHandCards(): PASS game state doesn't change after numHandCards() call\n");
        numPasses++;
    }
    else{
        printf("numHandCards(): FAIL game state does change after numHandCards() call\n");
    }

    if(numPasses == 4){
       printf("TEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("TEST FAILED\n");
    }

    return 0;
}

