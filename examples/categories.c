#include <stdio.h>
#include "aghpb.h" // import this bitch

int main() {
    char* categories = aghpb_categories();

    printf("--> %s\n", categories);

    return 0;
}