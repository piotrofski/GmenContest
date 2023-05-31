#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

size_t write_callback(char* ptr, size_t size, size_t nmemb, void* userdata)
{
    size_t total_size = size * nmemb;
    int* fd = (int*)userdata;
    write(*fd, ptr, total_size);
    return total_size;
}

int main()
{
    CURL* curl;
    CURLcode res;
    int fd;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "https://mazing.pythonanywhere.com/10");
        fd = open("maze_file", O_CREAT | O_RDWR | O_TRUNC, S_IRWXU | S_IRWXO | S_IRWXG);
        if (fd == -1)
        {
            fprintf(stderr, "Failed to open the file\n");
            return 1;
        }

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &fd);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        curl_easy_cleanup(curl);
        close(fd);
    }

    curl_global_cleanup();
    return 0;
}
