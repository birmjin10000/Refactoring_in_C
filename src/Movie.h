#ifndef _MOVIE_H_
#define _MOVIE_H_

#define MOVIE_CHILDRENS 2
#define MOVIE_REGULAR 0
#define MOVIE_NEW_RELEASE 1

typedef struct _Movie {
    char* _title;
    int _priceCode;
} Movie;

Movie* Movie_New(char*, int); 
int Movie_GetPriceCode(Movie*);
void Movie_SetPriceCode(Movie*, int);
char* Movie_GetTitle(Movie*);

#endif // _MOVIE_H_
