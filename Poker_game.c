 #include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <time.h>

#define HAND_SIZE 2

#define COMMUNITY_CARDS 5

#define DECK_SIZE 52

#define RANK_SIZE 13

#define SUIT_SIZE 4

typedef struct {

    int rank;

    int suit;

} Card;

void print_card(Card c) {

    char ranks[RANK_SIZE] = "23456789TJQKA";

    char suits[SUIT_SIZE] = "cdhs";

    printf("%c%c ", ranks[c.rank], suits[c.suit]);

}

void print_hand(Card hand[], int size) {

    int i;

    for (i = 0; i < size; i++) {

        print_card(hand[i]);

    }

    printf("\n");

}

void print_board(Card board[], int size) {

    int i;

    for (i = 0; i < size; i++) {

        print_card(board[i]);

    }

    printf("\n");

}

void shuffle(Card deck[], int size) {

    int i, j;

    Card temp;

    srand(time(NULL));

    for (i = size - 1; i > 0; i--) {

        j = rand() % (i + 1);

        temp = deck[i];

        deck[i] = deck[j];

        deck[j] = temp;

    }

}

void init_deck(Card deck[]) {

    int i, j, k;

    k = 0;

    for (i = 0; i < SUIT_SIZE; i++) {

        for (j = 0; j < RANK_SIZE; j++) {

            deck[k].rank = j;

            deck[k].suit = i;

            k++;

        }

    }

}

void deal(Card deck[], Card hands[][HAND_SIZE], int num_players, int *index) {

    int i, j;

    for (j = 0; j < HAND_SIZE; j++) {

        for (i = 0; i < num_players; i++) {

            hands[i][j] = deck[*index];

            (*index)++;

        }

    }

}

void flop(Card deck[], Card board[], int *index) {

    int i;

    (*index)++;

    for (i = 0; i < COMMUNITY_CARDS; i++) {

        board[i] = deck[*index];

        (*index)++;

    }

}

int rank_hand(Card hand[], Card board[], int size) {

    /* Implement your hand ranking algorithm here */

    /* For now, return a random integer between 0 and 9 */

    return rand() % 10;

}

int compare_hands(Card hand1[], Card hand2[], Card board[], int size) {

    int rank1, rank2;

    rank1 = rank_hand(hand1, board, size);

    rank2 = rank_hand(hand2, board, size);

    if (rank1 > rank2) {

        return 1;

    } else if (rank2 > rank1) {

        return 2;

    } else {

        int i;

        /* Implement tiebreaker algorithm here */

        for (i = 0; i < HAND_SIZE + COMMUNITY_CARDS; i++) {

            if (hand1[i].rank > hand2[i].rank) {

                return 1;

            } else if (hand2[i].rank > hand1[i].rank) {

                return 2;

            }

        }

        return 0;

    }

}

int main() {

    Card deck[DECK_SIZE], hands[2][HAND_SIZE], board[COMMUNITY_CARDS];

int index = 0, winner;

init_deck(deck);

shuffle(deck, DECK_SIZE);

deal(deck, hands, 2, &index);

flop(deck, board, &index);

printf("Flop: ");

print_board(board, 3);

flop(deck, board, &index);

printf("Turn: ");

print_board(board, 4);

flop(deck, board, &index);

printf("River: ");

print_board(board, 5);

printf("Player 1 Hand: ");

print_hand(hands[0], HAND_SIZE);

printf("Player 2 Hand: ");

print_hand(hands[1], HAND_SIZE);

winner = compare_hands(hands[0], hands[1], board, COMMUNITY_CARDS);

if (winner == 0) {

    printf("Tie game!\n");

} else {

    printf("Player %d wins!\n", winner);

}

return 0;}

