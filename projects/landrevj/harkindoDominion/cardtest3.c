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

  int before = G.handCount[player];
  cardEffect(smithy, -1, -1, -1, &G, 0, NULL);
  int after = G.handCount[player];

  assert_true("cards added == 3", (after - before) == 2); // we draw three then discard the played card, so a difference of 2

  return 0;
}
