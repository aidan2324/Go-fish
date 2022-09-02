#ifndef DECK_H
#define DECK_H

#include <stdlib.h>
#include <stdio.h>
#include "player.h"
#include "card.h"

/*
 * Structure: deck
 * ---------------
 *  An array of 52 cards.
 */
struct deck {
  struct card list[52];
  int top_card;
};

/*
 * Variable: deck_instance
 * -----------------------
 *
 * Go Fish uses a single deck
 */
struct deck deck_instance;

int shuffle();

struct card* next_card();

int deal_player_cards(struct player* target);

size_t deck_size();

#endif
