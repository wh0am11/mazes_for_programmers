#include "btree.h"



int main(int argc, char *argv[]) {

	if (argc != 3) {

		fprintf(stderr, "Usage: djikstra2 [rows] [columns]\n");
		return -1;
	}

	srand((unsigned int) time (NULL));

	int rows = strtol(argv[1], NULL, 10), columns = strtol(argv[2], NULL, 10);

	GRID *g = initialize_grid(rows, columns);

	if (!g) return -1;

	on(g);

	DISTANCES *d = distances(g->grid[0], rows * columns);

	if (!d) {

		dealloc_grid(g);
		return -1;
	}

	DISTANCES *d2 = path_to(d, g->grid[rand() % (rows * columns)], rows * columns);

	if (!d2) {

		dealloc_grid(g);
		free(d);
		return -1;
	}

	struct args a;
	
	a.djikstra = 1;
	a.djargs.d = d2;

	char *str = to_str(g, &a);	

	if (str) {

		printf("%s\n", str);
		free(str);

		a.djargs.d = d;

		str = to_str(g, &a);
		printf("%s\n", str);
		free(str);
	}

	dealloc_grid(g);
	free(d);
	free(d2);

	return 0;

}
