#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include "../../global.h"
#include "../../config/tcp.h"
#include "../../utils/utils.h"
#include "../../global.h"
#include <sys/select.h>
#include <unistd.h>
#include "../../utils/utils.h"

void game(int server_socket);

#endif
