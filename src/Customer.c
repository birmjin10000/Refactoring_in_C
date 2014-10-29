#include <stdio.h>
#include <stdlib.h>
#include "Customer.h"

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
    byteWritten = snprintf(result, 
                           bufferLen, 
                           "Rental Record for \"%s\"\n", Customer_GetName(this));
   
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
        byteWritten += snprintf(result + byteWritten,
                                bufferLen,
                                "\t%*s\t%f\n",
                                20, Movie_GetTitle(Rental_GetMovie(r)), thisAmount);
        totalAmount += thisAmount;
    }
    // add footer lines
    byteWritten += snprintf(result + byteWritten,
                            bufferLen, 
                            "Amount owed is %f\n",
                            totalAmount);
    byteWritten += snprintf(result + byteWritten,
                            bufferLen,
                            "You earned %d frequent renter points",
                            frequentRenterPoints);
    
    return byteWritten;
}

