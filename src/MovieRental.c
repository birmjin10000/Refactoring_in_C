#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MovieRental.h"

/////////////////////////////////////////////
/* Linked list */
/////////////////////////////////////////////

List* List_Append(List*, void*); 
List* List_Last(List*);
List* List_First(List*);
unsigned int List_Length(List*);

#define List_Previous(list)    ((list) ? (((List *)(list))->prev) : NULL)
#define List_Next(list)    ((list) ? (((List *)(list))->next) : NULL)

List* List_Append(List* list, void* data) {
    List* new_list;
    List* last;

    new_list = (List*)malloc(sizeof(List));
    new_list->data = data;
    new_list->next = NULL;

    if (list) {
        last = List_Last(list);
        last->next = new_list;
        new_list->prev = last;
        
        return list;
    }
    else {
        new_list->prev = NULL;
        return new_list;
    }
}

List* List_Last(List* list) {
    if (list) {
        while (list->next)
            list = list->next;
    }
  
    return list;
}

List* List_First(List* list) {
    if (list) {
        while (list->prev)
            list = list->prev;
    }
  
    return list;
}

unsigned int List_Length(List *list) {
    unsigned int length = 0;
  
    while (list) {
        length++;
        list = list->next;
    }
  
    return length;
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
    customer->_rentals = NULL;
    return customer;
}

void Customer_AddRental(Customer* this, Rental* rental) {
    this->_rentals = List_Append(this->_rentals, (void*)rental);
}

char* Customer_GetName(Customer* this) {
    return this->_name;
}

int Customer_Statement(Customer* this, char* result) {
    double totalAmount = 0;
    int frequentRenterPoints = 0;
    int byteWritten = 0;

    List* rentals = this->_rentals;
    byteWritten = snprintf(result, 2048, "Rental Record for \"%s\"\n", Customer_GetName(this));
   
    for ( ; rentals != NULL; rentals = List_Next(rentals)) {
        double thisAmount = 0;
        Rental* each = (Rental*)rentals->data;
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

