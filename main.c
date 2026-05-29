#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"
#include "sorting_basic.h"
#include "sorting_advance.h"

#define MAX_INT_DATA 1000
#define MAX_WORDS 5000
#define WORD_BUFFER 128
#define PRINT_LIMIT 10

// Helper: Menahan layar agar output tidak langsung tertimpa render menu CLI
void pause_screen() {
    printf("\n[Tekan Enter untuk melanjutkan...]");
    char buf[10];
    fgets(buf, sizeof(buf), stdin);
}

// Helper: Membaca input terminal dengan aman dan membersihkan newline
int get_valid_input() {
    char buf[64];
    if (fgets(buf, sizeof(buf), stdin)) {
        int choice;
        if (sscanf(buf, "%d", &choice) == 1) {
            return choice;
        }
    }
    return -1;
}

void run_basic_sorting() {
    int choice;
    int data[MAX_INT_DATA];
    clock_t start, end;
    
    // Generate data otomatis setiap kali masuk menu
    for(int i = 0; i < MAX_INT_DATA; i++) {
        data[i] = rand() % 10000;
    }

    do {
        printf("\n=== SORTING DASAR ===\n");
        printf("1. Bubble Sort\n");
        printf("2. Insertion Sort\n");
        printf("3. Selection Sort\n");
        printf("4. Kembali\n");
        printf("Pilih metode: ");
        
        choice = get_valid_input();

        if(choice >= 1 && choice <= 3) {
            shuffle_array_int(data, MAX_INT_DATA); 
            printf("\nData sebelum sorting (%d pertama):\n", PRINT_LIMIT);
            print_array_int(data, MAX_INT_DATA, PRINT_LIMIT);

            start = clock();
            if (choice == 1) bubble_sort(data, MAX_INT_DATA);
            else if (choice == 2) insertion_sort(data, MAX_INT_DATA);
            else if (choice == 3) selection_sort(data, MAX_INT_DATA);
            end = clock();

            printf("\nData setelah sorting (%d pertama):\n", PRINT_LIMIT);
            print_array_int(data, MAX_INT_DATA, PRINT_LIMIT);
            
            printf("\n>> Waktu Eksekusi: %.3f ms <<\n", calculate_time(start, end));
            pause_screen(); // Tahan layar agar data bisa dibaca
        } else if (choice != 4) {
            printf("\n[!] Input tidak valid.\n");
        }
    } while(choice != 4);
}

void run_advance_sorting() {
    int choice;
    char *words[MAX_WORDS];
    int word_count = 0;
    char buffer[WORD_BUFFER];
    clock_t start, end;

    // Deteksi file berlapis untuk mencegah silent error
    FILE *file = fopen("dataset/words.txt", "r");
    if (!file) file = fopen("words.txt", "r"); 
    if (!file) file = fopen("../words.txt", "r");

    if (!file) {
        printf("\n[FATAL ERROR] File 'words.txt' tidak ditemukan di direktori manapun!\n");
        printf("Pindahkan file words.txt ke folder yang sama dengan binary eksekusi.\n");
        pause_screen(); // Tahan layar agar error terbaca
        return;
    }

    while (fscanf(file, "%127s", buffer) == 1 && word_count < MAX_WORDS) {
        words[word_count] = malloc(strlen(buffer) + 1);
        strcpy(words[word_count], buffer);
        word_count++;
    }
    fclose(file);

    do {
        printf("\n=== ADVANCE SORTING (Total Kata: %d) ===\n", word_count);
        printf("1. Merge Sort\n");
        printf("2. Quick Sort\n");
        printf("3. Shell Sort\n");
        printf("4. Kembali\n");
        printf("Pilih metode: ");
        
        choice = get_valid_input();

        if(choice >= 1 && choice <= 3) {
            shuffle_array_string(words, word_count); 
            printf("\nData sebelum sorting (%d pertama):\n", PRINT_LIMIT);
            print_array_string(words, word_count, PRINT_LIMIT);

            start = clock();
            if (choice == 1) merge_sort(words, 0, word_count - 1);
            else if (choice == 2) quick_sort(words, 0, word_count - 1);
            else if (choice == 3) shell_sort(words, word_count);
            end = clock();

            printf("\nData setelah sorting (%d pertama):\n", PRINT_LIMIT);
            print_array_string(words, word_count, PRINT_LIMIT);
            
            printf("\n>> Waktu Eksekusi: %.3f ms <<\n", calculate_time(start, end));
            pause_screen(); // Tahan layar agar data bisa dibaca
        } else if (choice != 4) {
            printf("\n[!] Input tidak valid.\n");
        }
    } while(choice != 4);

    // Bebaskan memori
    for(int i = 0; i < word_count; i++) {
        free(words[i]);
    }
}

int main() {
    srand(time(NULL)); 
    int menu;

    do {
        printf("\n=== MENU UTAMA ===\n");
        printf("1. Sorting Dasar\n");
        printf("2. Advance Sorting\n");
        printf("3. Keluar\n");
        printf("Pilih menu: ");
        
        menu = get_valid_input();

        switch (menu) {
            case 1: run_basic_sorting(); break;
            case 2: run_advance_sorting(); break;
            case 3: printf("\nKeluar program...\n"); break;
            default: printf("\n[!] Pilihan tidak valid.\n");
        }
    } while (menu != 3);

    return 0;
}
