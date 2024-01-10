#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/select.h>
#include <unistd.h>

#include "../../global.h"
#include "../../config/tcp.h"
#include "../../utils/utils.h"
#include "../../global.h"
#include "../../utils/utils.h"
#include "../Receiver/receiver.h"

void game(int server_socket);

#endif
