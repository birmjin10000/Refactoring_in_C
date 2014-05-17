#include "MovieRental.h"
#include "unity.h"

void setUp(void) {
    // This is run before EACH TEST
}

void tearDown(void) {

}

void test_Customer_Statement_Should_Be_Correct(void) {
    char result[2048];
    int byteWritten;

    char* title1 = "Frozen";
    char* title2 = "Amazing Spiderman 2";
    char* title3 = "Iron Man 1";
    char* name1 = "Scott Ahn";

    Movie* movie1 = Movie_New(title1, MOVIE_CHILDRENS);
    Movie* movie2 = Movie_New(title2, MOVIE_NEW_RELEASE);
    Movie* movie3 = Movie_New(title3, MOVIE_REGULAR);

    Rental* rental1 = Rental_New(movie1, 2);
    Rental* rental2 = Rental_New(movie2, 3);
    Rental* rental3 = Rental_New(movie3, 4);
    Customer* customer1 = Customer_New(name1);
    
    Customer_AddRental(customer1, rental1);
    Customer_AddRental(customer1, rental2);
    Customer_AddRental(customer1, rental3);

    byteWritten = Customer_Statement(customer1, result, 2048);
    printf("%s\n", result); 
 
    // All of these should pass
    TEST_ASSERT_EQUAL_STRING("Rental Record for \"Scott Ahn\"\n"
				"\t              Frozen\t1.500000\n"
				"\t Amazing Spiderman 2\t9.000000\n"
				"\t          Iron Man 1\t5.000000\n"
				"Amount owed is 15.500000\n"
			"You earned 4 frequent renter points", result);
}

