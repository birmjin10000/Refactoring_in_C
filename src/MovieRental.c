#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MovieRental.h"

/////////////////////////////////////////////
/* Linked list */
/////////////////////////////////////////////
void List_Append(List*, List*);

#define List_ForEach(cursor, head) \
    for (cursor = (head)->next; cursor != (head); cursor = cursor->next)

void List_Init(List* list) {
    list->next = list;
    list->prev = list;
}

static void __List_Append(List* new, List* prev, List* next) {
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}

void List_Append(List* new, List* head) {
    __List_Append(new, head->prev, head);
}

/////////////////////////////////////////////
/* Movie related */
/////////////////////////////////////////////

void Movie_New(Movie* this, char* title, int priceCode) {
    this->_title = title;
    this->_priceCode = priceCode;
}

int Movie_GetPriceCode(Movie* this) {
    return this->_priceCode;
}

void Movie_SetPriceCode(Movie* this, int priceCode) {
    this->_priceCode = priceCode;
}

char* Movie_GetTitle(Movie* this) {
    return this->_title;
}

///////////////////////////////////////////
/* Rental related */
///////////////////////////////////////////
void Rental_New(Rental* this, Movie* movie, unsigned int daysRented) {
    this->_movie = movie;
    this->_daysRented = daysRented;
}

unsigned int Rental_GetDaysRented(Rental* this) {
    return this->_daysRented;
}

Movie* Rental_GetMovie(Rental* this) {
    return this->_movie;
}

/////////////////////////////////////////////
/* Customer related */
/////////////////////////////////////////////

Customer* Customer_New(char* name) {
    Customer* customer = (Customer*)malloc(sizeof(Customer));
    customer->_name = name;
    List_Init(&customer->_rentals);
    return customer;
}

void Customer_AddRental(Customer* this, Rental* rental) {
    List* new_list = (List*)malloc(sizeof(List));
    new_list->data = rental;
   
    List_Append(new_list, &this->_rentals);
}

char* Customer_GetName(Customer* this) {
    return this->_name;
}

int Customer_Statement(Customer* this, char* result, unsigned int bufferLen) {
    double totalAmount = 0;
    int frequentRenterPoints = 0;
    int byteWritten = 0;

    List* rentals = &this->_rentals;
    List* each;
    byteWritten = snprintf(result, bufferLen, "Rental Record for \"%s\"\n", Customer_GetName(this));
   
    List_ForEach(each, rentals) {
        double thisAmount = 0;
        Rental* r = (Rental*)each->data;
		// determine amounts for each line
        switch (Movie_GetPriceCode(Rental_GetMovie(r))) {
            case MOVIE_REGULAR:
                thisAmount += 2;
                if (Rental_GetDaysRented(r) > 2)
                    thisAmount += (Rental_GetDaysRented(r) - 2) * 1.5;
                break;

            case MOVIE_NEW_RELEASE:
                thisAmount += Rental_GetDaysRented(r) * 3;
                break;

            case MOVIE_CHILDRENS:
                thisAmount += 1.5;
                if (Rental_GetDaysRented(r) > 3)
                    thisAmount += (Rental_GetDaysRented(r) - 3) * 1.5;
                break;
        }

        // add frequent renter points
        frequentRenterPoints++;
        // add bonus for a two day new release rental
        if (Movie_GetPriceCode(Rental_GetMovie(r)) == MOVIE_NEW_RELEASE &&
            Rental_GetDaysRented(r) > 1)
            frequentRenterPoints++;

        // show figures for this rental
        byteWritten += snprintf(result + byteWritten, bufferLen, "\t%*s\t%f\n", 20,
                                Movie_GetTitle(Rental_GetMovie(r)), thisAmount);
        totalAmount += thisAmount;
    }
    // add footer lines
    byteWritten += snprintf(result + byteWritten, bufferLen, "Amount owed is %f\n", totalAmount);
    byteWritten += snprintf(result + byteWritten, bufferLen, "You earned %d frequent renter points", frequentRenterPoints);
    
    return byteWritten;
}

