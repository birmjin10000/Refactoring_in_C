#include <stdlib.h>
#include "Rental.h"

Rental* Rental_New(Movie* movie, unsigned int daysRented) {
    Rental* rental = (Rental*)malloc(sizeof(Rental));
    rental->_movie = movie;
    rental->_daysRented = daysRented;
    return rental;
}

unsigned int Rental_GetDaysRented(Rental* this) {
    return this->_daysRented;
}

Movie* Rental_GetMovie(Rental* this) {
    return this->_movie;
}

