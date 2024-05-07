#ifndef DATABASE_H_
#define DATABASE_H_

#include <time.h>
#include <stdio.h>


struct ReservationInformation {
    char holder_fname[30];
    char holder_lname[30];
    unsigned short int deposit_amount;
    unsigned short int number_of_people;
    time_t time_made;
    time_t reservation_time;
    unsigned short int still_active;
};

struct ReservationInformationList {
    struct ReservationInformation* data;
    struct ReservationInformationList* next;
    // size_t size;
};

int init_database();
int close_db_connection(FILE* dbfileptr);
int make_restraunt_reservation(struct ReservationInformation* info);
struct ReservationInformation* json_to_reservervation_info(char* data);
struct ReservationInformationList* lookup_reservations(char* holder_fname);
int convert_reservation_info_to_json(char buffer[], size_t buffer_size, struct ReservationInformation* info);


#endif
