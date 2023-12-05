/* File for helper functions used throughout the challenge */

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "aoc_helpers.h"

#define AOC_MAX_LINE_LENGTH 1024


int
file_parser(FILE *file, char ***arr)
{
	int count = 0;
	char buffer[AOC_MAX_LINE_LENGTH];

	while (fgets(buffer, sizeof(buffer), file) != NULL) {
		count++;
	}

	*arr = (char**)malloc(count * sizeof(char*));
	if (*arr == NULL)
		return -1;

	fseek(file, 0, SEEK_SET);

	for (int i = 0; i < count; i++) {

		if (fgets(buffer, sizeof(buffer), file) == NULL)
			return -1;

		size_t len = strlen(buffer);
		if (len > 0 && buffer[len - 1] == '\n') {
			buffer[len - 1] = '\0';
		}

		(*arr)[i] = strdup(buffer);
		if ((*arr)[i] == NULL)
			return -1;
	}
	return count;
}

void 
free_arr(char **arr, int len)
{
	for (int i = 0; i < len; i++)
		free(arr[i]);
	free(arr);
}
