<div align="center">

  # ⚫ aghpb.c 📚
  <sub>C API wrapper for the anime girls holding programming books [API](https://api.devgoldy.xyz/aghpb/v1/docs)</sub>

</div>

<div align="center">

  <img src="./assets/book_1.png" width="500px">

</div>

<br>

> [!Note]
> 
> This is part of my [aghpb api](https://github.com/THEGOLDENPRO/aghpb_api) wrapper challenge where I attempt to write an api wrapper in every language possible. So yes expect spaghetti code as it will be my first time writing in these languages. Although I'm 100% open to improvements and corrections so feel free to contribute anything.
> **[Other languages I've done](https://github.com/THEGOLDENPRO/aghpb_api#-api-wrappers)**

## Install
The `Makefile` compiles the code into a shared library called `libaghpb.so` that can be used in your code.
```sh
git clone https://github.com/THEGOLDENPRO/aghpb.c
cd aghpb.c
make
```
Make sure you have [``libcurl``](https://curl.se/libcurl/c/) installed first.

Use this command to compile the library together with your own C program:
```sh
gcc -o file_name file_name.c -L . -I . -laghpb
```
This is assuming `aghpb.h` & `libaghpb.so` are in the same folder as your main program.

## Examples
You can also run examples like so: 
```sh
cp ./examples/random.c ./book_generator.c
gcc -o book_generator ./book_generator.c -L . -I . -laghpb && ./book_generator
```

This is how you may retrieve a random anime girl holding a programming book:
```c
#include <stdio.h>
#include "aghpb.h" // import this bitch

int main() {
    // Create a file to store this mfing programming book.
    FILE *file = fopen("./anime_girl.png", "w");

    // Once we pass file into random the function *should... just maybe...* write to it. 
    // (There's possibly a slight change of it blowing up.)
    AGHPB_Book book* = aghpb_random(file);

    printf("Name: %s\n", book->name);
    printf("Category: %s\n", book->category);
    printf("Date Added: %s\n", book->date_added);

    free(book);
    fclose(file);
    // Hurry! Now you should have a picture of an anime girl holding a programming book (please kill me it's 1AM rn and I'M GOING INSANE FROM WRITING C CODE!!! AHHHHHHHHHHH)

    return 0;
}
```
You can also retrieve specific categories of anime girls holding programming books like so:
```c
AGHPB_Book book = aghpb_random_category(file, "c");
```

<br>

This is how you may retrieve a list of available categories:
```c
#include <stdio.h>
#include "aghpb.h" // import this bitch

int main() {
    char* categories = aghpb_categories();

    printf("--> %s", categories);

    return 0;
}
```

Made using my API at 👉 https://api.devgoldy.xyz/aghpb/v1/
