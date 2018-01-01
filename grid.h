#ifndef __grid__
#define __grid__

#include "cell.h"
#include "distances.h"
#include <time.h>

struct args {

	int djikstra;

	union djikstra_args {

		DISTANCES *d;

	} djargs;

};

void prepare_grid(GRID *g) {

	int a, b, i = 0;

	for (a = 0; a < g->rows; a++) {

		for (b = 0; b < g->columns; b++) {

			g->grid[i] = initialize(a, b);
			++i;
		}
	}

}

GRID *initialize_grid(int rows, int columns) {

	GRID *g = malloc(sizeof(GRID));

	check(g, "Couldn't allocate memory");

	g->rows = rows;
	g->columns = columns;
	g->grid = calloc(rows * columns, sizeof(CELL));

	check(g->grid, "Couldn't allocate memory");
	prepare_grid(g);

	return g;

error:
	if (g) free(g);
	return NULL;

}

CELL *random_cell(GRID *g, int size) {

	srand((unsigned int) time(NULL));

	int row = rand(), column = rand();

	CELL *c = find_cell(g->grid, size, row, column);
	
	return c;
}

int get_size(GRID *g) {

	return g->rows * g->columns;

}

CELL **each_row(GRID *g) {

	static int r = 0;
	int i = 0, j = 0, k = 0;
	CELL **grid = g->grid, **row = calloc(g->columns, sizeof(CELL));

	check(row, "Couldn't allocate memory");

	for (i = 0; i < (g->rows * g->columns); i++)  {

		if (grid[i]->row == r) {

			j = i;
			break;
		}
	}

	for (i = j; i < (j + g->columns); i++) { 	// `j + g->columns` gives us the index of the cell in the next row

		row[k] = g->grid[i];
		++k;
	}

	if (r < g->rows) {

		++r;

	} else {

		r = 0;
		free(row);
		row = NULL;
	}

	return row;

error:
	return NULL;

}

CELL *each_cell(GRID *g, CELL *row[]) {

	static int i = 0;
	CELL *c = NULL;

	if (i < g->columns) {

		c = row[i];
		++i;

	} else {

		i = 0;
	}

	return c;

}


char *to_str(GRID *g, struct args *args) {

	CELL **row = NULL, *cell = NULL;
	char *buffer = malloc(sizeof(char) * BUFSIZ + 1);
	int i = 0;

	check(buffer, "Couldn't allocate memory");
	bzero(buffer, sizeof(char) * BUFSIZ + 1);
	strncpy(buffer, "+", 1);

	for (i = 0; i < g->columns; i++) 
		strncat(buffer, "---+", 4);

	strncat(buffer, "\n", 1);

	while ((row = each_row(g))) {

		char top[BUFSIZ] = "|", bottom[BUFSIZ] = "+";

		while ((cell = each_cell(g, row))) {

			char east_bound = '|', *south_bound = "---", *body = "   ";
			CELL *east_cell = access_cell(g, cell, EAST), *south_cell = access_cell(g, cell, SOUTH);

			if (args && args->djikstra && args->djargs.d) {

				int distance = get_distance(args->djargs.d, cell, g->rows * g->columns);

				if (distance >= 0) {

					char bdy[4];
					snprintf(bdy, sizeof(bdy), " %d ", distance);
					body = bdy;
				}
			}

			east_bound = (east_cell && linked(cell, east_cell)) ? ' ' : '|';
			south_bound = (south_cell && linked(cell, south_cell)) ? "   " : "---";

			if (strlen(top) < BUFSIZ && strlen(bottom) < BUFSIZ) {

				strncat(top, body, 3);
				strncat(top, &east_bound, 1);

				strncat(bottom, south_bound, 3);
				strncat(bottom, "+", 1);

			}
		}

		if (strlen(top) < BUFSIZ) {

			strncat(buffer, top, strlen(top));
			strncat(buffer, "\n", 1);

		} 

		if (strlen(bottom) < BUFSIZ) { 

			strncat(buffer, bottom, strlen(bottom));
			strncat(buffer, "\n", 1);
		}
	}

	return buffer;

error:
	return NULL;

}

void dealloc_grid(GRID *g) {

	int i = 0;

	for (i = 0; i < g->rows * g->columns; i++) {

		if (g->grid[i]) free(g->grid[i]);
	}

	free(g->grid);
	free(g);

}

#endif
