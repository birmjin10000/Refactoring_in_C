#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/////////////////////////////////////////////
/* Linked list */
/////////////////////////////////////////////

typedef struct _Node {
    void* data;
    struct _Node* next;
} Node;

typedef struct _ArrayList {
    Node* head;
    Node* tail;
    Node* current;
} ArrayList;

typedef enum _boolean {
    false = 0,
    true = 1
} boolean;

//const int NULL = 0;

void ArrayList_AddElement(ArrayList* list, void* item); 
boolean ArrayList_HasMoreElements(ArrayList* list); 
void* ArrayList_NextElement(ArrayList* list); 

void ArrayList_AddElement(ArrayList* list, void* item) {
    Node* new_node;
    new_node = malloc(sizeof(Node));
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

boolean ArrayList_HasMoreElements(ArrayList* list) {
    if (list->current != list->tail)
        return true;
    
    list->current = list->head; // reset current cursor
    return false;
}

void* ArrayList_NextElement(ArrayList* list) {
    Node* next = list->current->next;
    list->current = next;
    return next->data;
}

/////////////////////////////////////////////
/* Movie related */
/////////////////////////////////////////////
#define MOVIE_CHILDRENS 2
#define MOVIE_REGULAR 0
#define MOVIE_NEW_RELEASE 1

typedef struct _Movie {
    char* _title;
    int _priceCode;
} Movie;

void Movie_NewMovie(Movie* self, char* title, int priceCode) {
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
typedef struct _Rental {
    Movie* _movie;
    int _daysRented;
} Rental;

void Rental_NewRental(Rental* self, Movie* movie, int daysRented) {
    self->_movie = movie;
    self->_daysRented = daysRented;
}

int Rental_GetDaysRented(Rental* self) {
    return self->_daysRented;
}

Movie* Rental_GetMovie(Rental* self) {
    return self->_movie;
}

/////////////////////////////////////////////
/* Customer related */
/////////////////////////////////////////////
typedef struct _Customer {
    char* _name;
    ArrayList* _rentals; 
} Customer;

void Customer_AddRental(Customer* self, Rental* rental) {
    ArrayList_AddElement(self->_rentals, (void*)rental);
}

char* Customer_GetName(Customer* self) {
    return self->_name;
}

int Customer_Statement(Customer* self, char* result) {
    double totalAmount = 0;
    int frequentRenterPoints = 0;
    int byteWritten = 0;

    ArrayList* rentals = self->_rentals;
    byteWritten = sprintf(result, "Rental Record for %s\n", Customer_GetName(self));

    while (ArrayList_HasMoreElements(rentals)) {
        double thisAmount = 0;
        Rental* each = (Rental*)ArrayList_NextElement(rentals);

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
        byteWritten += sprintf(result + byteWritten, "\t%s\t%f\n", 
                                Movie_GetTitle(Rental_GetMovie(each)), thisAmount);
        totalAmount += thisAmount;
    }
    // add footer lines
    byteWritten += sprintf(result + byteWritten, "Amount owed is %f\n", totalAmount);
    byteWritten += sprintf(result + byteWritten, "You earned %d frequent renter points", frequentRenterPoints);
    
    return byteWritten;
}

int main(void) {

    Movie aMovie;
    Movie bMovie;
    Movie cMovie;

    char* aTitle = "Home Alone";
    char* bTitle = "Amazing Spiderman 2";
    char* cTitle = "Iron Man 1";

    Movie_NewMovie(&aMovie, aTitle, MOVIE_CHILDRENS);
    Movie_NewMovie(&bMovie, bTitle, MOVIE_NEW_RELEASE);
    Movie_NewMovie(&cMovie, cTitle, MOVIE_REGULAR);

    return 1;
}
