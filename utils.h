#ifndef UTILS_H
#define UTILS_H

#include <time.h>

void print_array_int(int arr[], int n, int limit);
void print_array_string(char **arr, int n, int limit);
void shuffle_array_int(int arr[], int n);
void shuffle_array_string(char **arr, int n);
double calculate_time(clock_t start, clock_t end);

#endif