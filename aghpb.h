#ifndef AGHPBLIB_H_INCLUDED
#define AGHPBLIB_H_INCLUDED

#include <stdio.h>

typedef struct {
    char search_id[10];
    char name[1000];
    char category[1000];
    char date_added[30];
} AGHPB_Book;

AGHPB_Book *aghpb_random(FILE *file);
AGHPB_Book *aghpb_random_category(FILE *file, char category[]);
char *aghpb_categories();
AGHPB_Book *aghpb_get_book(FILE *file, char id[]);

#endif // AGHPBLIB_H_INCLUDED
