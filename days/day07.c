#include <stdio.h>
#include <stdlib.h>

#include "../aoc_helpers.h"

#define AOC_HAND_SIZE 5


typedef enum order {
    AOC_HIGH = 0,
    AOC_ONE = 1,
    AOC_TWO = 2,
    AOC_THREE = 3,
    AOC_FULL = 4,
    AOC_FOUR = 5,
    AOC_FIVE = 6,
} aoc_order;

typedef struct hand {
    int cards[5];
    int bid;
    aoc_order order;
	int highest_card;
} aoc_hand;

int
convert(char c) {
	switch (c) {
		case 'T': return 10;
		case 'J': return 11;
		case 'Q': return 12;
		case 'K': return 13;
		case 'A': return 14;
		default: return c - '0';
	};
}


aoc_order
rank_hand(aoc_hand h) {

	
}

int
part01(char **input, int len)
{
	int tot = 0;

	aoc_hand hands[len];

	/* Parse hands */
	for (int i = 0; i < len; i++) {
		aoc_hand h;
		int highest_card = 0;
		int total_matches = 0;
		char *pt = input[i];

		/* Get Cards */
		for (int j = 0; *pt != ' '; j++) {
			int n = convert(*pt);
			highest_card = n > highest_card ? n : highest_card;
			h.cards[j] = n;
			pt++;
		}
		h.highest_card = highest_card;
		pt++;

		/* Get Number */
		int n = atoi(pt);
		h.bid = n;

		aoc_order o = rank_hand(h);
		h.order = o;

		hands[i] = h;

		/* Print hand info */
		// for (int j = 0; j < AOC_HAND_SIZE; j++) {
		// 	printf("%d, ", h.cards[j]);
		// }
		// printf("\nBid: %d\nHighest: %d\nOrder: %d\n\n", h.bid, h.highest_card, h.order);

	}


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
