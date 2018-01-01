#ifndef __sidewinder__
#define __sidewinder__

#include "grid.h"

void sidewinder_on(GRID *g) {

	CELL **row = NULL, *cell = NULL;

	srand((unsigned int) time(NULL));

	while ((row = each_row(g))) {

		CELL **run = calloc(g->columns, sizeof(CELL));
		int k = 0;

		while ((cell = each_cell(g, row))) {

			if (k < g->columns) run[k] = cell;

			int at_eastern_boundary = (access_cell(g, cell, EAST) == NULL) ? 1 : 0;
			int at_northern_boundary = (access_cell(g, cell, NORTH) == NULL) ? 1 : 0;
			int should_close_out = 0, r = 0;

			r = rand() % 2;
			should_close_out = (at_eastern_boundary || (!at_northern_boundary && r == 0)) ? 1 : 0;

			if (should_close_out) {

				r = rand() % (k + 1);
				CELL *member = run[r], *member_north = access_cell(g, member, NORTH);

				if (member_north) link(member, member_north, 1);
				bzero(run, g->columns * sizeof(CELL));
				k = 0;

			} else {

				CELL *cell_east = access_cell(g, cell, EAST);
				link(cell, cell_east, 1);
				if (k < g->columns) ++k;
			}
		}

		free(run);
		free(row);
	}


}

#endif
