#ifndef __btree__
#define __btree__

#include "grid.h"

void on(GRID *g) {

	CELL **row = NULL, *c = NULL;

	srand((unsigned int) time(NULL));

	while ((row = each_row(g))) {

		while ((c = each_cell(g, row))) {

			CELL *neighbors[2];

			neighbors[0] = access_cell(g, c, NORTH);
			neighbors[1] = access_cell(g, c, EAST);

			int index = rand() % 2;

			if (neighbors[index]) {
			
				link(c, neighbors[index], 1);

			} else {

				if (index && neighbors[0]) link(c, neighbors[0], 1);
				else if (neighbors[1] )link(c, neighbors[1], 1);
			}

		}

		free(row);

	}


}

#endif
