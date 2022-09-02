#ifndef PLAYER_H
#define PLAYER_H

#include <stdlib.h>
#include <stdio.h>
#include "card.h"
/*
 * Structure: player
 * -----------------
 *  Each player holds some number of cards in their hand
 *  Each player can have at most 7 "books" before winning 
 */
struct player {
  struct hand* card_list;
  char book[7];
  size_t hand_size;
};

/*
 * Instance Variables: user, computer
 * ----------------------------------
 *
 *  We only support 2 users: a human and a computer
 */
struct player user;

struct player computer;

int add_card(struct player* target, struct card* new_card);

int remove_card(struct player* target, struct card* old_card);

char check_add_book(struct player* target);

int search(struct player* target, char rank1);

int transfer_cards(struct player* src, struct player* dest, char rank);

int game_over(struct player* target);

int reset_player(struct player* target);

char computer_play(struct player* target);

char user_play(struct player* target);

int print_player_hand(struct player* target);

int print_book(struct player* target);

int num_of_books(struct player* target);

#endif
