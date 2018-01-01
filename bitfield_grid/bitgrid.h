#ifndef __bitgrid__
#define __bitgrid__

#include "bitcell.h"



typedef enum tile_types {

	OPEN_SOUTH, OPEN_EAST, CLOSED_SOUTH, CLOSED_EAST

} TILE_TYPES;

void prepare_grid(int *grid[], int rows, int columns) {

	int a = 0, b = 0, i = 0;

	for (a = 0; a < rows; a++) {

		for (b = 0; b < columns; b++) {

			grid[i] = init_cell(a, b);
			++i;
		}
	}

}

int **init_grid(int rows, int columns) {

	int **grid = calloc(rows * columns, sizeof(int) * 3);
	check(grid, "Couldn't allocate memory");

	prepare_grid(grid, rows, columns);
	return grid;

error:
	return NULL;

}

char *generate_cell_tiles(TILE_TYPES *t[], int columns) {

	char *tile = malloc(sizeof(char) * 200); /* This includes the '\0' (NUL) terminator. */
	int i = 0;
	check(tile, "Couldn't allocate memory");
	bzero(tile, sizeof(char) * 200);
	strncpy(tile, "", 1);

	for (i = 0; i < columns; i++) {

		if (i == 0) strncat(tile, "|   ", 4);

		if (t[i][0] == OPEN_EAST) strncat(tile, "    ", 4);
		else strncat(tile, "|   ", 4);
	}

	strncat(tile, "\n", 1);

	for (i = 0; i < columns; i++)  {

		if (i == 0) strncat(tile, "+", 1);

		if (t[i][1] == OPEN_SOUTH) strncat(tile, "   +", 4);
		else strncat(tile, "---+", 4);
	}

	strncat(tile, "\n", 1);

	return tile;

error:
	return NULL;

}

char *to_str(int *grid[], int rows, int columns) {

	char *str = malloc(sizeof(char) * BUFSIZ + 1);
	int i = 0, k = 0, j = 0, size = rows * columns; 

	check(str, "Couldn't allocate memory");
	bzero(str, sizeof(char) * BUFSIZ + 1);

	strncpy(str, "+", 1);
	for (i = 0; i < columns; i++) 
			strncat(str, "---+", 4);
	strncat(str, "\n", 1);

	TILE_TYPES **t = calloc(columns, sizeof(TILE_TYPES) * 2);

	for (i = 0; i < rows; i++) {

		int a = 0;

		for (k = j; k < (j + columns); k++) {

			int *east_cell = access_cell(grid, size, grid[k], EBIT), *south_cell = access_cell(grid, size, grid[k], SBIT);

			t[a] = malloc(sizeof(TILE_TYPES) * 2);
			check(t[a], "Couldn't allocate memory");

			t[a][0] = (east_cell && is_linked(grid[k], east_cell, EBIT)) ? OPEN_EAST : CLOSED_EAST;
			t[a][1] = (south_cell && is_linked(grid[k], south_cell, SBIT)) ? OPEN_SOUTH : CLOSED_SOUTH;
/*
			if (t[a][0] == OPEN_EAST) debug("(%d, %d) is OPEN_EAST\n", grid[k][ROW], grid[k][COLUMN]);
			else debug("(%d, %d) is CLOSED_EAST\n", grid[k][ROW], grid[k][COLUMN]);

			if (t[a][1] == OPEN_SOUTH) debug("(%d, %d) is OPEN_SOUTH\n", grid[k][ROW], grid[k][COLUMN]);
			else debug("(%d, %d) is CLOSED_SOUTH\n", grid[k][ROW], grid[k][COLUMN]);
*/

			++a;
		}

		char *tiles = generate_cell_tiles(t, columns);
		if (strlen(tiles) < BUFSIZ) strncat(str, tiles, strlen(tiles));
		free(tiles);

		j += columns;
	}

	for (i = 0; i < columns; i++) free(t[i]);
	free(t);

	return str;

error:
	return NULL;

}

#endif
