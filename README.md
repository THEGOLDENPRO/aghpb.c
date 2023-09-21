<div align="center">

  # ⚫ aghpb.c 📚
  <sub>C API wrapper for the anime girls holding programming books [API](https://api.devgoldy.xyz/aghpb/v1/docs)</sub>

</div>

<div align="center">

  <img src="./assets/book_1.png" width="500px">

</div>

<br>

> **Note**
> 
> This is part of my [aghpb api](https://github.com/THEGOLDENPRO/aghpb_api) wrapper challenge where I attempt to write an api wrapper in every language possible. So yes expect spaghetti code as it will be my first time writing in these languages. Although I'm 100% open to improvements and corrections so feel free to contribute anything.
> **[Other languages I've done](https://github.com/THEGOLDENPRO/aghpb_api#-api-wrappers)**

## Install
idk, you guys are C devs you should know this, git clone the mfing repo and figure it out yourself.

I threw in a makefile template so I believe you can use that:
```sh
git clone https://github.com/THEGOLDENPRO/aghpb.c
cd aghpb.c
make
```
but make sure you have [``libcurl``](https://curl.se/libcurl/c/) installed.

This is the command I used to compile the library together with my own C program:
```sh
gcc -o file_name file_name.c aghpb.c -lcurl
```

## Examples
You can also run examples like so: 
```sh
cp ./examples/random.c ./book_generator.c
gcc -o book_generator ./book_generator.c aghpb.c -lcurl && ./book_generator
```
> *make sure to ``cd aghpb.c``*

This is how you may retrieve a random anime girl holding a programming book:
```c
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
> **Warning**
>
> The method above is currently broken. I'm struggling to fix it. 🫠 (Some help would be nice please 🙏)

Made using my API at 👉 https://api.devgoldy.xyz/aghpb/v1/