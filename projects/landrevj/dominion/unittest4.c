#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>

void assert_true(char test_string[100], int assertion)
{
  char build_str[100];
  strcpy(build_str, test_string);
  strcat(build_str, (assertion == 0 ? ": false" : ": true"));
  printf("%s\n", build_str);
}

int main()
{
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
  struct gameState G;

  initializeGame(2, k, 1, &G);
  int player = whoseTurn(&G);

  int before_draw = G.handCount[player];
  cardeffect_steward(1, -1, -1, &G, 0);
  int after_draw = G.handCount[player];
  assert_true("cards added == 2", (after_draw - before_draw) == 1); // we draw two then discard the played card, so a difference of 1

  int before_coins = G.coins;
  cardeffect_steward(2, -1, -1, &G, 0);
  int after_coins = G.coins;
  assert_true("coins added == 2", (after_coins - before_coins) == 2);

  int before_discard = G.handCount[player];
  cardeffect_steward(0, 1, 2, &G, 0);
  int after_discard = G.handCount[player];
  assert_true("cards discarded == 2", (after_discard - before_discard) == -3); // we discard two plus the played card so -3
  
  return 0;
}
