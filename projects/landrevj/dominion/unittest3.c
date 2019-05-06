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


  int actions_before = G.numActions;
  int before = G.handCount[player];
  cardeffect_village(&G, 0);
  int after = G.handCount[player];
  int actions_after = G.numActions;

  assert_true("cards added == 1", (after - before) == 0); // we draw one then discard the played card, so a difference of 0
  assert_true("actions added = 2", (actions_after - actions_before) == 2);
  return 0;
}
