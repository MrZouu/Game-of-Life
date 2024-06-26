/*
 * lifegame.c
 *
 *  Created on:
 *      Author:
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "lifegame.h"

/* hard-coded world size */
#define WORLDWIDTH 39
#define WORLDHEIGHT 20

/* character representations of cell states */
#define CHAR_ALIVE '*'
#define CHAR_DEAD ' '

/* current cell states of the world */
static int world[WORLDWIDTH][WORLDHEIGHT];

/* next generation cell states */
static int nextstates[WORLDWIDTH][WORLDHEIGHT];

/* functions to write for Part B of lab */
void initialize_world_from_file(const char * filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        abort();
    }

    char line[256];
    int j = 0;
    while (fgets(line, sizeof(line), file) != NULL && j < WORLDHEIGHT) {
        printf("Read line: %s", line); // Ajout du message de débogage
        for (int i = 0; i < WORLDWIDTH && i < strlen(line); i++) {
            if (line[i] == CHAR_ALIVE) {
                world[i][j] = ALIVE;
            } else {
                world[i][j] = DEAD;
            }
        }
        j++;
    }

    fclose(file);

    // Reset all the next generation states to DEAD
    for (int i = 0; i < WORLDWIDTH; i++) {
        for (int j = 0; j < WORLDHEIGHT; j++) {
            nextstates[i][j] = DEAD;
        }
    }
}


void save_world_to_file(const char *filename) {
    /* TODO: write the state of the world into a file with
       name "filename". Assume the file can be created, or if
       the file exists, overwrite the file. The ith character
       of the jth line (zero-indexed) describes world[i][j]
       using the characters CHAR_ALIVE and CHAR_DEAD

       This file should be readable using the function
       initialize_world_from_file(filename) above; we can use
       it to resume a game later
     */
    FILE *file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        abort();
    }

    for (int j = 0; j < WORLDHEIGHT; j++) {
        for (int i = 0; i < WORLDWIDTH; i++) {
            fputc(world[i][j] == ALIVE ? CHAR_ALIVE : CHAR_DEAD, file);
        }
        fputc('\n', file);
    }

    fclose(file);
}

/* you shouldn't need to edit anything below this line */

/* initializes the world to a hard-coded pattern, and resets
   all the cells in the next generation to DEAD */
void initialize_world(void) {
	int i, j;

	for (i = 0; i < WORLDWIDTH; i++)
		for (j = 0; j < WORLDHEIGHT; j++)
			world[i][j] = nextstates[i][j] = DEAD;
	/* pattern "glider" */
	world[1][2] = ALIVE;
	world[3][1] = ALIVE;
	world[3][2] = ALIVE;
	world[3][3] = ALIVE;
	world[2][3] = ALIVE;
}

int is_World_Empty(void) {
	for (int i = 0; i < WORLDWIDTH; i++)
		for (int j = 0; j < WORLDHEIGHT; j++)
			if (world[i][j] == ALIVE) return 0;
	return 1;
}

int get_world_width(void) {
	return WORLDWIDTH;
}

int get_world_height(void) {
	return WORLDHEIGHT;
}

int get_cell_state(int x, int y) {
	if (x < 0 || x >= WORLDWIDTH || y < 0 || y >= WORLDHEIGHT)
		return DEAD;
	return world[x][y];
}

void set_cell_state(int x, int y, int state) {
	if (x < 0 || x >= WORLDWIDTH || y < 0 || y >= WORLDHEIGHT) {
		fprintf(stderr,"Error: coordinates (%d,%d) are invalid.\n", x, y);
		abort();
	}
	nextstates[x][y] = state;
}

void finalize_evolution(void) {
	int x, y;
	for (x = 0; x < WORLDWIDTH; x++) {
		for (y = 0; y < WORLDHEIGHT; y++) {
			world[x][y] = nextstates[x][y];
			nextstates[x][y] = DEAD;
		}
	}
}

void output_world(void) {
	char worldstr[2*WORLDWIDTH+2];
	int i, j;

	worldstr[2*WORLDWIDTH+1] = '\0';
	worldstr[0] = '+';
	for (i = 1; i < 2*WORLDWIDTH; i++)
		worldstr[i] = '-';
	worldstr[2*WORLDWIDTH] = '+';
	puts(worldstr);
	for (i = 0; i <= 2*WORLDWIDTH; i+=2)
		worldstr[i] = '|';
	for (i = 0; i < WORLDHEIGHT; i++) {
		for (j = 0; j < WORLDWIDTH; j++)
			worldstr[2*j+1] = world[j][i] == ALIVE ? CHAR_ALIVE : CHAR_DEAD;
		puts(worldstr);
	}
	worldstr[0] = '+';
	for (i = 1; i < 2*WORLDWIDTH; i++)
		worldstr[i] = '-';
	worldstr[2*WORLDWIDTH] = '+';
	puts(worldstr);
}
