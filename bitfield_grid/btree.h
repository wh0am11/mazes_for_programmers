#ifndef __bit_tree__
#define __bit_tree__

#include "bitgrid.h"
#include <time.h>

void on(int *grid[], int rows, int columns) {

	int r = 0, i = 0, k = 0, j = 0, size = rows * columns;

	srand((unsigned int) time(NULL));

	for (i = 0; i < rows; i++) {

		for (k = j; k < (j + columns); k++) {

			int *neighbors[2], bit = 0;

			neighbors[0] = access_cell(grid, size, grid[k], NBIT);
			neighbors[1] = access_cell(grid, size, grid[k], EBIT);

			r = rand() % 2;

			if (neighbors[r]) {

				bit = r ? EBIT : NBIT;
				link_cell(grid[k], neighbors[r], bit, 1);

			} else {

				if (r && neighbors[0]) link_cell(grid[k], neighbors[0], NBIT, 1);
				else if (neighbors[1]) link_cell(grid[k], neighbors[1], EBIT, 1);
			} 
		
		}

		j += columns;
	}

}

#endif
