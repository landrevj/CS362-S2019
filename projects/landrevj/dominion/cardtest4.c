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

  // choice 1
  int before_actions = G.numActions;
  int before_coins = G.coins;
  cardEffect(minion, 1, 0,0, &G, 0, NULL);
  int after_actions = G.numActions;
  int after_coins = G.coins;

  assert_true("actions added = 1", (after_actions - before_actions) == 1);
  assert_true("coins added == 2", (after_coins - before_coins) == 2);

  // choice 2
  cardEffect(minion, 0,1,0, &G, 0, NULL);
  assert_true("cards in hand == 4", G.handCount[player] == 4);

  return 0;
}
