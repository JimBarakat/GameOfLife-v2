/*
 * Programmering i C
 * Fall 20
 * Mastery test 9
 * File:         game_of_life.c
 * Description:  The function definitions for game_of_life.h
 *
 * Author:       Jamie Barakat
 * CS username:  dv19jbt
 * Date:         6 November 2020
 */
#include "game_of_life.h"



void print_world(const int rows, const int cols, cell field[rows][cols])
{

   for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
             printf("%c ", field[r][c].current);
        }
        printf("\n");
   }

}



void print_menu(void)
{

   printf("Select one of the following options:\n");
   printf("        (enter) Step\n");
   printf("        (any)   Save and exit\n");

}



void next_step(const int rows, const int cols, cell field[rows][cols])
{

   decide_next(rows, cols, field);
   update_world(rows, cols, field);

}



void decide_next(const int rows, const int cols, cell field[rows][cols])
{
   //shorter, swedish word for neighbours.
   live_count grannar;
   init_count(&grannar);

   count_living(rows, cols, field, &grannar);

   for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
             if(field[r][c].current == ALIVE) {
                if(grannar.alive[r][c] == 2||grannar.alive[r][c]== 3) {
                   field[r][c].next = ALIVE;
                }
                else {
                      field[r][c].next = DEAD;
                }
             }
             else {
                   if(grannar.alive[r][c] == 3) {
                      field[r][c].next = ALIVE;
                   }
                   else {
                         field[r][c].next = DEAD;
                   }
             }
        }
   }

}



void init_count(live_count *grannar)
{

   for (int r = 0; r < MAX_ROWS; r++) {
        for (int c = 0; c < MAX_COLS; c++) {
             (*grannar).alive[r][c] = 0;
        }
   }

}



void count_living(const int rows, const int cols, cell field[rows][cols],
                      live_count *grannar)
{

   cell counter[rows+2][cols+2];

   for (int r = 0; r < rows+ 2; r++) {
        if(r == 0 || r == rows) {
           for (int c = 0; c < cols + 2; c++) {
                counter[r][c].current = DEAD;
           }
        }
        else if(r >= 1 && r < rows + 1) {
                for (int c = 1; c < cols + 1; c++) {
                     counter[r][c].current = field[r-1][c-1].current;
                }
                counter[r][0].current = DEAD;
                counter[r][cols+1].current = DEAD;
             }
   }

   for (int r = 0; r < rows + 2; r++) {
        if(r >= 1 && r < rows + 1) {
           for (int c = 1; c < cols + 1; c++) {
                for (int nr = r-1; nr <= r+1; nr++) {
                     for(int nc = c - 1; nc <= c+1; nc++) {
                         if(counter[nr][nc].current == ALIVE) {
                            if(&counter[nr][nc] != &counter[r][c]) {
                               (*grannar).alive[r-1][c-1] += 1;
                            }
                         }
                     }
                }
           }
        }
   }

}



void update_world(const int rows, const int cols, cell field[rows][cols])
{

   for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
             field[r][c].current = field[r][c].next;
        }
   }

}
