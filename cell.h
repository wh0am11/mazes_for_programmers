#ifndef __cell__
#define __cell__

#include "dbg.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef enum cardinals {

	NORTH, SOUTH, EAST, WEST

} DIRECTION;

typedef struct cell {

	int row;
	int column;
	struct cell **links;

} CELL;

typedef struct grid {

        int rows;
        int columns;

        CELL **grid;

} GRID;


CELL *initialize(int row, int column) {

	CELL *c = malloc(sizeof(CELL));
	int i = 0;

	check(c, "Couldn't allocate memory");

	c->row = row;
	c->column = column;
	c->links = calloc(4, sizeof(CELL));

	check(c->links, "Couldn't allocate memory");
	
	for (i = 0; i < 4; i++) {

		c->links[i] = NULL;
	}

	return c;	

error:

	if (c) free(c);
	return NULL;

}

int cmp_cell(CELL *c, CELL *c2) {

	int ret = 0;
		
	ret = (c && c2 && (c->row == c2->row && c->column == c2->column)) ? 1 : 0;

	return ret;

}

void add(CELL *links[], CELL *c) {

	int i = 0;

	while (links[i] && i < 4) ++i;

	if (links[i] == NULL) 
			links[i] = c;
	else
			log_warn("Unable to add variable to links list because it has reached max capacity.");

}

void delete(CELL *links[], CELL *c) {

	int i = 0;

	while (links[i] && i < 4) {

		if (cmp_cell(links[i], c)) {

			free(links[i]);
			links[i] = NULL;
		}
	}

}

CELL *find_cell(CELL *grid[], int size, int row, int column) {

	int i = 0;
	CELL *c = NULL;

	for (i = 0; i < size; i++) {

		if (grid[i]->row == row && grid[i]->column == column) {

			c = grid[i];
			break;
		}
	}

	return c;


}

CELL *access_cell(GRID *g, CELL *c, DIRECTION d) {

	CELL *cell = NULL, **grid = g->grid;
	int size = g->rows * g->columns;

	if (d == NORTH) cell = find_cell(grid, size, c->row - 1, c->column);
	if (d == SOUTH) cell = find_cell(grid, size, c->row + 1, c->column);
	if (d == EAST) cell = find_cell(grid, size, c->row, c->column + 1);
	if (d == WEST) cell = find_cell(grid, size, c->row, c->column - 1);

	return cell;

}


void link(CELL *c, CELL *c2, int bidi) {

	add(c->links, c2);
	if (bidi) link(c2, c, 0);

}

void unlink(CELL *c, CELL* c2, int bidi) {

	delete(c->links, c2);
	if (bidi) link(c2, c, 0);

}


int linked(CELL *c, CELL *c2) {

	int i = 0, ret = 0;

	for (i = 0; i < 4; i++)	 {

		if (cmp_cell(c->links[i], c2)) {

			ret = 1;
			break;

		}
	}

	return ret;

}


uint8_t neighbors(GRID *grid, CELL *c) {

	uint8_t list = 0;

	if (access_cell(grid, c, NORTH)) list |= 0x1;
	if (access_cell(grid, c, SOUTH)) list |= 0x2;
	if (access_cell(grid, c, EAST)) list |= 0x4;
	if (access_cell(grid, c, WEST)) list |= 0x8;

	return list;

}




#endif
