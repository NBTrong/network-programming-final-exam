#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * @brief Read data from the user and assign it to a variable pointed to by a void pointer.
 *
 * This function allows reading data from the user and assigning it to a variable pointed to by a void pointer,
 * based on the data type specified by the dataType string.
 *
 * @param data A void pointer pointing to the output data of the function.
 * @param dataType A string (char *) specifying the data type to be read (e.g., "int", "float", "char", "string").
 */
void input(void *data, char *dataType);

#endif