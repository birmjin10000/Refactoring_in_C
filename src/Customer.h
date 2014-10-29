#ifndef _CUSTOMER_H_
#define _CUSTOMER_H_

#include "list/List.h"
#include "Rental.h"

typedef struct _Customer {
    char* _name;
    List _rentals;		
} Customer; 

Customer* Customer_New(char*); 
void Customer_AddRental(Customer*, Rental*); 
int Customer_Statement(Customer*, char*, unsigned int);

#endif // _CUSTOMER_H_
