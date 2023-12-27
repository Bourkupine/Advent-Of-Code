#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../aoc_helpers.h"

#define AOC_HAND_SIZE 5
#define AOC_CARD_AMOUNT 13


enum order {
    AOC_HIGH = 1,	// 1
    AOC_ONE,		// 2
    AOC_TWO,		// 3
    AOC_THREE,		// 4
    AOC_FULL,		// 5
    AOC_FOUR,		// 6
    AOC_FIVE,		// 7
};

typedef struct card {
	char c;
	int val;
} aoc_card;

aoc_card card_list[AOC_CARD_AMOUNT] = {
	{'2', 0},
	{'3', 1},
	{'4', 2},
	{'5', 3},
	{'6', 4},
	{'7', 5},
	{'8', 6},
	{'9', 7},
	{'T', 8},
	{'J', 9},
	{'Q', 10},
	{'K', 11},
	{'A', 12},
};

typedef struct hand {
    char cards[AOC_HAND_SIZE];
    int bid;
    int strength;
} aoc_hand;

/* Function to get the strength of a hand
 * @return enum order
 */
int
get_strength(char *cards)
{
	int matches[2] = {0};
	int idx = 0;
	/* Loop through overall card list to get dupes */
	for (int i = 0; i < AOC_CARD_AMOUNT; i++) {
		matches[idx] = 0;
		for (int j = 0; j < AOC_HAND_SIZE; j++) {
			//printf("%c | %c\n", card_list[i].c, cards[j]);
			if (card_list[i].c == cards[j]) {
				//printf("match\n");
				matches[idx]++;
			}
		}
		if (matches[idx] > 1 && idx < 2) {idx++;}
	}

	switch (matches[0]) {
		case 5: return AOC_FIVE;
		case 4: return AOC_FOUR;
		case 3: if (matches[1] == 2) return AOC_FULL;
				else return AOC_THREE;
		case 2: if (matches[1] == 3) return AOC_FULL;
				else if (matches[1] == 2) return AOC_TWO;
				else return AOC_ONE;
		default: return AOC_HIGH; 
	};
}

void
swap_hands(aoc_hand *a, aoc_hand *b)
{
	aoc_hand temp = *a;
	*a = *b;
	*b = temp;
}

int
get_card_val(char card)
{
	for (int i = 0; i < AOC_CARD_AMOUNT; i++) {
		if (card == card_list[i].c)
			return card_list[i].val;
	}
}

/* func to compare cards
 *
 * @return
 *   0: b is stronger
 *   1: a is stronger
*/
int
comp_cards(char* card_a, char* card_b)
{
	for (int i = 0; i < AOC_HAND_SIZE; i++) {
		int a = get_card_val(card_a[i]);
		int b = get_card_val(card_b[i]);
		//printf("%c, %d | %c, %d\n", card_a[i], a, card_b[i], b);

		if (a > b) {
			return 1;
		}
		if (b > a) {
			return 0;
		}
	}
	return 0;
}

void
sort(aoc_hand *hands, int len)
{
	for (int i = 0; i < len - 1; i++) {
		for (int j = 0; j < len - i - 1; j++) {
			if (hands[j].strength > hands[j + 1].strength) {
				swap_hands(&hands[j], &hands[j + 1]);
			}
			else if (hands[j].strength == hands[j + 1].strength) {
				//printf("comparing: %s | %s\n", hands[j], hands[j+1]);
				if (comp_cards(hands[j].cards, hands[j + 1].cards)) {
					//printf("swapping\n");
					swap_hands(&hands[j], &hands[j + 1]);
				}
			}
		}
	}

	// for (int i = 0; i < len; i++) {
	// 	printf("Hand: %s | Bid: %d | Strength: %d\n", hands[i].cards, hands[i].bid, hands[i].strength);
	// }
}
/*
Correct Order:
32T3K
KTJJT
KK677
T55J5
QQQJA
*/
int
part01(char **input, int len)
{
	printf("Start\n");
	int tot = 0;

	aoc_hand hands[len];

	/* Parse Hands */
	for (int i = 0; i < len; i++) {
		strncpy(hands[i].cards, input[i], 5);
		hands[i].bid = atoi(input[i]+6);
		hands[i].strength = get_strength(hands[i].cards);
		//printf("Hand: %s | Bid: %d | Strength: %d\n", hands[i].cards, hands[i].bid, hands[i].strength);
	}

	/* Sort Hands */
	sort(hands, len);

	/* Calculate Total */
	for (int i = 0; i < len; i++) {
		tot += hands[i].bid * (i + 1);
	}


	printf("Finished\n");

	return tot;
}

int
part02(char **input, int len)
{
	int tot = 0;

	return tot;
}

int
main(int argc, char **argv){
	if (argc < 1) {
		printf("Error - args\n");
		return 1;
	}

	int len;
	char **arr;
	char *path = (char*)malloc(64 * sizeof(char));
	
	sprintf(path, "C:\\Users\\User\\Documents\\advent-of-code\\inputs\\day%s.txt", argv[1]);

	FILE *file = fopen(path, "r");
	if (file == NULL) {
		printf("Error - opening file\n");
		return 1;
	}

	len = file_parser(file, &arr);
	if (len == -1) {
		printf("Error - file parser func\n");
		return 1;
	}

	/* Call parts */
	int p1 = part01(arr, len);
	int p2 = part02(arr, len);
	printf("\nPart 1: %d\n", p1);
	printf("Part 2: %ld\n", p2);

	fclose(file);
	free_arr(arr, len);

	return 0;
}
