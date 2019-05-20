#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void assert_true(char test_string[100], int assertion)
{
  char build_str[100];
  strcpy(build_str, test_string);
  strcat(build_str, (assertion == 0 ? ": false" : ": true"));
  printf("%s\n", build_str);
}

int get_treasure_count(int player, struct gameState *state)
{
  int treasures = 0;
  for (int i = 0; i < state->handCount[player]; i++)
  {
    int hand = state->hand[player][i];
    if (hand == copper || hand == silver || hand == gold)
      treasures++;
  }
  return treasures;
}

int main()
{
  int RUN_COUNT = 5000;
  srand(time(0));

  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

  for (int i = 0; i < RUN_COUNT; i++)
  {
    printf("##### ITER %d\n", i + 1);

    // init game
    struct gameState G;
    initializeGame(2, k, rand(), &G); // init with random seed
    int player = whoseTurn(&G);

    // have a random number of cards left in the deck
    for (int j = rand() % 6; j < 5; j++)
      drawCard(player, &G);

    printf("deckCount: %d\n", G.deckCount[player]);

    int before = get_treasure_count(player, &G);  // count treasures before and after
    printf("treasures before: %d\n", before);
    cardeffect_adventurer(&G);
    int after = get_treasure_count(player, &G);
    printf("treasures after: %d\n", after);

    assert_true("treasures added == 2", (after - before) == 2);

    printf("\n");
  }
  return 0;
}
