/* -----------------------------------------------------------------------
 * To compile this file include the following lines in your makefile:
 *
 * testUpdateCoins: unittest3.c dominion.o rngs.o testLib.o
 *      	gcc -o unittest3 -g unittest3.c dominion.o rngs.o testLib.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "testLib.h"
#define TESTFUNC "buyCard()"

int main(){

    struct gameState states[8];
    int i, actual, expected, numPasses = 0;

    for(i = 0; i < 8; i++){
        initGameState(&states[i]);
    }
    /* Test 1 init */
    states[0].numBuys = 0;  

    /* Test 2 init */
    states[1].numBuys = 1;  
    states[1].supplyCount[province] = 0;

    /* Test 3 init */
    states[2].numBuys = 1;  
    states[2].supplyCount[province] = 1;
    states[2].coins = 0;

    /* Test 4 init */
    states[3].numBuys = 1;  
    states[3].supplyCount[province] = 1;
    states[3].coins = 8;

    /* Test 5 init */
    states[4].numBuys = 1;  
    states[4].supplyCount[province] = 1;
    states[4].coins = 0;
    states[5].numBuys = 1;
    states[5].supplyCount[province] = 1;
    states[5].coins = 0;

    /* Test 6 init */
    states[6].numBuys = 1;
    states[6].supplyCount[province] = 1;
    states[6].coins = 8;

    states[7].numBuys = states[7].supplyCount[province] = states[7].coins = 0;
    states[7].discard[0][states[7].discardCount[0]] = province;
    states[7].phase = 1;
    states[7].discardCount[0]++;
    

    printf("----------------- Testing function: %s ----------------\n", TESTFUNC);  
    /* Test 1 */
    actual = buyCard(province, &states[0]);
    expected = -1;
    if(expected == actual){
        printf("TEST 1: PASS card not bought when player's numBuys < 1\n");
        printf("\tcard bought = %d, expected = %d\n", actual, expected);
        numPasses++;
    }
    else{
        printf("TEST 1: FAIL card bought when player's numBuys < 1\n");
        printf("\tcard bought = %d, expected = %d\n", actual, expected);
    }

    /* Test 2 */
    actual = buyCard(province, &states[1]);
    expected = -1;
    if(expected == actual){
        printf("TEST 2: PASS card not bought when player's card supply count < 1\n");
        printf("\tcard bought = %d, expected = %d\n", actual, expected);
        numPasses++;
    }
    else{
        printf("TEST 2: FAIL card bought when player's supply count for card < 1\n");
        printf("\tcard bought = %d, expected = %d\n", actual, expected);
    }

    /* Test 3 */
    actual = buyCard(province, &states[2]);
    expected = -1;
    if(expected == actual){
        printf("TEST 3: PASS card not bought when there's not enough money\n");
        printf("\tcard bought = %d, expected = %d\n", actual, expected);
        numPasses++;
    }
    else{
        printf("TEST 3: FAIL card bought when there's not enough money\n");
        printf("\tcard bought = %d, expected = %d\n", actual, expected);
    }

    /* Test 4 */
    actual = buyCard(province, &states[3]);
    expected = 0;
    if(expected == actual){
        printf("TEST 4: PASS card bought when there's enough money\n");
        printf("\tcard bought = %d, expected = %d\n", actual, expected);
        numPasses++;
    }
    else{
        printf("TEST 4: FAIL card not bought when there's enough money\n");
        printf("\tcard bought = %d, expected = %d\n", actual, expected);
    }

    /* Test 5 */
    buyCard(province, &states[4]);
    actual = compareGameStates(&states[4], &states[5]);
    expected = 0;
    if(expected == actual){
        printf("TEST 5: PASS game state doesn't change after not buying card\n");
        printf("\tstate changed? = %d, expected = %d\n", actual, expected);
        numPasses++;
    }
    else{
        printf("TEST 5: FAIL game state does change after not buying card\n");
        printf("\tstate changed? = %d, expected = %d\n", actual, expected);
    }

    /* Test 6 */
    actual = buyCard(province, &states[6]);
    actual +=(states[6].supplyCount[province]);
    actual +=compareGameStates(&states[6], &states[7]);
    expected = 0;
    if(expected == actual){
        printf("TEST 6: PASS game state does change after buying card\n");
        printf("\tstate changed? = %d, expected = %d\n", actual, expected);
        numPasses++;
    }
    else{
        printf("TEST 6: FAIL game state doesn't change after buying card\n");
        printf("\tstate changed? = %d, expected = %d\n", actual, expected);
    }

    if(numPasses == 6){
       printf("TEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("TEST FAILED\n");
    }

   return 0;
}