#include <stdlib.h>
#include <stdio.h>
#include "aghpb.h" // import this "bitch", according to Goldy

int main() {
    // Create a file to store this programming book.
    FILE *file = fopen("./anime_girl.png", "w");

    // Once we pass file into get_book the function *should... just maybe...* write to it. 
    AGHPB_Book *book = aghpb_get_book(file, "151");

    printf("Search ID: %s\n", book->search_id);
    printf("Name: %s\n", book->name);
    printf("Category: %s\n", book->category);
    printf("Date Added: %s\n", book->date_added);

    free(book);
    fclose(file);
    // Hurry! Now you should have a picture of an anime girl holding a programming book (goldy originally went insane writing this code, but I'm already insane!!!)

    return 0;
}
