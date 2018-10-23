#include "testLib.h"

int main(){

    struct gameState test1, test2, test3, test4, test5;
    int i, retVal, expVal;

    for(i = 0; i < MAX_PLAYERS; i++){
        test1.handCount[i] = 0;
        test2.handCount[i] = 0;
        test3.handCount[i] = 0;
        test4.handCount[i] = 0;
        test5.handCount[i] = 0;
    }

    test1.whoseTurn = 0;
    test1.handCount[test1.whoseTurn] = 1;

    test2.whoseTurn = 4;
    test2.handCount[test2.whoseTurn] = 1;

    test3.whoseTurn = 0;
    test3.handCount[test3.whoseTurn] = 20;

    initGameState(&test4);
    initGameState(&test5);

    test4.whoseTurn = 0;
    test4.handCount[test4.whoseTurn] = 1;

    test5.whoseTurn = 0;
    test5.handCount[test5.whoseTurn] = 1;
  
    retVal = numHandCards(&test1);
    expVal = 1;
    if(compareInts(expVal, retVal) == 0){
        printf("numHandCards(): PASS if player 0's handcount = 1\n");
    }
    else{
        printf("numHandCards(): FAIL if player 0's handcount != 1\n");
    }

    retVal = numHandCards(&test2);
    expVal = 1;
    if(compareInts(expVal, retVal) == 0){
        printf("numHandCards(): PASS if player 4's handcount = 1\n");
    }
    else{
        printf("numHandCards(): FAIL if player 4's handcount != 1\n");
    }

    retVal = numHandCards(&test3);
    expVal = 20;
    if(compareInts(expVal, retVal) == 0){
        printf("numHandCards(): PASS if player 1's handcount = 20\n");
    }
    else{
        printf("numHandCards(): FAIL if player 1's handcount != 20\n");
    }

    numHandCards(&test4);
    retVal = compareGameStates(&test4, &test5);
    expVal = 0;
    if(compareInts(expVal, retVal) == 0){
        printf("numHandCards(): PASS if game state doesn't change after numHandCards() call\n");
    }
    else{
        printf("numHandCards(): FAIL if game state does change after numHandCards() call\n");
    }
    return 0;
}

