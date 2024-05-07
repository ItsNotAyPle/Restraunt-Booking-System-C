#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "includes/database.h"
#include "includes/logger.h"
#include "includes/utils.h"



int close_db_connection(FILE* dbfileptr) {
    
    if (dbfileptr == NULL) {
        log_error("Trying to close db connection but its null?\n");
        return -1;
    }

    fclose(dbfileptr); // TODO -> add error check for this
    return 0;
}

int init_database() {
    FILE* dbfileptr = fopen("database.json", "r+");
    if (dbfileptr == NULL) {
        return -1;
    }

    // move file pointer to end and get the size
    fseek(dbfileptr, 0, SEEK_END);
    size_t size = ftell(dbfileptr);
    //

    if (size == 0) {
        close_db_connection(dbfileptr);
        dbfileptr = fopen("database.json", "w");
        if (dbfileptr == NULL) {
            return -1;
        }

        fputs("[]", dbfileptr);
    }

    
    close_db_connection(dbfileptr);
    return 0;
}



/*

It's safe to say, i did not cook on this function. However, furthermore and to add to this,
it works.

Chances are i will come back and think of a better way to do this function
1) one idea that comes to mind is to layout the json differently, it doesn't need
   to be in the perfect way i've laid it out
*/

// TODO: look into another idea for optimization of instead of checking each
// string to see if it matches we just use an assumption system so
// buffer[0] (line 1) is the fname
struct ReservationInformation* json_to_reservervation_info(char* data) {
    size_t size = strlen(data);
    struct ReservationInformation* reservation = (struct ReservationInformation*) malloc(sizeof(struct ReservationInformation));
    char buffer[size];
    char* line;
    char* temp;
    const char delim[2] = ",";
    
    if (reservation == NULL) {
        return NULL;
    }

    snprintf(buffer, size, "%s", data);
    line = strtok(buffer, delim);

    while (line != NULL) {
        // printf( "Line: %s\n", line);
        if (strstr(line, "fname")) {
            temp = str_splice(line, "fname");
            temp = str_splice(temp, "\":");
            temp = str_splice(temp, "{");
            temp = str_splice(temp, "\"");

            snprintf(reservation->holder_fname, 30, "%s", temp);
        }  
        else if (strstr(line, "lname")) {
            temp = str_splice(line, "lname");
            temp = str_splice(temp, "\":");
            temp = str_splice(temp, "\"");
            temp = str_splice(temp, "\n");

            snprintf(reservation->holder_lname, 30, "%s", temp);
        }
        else if (strstr(line, "deposit_amount")) {
            temp = str_splice(line, "deposit_amount");
            temp = str_splice(temp, "\"");
            
            reservation->deposit_amount = atoi(temp);
        }
        else if (strstr(line, "number_of_people")) {
            temp = str_splice(line, "number_of_people");
            temp = str_splice(temp, "\"");

            reservation->number_of_people = atoi(temp);
        }
        else if (strstr(line, "time_made")) {
            temp = str_splice(line, "time_made");
            temp = str_splice(temp, "\"");

            reservation->time_made = atoi(temp);
        }
        else if (strstr(line, "reservation_time")) {
            temp = str_splice(line, "reservation_time");
            temp = str_splice(temp, "\"");

            reservation->reservation_time = atoi(temp);
        }
        else if (strstr(line, "still_active")) {
            temp = str_splice(line, "still_active");
            temp = str_splice(temp, "\"");

            reservation->still_active = atoi(temp);
        }


        line = strtok(NULL, delim);
    }

    free(temp);
    free(line);
    return reservation;
}

int convert_reservation_info_to_json(char buffer[], size_t buffer_size, struct ReservationInformation* info) {
    return snprintf(
        buffer, 
        buffer_size, 
        "{\n\"fname\":\"%s\",\n \"lname\":\"%s\",\n \"deposit_amount\":%hu,\n \"number_of_people\":%hu,\n \"time_made\":%zu,\n \"reservation_time\":%zu,\n \"still_active\":%d\n}", 
        info->holder_fname,
        info->holder_lname,
        info->deposit_amount,
        info->number_of_people,
        info->time_made,
        info->reservation_time,
        info->still_active
    );
}


