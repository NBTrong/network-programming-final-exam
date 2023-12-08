#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>

/**
 * Read user input with a specified message and store it in the provided buffer.
 *
 * This function prints the given message to the console, reads user input, and
 * stores the input in the buffer. It removes the trailing newline character, if
 * present, to ensure the input is a proper string.
 *
 * @param buffer The character array to store the user input.
 * @param message The message to display as a prompt for user input.
 * @return A pointer to the buffer containing the user input.
 */
char* input(char *buffer, const char *message);

#endif