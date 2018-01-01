#include "btree.h"


int main(int argc, char *argv[]) {

	if (argc != 3) {

		fprintf(stderr, "Usage: ./btree [rows] [columns]\n");
		return -1;
	}

	int rows = strtol(argv[1], NULL, 10);
	int columns = strtol(argv[2], NULL, 10);


	GRID *g = initialize_grid(rows, columns);

	if (g) {

		on(g);

		char *str = to_str(g, NULL);
		int i = 0;

		if (str) {

			printf("%s", str);
			free(str);
		}

		for (i = 0; i < g->rows * g->columns; i++) 
				free(g->grid[i]);

		free(g->grid);
		free(g);

	}

	return 0;

}
