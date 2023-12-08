#include "global.h"

char currentUser[STRING_LENGTH] = "\0";
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;