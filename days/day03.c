#include "stdio.h"
#include "ctype.h"
#include "string.h"
#include "stdlib.h"
#include "stdbool.h"

#include "../aoc_helpers.h"

typedef struct num {
	int num;
	int x;
	int y;
} gear_num;

typedef struct gear {
	int size;
	gear_num nums[6]; /* 6 as thats the most surrounding nums */
	int x;
	int y;
} gear;

struct gear gears[500];
int gear_size = 0;


void
create_gear(int x, int y, gear_num num) {
	for (int i = 0; i < gear_size; i++) {
		if (gears[i].x == x && gears[i].y == y) {
			for (int j = 0; j < 6; j++) {
				if (gears[i].nums[j].x == num.x && gears[i].nums[j].y == num.y) {
					return;
				}
				gears[i].nums[gears[i].size++] = num;
				return;

			}
		}
		
	}
	gear g = {
		.nums[0] = num,
		.size = 1,
		.x = x,
		.y = y,
	};
	gears[gear_size] = g;
	gear_size++;
}

int
part01(char **input, int len)
{
	int tot = 0;

	char *arr[len + 2];
	char *dots = "............................................................................................................................................";
	arr[0] = dots;
	for (int i = 1; i < len + 1; i++)
		arr[i] = input[i - 1];
	arr[len + 1] = dots;

	for (int i = 0; i < len + 1; i++) {
		char *above = arr[i - 1];
		char *pt = arr[i];
		char *below = arr[i + 1];
		int count = 0;

		do {
			if (isdigit(*pt)) {
				bool symbol = false;
				int n = strtod(pt, NULL);

				/* Check before */
				if (count > 0) {
					if (!(isdigit(*(above - 1))) && *(above - 1) != '.' ||
						!(isdigit(*(pt - 1))) && *(pt - 1) != '.' ||
						!(isdigit(*(below - 1))) && *(below - 1) != '.')
						symbol = true;
				}

				/* Check above/below */
				int temp = n;
				while (temp > 0) {
					if (!(isdigit(*above)) && *above != '.' ||
						!(isdigit(*below)) && *below != '.')
						symbol = true;
					pt++, above++, below++, count++;
					temp /= 10;
				}

				/* Check after */
				if (!(isdigit(*above)) && *above != '.' && *above != '\0' ||
					!(isdigit(*pt)) && *pt != '.' && *pt != '\0' ||
					!(isdigit(*below)) && *below != '.' && *below != '\0')
					symbol = true;
				if (symbol)
					tot += n;
			}
			pt++, above++, below++, count++;
		} while (*pt != '\0');
	}

	return tot;
}

int
part02(char **input, int len)
{
	int tot = 0;

	char *arr[len + 2];
	char *dots = "............................................................................................................................................";
	arr[0] = dots;
	for (int i = 1; i < len + 2; i++)
		arr[i] = input[i - 1];
	arr[len + 1] = dots;

	for (int i = 0; i < len+1; i++) {
		char *above = arr[i-1];
		char *pt = arr[i];
		char *below = arr[i+1];
		int count = 0;

		do {
			if (isdigit(*pt)) {
				int n = strtod(pt, NULL);

				/* Check before */
				if (count > 0) {
					if (*(above - 1) == '*' ) {
						gear_num num = {
							.num = n,
							.x = count,
							.y = i,
						};
						create_gear(count-1, i-1, num);
					}
					if (*(pt - 1) == '*') {
						gear_num num = {
							.num = n,
							.x = count,
							.y = i,
						};
						create_gear(count-1, i, num);
					}
					if (*(below - 1) == '*') {
						gear_num num = {
							.num = n,
							.x = count,
							.y = i,
						};
						create_gear(count-1, i+1, num);
					}
				}

				/* Check above/below */
				int temp = n;
				while (temp > 0) {
					if (*above == '*') {
						gear_num num = {
							.num = n,
							.x = count,
							.y = i,
						};
						create_gear(count, i-1, num);
					}
					if (*below == '*') {
						gear_num num = {
							.num = n,
							.x = count,
							.y = i,
						};
						create_gear(count, i+1, num);
					}
					pt++, above++, below++, count++;
					temp /= 10;
				}

				/* Check after */
				if (*above == '*' ) {
					gear_num num = {
						.num = n,
						.x = count,
						.y = i,
					};
					create_gear(count, i-1, num);
				}
				if (*pt == '*') {
					gear_num num = {
						.num = n,
						.x = count,
						.y = i,
					};
					create_gear(count, i, num);
				}
				if (*below == '*') {
					gear_num num = {
						.num = n,
						.x = count,
						.y = i,
					};
					create_gear(count, i+1, num);
				}
			}
			pt++, below++, above++, count++;
		} while (*pt != '\0');
	}

	for (int i = 0; i < gear_size; i++) {
		if (gears[i].size == 2) {
			tot += (gears[i].nums[0].num * gears[i].nums[1].num);
		}
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
	printf("Part 2: %ld\n", p2);

	fclose(file);
	free_arr(arr, len);

	return 0;
}