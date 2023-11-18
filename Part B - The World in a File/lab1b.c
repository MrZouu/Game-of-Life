/*
 * lab1b.c
 *
 *  Created on:
 *      Author:
 */

/* include helper functions for game */
#include "lifegame.h"

/* add whatever other includes here */
#include <stdio.h>

/* number of generations to evolve the world */
#define NUM_GENERATIONS 50

/* functions to implement -- can copy from Part A */

/* this function should set the state of all
   the cells in the next generation and call
   finalize_evolution() to update the current
   state of the world to the next generation */
void next_generation(void);

/* this function should return the state of the cell
   at (x,y) in the next generation, according to the
   rules of Conway's Game of Life (see handout) */
int get_next_state(int x, int y);

/* this function should calculate the number of alive
   neighbors of the cell at (x,y) */
int num_neighbors(int x, int y);

int main(int argc, char ** argv)
{
    int n;

    /* TODO: initialize the world, from file argv[1]
       if command line argument provided (argc > 1), or
       using hard-coded pattern (use Part A) otherwise */
    if (argc > 1) {
        initialize_world_from_file(argv[1]);
    } else {
        initialize_world();
    }

    for (n = 0; n < NUM_GENERATIONS; n++) {
        next_generation();
    }

    /* TODO: output final world state to console and save
       world to file "world.txt" in the current directory */
    output_world();
    save_world_to_file("world.txt");

    return 0;
}

void next_generation(void) {
    /* TODO: for every cell, set the state in the next
       generation according to the Game of Life rules
       Hint: use get_next_state(x,y) */
    for (int i = 0; i < get_world_width(); i++) {
        for (int j = 0; j < get_world_height(); j++) {
            set_cell_state(i, j, get_next_state(i, j));
        }
    }
    finalize_evolution(); /* called at the end to finalize */
}

int get_next_state(int x, int y) {
    /* TODO: for the specified cell, compute the state in
       the next generation using the rules
       Use num_neighbors(x,y) to compute the number of live
       neighbors */
    int n_state = num_neighbors(x, y);
    if (n_state == 3 || (n_state == 2 && get_cell_state(x, y) == ALIVE)) {
        return ALIVE;
    } else {
        return DEAD;
    }
}

int num_neighbors(int x, int y) {
    /* TODO: for the specified cell, return the number of
       neighbors that are ALIVE
       Use get_cell_state(x,y) */
    int n_state = 0;
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            if (i >= 0 && i < get_world_width() && j >= 0 && j < get_world_height() && !(i == x && j == y)) {
                n_state += (get_cell_state(i, j) == ALIVE) ? 1 : 0;
            }
        }
    }
    return n_state;
}
