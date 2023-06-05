#include "../includes/header.h"

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    size_t total_size; 
    t_var *var;
    
    var = (t_var*)userdata;
    total_size = size * nmemb;
    var->maze_string = malloc(sizeof(char) * (total_size + 1));
    memcpy(var->maze_string, ptr, total_size);
    var->maze_string[total_size] = '\0';  // Ensure null-termination
    return total_size;
}

int getReadURL(int dimension, t_var *var)
{
    CURL* curl;
    CURLcode res;
    char url[100];

    snprintf(url, sizeof(url), "https://mazing.pythonanywhere.com/%d", dimension);
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

void    splitting(t_var *var)
{
    int i;
    
    i = 0;
    var->num_lines = 0;
    while (var->maze_string[i] != '\0')
    {
        if (var->maze_string[i] == '\n')
            var->num_lines++;
        i++;
    }
    var->num_lines++;
    printf("\nnum_lines = %d", var->num_lines);
    var->maze_map = ft_split(var->maze_string, "\n");        
    i = -1;
    printf("\n");
    while (++i < var->num_lines)
        printf("\nvar->maze_map[%d]\t:\t%s", i, var->maze_map[i]);
    return ;
}

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        clock_t start_time;
        clock_t end_time;
        double execution_time;
        int dimension = atoi(argv[1]);
        t_var var;
    
        start_time = clock();
        dimension = (dimension < 0) ? -dimension : dimension; //args error check
        if (getReadURL(dimension, &var) == 1) //writes in the terminal & in the maze_file
            return (0);
        end_time = clock();
        printf("\n%s\n", var.maze_string);
        splitting(&var);
        execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        printf("\nExecution time: %.4f seconds\n", execution_time);
    }
    else
        printf("Please write the dimension of the maze such as: ./a.out X\n");
    return (0);
}
