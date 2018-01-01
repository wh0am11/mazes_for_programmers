#include "btree.h"



int main(int argc, char *argv[]) {

	if (argc != 3) {

		fprintf(stderr, "Usage: ./bit_tree [rows] [columns]\n");
		return -1;
	}

	int rows = strtol(argv[1], NULL, 10);
	int columns = strtol(argv[2], NULL, 10);

	int **grid = init_grid(rows, columns), i = 0;

	on(grid, rows, columns);
	char *str = to_str(grid, rows, columns);

	if (str) {

		printf("%s\n", str);
		free(str);
	}

	for (i = 0; i < columns; i++) free(grid[i]);

	free(grid);

	return 0;


}
