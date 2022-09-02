#include <stdio.h>
#include "deck.h"
#include "player.h"
#include <time.h>

int main()
{
	// initialize deck and players
	srand(time(0));
	printf("Shuffling deck...\n");
	shuffle();

	//Player 1
	struct player player1;
	for (int i=0; i<7; i++){player1.book[i] = '0';};
	deal_player_cards(&player1);
	//Player 2
	struct player player2;
	for (int i=0; i<7; i++){player2.book[i] = '0';};
	deal_player_cards(&player2);

	//gameover outputs 1 when over
	int game = 0;
	char pasks;
	char play_again[2] ={ 'Y','0'};
	while(play_again[0] == 'Y'){
		while(game == 0){
			// print hand and book
			if (player1.hand_size == 0){add_card(&player1, next_card());}
			if (player2.hand_size == 0){add_card(&player2, next_card());}
			printf("\nPlayer 1's Hand - ");
			print_player_hand(&player1);
			printf("Player 1's Book - ");
			check_add_book(&player1);
			print_book(&player1);
			//printf("Player 2's Hand - ");
			//print_player_hand(&player2);
			printf("Player 2's Book - ");
			check_add_book(&player1);
			print_book(&player2);

			//Player 1's turn
			int searchP2 = 1;
			while (searchP2 == 1){
				printf("Player 1's turn,");
				pasks = user_play(&player1);
				searchP2 =search(&player2, pasks);
				if (pasks == 'T'){pasks = '1';};
				if (searchP2 == 0 && pasks=='1'){printf("  -Player 2 has no 10's\n");}
				else if (searchP2 == 0){printf("  -Player 2 has no %c's\n", pasks);}
				if (searchP2 ==0){
					if (deck_size() > 1){add_card(&player1, next_card());}
					else {printf("There are no more cards in the deck, so the game is over\n");
						game = 1;
						break;}
				}
				else {
					int transfer_return = transfer_cards(&player2, &player1, pasks);
					if (transfer_return == 1){
						if (pasks == '1'){printf("  -Player 2 has 1 10\n");}
						else {printf("  -Player 2 has 1 %c \n", pasks);}
					}
					else{
						if (pasks == '1'){printf("  -Player 2 has %d 10's \n", transfer_return);}
						else {printf("  -Player 2 has %d %c's\n",transfer_return, pasks);}
					}
				}
			};
			//print hand and book
			if (player1.hand_size == 0){add_card(&player1, next_card());}
			if (player2.hand_size == 0){add_card(&player2, next_card());}
			printf("\nPlayer 1's Hand - ");
			print_player_hand(&player1);
			printf("Player 1's Book - ");
			check_add_book(&player1);
			print_book(&player1);
			//printf("Player 2's Hand - ");
			//print_player_hand(&player2);
			printf("Player 2's Book - ");
			check_add_book(&player2);
			print_book(&player2);

			//player 2s turn
			int searchP1 = 1;
			while (searchP1 ==1){
				printf("Player 2's turn,");
				pasks = computer_play(&player2);
				//printf("computer chooses %c \n", pasks);
				searchP1 = search(&player1, pasks);
				printf( " %c\n", pasks);
				if (pasks == 'T'){pasks = '1';}
				if (searchP1 == 0 && pasks == '1'){printf("Player 1 has no 10's\n");}
				else if (searchP1 == 0){printf("  -Player 1 has no %c's\n", pasks);}
				if (searchP1 == 0){
					if (deck_size() > 1) {add_card(&player2, next_card());}
					else {printf("There are no more cards in the deck, so the game is over\n");
						game = 1;
						break;}
					}
				else {
					int transfer_return = transfer_cards(&player1, &player2, pasks);
					if (transfer_return == 1){
						if (pasks == '1'){printf("  -Player 1 has 1 10\n");}
						else {printf("  -Player 1 has 1 %c\n", pasks);}
					}
					else{
						if (pasks == '1'){printf("  -Player 1 has %d 10's \n", transfer_return);}
						else {printf("  -Player 1 has %d %c's\n",transfer_return, pasks);}
					};
				};
			};
			//check if game over
			game = game + game_over(&player1) + game_over(&player2);
		};
		if (num_of_books(&player1) > num_of_books(&player2)){
			printf("Player 1 wins!\n");
		}
		else if (num_of_books(&player1) == num_of_books(&player2)){printf("Both players have the same amount of books, so its a tie!\n");}
		else { printf("Player 2 wins!\n");}
		printf("Do you want to play again [Y/N]: ");
		scanf("%s", play_again);
		if (play_again[0] == 'Y'){
			reset_player(&player1);
			reset_player(&player2);
			shuffle();
			for (int i=0; i<7; i++){player1.book[i] = '0';};
			for (int i=0; i<7; i++){player2.book[i] = '0';};
			deal_player_cards(&player1);
			deal_player_cards(&player2);
		}
		game = 0;
	};
};
