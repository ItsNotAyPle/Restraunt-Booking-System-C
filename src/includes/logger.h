#ifndef LOGGER_H_
#define LOGGER_H_
#include <stdio.h>

// enum LOG_TYPE {
//     NORMAL,
//     ERROR
// }


// void console_log(char* text, LOG_TYPE type);

void log_normal(char* text);
void log_error(char* text);

#endif