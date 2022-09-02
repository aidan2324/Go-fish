#include <stdio.h>
#include <stdlib.h>
#include "card.h"
#include "player.h"
/*
 *
 * Function: add_card
 * -------------------
 *  Add a new card to the player's hand.
 *
 *  target: the target player
 *  new_card: pointer to the new card to add
 *
 *  returns: return 0 if no error, non-zero otherwise
 */
int add_card(struct player* target, struct card* new_card){
	// allocate space for new element
	struct hand* temp;
	temp = (struct hand*)malloc(sizeof(struct hand));
	if (temp == NULL){return -1;}
	// initialize new element
	temp -> top = *new_card;
	temp -> next = target -> card_list;
	target -> card_list = temp;
	++(target -> hand_size);
	return 0;
};
/*
 * Function: remove_card
 * ---------------------
 *  Remove a card from the player's hand. 
 *
 *  target: the target player
 *  old_card: pointer to the old card to remove
 *
 *  returns: return 0 if no error, non-zero otherwise
 */
int remove_card(struct player* target, struct card* old_card){
	struct hand* iterator = target -> card_list;
	struct hand* previous = NULL;
	if (iterator == NULL){return 1;}
	while (iterator->top.rank[0] != old_card->rank[0] || iterator->top.suit != old_card->suit){
		//printf(" removing %c\n", (iterator->top).rank[0]);
		previous = iterator;
		iterator = iterator->next;
		if (iterator == NULL){return 1;}
	};
	//item has been found
	if (previous != NULL){
		previous -> next = iterator -> next;}// remove item from list
	else{
		target -> card_list = iterator -> next; //set new front of list
	}
	--(target->hand_size);
	free(iterator);
	return 0;
};

/*
 * Function: check_add_book
 * ------------------------
 *  Check if a player has all 4 cards of the same rank.
 *  If so, remove those cards from the hand, and add the rank to the book.
 *  Returns after finding one matching set of 4, so should be called after adding each a new card.
 *
 *  target: pointer to the player to check
 *
 *  Return: a char that indicates the book that was added; return 0 if no book added.
 */
char check_add_book(struct player* target){
	struct hand* iterator = target -> card_list;
	if (iterator == NULL){return 0;}
	char numbers[13] = {'2','3','4','5','6','7','8','9','T','J','Q','K','A'};
	int num_of_rank[13] = {0};
	char suits[4] = {'D', 'C', 'H', 'S'};
	//iterate through each card in the hand
	for(int h=0; h< (target->hand_size); h++){
		if (iterator == NULL){return 0;}
		//printf("hand is %c \n",(iterator->top).rank[0] 
		for (int i=0; i<13; i++){
	// count how many times each card is in the hand
			if (numbers[i] == 'T'){
				if ((iterator->top).rank[0]  == '1' && (iterator->top).rank[1]== '0'){
					++num_of_rank[i];
				}
			}
			else{
				if ((iterator->top).rank[0] == numbers[i]){
					++num_of_rank[i];
					//printf("  num of rank %d", num_of_rank[i]);
				}
			};
	// if there is four of any rank if a hand remove the four cards
			if(num_of_rank[i] == 4){
				struct card booked_card;
				//booked_card = (struct card)malloc(sizeof(struct card));
	// create a card and use remove card function for each suit of the rank
				if (numbers[i] == 'T'){
					booked_card.rank[0] = '1';
					booked_card.rank[1] = '0';}
				else{booked_card.rank[0] = numbers[i];};
				for (int j=0; j<4; j++){
					booked_card.suit = suits[j];
					 remove_card(target, &booked_card);
				};
	// add what rank cards it was to the book
				for (int k=0; k<7; k++){
					if ( target->book[k] == '0'){
						target->book[k] = numbers[i];
						return numbers[i];
					};
				};
				//free(booked_card);
			};
		};
		iterator = iterator->next;
	};
	return 0;
};
/*
 * Function: search
 * ----------------
 *  Search a player's hand for a requested rank.
 *
 *  rank: the rank to search for
 *  target: the player (and their hand) to search
 *
 *  Return: If the player has a card of that rank, return 1, else return 0
 */
int search(struct player* target, char rank1){
	struct hand* iterator = target -> card_list;
	if (iterator == NULL){return 0;}
	for (int h=0; h < (target->hand_size);h++){
		if ((iterator->top).rank[0] != rank1){
			iterator = iterator->next;
			if (iterator == NULL){return 0;}
		};
		if ((iterator->top).rank[0] == rank1){return 1;}
	};
	return 0;
};

