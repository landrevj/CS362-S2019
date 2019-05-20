#ifndef _DOMINION_HELPERS_H
#define _DOMINION_HELPERS_H

#include "dominion.h"

int drawCard(int player, struct gameState *state);
int updateCoins(int player, struct gameState *state, int bonus);
int discardCard(int handPos, int currentPlayer, struct gameState *state, 
		int trashFlag);
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player);
int getCost(int cardNumber);
int cardEffect(int card, int choice1, int choice2, int choice3, 
	       struct gameState *state, int handPos, int *bonus);
				 
// Card effect refactored functions
int cardeffect_adventurer(struct gameState *state);
int cardeffect_smithy(struct gameState *state, int handPos);
int cardeffect_village(struct gameState *state, int handPos);
int cardeffect_steward(int choice1, int choice2, int choice3, struct gameState *state, int handPos);
int cardeffect_embargo(int choice1, struct gameState *state, int handPos);
#endif
