#ifndef _MOVIE_RENTAL_H_
#define _MOVIE_RENTAL_H_

#define MOVIE_CHILDRENS 2
#define MOVIE_REGULAR 0
#define MOVIE_NEW_RELEASE 1

typedef struct _Node {
    void* data;
    struct _Node* next;
} Node;

typedef struct _ArrayList {
    Node* head;
    Node* tail;
    Node* current;
} ArrayList;

typedef struct _Customer {
    char* _name;
    ArrayList* _rentals;		
} Customer; 

typedef struct _Movie {
    char* _title;
    int _priceCode;
} Movie;

typedef struct _Rental {
    Movie* _movie;
    unsigned int _daysRented;
} Rental;


void Movie_New(Movie* self, char* title, int priceCode); 

void Rental_New(Rental* self, Movie* movie, unsigned int daysRented); 

Customer* Customer_New(char* name); 
void Customer_AddRental(Customer* self, Rental* rental); 
int Customer_Statement(Customer* customer, char* result);
 
#endif
