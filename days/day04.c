#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "../aoc_helpers.h"


int
part01(char **input, int len)
{
	int tot = 0;
	uint8_t prefix = 0;

	/* Get amount of nums in first section */
	while (input[0][prefix++] != ':');

	for (int i = 0; i < len; i++) {
		int card_pts = 0;
		uint8_t nums_arr[10];
		uint8_t count = 0;

		char *pt = input[i] + prefix;

		/* Get first section of nums */
		do {
			if (isdigit(*pt)) {
				int n = atoi(pt);
				nums_arr[count++] = n;
				pt++;
			}
		} while (*pt++ != '|');

		/* Get second section of nums */
		do {
			if (isdigit(*pt)) {
				int n = atoi(pt);
				for (int j = 0; j < count; j++) {
					if (n == nums_arr[j]) {
						card_pts++;
					}
				}
				pt++;
			}
		} while (*pt++ != '\0');

		tot += (!!card_pts << card_pts-1);
	}
	return tot;
}

int
part02(char **input, int len)
{
	int tot = 0;
	uint8_t prefix = 0;
	int card_amounts[len];
	for (int i = 0; i < len; i++)
		card_amounts[i] = 1;

	/* Get amount of nums in first section */
	while (input[0][prefix++] != ':');

	for (int i = 0; i < len; i++) {
		int card_pts = 0;
		uint8_t nums_arr[10];
		uint8_t count = 0;

		char *pt = input[i] + prefix;

		/* Get first section of nums */
		do {
			if (isdigit(*pt)) {
				int n = atoi(pt);
				nums_arr[count++] = n;
				pt++;
			}
		} while (*pt++ != '|');

		/* Get second section of nums */
		do {
			if (isdigit(*pt)) {
				int n = atoi(pt);
				for (int j = 0; j < count; j++) {
					if (n == nums_arr[j]) {
						card_pts++;
					}
				}
				pt++;
			}
		} while (*pt++ != '\0');

		/* Add up cards */
		for (int j = 1; j < card_pts+1; j++)
			card_amounts[i + j] += card_amounts[i];
	}

	for (int i = 0; i < len; i++)
		tot += card_amounts[i];

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
	printf("Part 1: %d\n", p1);
	printf("Part 2: %ld\n", p2);

	fclose(file);
	free_arr(arr, len);

	return 0;
}