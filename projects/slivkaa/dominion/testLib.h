#ifndef _TESTLIB_H
#define _TESTLIB_H

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

int compareInts(int a, int b);
int compareGameStates(struct gameState *state1, struct gameState *state2);
void initGameState(struct gameState *state);
void printGameState(struct gameState *state);


#endif