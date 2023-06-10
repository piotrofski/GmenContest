#include "../includes/header.h"

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    size_t total_size; 
    size_t current_size;
    size_t new_size;
    t_var *var;
    
    var = (t_var*)userdata;
    printf("\nsize %ld\nnmemb: %ld\n", size, nmemb);
    total_size = size * nmemb;
    printf ("\ntotal_size: %ld\n", total_size);
    current_size = strlen(var->maze_string);
    printf("\ncurrent_size\t%ld\n", current_size);
    new_size = current_size + total_size;
    printf("\nnew_size\t%ld\n", new_size);
    var->maze_string = realloc(var->maze_string, new_size + 1);
    if (var->maze_string == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        return 0;
    }
    memcpy(var->maze_string + current_size, ptr, total_size);
    var->maze_string[new_size] = '\0';

    return total_size;
}

int getReadURL(int dimension, t_var *var, int density)
{
    CURL* curl;
    CURLcode res;
    char url[100];

    snprintf(url, sizeof(url), "https://mazing.pythonanywhere.com/imperfect/%d/%d", dimension, density);
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        var->maze_string = malloc(1);
        var->maze_string[0] = '\0';
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, var);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            free(var->maze_string);
            curl_easy_cleanup(curl);
            return 1;
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return 0;
}