/*
 * Function: transfer_cards
 * ------------------------
 *   Transfer cards of a given rank from the source player's
 *   hand to the destination player's hand. Remove transferred
 *   cards from the source player's hand. Add transferred cards
 *   to the destination player's hand.
 *
 *   src: a pointer to the source player
 *   dest: a pointer to the destination player
 *   rank: the rank to transfer
 *
 *   Return: 0 if no cards found/transferred, <0 if error, otherwise
 *   return value indicates number of cards transferred
 */
int transfer_cards(struct player* src, struct player* dest, char rank){
	struct hand* iterator = src -> card_list;
	struct hand* next = NULL;
	int num_cards_transfered = 0;
	if (iterator == NULL){return -1;}
	// itterate through all cards in the sources hand
	int size = src->hand_size;
	for(int h=0; h < (size);h++){
		if(iterator == NULL){return num_cards_transfered;}
		//printf("ra  %c %c %d %d\n",rank, (iterator->top).rank[0],h, src->hand_size);
		if ((iterator->top).rank[0] == rank){
			//card found
			//printf("rank found %c %c \n",rank, (iterator->top).rank[0]);
			next = iterator->next;
			struct card transfer_card = iterator->top;
			remove_card(src, &transfer_card);
			add_card(dest, &transfer_card);
			++num_cards_transfered;
			iterator = next;
		}
		else {
			iterator = iterator->next;
		}
	};
	return num_cards_transfered;
};

/*
 * Function: game_over
 * -------------------
 *   Boolean function to check if a player has 7 books yet
 *   and the game is over
 *
 *   target: the player to check
 *
 *   Return: 1 if game is over, 0 if game is not over
 */
int game_over(struct player* target){
	int books = 0;
	for (int i=0; i<7; i++){
		if (target->book[i] != '0'){
			++books;
		}
	}
	if (books == 7){return 1;}
	else {return 0;}
};

/*
 * Function: reset_player
 * ----------------------
 *
 *   Reset player by free'ing any memory of cards remaining in hand,
 *   and re-initializes the book.  Used when playing a new game.
 *
 *   target: player to reset
 *
 *   Return: 0 if no error, and non-zero on error.
 */
int reset_player(struct player* target){
	for (int i=0; i<7; i++){
		target->book[i] = '0';
	}
	struct hand* next = NULL;
	struct hand* iterator = target -> card_list;
	for(int h=0; h< (target->hand_size); h++){
		if (iterator == NULL){return 1;}
		next = iterator->next;
		remove_card(target, &(iterator->top));
		iterator = next;
	}
	return 0;
}

/*
 * Function: computer_play
 * -----------------------
 *
 *   Select a rank randomly to play this turn. The player must have at least
 *   one card of the selected rank in their hand.
 *
 *   target: the player's hand to select from
 *
 *   Rank: return a valid selected rank
 */
char computer_play(struct player* target){
	struct hand* iterator = target -> card_list;
	// random index of card from linked list
	int max = target->hand_size;
	int random = rand() % max;
	for (int i =0; i<random; i++){
		iterator = iterator -> next;
	}
	return *(iterator->top).rank;
};

/* \
 * Function: user_play
 * -------------------
 *
 *   Read standard input to get rank user wishes to play.  Must perform error
 *   checking to make sure at least one card in the player's hand is of the
 *   requested rank.  If not, print out "Error - must have at least one card from rank to play"
 *   and then re-prompt the user.
 *
 *   target: the player's hand to check
 *
 *   returns: return a valid selected rank
 */

char user_play(struct player* target){
	// malloc array of size 3 to return  (2 for '1' and '0', one for '\0')
	while(1==1){
		char rank[3];
		printf( " enter a Rank: " );
		scanf( "%s", rank);
		char rank2 = rank[1];
		char rank1 = rank[0];
		int search_return = search(target, rank1);
		if (search_return == 1){
			if (rank1=='1'&& rank2 =='0'){
				return '1';}
			return rank1;}
		else {printf("Error - must have at least one card from rank to play \n");}
	};
};

int print_player_hand(struct player* target){
	struct hand* iterator = target -> card_list;
	//printf(" PLAYER HAND SIZE = %d", target->hand_size
	for(int h=0;h < (target->hand_size);h++){
		if ((iterator->top).rank[0] == '1'){
			printf("10%c ", (iterator->top).suit);
		}
		else {printf("%c%c ", (iterator->top).rank[0], (iterator->top).suit);}
		iterator = iterator->next;
	}
	printf("\n");
	return 0;
};

int print_book(struct player* target){
	for(int i=0; i<7;i++){
		if ((*target).book[i] != '0'){
			printf("%c ", (*target).book[i]);
		}
	}
	printf("\n");
	return 0;
};

int num_of_books(struct player* target){
	int num=0;
	for(int i=0; i<7; i++){
		if ((*target).book[i] != '0'){
			num++;}
	}
	return num;
};

