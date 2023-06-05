#ifndef HEADER_H
# define HEADER_H

#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

typedef struct s_var
{
    char *maze_string;
    char **maze_map;
    int num_lines;
} t_var;

char **ft_split(char *str, char *charset);
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);
int getReadURL(int dimension, t_var *var);

#endif