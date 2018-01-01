#include "btree.h"


int main(int argc, char *argv[]) {

	if (argc != 3) {

		fprintf(stderr, "Usage: ./djikstra [rows] [columns]\n");
		return -1;

	}

	int rows = strtol(argv[1], NULL, 10), columns = strtol(argv[2], NULL, 10);

	GRID *g = initialize_grid(rows, columns);
	on(g);

	if (g) {

		DISTANCES *d = distances(g->grid[0], rows * columns);

		if (d) {

			struct args a;
			a.djikstra = 1;
			a.djargs.d = d;

			char *str = to_str(g, &a);

			if (str) {

				printf("%s\n", str);
				free(str);
			}

			free(d);

		} else {

			fprintf(stderr, "Couldn't allocate memory.\n");
		}

		dealloc_grid(g);


	} else {

		fprintf(stderr, "Couldn't allocate memory.\n");
		return -1;
	}

	return 0;

}
