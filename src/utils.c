#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "includes/utils.h"


// TODO: try to optmize this or think of other solution
// should be ok since speed can be sacraficed in this program
// TODO: realloc memory size to fit new string
char* str_splice(char* string, const char* substring) {
    int k, j, p = 0;
    size_t str_size = strlen(string);
    size_t sub_str_size = strlen(substring);
    char* buffer;

    if ((sub_str_size > str_size) || str_size <= 0) {
        return string;
    }

    if (!strstr(string, substring)) {
        return string;
    }   

    
    buffer = (char*) malloc(sizeof(char) * str_size);
    memset(buffer, 0, str_size);

    k = 0;
    for (int i = 0; i < str_size; i++) {
        // printf("%s : %d\n", buffer, i);
        if (string[i] == substring[0]) {
            j = i;

            // verify match to substring
            for (k = 0; k < sub_str_size; k++) {
                if(string[j] == substring[k]) {
                    j++;
                    continue;
                }

                break;
            }

        }

        // if match was fount
        if (k == sub_str_size) {
            i += k; // i + k (offset to avoid the substring)
            k = 0;
            continue;
        }

        buffer[p] = string[i];
        p++;
        // printf("[%d]  : %c : %c\n", i, buffer[i], string[i]);
        
    }

    return buffer;
}


// char* str_splice(char* string, const char* substring) {
//     int k, j, block_start = 0;
//     size_t str_size = strlen(string);
//     size_t sub_str_size = strlen(substring);
//     char* buffer;

//     if ((sub_str_size > str_size) || str_size <= 0) {
//         return string;
//     }

//     if (!strstr(string, substring)) {
//         return string;
//     }

//     buffer = (char*) malloc(sizeof(char) * str_size);
//     // snprintf(buffer, str_size + 1, "%s", string);

//     // memset(buffer, 0, str_size);
//     // strncpy(buffer, string, str_size);


//     // j is starting point of block

//     for (int i = 0; i < str_size; i++) {
//         if (buffer[i] == substring[0]) {
//             j = i;

//             // verify substring matches:
//             for (k = 0; k < sub_str_size; k++) {
//                 if(buffer[j] == substring[k]) {
//                     j++;
//                     continue;
//                 }

//                 break;
//             }

//             // while (k <= sub_str_size) {
//             //     if (buffer[j] == substring[k]) {
//             //         j++;
//             //         k++;
//             //         continue;
//             //     } 
                
//             //     break;
//             // }

//             // if substring matches, set string from j... (j + k) 
//             // where j is the start position and o is the offset
//             // then set the char valeus to null
//             // k starts at 0 so -1 from size
//             // printf("%d : %ld", k, sub_str_size);
//             // printf("%d\n", k == sub_str_size);
//             printf("buffer: %s\n", buffer);
//             if (k == sub_str_size) {
//                 for (int o = 0; o < sub_str_size; o++) {
//                     buffer[i + o] = '\0';
//                     printf("buffer: %s\n", buffer);
//                 }
//             }
//         }
//     }

//     return buffer;
// }

char* str_splice_chr(char* string, const char chr) {
    return NULL;
}
