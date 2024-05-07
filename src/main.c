#include <stdio.h>
#include <string.h>
#include "includes/logger.h"
#include "includes/database.h"
#include "includes/utils.h"


void handle_new_reservation() {
	time_t current_time;
    struct ReservationInformation info;
    int ret;

    time(&current_time);

	printf("Enter first name: ");
    scanf("%29s", info.holder_fname);
    
    
	printf("Enter last name: ");
    scanf("%29s", info.holder_lname);
    
    
	printf("Deposit amount? [0 if none]: ");
    ret = scanf("%hu", &info.deposit_amount);
    if (ret == 0) {
        info.deposit_amount = 0;
    }
    
	
	printf("Number of people: ");
    ret = scanf("%hu", &info.number_of_people);
    if (ret == 0) {
        info.number_of_people = 1;
    }
    
	
	// printf("[Day/Month/Year] [HH:MM] of reservation: ");
    // scanf("%lu", &info.reservation_time);
    info.still_active = 1;
    info.time_made = current_time;
    info.reservation_time = current_time + 1;
    
	make_restraunt_reservation(&info);
    printf("Made reservation!\n");

}

void handle_search_reservation() {
    struct ReservationInformationList* current;
	char lname[30] = {0};

	printf("Enter last name of person to search: ");
    scanf("%29s", lname);
    current = lookup_reservations(lname);
    
    while (current != NULL) {
        if (current->data == NULL) {
            break;
        }

        printf("First Name: %s\n", current->data->holder_fname);
        printf("Last Name: %s\n", current->data->holder_lname);
        printf("Number of people: %d\n", current->data->number_of_people);
        printf("Deposit amount: %d\n", current->data->deposit_amount);
        printf("date/time made: %lu\n", current->data->time_made);
        printf("date/time of reservation: %lu\n", current->data->reservation_time);
        printf("still active: %s\n", current->data->still_active ? "yes" : "no");
        
        current = current->next;
    }
}

int main() {
    bool running = true;
    int ret;
    ret = init_database();
    if (ret == -1) {
        log_error("Problem in init_database()");
    }

    while (running) {
        int num = 0;

        printf("\n---- Restraunt Reservation System ----\n");
        printf("[1] new reservation\n");
        printf("[2] search reservation\n");
        printf("[3] cancel a reservation\n");
        printf("[99] exit\n");
        printf("---> ");

        ret = scanf("%d", &num);
        if (ret == 0) {
            return -1;
        }

        switch (num) {
            case 1:
                handle_new_reservation();
                break;
            case 2:
                handle_search_reservation();
                break;
            case 99:
                running = false;
                break;
        }
    }

    // ret = make_restraunt_reservation(&info);
    // if (ret == -1) {
    //     log_error("Problem in make_restraunt_reservation()");
    // }

    


    return 0;
}
