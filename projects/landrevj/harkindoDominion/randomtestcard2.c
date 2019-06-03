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
    if (G->hand[whoseTurn(G)][i] == card)
    {
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

  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, steward};

  for (int i = 0; i < RUN_COUNT; i++)
  {
    printf("##### ITER %d\n", i + 1);

    // init game
    struct gameState G;
    initializeGame(2, k, rand(), &G); // init with random seed
    int player = whoseTurn(&G);

    // discard a random number of cards from the hand
    for (int j = rand() % 6; j < 5; j++)
      discardCard(0, player, &G, 0);

    // add the smithy card to the hand and find where it is
    gainCard(steward, &G, 2, player);
    int cardpos_before = find_card_in_hand(steward, &G);
    printf("cardpos_before: %d\n", cardpos_before);

    if (cardpos_before >= 0) // if the smithy card is in hand
    {
      int choice1 = rand() % 3;

      if (choice1 == 1)
      {
        printf("choice: +2 cards\n");
        int before_draw = G.handCount[player];
        cardeffect_steward(1, -1, -1, &G, cardpos_before);
        int after_draw = G.handCount[player];
        assert_true("cards added == 2", (after_draw - before_draw) == 1); // we draw two then discard the played card, so a difference of 1
      }
      else if (choice1 == 2)
      {
        printf("choice: +2 coins\n");
        int before_coins = G.coins;
        cardeffect_steward(2, -1, -1, &G, cardpos_before);
        int after_coins = G.coins;
        assert_true("coins added == 2", (after_coins - before_coins) == 2);
      }
      else
      {
        printf("choice: trash two cards\n");
        if (numHandCards(&G) >= 2)
        {
          int choice2 = -1, choice3 = -1, do_choice3 = 0; // pick two random cards from the deck which arent the steward card
          while(choice2 == -1 || choice3 == -1)
          {
            int temp = rand() % G.handCount[player];
            if (temp != cardpos_before)
            {
              if (!do_choice3)
              {
                choice2 = temp;
                do_choice3 = 1;
              }
              else choice3 = temp;
            }
          }

          int before_discard = G.handCount[player];
          cardeffect_steward(0, choice2, choice3, &G, cardpos_before);
          int after_discard = G.handCount[player];
          assert_true("cards discarded == 2", (after_discard - before_discard) == -3); // we discard two plus the played card so -3
        }
        else
        {
          printf("had less than two cards in hand; skipped\n\n");
          continue;
        }
      int cardpos_after = find_card_in_hand(steward, &G);
      assert_true("steward was removed", cardpos_after == -1); // check to see if the smithy card was removed from the deck
      }
    }
    else printf("steward wasn't in hand\n");
    printf("\n");
  }
  return 0;
}
