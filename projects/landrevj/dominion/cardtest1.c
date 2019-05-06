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

  int before_embargo = G.embargoTokens[estate];
  int before_coins = G.coins;
  cardEffect(embargo, estate,-1,-1, &G, 0, NULL);
  int after_coins = G.coins;
  int after_embargo = G.embargoTokens[estate];
  assert_true("coins added == 2", (after_coins - before_coins) == 2);
  assert_true("embargo tokens added == 1", (after_embargo - before_embargo) == 1);
  
  return 0;
}
