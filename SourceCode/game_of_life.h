/*
 * Programmering i C
 * Fall 20
 * Mastery test 9
 * File:         game_of_life.h
 * Description:  The funtions for conway's game of life.
 *               A field array is populated with either alive or dead
 *               members, it is displayed, user is given a choice
 *               on the next stage.
 *               if the user chooses the proceed, the next stage of the
 *               field is determined then displayed, by counting the
 *               living neighbours to every position in the array,
 *               and calculating wether the member is alive or dead in
 *               next stage based on this count.
 *
 * Author:       Jamie Barakat
 * CS username:  dv19jbt
 * Date:         6 November 2020
 */

#ifndef GAME_OF_LIFE_FILE_H
#define GAME_OF_LIFE_FILE_H

#include <stdio.h>
#include <stdlib.h>

/* Constants, representation of states */
#define ALIVE 'X'
#define DEAD '.'

//change these values if you want to adjust field size
#define MAX_ROWS 20
#define MAX_COLS 20



/* Declaration of data structure */
typedef struct {
  char current;
  char next;
} cell;

//struct for counting live neighbours to a cell
typedef struct {
  int alive[MAX_ROWS][MAX_COLS];
} live_count;



/* Description: prints the field's current state on screen.
 * Input:       The field array and its size.
 * Output:      The field array is displayed.
 */

void print_world(const int rows, const int cols, cell field[rows][cols]);


/* Description: prints the menu onscreen for the user.
 * Input:       none.
 * Output:      Menu providing options is displayed.
 */
void print_menu(void);


/* Description: Determines what state the next step of the field array
 *              will be, updates the field array to that state.
 * Input:       The field array and its size.
 * Output:      The field array is updated.
 */

void next_step(const int rows, const int cols, cell field[rows][cols]);


/* Description: Determines what state the next step of the field array
 *              will be.
 * Input:       The field array and its size.
 * Output:      The field array's next state updated.
 */

void decide_next(const int rows, const int cols, cell field[rows][cols]);


/* Description: Initialize all the values in the reference array to 0.
 * Input:       Pointer to reference array
 * Output:      The reference array is initialized.
 */

void init_count(live_count *grannar);


/* Description: Allocates the reference array with the number of
 *              living neighbours to every position in the field.
 * Input:       The field array and its size, pointer to reference array.
 * Output:      The reference array is updated.
 */

void count_living(const int rows, const int cols, cell field[rows][cols],
                      live_count *grannar);


/* Description: Updates the field to it's next state.
 * Input:       The field array and its size.
 * Output:      The field array is updated.
 */

void update_world(const int rows, const int cols, cell field[rows][cols]);

#endif
