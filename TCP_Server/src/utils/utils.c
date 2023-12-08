#include "utils.h"

char* input(char *buffer, const char *message) {
    memset(buffer, 0, strlen(buffer));
    sprintf(buffer, "%s", message);
    return buffer;
}