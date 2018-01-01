#ifndef __bitcell__
#define __bitcell__

#include "dbg.h"
#include <stdio.h>
#include <stdlib.h>

#define INT_FIELDS 3 /* One slot for the row, one slot for the column, and
			another for storing the links of the cell. */

#define ROW 0
#define COLUMN 1
#define LINKS 2

#define NBIT 0x8
#define SBIT 0x4
#define EBIT 0x2
#define WBIT 0x1

int *init_cell(int row, int column) {

	int *cell = calloc(INT_FIELDS, sizeof(int));
	check(cell, "Couldn't allocate memory");

	cell[ROW] = row;
	cell[COLUMN] = column;
	cell[LINKS] = 0;

	return cell;

error:
	return NULL;

}

int opposite_bit(int bit) {

	int new_bit = 0;

	switch(bit) {

		case NBIT:
			new_bit = SBIT;
			break;
		case SBIT:
			new_bit = NBIT;
			break;
		case EBIT:
			new_bit = WBIT;
			break;
		case WBIT:
			new_bit = EBIT;
			break;
	}

	return new_bit;

}

void link_cell(int *c, int *c2, int bit, int bidi) {

	c[LINKS] |= bit;
	if (bidi) link_cell(c2, c, opposite_bit(bit), 0);

}

int is_linked(int *c, int *c2, int bit) {


	int ret = 0;

	ret = ((c[LINKS] & bit) && (c2[LINKS] & opposite_bit(bit))) ? 1 : 0;

	return ret;

}

int *find_cell(int *grid[], int size, int row, int column) {

	int i = 0, *cell = NULL;

	for (i = 0; i < size; i++) {

		if (grid[i][ROW] == row && grid[i][COLUMN] == column) {

			cell = grid[i];
			break;
		}
	}

	return cell;

}

int *access_cell(int *grid[], int size, int *cell, int bit) {

	int *c = NULL, row = cell[ROW], column = cell[COLUMN];

	if (bit == NBIT) c = find_cell(grid, size, row - 1, column);
	else if (bit == SBIT) c = find_cell(grid, size, row + 1, column);
	else if (bit == EBIT) c = find_cell(grid, size, row, column + 1);
	else if (bit == WBIT) c = find_cell(grid, size, row, column - 1);

	return c;

}

#endif
