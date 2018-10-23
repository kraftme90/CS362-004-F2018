#include "testLib.h"

int main(){

    struct gameState test1, test2, test3, test4;
    int i, retVal, expVal;

    for(i = 0; i < 25; i++){
        test1.supplyCount[i] = 1;
        test2.supplyCount[i] = 1;
        test3.supplyCount[i] = 1;
        test4.supplyCount[i] = 1;
    }
    test1.supplyCount[province] = 0;

    test2.supplyCount[province] = 2;

    for(i = 0; i < 3; i++){
        test3.supplyCount[i] = 0;
    }
    
    for(i = 0; i < 2; i++){
        test4.supplyCount[i] = 2;
    }

    retVal = isGameOver(&test1);
    expVal = 1;
    if(compareInts(expVal, retVal) == 0){
        printf("isGameOver(): PASS if game over with 0 province cards\n");
    }
    else{
        printf("isGameOver(): FAIL if game not over with 0 province cards\n ");
    }
   
    retVal = isGameOver(&test2);
    expVal = 0;
    if(compareInts(expVal, retVal) == 0){
        printf("isGameOver(): PASS if game not over with 2 province cards\n");
    }
    else{
        printf("isGameOver(): FAIL if game over with 2 province cards left\n");
    }
    
    retVal = isGameOver(&test3);
    expVal = 1;
     if(compareInts(expVal, retVal) == 0){
        printf("isGameOver(): PASS if game over with 3 supply piles empty\n");
    }
    else{
        printf("isGameOver(): FAIL if game not over with 3 supply piles empty\n");
    }
   
    retVal = isGameOver(&test4);
    expVal = 0;
    if(compareInts(expVal, retVal) == 0){
        printf("isGameOver(): PASS if game not over with <3 supply piles empty\n");
    }
    else{
        printf("isGameOver(): FAIL Game over with <3 supply piles empty\n");
    }
   
    return 0;
}
