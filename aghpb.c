#include "aghpb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

struct MemoryStruct {
    char *memory;
    size_t size;
};

static void init_memory_struct(struct MemoryStruct *s) {
    s->size = 0;
    s->memory = malloc(s->size+1);
    if (s->memory == NULL) {
        fprintf(stderr, "malloc() failed\n");
        exit(EXIT_FAILURE);
    }
    s->memory[0] = '\0';
}

static size_t write_func(void *memory, size_t size_, size_t nmemb, struct MemoryStruct *s) {
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
 * Fetches a book from the URL given as input and writes it to the given file.
 * @param file The file you would like to curse with anime girls.
 * @param url The url used to fetch the book.
 * @return The programming book or NULL in case of failure.
 */
static AGHPB_Book *get_book(FILE *file, const char *url) {
    CURL *curl;
    CURLcode response;

    struct curl_header *header;
    AGHPB_Book *book = NULL;

    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

        response = curl_easy_perform(curl);

        if (response != CURLE_OK) {
            fprintf(stderr, "Request failed: %s\n", curl_easy_strerror(response));
        } else {
            book = malloc(sizeof(AGHPB_Book));

            curl_easy_header(curl, "Book-Name", 0, CURLH_HEADER, -1, &header);
            strcpy(book->name, header->value);

            curl_easy_header(curl, "Book-Category", 0, CURLH_HEADER, -1, &header);
            strcpy(book->category, header->value);

            curl_easy_header(curl, "Book-Date-Added", 0, CURLH_HEADER, -1, &header);
            strcpy(book->date_added, header->value);

            curl_easy_header(curl, "Book-Search-ID", 0, CURLH_HEADER, -1, &header);
            strcpy(book->search_id, header->value);
        }
    } else {
        fprintf(stderr, "Couldn't initialize easy curl!");
    }

    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return book;

}

/**
 * Writes a random anime girl holding a programming book to a file object.
 * @param file The file you would like to curse with anime girls.
 * @return The programming book or NULL in case of failure.
 */
AGHPB_Book *aghpb_random(FILE *file) {
    return get_book(file, "https://api.devgoldy.xyz/aghpb/v1/random");
}


/**
 * Writes a random anime girl holding a programming book of that specified category to a file object.
 * @param file The file you would like to curse with anime girls.
 * @param category The category of programming books you would like.
 * @return The programming book or NULL in case of failure.
 */
AGHPB_Book *aghpb_random_category(FILE *file, char category[]) {
    AGHPB_Book* book = NULL;

    CURL *curl = curl_easy_init();
    if(curl) {
        char* escaped_category = curl_easy_escape(curl, category, 0);
        if(escaped_category) {
            char url[2048];
            sprintf(url, "https://api.devgoldy.xyz/aghpb/v1/random?category=%s", escaped_category);
            curl_free(escaped_category);
            book = get_book(file, url);
        }
        curl_easy_cleanup(curl);
    }
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


/**
 * Retrieves a programming book indicated by the search ID and writes it to a file.
 * @param file The file you would like to curse with anime girls.
 * @param id The search ID of the programming book you would like to retrieve.
 * @return The programming book or NULL in case of failure.
 */
AGHPB_Book *aghpb_get_book(FILE *file, char id[]) {
    char url[2048];
    sprintf(url, "https://api.devgoldy.xyz/aghpb/v1/get/id/%s", id);

    return get_book(file, url);
}

/*
TODO: add search API function with the help of a JSON serializer
I found one called Parson (https://github.com/kgabis/parson) but it requires the build infrastructure for aghpb.c to change
I'm too lazy to change it now, so I'll do it later :3
*/
