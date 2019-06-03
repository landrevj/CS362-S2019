#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>

void assert_true(char test_string[100], int assertion) {
  char build_str[100];
  strcpy(build_str, test_string);
  strcat(build_str, (assertion == 0 ? ": false" : ": true"));
  printf("%s\n", build_str);
}

int get_treasure_count(int player, struct gameState *state) {
  int treasures = 0;
  for (int i = 0; i < state->handCount[player]; i++)
  {
    int hand = state->hand[player][i];
    if (hand == copper || hand == silver || hand == gold) treasures++;
  }
  return treasures;
}

int main()
{
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
  struct gameState G;

  initializeGame(2, k, 1, &G);
  int player = whoseTurn(&G);

  int before = get_treasure_count(player, &G);
  cardeffect_adventurer(&G);
  int after = get_treasure_count(player, &G);

  assert_true("treasures added == 2", (after - before) == 2);

  return 0;
}
