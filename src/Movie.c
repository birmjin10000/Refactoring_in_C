#include <stdlib.h>
#include "Movie.h"

Movie* Movie_New(char* title, int priceCode) {
    Movie* movie = (Movie*)malloc(sizeof(Movie));
    movie->_title = title;
    movie->_priceCode = priceCode;
    return movie;
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
