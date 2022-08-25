/*
 * Programmering i C
 * Fall 20
 * Mastery test 9

 * File:         mp9.c
 * Description:  A simple implementation of Conway's Game of Life.
 * Author:       Jamie Barakat
 * CS username:  dv19jbt
 * Date:         6 November 2020
 * Input:        Configuartion file containing field state.
                 Instruction to step or exit.
 * Output:       Prints the game field in each step, or saves to
 *               output file.
 * Limitations:  Program must have 2 arguments (in/output files)
 *               Input / output files must be able to be opened
 *               Input file must be correctly configured.
 *               Output file must be writable.
 */
#include "game_of_life_file_handler.h"

//declaration of function
int check_prog_params(int argc, const char *argv[],FILE **in_file_p, FILE
   **out_file_p);




int main(int argc, char **argv)
{

   FILE *load;
   FILE *save;

   if(check_prog_params(argc, (const char **) argv, &load, &save) != 0) {
      return 1;
   }

   const int rows = MAX_ROWS;
   const int cols = MAX_COLS;

   cell field[rows][cols];

   if(load_config_from_file(rows, cols, field, load) != 0) {
      return 1;
   }

   char user_choice;

   do {

       print_world(rows, cols, field);
       print_menu();

       user_choice = getchar();

       if(user_choice == '\n') {
          next_step(rows, cols, field);
       }
   } while (user_choice == '\n');

   if(save_config_to_file(rows, cols, field, save)!= 0) {
      return 1;
   }

   return 0;

}



/* Description: Checks the parameters to the program. Checks if the
*               call to the program has the right number of parameters.
*               Open the input and output files.
* Input:        The parameters to the program and two pointers to file
*               pointers.
* Output:       Returns 0 when the files are correctly opened.
*               Returns a non-zero value on failure.
*/

int check_prog_params(int argc, const char *argv[],
FILE **in_file_p, FILE **out_file_p)
{

   if(argc != 3) {
      fprintf(stderr, "Usage: %s <input configuration file> <output "
                       "configuration file>\n", argv[0]);
      return 1;
   }

   if((*in_file_p = fopen(argv[1], "r")) == NULL) {
      fprintf(stderr, "Could not open the file: %s\n", argv[1]);
      return 1;
   }

   if((*out_file_p = fopen(argv[2], "w")) == NULL) {
      fprintf(stderr, "Could not open the file: %s\n", argv[2]);
      return 1;
   }

   return 0;

}
