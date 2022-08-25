/*
 * Programmering i C
 * Fall 20
 * Mastery test 9
 * File:         game_of_life_file_handler.h
 * Description:  functions for the file handler, enabling game of life
 *               to be used with load and save files.
 *               load_config_from_file is called from main, calls sub-functions
 *               is_format_correct, check_file_params and field_from_file in
 *               order, terminating if any return 1. These verify the
 *               format of the load file, the size specified and then populate
 *               the field after these checks return 0.
 *               save_config_to_file prints the field state to a file,
 *               returning 0 if successful.
 * Author:       Jamie Barakat
 * CS username:  dv19jbt
 * Date:         6 November 2020
 */
#ifndef GAME_OF_LIFE_FILE_HANDLER_H
#define GAME_OF_LIFE_FILE_HANDLER_H

#include <string.h>
#include <ctype.h>
#include "game_of_life.h"


/* Description: Load a configuration to the field array from a file.
*  Input:       The field array, its size and a file pointer to the
*               file with the initial configuration.
*  Output:      Returns 0 on success, the field array is updated with
*               the configuration from the file.
*               Returns a non-zero value on failure.
*               The file pointed to by fp is closed.
*/

int load_config_from_file(const int rows, const int cols,
cell field[rows][cols], FILE *fp);


/*  Description: Checks that the config file has the correct format
 *  Input:       pointer to string confaint first line from the config
 *               file and the string's size
 *  Output:      Returns 0 if the first line of the config file
 *               is correctly formatted.
 *               Returns 1 and prints to sdterr if not.
 */

int is_format_correct(int end_of_params, char *first_line);


/* Description:  Determines if size of the field specified by the config
 *               file is within program limits.
 *  Input:       Pointer to string containing first line from the config file,
 *               the string's size. Pointers to programs maximum field size
 *               values.
 *  Output:      Returns 0 if specified size within program limits.
 *               values in size pointers updated with file's values.
 *               Returns 1 and prints to sdterr if not within limits.
 */

int check_file_params(int end_of_params, int *row_val, int *col_val,
                      char *first_line);

/* Description:  Populates the field with the values specified by the load file.
 * Input:        Pointer to config file's second line. The size values of the
 *               config file's field. The field array and it's size.
 *  Output:      Returns 0 on success, 1 on failure.
 *               The field array is populated according to the config file.
 */

int field_from_file(int row_val, int col_val, const int rows, const int cols,
                    cell field[rows][cols], FILE *fp);


/* Description: Saves the current configuration of the field array to
 *               a specified file.
 * Input:        The field array, its size and a file pointer to the
 *               file where the final configuration should be saved.
 * Output:       Returns 0 on success, the current configuration in the
 *               field array is written to the file.
 *               Returns a non-zero value on failure.
 *               The file pointed to by fp is closed.
 */
int save_config_to_file(const int rows, const int cols,
                        const cell field[rows][cols], FILE *fp);

#endif
