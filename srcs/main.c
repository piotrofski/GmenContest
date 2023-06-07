#include "../includes/header.h"

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    size_t total_size; 
    t_var *var;
    
    var = (t_var*)userdata;
    total_size = size * nmemb;
    free(var->maze_string);
    var->maze_string = malloc(sizeof(char) * (total_size + 1));
    memcpy(var->maze_string, ptr, total_size);
    var->maze_string[total_size] = '\0';  
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
    printf("\n");
    return ;
}

void update_map(t_var *var, int i, int j)
{
    int count_obs;

    count_obs = 0;
    if (var->maze_map[i][j] == '5')
        return ;
    if (j != var->num_lines)
    {
        if (var->maze_map[i][j + 1] == '#')
            count_obs++;
    }
    if (j != 0)
    {
        if (var->maze_map[i][j - 1] == '#' && j != 0)
            count_obs++;
    }
    if (i != var->num_lines)
    {
        if (var->maze_map[i + 1][j] == '#' && i != var->num_lines)
            count_obs++;
    }
    if (i != 0)
    {
        if (var->maze_map[i - 1][j] == '#'&& i != 0)
            count_obs++;
    }
    var->maze_map[i][j] = (4 - count_obs) + '0';
    return ;
}

void tr_map(t_var *var)
{
    int i;
    int j;

    i = -1;
    while (++i < var->num_lines)
        printf("\nvar->maze_map[%d]\t:\t%s", i, var->maze_map[i]);
    i = 1;
    j = 1;
    while (i < var->num_lines - 1)
    {
        j = 1;
        while (j < var->num_lines - 1)
        {
            if (var->maze_map[i][j] != '#')
                update_map(var, i, j);
            j++;
        }
        i++;
    }
    var->maze_map[var->num_lines - 2][1] = '5';
    var->maze_map[1][var->num_lines - 2] = '5';
    printf("\n\ntranslated\n");
    i = -1;
    while (++i < var->num_lines)
        printf("\nvar->maze_map[%d]\t:\t%s", i, var->maze_map[i]);
    return ;
}

void    print_solution(t_var *var)
{
    int i;
    int j;
    int index;
    
    i = -1;
    j = 0;
    index = 0;
    printf("\n\ntranslated solution\n");
    while (++i < var->num_lines)
        printf("\nvar->maze_map[%d]\t:\t%s", i, var->maze_map[i]);
    i = -1;
    printf("\n\nfinal solution\n");
    i = 0;
    while (i < var->num_lines)
    {
        j = 0;
        while (j < var->num_lines)
        {
            if (var->maze_map[i][j] == '2' || var->maze_map[i][j] == '5')
            {
                index = (i * (var->num_lines + 1)) + j;
                var->maze_string[index] = 'O';
            }                
            j++;
        }
        i++;
    }
    printf("\n%s\n", var->maze_string);
    return ;
}

void    resolve(t_var *var)
{
    int i;
    int j;
    int flag;

    i = 1;
    j = 1;
    flag = 0;
    while (flag != 1)
    {
        flag = 1;
        i = 1;
        while (i < var->num_lines - 1)
        {
            j = 1;
            while (j < var->num_lines - 1)
            {
                if ((var->maze_map[i][j] != '#') && (var->maze_map[i][j] != '5'))
                {
                    if (var->maze_map[i][j] == '1')
                    {
                        var->maze_map[i][j] = '#';
                        if (var->maze_map[i][j + 1] != '#') 
                            update_map(var, i, j + 1);
                        else if (var->maze_map[i][j - 1] != '#') 
                            update_map(var, i, j - 1);
                        else if (var->maze_map[i + 1][j] != '#') 
                            update_map(var, i + 1, j);
                        else if (var->maze_map[i - 1][j] != '#') 
                            update_map(var, i - 1, j);
                    }
                    if (var->maze_map[i][j] != '2' && var->maze_map[i][j] != '5')
                        flag = 0;
                }
                j++;
            }
            i++;
        }
    }
    return ;
}

int main(int argc, char **argv)
{
    if (argc == 3)
    {
        clock_t start_time;
        clock_t end_time;
        double execution_time;
        int dimension = atoi(argv[1]);
        int density = atoi(argv[2]);
        t_var var;
    
        start_time = clock();
        dimension = (dimension < 0) ? -dimension : dimension; //args error check

        if (getReadURL(dimension, &var, density) == 1) //writes in the terminal & in the maze_file
            return (0);
        printf("\n%s\n", var.maze_string);
        splitting(&var);
        tr_map(&var);
        resolve(&var);
        print_solution(&var);
        end_time = clock();
        execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        printf("\nExecution time: %.4f seconds\n", execution_time);
    }
    else
        printf("Please write the dimension(positive integer) and density(float between 0 and 1) of the maze such as: ./a.out X X\n");
    return (0);
}
