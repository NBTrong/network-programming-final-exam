#ifndef CHALLENGE_H
#define CHALLENGE_H

#include <stdio.h>
#include "../../global.h"
#include "../../config/tcp.h"
#include "../../utils/utils.h"
#include "../../global.h"
#include <sys/select.h>
#include <unistd.h>
#include "../../utils/utils.h"

void challenge(int socket);

void get_challenged_list(int client_socket);

#endif // CHALLENGE_H
