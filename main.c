#include "header.h"

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    size_t total_size; 
    int* fd = (int*)userdata;

    total_size = size * nmemb;
    write(*fd, ptr, total_size);
    fwrite(ptr, size, nmemb, stdout);
    return (total_size);
}

int getReadURL(int dimension)
{
    CURL* curl;
    CURLcode res;
    char url[100];
    int fd;

    snprintf(url, sizeof(url), "https://mazing.pythonanywhere.com/%d", dimension);
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        fd = open("maze_file", O_CREAT | O_RDWR | O_TRUNC, S_IRWXU | S_IRWXO | S_IRWXG);
        if (fd == -1)
        {
            fprintf(stderr, "Failed to open the file\n");
            close(fd);
            return 1;
        }
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &fd);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            close(fd);
            return 1;
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    close(fd);
    return 0;
}

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        int dimension = atoi(argv[1]);
        dimension = (dimension < 0) ? -dimension : dimension; //args error check
        if (getReadURL(dimension) == 1) //writes in the terminal & in the maze_file
            return (0);
    }
    else
        printf("Please write the dimension of the maze such as: ./a.out X\n");
    return (0);
}
