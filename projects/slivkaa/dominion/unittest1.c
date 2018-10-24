
/* -----------------------------------------------------------------------
 * To compile this file include the following lines in your makefile:
 *
 * testUpdateCoins: unittest1.c dominion.o rngs.o testLib.o
 *      	gcc -o unittest1 -g unittest1.c dominion.o rngs.o testLib.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "testLib.h"

int main(){

    struct gameState states[5];
    int i, retVal, expVal, numPasses = 0;

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

    retVal = isGameOver(&states[0]);
    expVal = 1;
    if(compareInts(expVal, retVal) == 0){
        printf("isGameOver(): PASS game over with 0 province cards\n");
        numPasses++;
    }
    else{
        printf("isGameOver(): FAIL game not over with 0 province cards\n ");
    }
   
    retVal = isGameOver(&states[1]);
    expVal = 0;
    if(compareInts(expVal, retVal) == 0){
        printf("isGameOver(): PASS game not over with 2 province cards\n");
        numPasses++;
    }
    else{
        printf("isGameOver(): FAIL game over with 2 province cards left\n");
    }
    
    retVal = isGameOver(&states[2]);
    expVal = 1;
     if(compareInts(expVal, retVal) == 0){
        printf("isGameOver(): PASS game over with 3 supply piles empty\n");
        numPasses++;
    }
    else{
        printf("isGameOver(): FAIL game not over with 3 supply piles empty\n");
    }
   
    retVal = isGameOver(&states[3]);
    expVal = 0;
    if(compareInts(expVal, retVal) == 0){
        printf("isGameOver(): PASS game not over with <3 supply piles empty\n");
        numPasses++;
    }
    else{
        printf("isGameOver(): FAIL game over with <3 supply piles empty\n");
    }
   
   if(numPasses == 4){
       printf("TEST SUCCESSFULLY COMPLETED\n");
   }
   else{
       printf("TEST FAILED\n");
   }
    return 0;
}
