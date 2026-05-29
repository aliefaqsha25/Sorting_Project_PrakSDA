#include <string.h>
#include <stdlib.h>
#include "sorting_advance.h"

void shell_sort(char **arr, int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            char *temp = arr[i];
            int j;
            for (j = i; j >= gap && strcmp(arr[j - gap], temp) > 0; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

static void merge(char **arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    
    char **L = malloc(n1 * sizeof(char *));
    char **R = malloc(n2 * sizeof(char *));
    
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (strcmp(L[i], R[j]) <= 0) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    
    free(L);
    free(R);
}

void merge_sort(char **arr, int left, int right) {
    if (left < right) {
        int m = left + (right - left) / 2;
        merge_sort(arr, left, m);
        merge_sort(arr, m + 1, right);
        merge(arr, left, m, right);
    }
}

static int partition(char **arr, int low, int high) {
    char *pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (strcmp(arr[j], pivot) < 0) {
            i++;
            char *temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    char *temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quick_sort(char **arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}
