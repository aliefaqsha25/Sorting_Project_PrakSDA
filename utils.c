#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void print_array_int(int arr[], int n, int limit) {
    int count = (limit < n) ? limit : n;
    printf("[ ");
    for(int i = 0; i < count; i++) {
        printf("%d%s", arr[i], (i == count - 1) ? "" : ", ");
    }
    printf(" ... ]\n");
}

void print_array_string(char **arr, int n, int limit) {
    int count = (limit < n) ? limit : n;
    printf("[ ");
    for(int i = 0; i < count; i++) {
        printf("\"%s\"%s", arr[i], (i == count - 1) ? "" : ", ");
    }
    printf(" ... ]\n");
}

void shuffle_array_int(int arr[], int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void shuffle_array_string(char **arr, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char *temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

double calculate_time(clock_t start, clock_t end) {
    return ((double) (end - start)) / CLOCKS_PER_SEC * 1000.0;
}