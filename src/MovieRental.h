#ifndef _MOVIE_RENTAL_H_
#define _MOVIE_RENTAL_H_

#define MOVIE_CHILDRENS 2
#define MOVIE_REGULAR 0
#define MOVIE_NEW_RELEASE 1

typedef struct _List{
    void* data;
    struct _List* next;
    struct _List* prev;
} List;

typedef struct _Customer {
    char* _name;
    List* _rentals;		
} Customer; 

typedef struct _Movie {
    char* _title;
    int _priceCode;
} Movie;

typedef struct _Rental {
    Movie* _movie;
    unsigned int _daysRented;
} Rental;


void Movie_New(Movie*, char*, int); 

void Rental_New(Rental*, Movie*, unsigned int); 

Customer* Customer_New(char*); 
void Customer_AddRental(Customer*, Rental*); 
int Customer_Statement(Customer*, char*);
 
#endif
