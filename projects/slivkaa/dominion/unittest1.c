/* -----------------------------------------------------------------------
 * To compile this file include the following lines in your makefile:
 *
 * testUpdateCoins: unittest1.c dominion.o rngs.o testLib.o
 *      	gcc -o unittest1 -g unittest1.c dominion.o rngs.o testLib.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "testLib.h"
#define TESTFUNC "isGameOver()"

int main(){

    struct gameState states[5];
    int i, actual, expected, numPasses = 0;

    for(i = 0; i < 25; i++){
        states[0].supplyCount[i] = 1;
        states[1].supplyCount[i] = 1;
        states[2].supplyCount[i] = 1;
        states[3].supplyCount[i] = 1;
    }
    states[0].supplyCount[province] = 0;
    states[1].supplyCount[province] = 2;

    for(i = 0; i < 3; i++){
        states[2].supplyCount[i] = 0;
    }
    
    for(i = 0; i < 2; i++){
        states[3].supplyCount[i] = 2;
    }

	printf("----------------- Testing function: %s ----------------\n", TESTFUNC);
    // ----------- TEST 1: game over with 0 province cards --------------
   
    actual = isGameOver(&states[0]);
    expected = 1;
    if(actual == expected){
        printf("TEST 1: PASS game over with 0 province cards\n");
        printf("\treturn value = %d, expected = %d\n", actual, expected);
        numPasses++;
    }
    else{
        printf("TEST 1: FAIL game not over with 0 province cards\n");
        printf("\treturn value = %d, expected = %d\n", actual, expected);
    }
   
    actual = isGameOver(&states[1]);
    expected = 0;
    if(actual == expected){
        printf("TEST 2: PASS game not over with 2 province cards left\n");
        printf("\treturn value = %d, expected = %d\n", actual, expected);
        numPasses++;
    }
    else{
        printf("TEST 2: FAIL game over with 2 province cards left\n");
        printf("\treturn value = %d, expected = %d\n", actual, expected);
    }
    
    actual = isGameOver(&states[2]);
    expected = 1;
    if(actual == expected){
        printf("TEST 3: PASS game over with 3 supply piles empty\n");
        printf("\treturn value = %d, expected = %d\n", actual, expected);
        numPasses++;
    }
    else{
        printf("TEST 3: FAIL game not over with 3 supply piles empty\n");
        printf("\treturn value = %d, expected = %d\n", actual, expected);
    }
   
    actual = isGameOver(&states[3]);
    expected = 0;
    if(actual == expected){
        printf("TEST 4: PASS game not over with <3 supply piles empty\n");
        printf("\treturn value = %d, expected = %d\n", actual, expected);
        numPasses++;
    }
    else{
        printf("TEST 4: FAIL game over with <3 supply piles empty\n");
        printf("\treturn value = %d, expected = %d\n", actual, expected);
    }
   
   if(numPasses == 4){
       printf("TEST SUCCESSFULLY COMPLETED\n");
   }
   else{
       printf("TEST FAILED\n");
   }
    return 0;
}
