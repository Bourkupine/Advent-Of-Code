#ifndef _AOC_HELPERS_H_
#define _AOC_HELPERS_H_

#include <stdint.h>


/* Implementation of strndup */
char*
strndup( const char *s1, size_t n);

/* Parse the file into the string array
 * @return length of array
 */
int
file_parser(FILE *file, char ***arr);

/* Free array */
void
free_arr(char **arr, int len);

#endif /* _AOC_HELPERS_H_ */
