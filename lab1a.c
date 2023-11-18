/*
 * lab1a.c
 *
 *  Created on:
 *      Author:
 */

/* include helper functions for game */
#include "lifegame.h"
#include <stdlib.h>
#include <unistd.h>

/* add whatever other includes here */

/* number of generations to evolve the world */
#define NUM_GENERATIONS 50 


/* functions to implement */

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

int main(void)
{
	int n;

	/* TODO: initialize the world */
	initialize_world();

	output_world();
	save_world_to_file("world.txt");
	for (n = 0; n < NUM_GENERATIONS; n++){
		next_generation();
		/* TODO (optional): Visualise world in each generation */
		finalize_evolution();
		output_world();
	}
	
	/* TODO: output final world state */
	//output_world();

	return 0;
}

void next_generation(void) {
	/* TODO: for every cell, set the state in the next
	   generation according to the Game of Life rules

	
	   Hint: use get_next_state(x,y) and set_next_state(x,y) */
	for (int i=0;i<get_world_width();i++){
		for (int j =0;j<get_world_height();j++){
			set_cell_state(i,j,get_next_state(i,j));
		}
	}

}

int get_next_state(int x, int y) {
	int n_state=0;
	n_state=num_neighbors(x,y);
	if (n_state==3 || n_state==2){
		return ALIVE;
	}
	else if (n_state==3 && get_cell_state(x,y)==DEAD){
		return ALIVE;
	}	
	else{
		return DEAD;
	}
	
	/* TODO: for the specified cell, compute the state in
	   the next generation using the rules

	   Use num_neighbors(x,y) to compute the number of live
	   neighbors */
}

int num_neighbors(int x, int y) {
	/* TODO: for the specified cell, return the number of
	   neighbors that are ALIVE

	   Use get_cell_state(x,y) */
	int n_state=0;
	for (int i=x-1;i<x+1;i++){
		for (int j=y-1;j<y+1;j++){
			if (get_cell_state(i,j)==ALIVE){
				n_state++;
			}
		}
	}
	return n_state;
}
