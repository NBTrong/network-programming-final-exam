#ifndef ONLINE_H
#define ONLINE_H

#include "../../config/tcp.h"
#include "../../global.h"
#include "../../utils/utils.h"

void get_list_user_online(int socket);

void process_user_list(const char *userList);

#endif
