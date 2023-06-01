#ifndef HEADER_H
# define HEADER_H

#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);
int getReadURL(int dimension);


#endif