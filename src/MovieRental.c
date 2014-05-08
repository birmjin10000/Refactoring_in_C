#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MovieRental.h"

/////////////////////////////////////////////
/* Linked list */
/////////////////////////////////////////////

typedef enum _boolean {
    false = 0,
    true = 1
} boolean;

ArrayList* ArrayList_New(void);
void ArrayList_Add(ArrayList*, void*); 
void* ArrayList_Next(ArrayList*); 
void* ArrayList_Get(ArrayList*, int);

ArrayList* ArrayList_New(void) {
    ArrayList* list = (ArrayList*)malloc(sizeof(ArrayList));
    return list;
}

void ArrayList_Add(ArrayList* list, void* item) {
    Node* new_node;
    new_node = (Node*)malloc(sizeof(Node));
    new_node->data = item;
    new_node->next = NULL;

    if (list->head == NULL) {
        list->head = new_node;
        list->tail = new_node;
        list->current = new_node;
    }
    else {
        list->tail->next = new_node;
        list->tail = new_node;
    }
}

void* ArrayList_Next(ArrayList* list) {
    Node* next = list->current->next;
    if (next == NULL)
        return NULL;
    list->current = next;
    return next->data;
}

void* ArrayList_Get(ArrayList* list, int position) {
    Node* item = NULL;
    int index;
    Node* current = list->head;
    for (index = 0; index <= position; index++) {
        if (current == NULL)
            break;
        item = current;
        current = current->next;
    }
    return item->data;
}

/////////////////////////////////////////////
/* Movie related */
/////////////////////////////////////////////

void Movie_New(Movie* self, char* title, int priceCode) {
    self->_title = title;
    self->_priceCode = priceCode;
}

int Movie_GetPriceCode(Movie* self) {
    return self->_priceCode;
}

void Movie_SetPriceCode(Movie* self, int priceCode) {
    self->_priceCode = priceCode;
}

char* Movie_GetTitle(Movie* self) {
    return self->_title;
}

///////////////////////////////////////////
/* Rental related */
///////////////////////////////////////////
void Rental_New(Rental* self, Movie* movie, unsigned int daysRented) {
    self->_movie = movie;
    self->_daysRented = daysRented;
}

unsigned int Rental_GetDaysRented(Rental* self) {
    return self->_daysRented;
}

Movie* Rental_GetMovie(Rental* self) {
    return self->_movie;
}

/////////////////////////////////////////////
/* Customer related */
/////////////////////////////////////////////

Customer* Customer_New(char* name) {
    Customer* customer = (Customer*)malloc(sizeof(Customer));
    customer->_name = name;
    customer->_rentals = ArrayList_New();
    return customer;
}

void Customer_AddRental(Customer* self, Rental* rental) {
    ArrayList_Add(self->_rentals, (void*)rental);
}

char* Customer_GetName(Customer* self) {
    return self->_name;
}

int Customer_Statement(Customer* self, char* result) {
    double totalAmount = 0;
    int frequentRenterPoints = 0;
    int byteWritten = 0;

    ArrayList* rentals = self->_rentals;
    byteWritten = snprintf(result, 2048, "Rental Record for \"%s\"\n", Customer_GetName(self));
    Rental* each = (Rental*)ArrayList_Get(rentals, 0);
    for ( ; each != NULL; each = (Rental*)ArrayList_Next(rentals)) {
        double thisAmount = 0;

		// determine amounts for each line
        switch (Movie_GetPriceCode(Rental_GetMovie(each))) {
            case MOVIE_REGULAR:
                thisAmount += 2;
                if (Rental_GetDaysRented(each) > 2)
                    thisAmount += (Rental_GetDaysRented(each) - 2) * 1.5;
                break;

            case MOVIE_NEW_RELEASE:
                thisAmount += Rental_GetDaysRented(each) * 3;
                break;

            case MOVIE_CHILDRENS:
                thisAmount += 1.5;
                if (Rental_GetDaysRented(each) > 3)
                    thisAmount += (Rental_GetDaysRented(each) - 3) * 1.5;
                break;
        }

        // add frequent renter points
        frequentRenterPoints++;
        // add bonus for a two day new release rental
        if (Movie_GetPriceCode(Rental_GetMovie(each)) == MOVIE_NEW_RELEASE &&
            Rental_GetDaysRented(each) > 1)
            frequentRenterPoints++;

        // show figures for this rental
        byteWritten += snprintf(result + byteWritten, 2048, "\t%*s\t%f\n", 20,
                                Movie_GetTitle(Rental_GetMovie(each)), thisAmount);
        totalAmount += thisAmount;
    }
    // add footer lines
    byteWritten += sprintf(result + byteWritten, "Amount owed is %f\n", totalAmount);
    byteWritten += sprintf(result + byteWritten, "You earned %d frequent renter points", frequentRenterPoints);
    
    return byteWritten;
}

