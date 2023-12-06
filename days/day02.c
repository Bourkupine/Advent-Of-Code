#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"
#include "string.h"

#include "../aoc_helpers.h"

int
part01(char **arr, int len)
{
	int tot = 0;
	const char *arr2[] = {"red", "green", "blue"};

	for (int i = 0; i < len; i++) {
		char *pt = arr[i];
		while (*pt != ':') pt++;

		do {
			int n = 0;

			while (!isalnum(*pt)) pt++;
			n = strtod(pt, &pt); /* Get num */
			while (!isalnum(*pt)) pt++;

			/* Get colour */
			for (int j = 0; j < 3; j++) {
				if (strncmp(pt, arr2[j], strlen(arr2[j])) == 0) {
					if (n > 12+j)
						goto end; /*Skip to next line*/
				}
			}
			pt++;
		} while (*pt != '\0');
		tot += i + 1;
	end:
	}
	return tot;
}

int
part02(char **arr, int len)
{
	int tot = 0;
	const char *arr2[] = {"red", "green", "blue"};

	for (int i = 0; i < len; i++) {
		int red = 0, green = 0, blue = 0;
		char *pt = arr[i];
		while (*pt != ':') pt++;

		do {
			int n = 0;

			while (!isalnum(*pt)) pt++;
			n = strtod(pt, &pt); /* Get num */
			while (!isalnum(*pt)) pt++;

			/* Get colour & check values of red/green/blue*/
			for (int j = 0; j < 3; j++) {
				if (strncmp(pt, arr2[j], strlen(arr2[j])) == 0) {
					switch (j) {
					case 0: red = n > red ? n : red; break;
					case 1: green = n > green ? n : green; break;
					case 2: blue = n > blue ? n : blue; break;
					}
				}
			}
			pt++;
		} while (*pt != '\0');
		tot += (red * green * blue);
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
	char *path = (char *)malloc(64 * sizeof(char));

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