int make_restraunt_reservation(struct ReservationInformation *info) {
    bool add_comma = false;
    size_t fsize;
    char buffer[1024];
    FILE* dbfileptr;

    dbfileptr = fopen("database.json", "r+");
    convert_reservation_info_to_json(buffer, sizeof(buffer), info);
    if (dbfileptr == NULL) {
        log_error("Failed to open db file. make_restraunt_reservation()");
        return -1;
    }

    // last character in file
    char last_chr[1];
    fseek(dbfileptr, 0, SEEK_END);
    fread(last_chr, 1, sizeof(last_chr), dbfileptr);
    fsize = ftell(dbfileptr);

    if (strncmp(last_chr, "]", sizeof(last_chr))) {
        fseek(dbfileptr, -1, SEEK_END);
        fputs(" ", dbfileptr);
        
        // random number, logic is there must already be data inside greater than
        // 4 for assumption of it not being the first
        if (fsize > 4) {
            add_comma = true;
        } 
    }

    close_db_connection(dbfileptr);
    //

    dbfileptr = fopen("database.json", "a");    
    if (add_comma) {
        fputs(",", dbfileptr);
    }

    fputs(buffer, dbfileptr);
    fputs("]", dbfileptr);


    close_db_connection(dbfileptr);
    return 0;
}


void push_reservation_to_list(struct ReservationInformationList** head, struct ReservationInformation* data) {
    struct ReservationInformationList* temp = (struct ReservationInformationList*) malloc(sizeof(struct ReservationInformationList));
    temp->data = data;
    temp->next = (*head);
    (*head) = temp;    
}


// for the love of god, future me, spend the time making an actual linked
// list libary. and test your stuff fully.
// https://stackoverflow.com/questions/3501338/c-read-file-line-by-line
struct ReservationInformationList* lookup_reservations(char* holder_fname) {
    struct ReservationInformationList* reservations_head = (struct ReservationInformationList*) malloc(sizeof(struct ReservationInformationList));
    // struct ReservationInformationList* reservations_head = NULL;

    FILE* dbfileptr;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    // if (reservations_head == NULL) {
    //     return NULL;
    // }





    dbfileptr = fopen("database.json", "r");
    if (dbfileptr == NULL) {
        return NULL;
    }
	
    while ((read = getline(&line, &len, dbfileptr)) != -1) {
		if (strstr(line, holder_fname)) {
			size_t block_location;
			size_t block_start = 0;
			size_t block_end = 0;
			size_t buffer_i = 0;
			char buffer[1024] = {0};
			char letter;

			block_location = ftell(dbfileptr);
			for (size_t i = block_location; i >= 0; i--) {
				fseek(dbfileptr, i, SEEK_SET);
				letter = fgetc(dbfileptr);
				
    			if (letter == '{') {
                    block_start = ftell(dbfileptr);
                    buffer[0] = '{';
                    buffer_i++;
                    break;
                }
    
                if (feof(dbfileptr) || i == 0) {
                    break;
                }
			}

            for (size_t i = block_start; i >= 0; i++) {
                fseek(dbfileptr, i, SEEK_SET);
                //fread(letter, sizeof(letter), 1, dbfileptr);
				letter = fgetc(dbfileptr);	

                buffer[buffer_i] = letter;
                buffer_i++;

				if (feof(dbfileptr)) {
					break;
				}

                if (letter == '}') {
                    block_end = i;
					break;
                }

            }

            
            push_reservation_to_list(&reservations_head, json_to_reservervation_info(buffer));

            // keep looping through linked list until next
            // a null (list->next) is null
            // while (current != NULL) {
            //     current = current->next;
            // }

            // current = (struct ReservationInformationList*) malloc(sizeof(struct ReservationInformationList));
            // current->data = json_to_reservervation_info(buffer);
            // current->next = NULL;
        }
    }


    free(line);
    close_db_connection(dbfileptr);

    return reservations_head;

}


// archive code:
    // pretty obv where this was used, finally figured out "{" != '{'
			/*
			
			break;
			fseek(dbfileptr, 0, SEEK_CUR);
            size_t size; // size -> location on the line containing matching fname
            size_t block_start = 0;
            size_t block_end = 0;
            int buffer_i = 0;
            char buffer[1024];
            //char letter[1];
			char letter;

            size = ftell(dbfileptr);
			for (int i = size; i > 0; i--) {
                //fseek(dbfileptr, i, SEEK_CUR);
                //fread(letter, sizeof(letter), 1, dbfileptr);
				letter = fgetc(dbfileptr);
				printf("%c", letter);

                if (strncmp(&letter, "{", sizeof(letter))) {
                    block_start = i;
                    break;
                }

				if (feof(dbfileptr)) {
					break;
				}
            }

			continue;
			
			for (size_t i = block_start; i >= 0; i++) {
                fseek(dbfileptr, i, SEEK_CUR);
                //fread(letter, sizeof(letter), 1, dbfileptr);
				letter = fgetc(dbfileptr);	

                buffer[buffer_i] = letter;
                buffer_i++;

                if (strncmp(&letter, "}", sizeof(letter))) {
                    block_end = i;
					break;
                }

				if (feof(dbfileptr)) {
					break;
				}
            }
			*/

            
			//log_normal(buffer);
