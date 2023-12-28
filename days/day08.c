#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../aoc_helpers.h"

#define AOC_INSTRUCTIONS 0
#define AOC_NODES 2
#define AOC_NODE_LEN 3
#define AOC_NODE_2 7
#define AOC_NODE_3 12

typedef struct node {
	char *name;
	char *left_name;
	char *right_name;
} aoc_node;

/* Returns the index of a node */
int
find_node(aoc_node *nodes, int node_amount, char* node_name)
{
	for (int i = 0; i < node_amount; i++) {
		if (!strcmp(nodes[i].name, node_name)) return i;
	}
}

int
part01(char **input, int len)
{
	int tot = 0;
	int node_amount = len - AOC_NODES;

	/* Get Instruction Length */
	int instr_len = strlen(input[AOC_INSTRUCTIONS]);
	
	/* Parse Instructions */
	int instr[instr_len];
	char *pt = input[AOC_INSTRUCTIONS];
	for (int i = 0; *pt != '\0'; i++, pt++) {
		instr[i] = !!(*pt == 'R');
	}

	/* Parse Nodes */
	aoc_node nodes[node_amount];
	for (int pos = AOC_NODES, i = 0; pos < len; i++, pos++) {
		nodes[i].name = strndup(input[pos], 3);
		nodes[i].left_name = strndup(input[pos]+AOC_NODE_2, 3);
		nodes[i].right_name = strndup(input[pos]+AOC_NODE_3, 3);
	}

	int i = find_node(nodes, node_amount, "AAA");
	while(strcmp(nodes[i].name, "ZZZ")) {
		if(instr[tot % instr_len] == 0)
			i = find_node(nodes, node_amount, nodes[i].left_name);
		else
			i = find_node(nodes, node_amount, nodes[i].right_name);
		tot++;
	}

	return tot;
}

uint64_t
calc_gcd(uint64_t a, uint64_t b) {
	while(1) {
		if(a >= b) a -= b;
		else if(a < b) b -= a;
		if(a == 0) return b;
	}
}

uint64_t
calc_lcm(uint64_t a, uint64_t b) {
	return (a * b)/ calc_gcd(a,b);
}

uint64_t
part02(char **input, int len)
{
	int node_amount = len - AOC_NODES;
	int names_with_a = 0;

	/* Get Instruction Length */
	int instr_len = strlen(input[AOC_INSTRUCTIONS]);
	
	/* Parse Instructions */
	int instr[instr_len];
	char *pt = input[AOC_INSTRUCTIONS];
	for (int i = 0; *pt != '\0'; i++, pt++) {
		instr[i] = !!(*pt == 'R');
	}

	/* Parse Nodes */
	aoc_node nodes[node_amount];
	for (int pos = AOC_NODES, i = 0; pos < len; i++, pos++) {
		nodes[i].name = strndup(input[pos], 3);
		nodes[i].left_name = strndup(input[pos]+AOC_NODE_2, 3);
		nodes[i].right_name = strndup(input[pos]+AOC_NODE_3, 3);
		if (nodes[i].name[2] == 'A') names_with_a++;
	}

	/* Get Starting Nodes */
	aoc_node starting_nodes[names_with_a];
	for (int i = 0, count = 0; i < node_amount; i++) {
		if (nodes[i].name[2] == 'A')
			starting_nodes[count++] = nodes[i];
	}
	uint64_t temp[names_with_a];

	/* Calc A->Z */
	for (int node = 0; node < names_with_a; node++) {
		int count = 0;
		int i = find_node(nodes, node_amount, starting_nodes[node].name);

		while (nodes[i].name[2] != 'Z') {
			if(instr[count % instr_len] == 0)
				i = find_node(nodes, node_amount, nodes[i].left_name);
			else
				i = find_node(nodes, node_amount, nodes[i].right_name);
			count++;
		}
		temp[node] = count;
	}

	/* Calc LCM = (num1 * num2) / GCD */
	for (int i = 0; i < names_with_a; i++) {
		temp[0] = calc_lcm(temp[0], temp[i]); //we can use temp[0] intead of a total to save
	}

	return temp[0];
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
	printf("\nPart 1: %d\n", p1);
	uint64_t p2 = part02(arr, len);
	printf("Part 2: %lld\n", p2);

	fclose(file);
	free_arr(arr, len);

	return 0;
}