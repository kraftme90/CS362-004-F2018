#include "testLib.h"

int main(){

    struct gameState states[5];
    int i, retVal, expVal;

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
   
    /* Test 1 */
    retVal = handCard(smithy, &states[0]);
    expVal = smithy;
    if(compareInts(expVal, retVal) == 0){
        printf("handCard(): PASS if smithy in hand when player 1 plays smithy\n");
    }
    else{
        printf("handCard(): FAIL if smithy not in hand when player 1 plays smithy\n");
    }

     /* Test 2 */
    retVal = handCard(treasure_map, &states[1]);
    expVal = treasure_map;
    if(compareInts(expVal, retVal) == 0){
        printf("handCard(): PASS if treasure_map in hand when player 1 plays treasure_map\n");
    }
    else{
        printf("handCard(): FAIL if treasure_map not in hand when player 1 plays treasure_map\n");
    }

     /* Test 3 */
    retVal = handCard(smithy, &states[2]);
    expVal = smithy;
    if(compareInts(expVal, retVal) == 0){
        printf("handCard(): PASS if smithy in hand when player 4 plays smithy\n");
    }
    else{
        printf("handCard(): FAIL if smithy not in hand when player 4 plays smithy\n");
    }

    /* Test 4 */
    handCard(smithy, &states[3]);
    retVal = compareGameStates(&states[3], &states[4]);
    expVal = 0;
    if(compareInts(expVal, retVal) == 0){
        printf("handCard(): PASS if hand array (in game state) changes when player 1 plays smithy\n");
    }
    else{
        printf("handCard(): FAIL if hand array(in game state) doesn't change when player 1 plays smithy\n");
    }


   return 0;
}

/*
int handCard(int handPos, struct gameState *state){
  int currentPlayer = whoseTurn(state);
  return state->hand[currentPlayer][handPos];
}
*/