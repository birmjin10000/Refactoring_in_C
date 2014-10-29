#ifndef _RENTAL_H_
#define _RENTAL_H_

#include "Movie.h"

typedef struct _Rental {
    Movie* _movie;
    unsigned int _daysRented;
} Rental;

Rental* Rental_New(Movie*, unsigned int); 
Movie* Rental_GetMovie(Rental*);

#endif // _RENTAL_H_
