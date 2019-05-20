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

int find_card_in_hand(int card, struct gameState *G)
{
  printf("hand:");
  for (int i = 0; i < numHandCards(G); i++)
  {
    printf(" %d", G->hand[whoseTurn(G)][i]);
    if (G->hand[whoseTurn(G)][i] == card) {
      printf("\n");
      return i;
    }
  }
  printf("\n");
  return -1;
}

int main()
{
  int RUN_COUNT = 50;
  srand(time(0));

  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

  for (int i = 0; i < RUN_COUNT; i++)
  {
    printf("##### ITER %d\n", i + 1);

    // init game
    struct gameState G;
    initializeGame(2, k, rand(), &G); // init with random seed
    int player = whoseTurn(&G);

    // discard a random number of cards from the hand
    for (int j = rand() % 6; j < 5; j++) discardCard(0, player, &G, 0);

    // add the smithy card to the hand and find where it is
    gainCard(smithy, &G, 2, player);
    int cardpos_before = find_card_in_hand(smithy, &G);
    printf("cardpos_before: %d\n", cardpos_before);

    if (cardpos_before >= 0) // if the smithy card is in hand
    {
      // count the number of cards in hand before and after smithy is played
      int before = G.handCount[player];
      cardeffect_smithy(&G, cardpos_before);
      int after = G.handCount[player];
      int cardpos_after = find_card_in_hand(smithy, &G);

      assert_true("cards added == 3", (after - before) == 2); // we draw three then discard the played card, so a difference of 2
      assert_true("smithy was removed", cardpos_after == -1); // check to see if the smithy card was removed from the deck
    }
    else printf("smithy wasn't in hand\n");
    printf("\n");
  }
  return 0;
}
