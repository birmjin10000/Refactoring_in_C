#include "MovieRental.h"
#include "unity.h"

void setUp(void) {
    // This is run before EACH TEST
}

void tearDown(void) {

}

void test_Customer_Statement_Should_Be_Correct(void) {
    Movie Movie1;
    Movie Movie2;
    Movie Movie3;
    Rental Rental1;
    Rental Rental2;
    Rental Rental3;
    Customer* pCustomer;
    char result[2048];
    int byteWritten;

    char* Title1 = "Frozen";
    char* Title2 = "Amazing Spiderman 2";
    char* Title3 = "Iron Man 1";
    char* aName = "Scott Ahn";

    Movie_New(&Movie1, Title1, MOVIE_CHILDRENS);
    Movie_New(&Movie2, Title2, MOVIE_NEW_RELEASE);
    Movie_New(&Movie3, Title3, MOVIE_REGULAR);

    Rental_New(&Rental1, &Movie1, 2);
    Rental_New(&Rental2, &Movie2, 3);
    Rental_New(&Rental3, &Movie3, 4);
    pCustomer = Customer_New(aName);
    
    Customer_AddRental(pCustomer, &Rental1);
    Customer_AddRental(pCustomer, &Rental2);
    Customer_AddRental(pCustomer, &Rental3);

    byteWritten = Customer_Statement(pCustomer, result);
    printf(result); 
 
    // All of these should pass
    TEST_ASSERT_EQUAL_STRING("Rental Record for \"Scott Ahn\"\n"
				"\t              Frozen\t1.500000\n"
				"\t Amazing Spiderman 2\t9.000000\n"
				"\t          Iron Man 1\t5.000000\n"
				"Amount owed is 15.500000\n"
			"You earned 4 frequent renter points", result);
}


