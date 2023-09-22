#include "aghpb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

struct MemoryStruct {
    char *memory;
    size_t size;
};

void init_memory_struct(struct MemoryStruct *s) {
    s->size = 0;
    s->memory = malloc(s->size+1);
    if (s->memory == NULL) {
        fprintf(stderr, "malloc() failed\n");
        exit(EXIT_FAILURE);
    }
    s->memory[0] = '\0';
}

size_t write_func(void *memory, size_t size_, size_t nmemb, struct MemoryStruct *s) {
    size_t new_size = s->size + size_*nmemb;
    s->memory = realloc(s->memory, new_size+1);
    if (s->memory == NULL) {
        fprintf(stderr, "realloc() failed\n");
        exit(EXIT_FAILURE);
    }
    memcpy(s->memory+s->size, memory, size_*nmemb);
    s->memory[new_size] = '\0';
    s->size = new_size;

    return size_*nmemb;
}

/**
 * Writes a random anime girl holding a programming book to a file object.
 * @param file The file you would like to curse with anime girls.
 * @return The programming book.
 */
struct Book aghpb_random(FILE *file) {
    CURL *curl;
    CURLcode response;

    struct curl_header *header;
    struct Book book;

    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.devgoldy.xyz/aghpb/v1/random");

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

        response = curl_easy_perform(curl);

        if (response != CURLE_OK) {
            fprintf(stderr, "Request failed: %s\n", curl_easy_strerror(response));
        }

        curl_easy_header(curl, "Book-Name", 0, CURLH_HEADER, -1, &header);
        char book_name[1000];
        strcpy(book_name, header->value);

        curl_easy_header(curl, "Book-Category", 0, CURLH_HEADER, -1, &header);
        char book_category[1000];
        strcpy(book_category, header->value);

        curl_easy_header(curl, "Book-Date-Added", 0, CURLH_HEADER, -1, &header);
        char book_date_added[30];
        strcpy(book_date_added, header->value);

        book.name = book_name;
        book.category = book_category;
        book.date_added = book_date_added;
    } else {
        fprintf(stderr, "Couldn't initialize easy curl!");
    }

    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return book;
}


/**
 * Writes a random anime girl holding a programming book of that specified category to a file object.
 * @param file The file you would like to curse with anime girls.
 * @param category The category of programming books you would like.
 * @return The programming book.
 */
struct Book aghpb_random_category(FILE *file, char category[]) {
    CURL *curl;
    CURLcode response;

    struct curl_header *header;
    struct Book book;

    curl = curl_easy_init();

    if (curl) {
        char url[2048];
        char* escaped_category = curl_easy_escape(curl, category, 0);
        sprintf(url, "https://api.devgoldy.xyz/aghpb/v1/random?category=%s", escaped_category);
        curl_free(escaped_category);

        curl_easy_setopt(curl, CURLOPT_URL, url);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

        response = curl_easy_perform(curl);

        if (response != CURLE_OK) {
            fprintf(stderr, "Request failed: %s\n", curl_easy_strerror(response));
        }

        curl_easy_header(curl, "Book-Name", 0, CURLH_HEADER, -1, &header);
        char book_name[1000];
        strcpy(book_name, header->value);

        curl_easy_header(curl, "Book-Category", 0, CURLH_HEADER, -1, &header);
        char book_category[1000];
        strcpy(book_category, header->value);

        curl_easy_header(curl, "Book-Date-Added", 0, CURLH_HEADER, -1, &header);
        char book_date_added[30];
        strcpy(book_date_added, header->value);

        book.name = book_name;
        book.category = book_category;
        book.date_added = book_date_added;

        //curl_free(url);
    } else {
        fprintf(stderr, "Couldn't initialize easy curl!");
    }

    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return book;
}


/**
 * Returns a string of a json array of available categories.
 * @return String of a json array.
 */
char* aghpb_categories() {
    CURL *curl;
    CURLcode response;

    struct MemoryStruct memory_struct;
    init_memory_struct(&memory_struct);

    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.devgoldy.xyz/aghpb/v1/categories");

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_func);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &memory_struct);

        response = curl_easy_perform(curl);

        if (response != CURLE_OK) {
            fprintf(stderr, "Request failed: %s\n", curl_easy_strerror(response));
        }

    } else {
        fprintf(stderr, "Couldn't initialize easy curl!");
    }

    char *categories = memory_struct.memory;

    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return categories;
}