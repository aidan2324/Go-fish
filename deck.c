#include <stdlib.h>
#include <stdio.h>
#include "deck.h"

/*
 * Function: shuffle
 * --------------------
 *  Initializes deck_instance and shuffles it.
 *  Resets the deck if a prior game has been played.
 *
 *  returns: 0 if no error, and non-zero on error
 */
int shuffle(){
	deck_instance.top_card=0;
	char card_number[13] = {'2','3','4','5','6','7','8','9','T','J','Q','K','A'};
	char suit[4] = {'D', 'H', 'S', 'C'};
	int list_index = 0;
	for (int i=0; i<4;i++){
		for(int j=0; j<13; j++){
		deck_instance.list[list_index].suit = suit[i];
		if(card_number[j] == 'T'){
			deck_instance.list[list_index].rank[0] = '1';
			deck_instance.list[list_index].rank[1] = '0';
		}
		else{
			deck_instance.list[list_index].rank[0] = card_number[j];
		}
		list_index++;
		};
	};
// -------------------------deck made now shuffle it ------------------------

	int max = 52;
	for(int i=0; i < 1000; i++){
		int random1 = rand() % max;
		int random2 = rand() % max;
		struct card temp = deck_instance.list[random1];
		deck_instance.list[random1] = deck_instance.list[random2];
		deck_instance.list[random2] = temp;
	}
	return 0;
};

struct card* next_card(){
	struct card *topC;
	topC = &deck_instance.list[deck_instance.top_card];
	deck_instance.top_card++;
	return topC;
};
/*
 * Function: deal_player_cards
 * ---------------------------
 *  Deal 7 random cards to the player specified in the function.
 *  Remove the dealt cards from the deck.
 *
 *  target: pointer to the player to be dealt cards
 *
 *  returns: 0 if no error, and non-zero on error
 */
int deal_player_cards(struct player* target){
	target -> hand_size = 0;
	for (int h = 0; h < 7; h++){
		add_card(target,next_card());
	};
	return 0;
}

/*
 * Function: size
 * --------------
 *  Return the number of cards left in the current deck.
 *
 *  returns: number of cards left in the deck.
 */
size_t deck_size( ){
	int size = 52 - deck_instance.top_card;
	return size;
}
