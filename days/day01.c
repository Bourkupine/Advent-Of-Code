#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"
#include "string.h"
#include "stdbool.h"

#include "../aoc_helpers.h"


int
part01(char **arr, int len)
{
	int tot = 0;
	for (int i = 0; i < len; i++) {
		uint8_t num1 = 10;
		uint8_t num2;
		char *end = arr[i];

		do {
			if (isdigit(*end)) {
				if (num1 == 10)
					num1 = *end - '0';
				num2 = *end - '0';
			}
			end++;
		} while (*end != '\0');
		tot += (num1 * 10) + num2;
	}
	return tot;
}

int
part02(char **arr, int len)
{
	/* Use empty string at index 0 so we can get the strings number using index (i.e "one" becomes arr[1])*/
	char *arr2[] = {"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

	int tot = 0;
	for (int i = 0; i < len; i++) {
		uint8_t num1 = 10;
		uint8_t num2;
		char *p1 = arr[i];

		do {
			int n = 10;
			for (int j = 1; j < 10; j++) {
				if (isdigit(*p1)) {
					n = (*p1 - '0');
					break;
				}
				int cmp = strncmp(p1, arr2[j], strlen(arr2[j]));

				if (cmp == 0) {
					n = j;
					break;
				}
			}
			if (n != 10) {
				if (num1 == 10)
					num1 = n;
				num2 = n;
			}
			p1++;
		} while (*p1 != '\0');
		tot += (num1 * 10) + num2;
	}
	return tot;
}

int
main(int argc, char **argv)
{
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
	printf("Part 1: %ld\n", p1);
	printf("Part 2: %ld\n", p2);

	fclose(file);
	free_arr(arr, len);

	return 0;
}
