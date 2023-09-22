#ifndef AGHPBLIB_H_INCLUDED
#define AGHPBLIB_H_INCLUDED

#include <stdio.h>

typedef struct Book {
    char *name;
    char *category;
    char *date_added;
} AGHPB_Book;

struct Book aghpb_random(FILE *file);
struct Book aghpb_random_category(FILE *file, char category[]);
char* aghpb_categories();

#endif // AGHPBLIB_H_INCLUDED