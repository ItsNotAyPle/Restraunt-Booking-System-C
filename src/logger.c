#include "includes/logger.h"
#include <stdio.h>
#include <string.h>

// void console_log(char* text, LOG_TYPE type) {
//     switch(type) {
//         case LOG_TYPE.NORMAL:
//             log_normal(text);
//         case LOG_TYPE.ERROR:
//             log_error(text);
//         default:
//             break;
//     }
// }

void log_normal(char* text) {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "[NORMAL] ---> %s", text);
    puts(buffer);
}

void log_error(char* text) {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "[ERROR] ---> %s", text);
    puts(buffer);
}
