#ifndef HEADER_H
# define HEADER_H

#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>

typedef struct s_var
{
    char *maze_string;
    char **maze_map;
    int num_lines;
} t_var;

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);
char	**ft_split(char const *s, char c);
int     getReadURL(int dimension, t_var *var, int density);

#endif