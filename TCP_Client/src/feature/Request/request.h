#ifndef REQUEST_H
#define REQUEST_H

#include "../../global.h"
#include <stdio.h>
#include "../../config/tcp.h"
#include "../../utils/utils.h"
#include "../../global.h"

void request(int socket);

void reply_request(int socket);

#endif // REQUEST_H
