#include "sidewinder.h"
#include "distances.h"

void dealloc(DISTANCES *d, int size) {

	int i = 0;

	for (i = 0; i < size; i++) {

		if (d->dist[i]) free(d->dist[i]);
	}

	free(d->dist);
	free(d);

}

int main(int argc, char *argv[]) {

	if (argc != 3) {

		fprintf(stderr, "Usage: ./longest_path [rows] [columns]\n");
		return -1;
	}

	int rows = strtol(argv[1], NULL, 10), columns = strtol(argv[2], NULL, 10);

	GRID *g = initialize_grid(rows, columns);
	
	if (!g) return -1;

	sidewinder_on(g); /* I neglect sidewinder too much :p */

	CELL *start = g->grid[0];
	
	DISTANCES *d = distances(start, rows * columns);
	if (!d) {

		dealloc_grid(g);
		return -1;
	}
	
	CELL_DISTANCE *new_start = max(d, rows * columns);
	if (!new_start) {

		dealloc_grid(g);
		dealloc(d, rows * columns);
		return -1;
	}

	DISTANCES *new_distances = distances(new_start->cell, rows * columns);
	if (!new_distances) {

		dealloc_grid(g);
		dealloc(d, rows * columns);
		free(new_start);
		return -1;
	}

	CELL_DISTANCE *goal = max(new_distances, rows * columns);
	if (!goal) {

		dealloc_grid(g);
		dealloc(d, rows * columns);
		free(new_start);
		dealloc(new_distances, rows * columns);
	}

	DISTANCES *dist = path_to(new_distances, goal->cell, rows * columns);	
	if (!dist) {

		dealloc_grid(g);
		dealloc(d, rows * columns);
		free(new_start);
		dealloc(new_distances, rows * columns);
		free(goal);
		dealloc(dist, rows * columns);
	}

	struct args a;

	a.djikstra = 1;
	a.djargs.d = dist;

	char *str = to_str(g, &a);		

	if (str) {

		printf("%s\n", str);
		free(str);

	}

	dealloc_grid(g);
	free(new_start);
	dealloc(new_distances, rows * columns);
	dealloc(d, rows * columns);
	free(goal);
	dealloc(dist, rows * columns);

	return 0;


}
