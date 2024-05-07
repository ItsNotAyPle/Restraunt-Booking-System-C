#include "includes/database.h"
#include <stdlib.h>

void push_reservation_to_list(struct ReservationInformationList** head, struct ReservationInformation* data) {
    struct ReservationInformationList* temp = (struct ReservationInformationList*) malloc(sizeof(struct ReservationInformationList));
    temp->data = data;
    temp->next = (*head);
    (*head) = temp;    
}

int main() {
    struct ReservationInformation test1 = {"sam", "valentine", 0, 2, 12345, 1234562, 1};
    struct ReservationInformation test2 = {"david", "valentine", 1000, 3, 12345, 1234562, 1};

    struct ReservationInformationList* head = NULL;
    push_reservation_to_list(&head, &test1);
    push_reservation_to_list(&head, &test2);

    printf("Finished");
}