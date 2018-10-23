#include "testLib.h"

int main(){

    struct gameState states[8];
    int i, retVal, expVal;

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
    
    printf("unittest3.c:\n");
    /* Test 1 */
    retVal = buyCard(province, &states[0]);
    expVal = -1;
    if(compareInts(expVal, retVal) == 0){
        printf("buyCard(): PASS when player's numBuys < 1 \n");
    }
    else{
        printf("buyCard(): FAIL when player's numBuys < 1\n");
    }

    /* Test 2 */
    retVal = buyCard(province, &states[1]);
    expVal = -1;
    if(compareInts(expVal, retVal) == 0){
        printf("buyCard(): PASS when player's supply count for card < 1\n");
    }
    else{
        printf("buyCard(): FAIL when player's supply count for card  < 1\n");
    }

    /* Test 3 */
    retVal = buyCard(province, &states[2]);
    expVal = -1;
    if(compareInts(expVal, retVal) == 0){
        printf("buyCard(): PASS when player doesn't have enough money to buy card\n");
    }
    else{
        printf("buyCard(): FAIL when player doesn't have enough money to buy card\n");
    }

    /* Test 4 */
    retVal = buyCard(province, &states[3]);
    expVal = 0;
    if(compareInts(expVal, retVal) == 0){
        printf("buyCard(): PASS when player has enough money to buy card\n");
    }
    else{
        printf("buyCard(): FAIL when player has enough money to buy card\n");
    }

    /* Test 5 */
    buyCard(province, &states[4]);
    retVal = compareGameStates(&states[4], &states[5]);
    expVal = 0;
    if(compareInts(expVal, retVal) == 0){
        printf("buyCard(): PASS when game state doesn't change after not buying card\n");
    }
    else{
        printf("buyCard(): FAIL when game state does change after not buying card\n");
    }

    /* Test 6 */
    retVal = buyCard(province, &states[6]);
    retVal +=(states[6].supplyCount[province]);
    retVal +=compareGameStates(&states[6], &states[7]);
    expVal = 0;
    if(compareInts(expVal, retVal) == 0){
        printf("buyCard(): PASS when game state does change after buying card\n");
    }
    else{
        printf("buyCard(): FAIL when game state doesn't change after buying card\n");
    }

   return 0;
}