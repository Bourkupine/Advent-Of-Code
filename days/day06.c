#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdlib.h>

#include "../aoc_helpers.h"


typedef struct {
	int time;
	int distance;
} aoc_race;

uint64_t
power(int exp)
{
	uint64_t tot = 1;
	while (exp > 0) {
		tot *= 10;
		exp--;
	}
	return tot;
}

int
get_race_amount(char **input)
{
	int race_amount = 0;
	char *pt = input[0];
	do {
		while (!isdigit(*pt)) pt++;
		race_amount++;
		while (isdigit(*pt)) pt++;
	} while (*pt != '\0');
	return race_amount;
}

uint64_t
part01(char **input, int len)
{
	uint64_t tot = 0;
	int race_amount = get_race_amount(input);

	/* Parse inputs */
	aoc_race races[race_amount];
	for (int i = 0; i < len; i++) {
		char *pt = input[i];
		int count = 0;
		for (int j = 0; j < race_amount; j++) {
			while (!isdigit(*pt))
				pt++;
			int n = atoi(pt);
			switch (i) {
				case 0: races[count].time = n;
				case 1: races[count].distance = n;
			}
			while (isdigit(*pt))
				pt++;
			count++;
		}
	}

	int results[race_amount];
	/* Do calculations */
	for (int i = 0; i < race_amount; i++) {
		int count = 0;
		for (int j = 0; j < races[i].time; j++) {
			count += ((races[i].time - j) * j) > races[i].distance;
		}
		results[i] = count;
	}

	/* Calculate total */
	tot = results[0];
	for (int i = 1; i < race_amount; i++) {
		tot *= results[i];
	}
	return tot;
}

uint64_t
part02(char **input, int len)
{
	uint64_t tot = 0;
	int race_amount = get_race_amount(input);

	/* Parse inputs Part 2 */
	uint64_t time = 0;
	uint64_t dist = 0;
	char *pt = input[0];

	for (int row = 0; row < len; row++) {
		int counter = 0;
		pt = input[row];
		do { pt++; } while (*pt != '\0');
		for (int i = 0; i < race_amount;) {
			while (!isdigit(*pt)) pt--;
			int n = *pt-- - '0';
			switch (row) {
			case 0:
				time += n * power(counter);
				break;
			case 1:
				dist += n * power(counter);
				break;
			}
			counter++;
			if (*pt == ' ') i++;
		}
	}

	/* Do calculations */
	for (int j = 0; j < time; j++) {
		tot += ((time - j) * j) > dist;
	}

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
	printf("Part 2: %lld\n", p2);

	fclose(file);
	free_arr(arr, len);

	return 0;
}