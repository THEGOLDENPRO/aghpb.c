#include <stdio.h>
#include "aghpb.h" // import this bitch

int main() {
    // Create a file to store this mfing programming book.
    FILE *file = fopen("./anime_girl.png", "w");

    // Once we pass file into random the function *should... just maybe...* write to it. 
    // (There's possibly a slight change of it blowing up.)
    AGHPB_Book book = aghpb_random(file);

    printf("Name: %s\n", book.name);
    printf("Category: %s\n", book.category);
    printf("Date Added: %s\n", book.date_added);

    fclose(file);
    // Hurry! Now you should have a picture of an anime girl holding a programming book (please kill me it's 1AM rn and I'M GOING INSANE FROM WRITING C CODE!!! AHHHHHHHHHHH)

    return 0;
}