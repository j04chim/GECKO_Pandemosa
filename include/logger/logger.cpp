#include <stdio.h>
#include <ctime>

#include "logger.h"

void logger( int level, const char* message ) {
#if LOG_LEVEL <= 3
    time_t timestamp;
    time(&timestamp);
#endif
#if LOG_LEVEL <= 3
    switch (level) {
        case 3:
            printf(
                "\033[31m(%.24s)[fat] %s\033[0m\n", ctime(&timestamp), message
            ); break;
#if LOG_LEVEL <= 2
        case 2:
            printf(
                "(%.24s)[\033[31merr\033[0m] %s\n", ctime(&timestamp), message
            ); break;

#if LOG_LEVEL <= 1
        case 1:
            printf(
                "(%.24s)[\033[33mwar\033[0m] %s\n", ctime(&timestamp), message
            ); break;
#if LOG_LEVEL <= 0
        case 0:
            printf(
                "(%.24s)[\033[32minf\033[0m] %s\n", ctime(&timestamp), message
            ); break;
#endif
#endif
#endif
    }
#endif
}