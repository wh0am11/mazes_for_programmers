#include "sidewinder.h"



int main(int argc, char *argv[]) {

	GRID *g = initialize_grid(4, 4);

	if (g) {

		sidewinder_on(g);

		char *str = to_str(g, NULL);
		int i = 0;

		if (str) {

			printf("%s\n", str);
			free(str);
		}

		for (i = 0; i < g->rows * g->columns; i++) {

			free(g->grid[i]);
		}

		free(g->grid);
		free(g);

	}

	return 0;

}
