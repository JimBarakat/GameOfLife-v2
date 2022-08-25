/*
 * Programmering i C
 * Fall 20
 * Mastery test 9
 * File:         game_of_life_file_handler.c
 * Description:  The function definitions for game_of_life_file_handler.h
 *
 * Author:       Jamie Barakat
 * CS username:  dv19jbt
 * Date:         6 November 2020
 */
#include "game_of_life_file_handler.h"


int load_config_from_file(const int rows, const int cols,cell field[rows][cols],
                          FILE *fp)
{

   char first_line[cols];

   if(fgets(first_line, cols, fp) == NULL) {
      fprintf(stderr, "Incorrect configuration file format\n");
      return 1;
   }

   int end_of_params =  strlen(first_line);

   if(is_format_correct(end_of_params, first_line) != 0) {
      return 1;
   }

   int row_val = rows, col_val = cols;

   if(check_file_params(end_of_params, &row_val, &col_val, first_line) != 0) {
      return 1;
   }
   if(field_from_file(row_val, col_val, rows, cols, field, fp) != 0) {
      return 1;
   }
   fclose(fp);

   return 0;

}



int is_format_correct(int end_of_params, char *first_line)
{

   if(first_line[end_of_params - 1] == '\n') {
      first_line[end_of_params - 1] = '\0';
   }
   int index = 0;

   do {

      if(!(isdigit(first_line[index]))) {
         if(!(first_line[index] == ',')) {
            if(!(first_line[index] == '\0')){
               fprintf(stderr, "Incorrect configuration file format\n");
               return 1;
            }
         }
      }
      index++;
   } while (index < end_of_params && first_line[index] != ('\n'||'\0'));

   return 0;

}



int check_file_params(int end_of_params, int *row_val, int *col_val,
                      char *first_line)
{

   int param_size = (end_of_params / 2) + 1;
   int param_marker = 0, index = 0, col_index = 0;
   char file_rows[param_size], file_cols[param_size];

   for (index = 0; index < end_of_params; index++) {
        if(col_index == 0 && isdigit(first_line[index])) {
           file_rows[index] = first_line[index];
        }
        if(first_line[index] == ',') {
           file_rows[index] = '\0';
           param_marker = 1;
           index++;
        }
        if(param_marker == 1 && isdigit(first_line[index])) {
           file_cols[col_index] = first_line[index];
           col_index++;
        }
        else if(param_marker == 1 && first_line[index] == '\0') {
                file_cols[col_index] = '\0';
              }
    }
    if(atoi(file_rows) > *row_val || atoi(file_cols) > *col_val) {
       fprintf(stderr, "The configuration is too big for the field\nThe field");
       fprintf(stderr, " needs to be at least %d rows and %d columns\n",
                       atoi(file_rows), atoi(file_cols));
      return 1;
   }
   *row_val = atoi(file_rows);
   *col_val = atoi(file_cols);

   return 0;

}



int field_from_file(int row_val, int col_val, const int rows, const int cols,
                    cell field[rows][cols], FILE *fp)
{

   for (int r = 0; r < rows; r++) {
        if(r < row_val) {
           char this_row[col_val+2];
           if(fgets(this_row, col_val+2, fp) == NULL){
              return 1;
           }
           for (int c = 0; c < cols; c++) {
                if(c < col_val) {
                   if(this_row[c] == '*') {
                      field[r][c].current = ALIVE;
                   }
                   else if(this_row[c] == '0') {
                           field[r][c].current = DEAD;
                        }
                   else if(this_row[c] != ('*'||'0'||'\n')) {
                           return 1;
                        }
                }
                if(c >= col_val) {
                   field[r][c].current = DEAD;
                }
           }
        }
        if(r >= row_val) {
           for (int c = 0; c < cols; c++) {
                field[r][c].current = DEAD;
           }
        }
   }

   return 0;

}



int save_config_to_file(const int rows, const int cols,
                        const cell field[rows][cols], FILE *fp)
{

   if(!(fprintf(fp, "%d,%d\n", rows, cols))) {
     return 1;
   }
   for (int r = 0; r < rows; r++) {
        char this_row[cols+2];
        for (int c = 0; c < cols; c++) {
             if(field[r][c].current == ALIVE) {
               this_row[c] = '*';
             }
             else {
                   this_row[c] = '0';
             }
        }
        this_row[cols] = '\n';
        this_row[cols+1] = '\0';
        if(!(fprintf(fp, "%s", this_row))) {
           return 1;
        }
   }
   if(!(fclose(fp))) {
     return 1;
   }

   return 0;

}
