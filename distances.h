#ifndef __distances__
#define __distances__

#include "cell.h"

typedef struct cell_list {

	CELL *cell;
	int distance;

} CELL_DISTANCE;

typedef struct distances {

	CELL *root;
	CELL_DISTANCE **dist;

} DISTANCES;

DISTANCES *init_distance(CELL *root, int size) {

	DISTANCES *d = malloc(sizeof(DISTANCES));
	check(d, "Couldn't allocate memory");

	d->root = root;
	d->dist = calloc(size, sizeof(CELL_DISTANCE));
	check(d->dist, "Couldn't allocate memory");

	int i = 0;

	for (i = 0; i < size; i++) {

		d->dist[i] = malloc(sizeof(CELL_DISTANCE));
		check(d->dist[i], "Couldn't allocate memory");

		d->dist[i]->cell = NULL;
		d->dist[i]->distance = -1;
	}

	d->dist[0]->cell = root;
	d->dist[0]->distance = 0;

	return d;

error:
	if (d) free(d);

	if (d->dist) {

		for (i = 0; d->dist[i] != NULL; i++) 
					free(d->dist[i]);
		free(d->dist);
	}

	return NULL;

}

int get_distance(DISTANCES *d, CELL *c, int size) {


	int i = 0, distance = -1;

	for (i = 0; i < size; i++) {

		if (cmp_cell(d->dist[i]->cell, c)) {

			distance = d->dist[i]->distance;
			break;
		}

	}

	return distance;
}

void set_distance(DISTANCES *d, CELL *c, int distance, int size) {

	int i = 0;

	for (i = 0; i < size; i++) {

		if (d->dist[i]->cell == NULL) {

			d->dist[i]->cell = c;
			d->dist[i]->distance = distance;
			break;
		}
	}

}

DISTANCES *distances(CELL *root, int size) {

	DISTANCES *d = init_distance(root, size);
	CELL **frontier = calloc(size, sizeof(CELL));
	check(d, "Couldn't allocate memory");
	check(frontier, "Couldn't allocate memory");

	frontier[0] = root;

	while (frontier[0]) {

		CELL **new_frontier = calloc(size, sizeof(CELL));
		check(new_frontier, "Couldn't allocate memory");
		int i = 0, j = 0, k = 0;

		for (i = 0; i < size && frontier[i] != NULL; i++) {

			CELL **links = frontier[i]->links;
			if (!links) continue;

			for (j = 0; j < 4 && links[j] != NULL; j++) { 	/* Cell can have a maximum of 4 links. */

				if (get_distance(d, links[j], size) < 0) {

					int new_distance = get_distance(d, frontier[i], size) + 1;
					set_distance(d, links[j], new_distance, size);

					if (k < size) {

						new_frontier[k] = links[j];
						++k;
					}
				}

			}
		}

		bzero(frontier, size * sizeof(CELL));
		memcpy(frontier, new_frontier, size * sizeof(CELL));
		free(new_frontier);
	}

	free(frontier);

	return d;

error:

	if (d) free(d);
	if (frontier) free(frontier);
	return NULL;

}

DISTANCES *path_to(DISTANCES *all_distances, CELL *goal, int size) {

	CELL *current = goal;
	DISTANCES *breadcrumbs = init_distance(all_distances->root, size);
	check(breadcrumbs, "Couldn't allocate memory");
	
	int distance = get_distance(all_distances, current, size), i = 0;
	set_distance(breadcrumbs, current, distance, size);

	while (!cmp_cell(all_distances->root, current)) {

		CELL **links = current->links;
		if (!links) break;

		for (i = 0; i < 4 && links[i] != NULL; i++) {

			distance = get_distance(all_distances, links[i], size);

			if (distance < get_distance(all_distances, current, size)) {

				distance = get_distance(all_distances, links[i], size);
				set_distance(breadcrumbs, links[i], distance, size);
				current = links[i];
				break;
			}
		}
	}

	return breadcrumbs;

error:
	return NULL;

}

CELL_DISTANCE *max(DISTANCES *d, int size) {

	int max_distance = 0, i = 0;
	CELL *max_cell = d->root;

	for (i = 0; i < size; i++) {

		if (d->dist[i]->distance > max_distance) {

			max_cell = d->dist[i]->cell;
			max_distance = d->dist[i]->distance;
		}
	}

	CELL_DISTANCE *table = malloc(sizeof(CELL_DISTANCE));
	check(table, "Couldn't allocate memory");

	table->cell = max_cell;
	table->distance = max_distance;

	return table;

error:
	return NULL;
}



#endif
