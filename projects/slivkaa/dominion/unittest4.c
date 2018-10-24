/* -----------------------------------------------------------------------
 * To compile this file include the following lines in your makefile:
 *
 * testUpdateCoins: unittest4.c dominion.o rngs.o testLib.o
 *      	gcc -o unittest4 -g unittest4.c dominion.o rngs.o testLib.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "testLib.h"
#define TESTFUNC "handCard()"


int main(){

    struct gameState states[5];
    int i, actual, expected, numPasses = 0;

    for(i = 0; i < 5; i++){
        initGameState(&states[i]);
    }
   
    states[0].whoseTurn = 0;   /* Test 1 init */
    states[0].hand[0][smithy] = smithy;

    states[1].whoseTurn = 0;  /* Test 2 init */
    states[1].hand[0][treasure_map] = treasure_map;

    states[2].whoseTurn = 3;  /* Test 3 init */
    states[2].hand[3][smithy] = smithy;

    states[3].whoseTurn = 0;  /* Test 3 init */
    states[3].hand[0][smithy] = smithy;

    states[4].whoseTurn = 0;  /* Test 3 init */
    states[4].hand[0][smithy] = smithy;
   
    printf("----------------- Testing function: %s ----------------\n", TESTFUNC);  
    /* Test 1 */
    actual = handCard(smithy, &states[0]);
    expected = smithy;
    if(expected == actual){
        printf("handCard(): PASS smithy in hand when player 1 plays smithy\n");
        printf("\tcurrent card in hand= %d, expected = %d\n", actual, expected);
        numPasses++;
    }
    else{
        printf("handCard(): FAIL smithy not in hand when player 1 plays smithy\n");
        printf("\tcurrent card in hand= %d, expected = %d\n", actual, expected);
    }

     /* Test 2 */
    actual = handCard(treasure_map, &states[1]);
    expected = treasure_map;
    if(expected == actual){
        printf("handCard(): PASS treasure_map in hand when player 1 plays treasure_map\n");
        printf("\tcurrent card in hand= %d, expected = %d\n", actual, expected);
        numPasses++;
    }
    else{
        printf("handCard(): FAIL treasure_map not in hand when player 1 plays treasure_map\n");
        printf("\tcurrent card in hand= %d, expected = %d\n", actual, expected);
    }

     /* Test 3 */
    actual = handCard(smithy, &states[2]);
    expected = smithy;
    if(expected == actual){
        printf("handCard(): PASS smithy in hand when player 4 plays smithy\n");
        printf("\tcurrent card in hand= %d, expected = %d\n", actual, expected);
        numPasses++;
    }
    else{
        printf("handCard(): FAIL smithy not in hand when player 4 plays smithy\n");
        printf("\tcurrent card in hand= %d, expected = %d\n", actual, expected);
    }

    /* Test 4 */
    handCard(smithy, &states[3]);
    actual = compareGameStates(&states[3], &states[4]);
    expected = 0;
    if(expected == actual){
        printf("handCard(): PASS hand array (in game state) changes when player 1 plays smithy\n");
        printf("\tgame state changed?= %d, expected = %d\n", actual, expected);
        numPasses++;
    }
    else{
        printf("handCard(): FAIL hand array (in game state) doesn't change when player 1 plays smithy\n");
        printf("\tgame state changed?= %d, expected = %d\n", actual, expected);
    }

    if(numPasses == 4){
       printf("TEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("TEST FAILED\n");
    }

   return 0;
}
