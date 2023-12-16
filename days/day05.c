#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "../aoc_helpers.h"

/* returns the amout of seeds */
int
get_seeds_size(char **input)
{
	int seeds_size = 0;
	char *seeds_pt = input[0];
	while (*seeds_pt != '\0') {
		if (*seeds_pt++ == ' ' && isdigit(*seeds_pt)) {
			seeds_size++;
		}
	}
	return seeds_size;
}

/* short func to check if num is in range */
int
is_between(uint64_t num, uint64_t *map) {
	return (num >= map[1]) && (num < (map[1] + map[2]));
}

uint64_t
part01(char **input, int len)
{
	int line = 0;

	int seeds_size = get_seeds_size(input);
	uint64_t seeds_arr[seeds_size];

	/* Get seeds */
	char *pt = input[line++];
	int count = 0;
	do {
		if (*pt++ == ' ' && isdigit(*pt)) {
			uint64_t n = strtod(pt, NULL);
			seeds_arr[count++] = n;
		}
	} while (*pt != '\0');

	int counter = 0;

	/* Put seeds array through the mappings */
	for (int maps = 0; maps < 7; maps++) {

		/* Get pointer to next mapping */
		while (line < len && !isalpha(*input[line])) line++;
		int start = ++line; /* Keep note of start */
		for (int seed = 0; seed < seeds_size; seed++) {
			line = start;
			while (isdigit(*input[line])) {
				pt = input[line];

				/* Get mapping */
				uint64_t mapping[3];
				for (int i = 0; i < 3; i++) {
					mapping[i] = strtoll(pt, &pt, 10);
					if (*pt == '\0') {
						break;
					}
					pt++;
				}

				/* Run checks with seed */
				if (is_between(seeds_arr[seed], mapping)) {
					seeds_arr[seed] = (seeds_arr[seed] - mapping[1] + mapping[0]);
					goto next_seed;
				}
				line++;
				if (line >= len && seed >= seeds_size) goto end; /* Quick check to see if you finish */
				if (line >= len) goto next_seed;
			}
			next_seed:;
		}
	}
	end:
	
	/* Get lowest seed */
	uint64_t lowest = seeds_arr[0];
	for (int i = 1; i < seeds_size; i++) {
		if (seeds_arr[i] < lowest) lowest = seeds_arr[i];
	}

	return lowest;
}

/* Using a brute force-like method for pt 2 */
int
part02(char **input, int len)
{
	int tot = 0;
	int seeds_size = get_seeds_size(input);
	uint64_t seeds_arr[seeds_size];

	/* Get Seeds */
	char *pt = input[0];
	int count = 0;
	do {
		if (*pt++ == ' ' && isdigit(*pt)) {
			uint64_t n = strtod(pt, NULL);
			seeds_arr[count++] = n;
		}
	} while (*pt != '\0');

	int counter = 0;

	for (uint64_t i = 0; i < UINT64_MAX; i++) {
		uint64_t num = i; 
		int row = len-1;
		int bl = 0;
		for (; row > 1; row--) {
			pt = input[row];
			/* Reset bl to 0 after each section */
			if (!isdigit(*pt)) {
				bl = 0;
				continue;
			}
			if (isdigit(*pt) && bl == 0) {
				uint64_t mapping[3];
				for (int j = 0; j < 3; j++) {
					mapping[j] = strtoull(pt, &pt, 10);
					if (*pt == '\0') break;
					pt++;
				}
				if ((num >= mapping[0]) && (num < (mapping[0] + mapping[2]))) {
					uint64_t temp = num - mapping[0] + mapping[1];
					num = temp;
					bl = 1;
				}
			}
		}
		for (int seed = 0; seed < seeds_size; seed+=2) {
			if (num >= seeds_arr[seed] && num < (seeds_arr[seed] + seeds_arr[seed+1])) {
				tot = i;
				goto end;
			}
		}
	}
	end:
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
	uint64_t p1 = part01(arr, len);
	int p2 = part02(arr, len);
	printf("Part 1: %lld\n", p1);
	printf("Part 2: %d\n", p2);

	fclose(file);
	free_arr(arr, len);

	return 0;
}