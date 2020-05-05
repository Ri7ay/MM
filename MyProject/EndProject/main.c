#include "memalloc.h"
#include <stdio.h>
#include <stdlib.h>
#define  MEMORY_SIZE 500
#define  MEMORY_SIZE_LITTLE 500
#define  MEMORY_SIZE_BIG 100000

int main (void) {
    int *mem_block[1000], block_lifetime[1000], no_memory = 0;

    for (int i = 0; i < 1000; i++) {
        block_lifetime[i] = 0;
    }

    AVAIL = calloc(MEMORY_SIZE, sizeof(int));
    end_mem = calloc( MEMORY_SIZE, sizeof(int));

    free_block[0] = calloc(MEMORY_SIZE_LITTLE, sizeof(int));
    free_block[1] = calloc(MEMORY_SIZE, sizeof(int));
    free_block[2] = calloc(MEMORY_SIZE_LITTLE, sizeof(int));
    free_block[3] = calloc(MEMORY_SIZE_BIG, sizeof(int));
    free_block[4] = calloc(MEMORY_SIZE, sizeof(int));
    free_block[5] = calloc(MEMORY_SIZE, sizeof(int));
    free_block[6] = calloc(MEMORY_SIZE_LITTLE, sizeof(int));
    free_block[7] = calloc(MEMORY_SIZE_LITTLE, sizeof(int));
    free_block[8] = calloc(MEMORY_SIZE, sizeof(int));
    free_block[9] = calloc(MEMORY_SIZE_LITTLE, sizeof(int));

    *free_block[0] = -MEMORY_SIZE_LITTLE;
    *(free_block[0] + MEMORY_SIZE_LITTLE - 1) = -MEMORY_SIZE_LITTLE;
    *((int**)(free_block[0] + 1)) = free_block[1];
    *((int**)(free_block[0] + 3)) = AVAIL;

    *free_block[1] = -MEMORY_SIZE;
    *(free_block[1] + MEMORY_SIZE - 1) = -MEMORY_SIZE;
    *((int**)(free_block[1] + 1)) = free_block[2];
    *((int**)(free_block[1] + 3)) = free_block[0];

    *free_block[2] = -MEMORY_SIZE_LITTLE;
    *(free_block[2] + MEMORY_SIZE_LITTLE - 1) = -MEMORY_SIZE_LITTLE;
    *((int**)(free_block[2] + 1)) = free_block[3];
    *((int**)(free_block[2] + 3)) = free_block[1];

    *free_block[3] = -MEMORY_SIZE_BIG;
    *(free_block[3] + MEMORY_SIZE_BIG - 1) = -MEMORY_SIZE_BIG;
    *((int**)(free_block[3] + 1)) = free_block[4];
    *((int**)(free_block[3] + 3)) = free_block[2];

    *free_block[4] = -MEMORY_SIZE;
    *(free_block[4] + MEMORY_SIZE - 1) = -MEMORY_SIZE;
    *((int**)(free_block[4] + 1)) = free_block[5];
    *((int**)(free_block[4] + 3)) = free_block[3];

    *free_block[5] = -MEMORY_SIZE;
    *(free_block[5] + MEMORY_SIZE - 1) = -MEMORY_SIZE;
    *((int**)(free_block[5] + 1)) = free_block[6];
    *((int**)(free_block[5] + 3)) = free_block[4];

    *free_block[6] = -MEMORY_SIZE_LITTLE;
    *(free_block[6] + MEMORY_SIZE_LITTLE - 1) = -MEMORY_SIZE_LITTLE;
    *((int**)(free_block[6] + 1)) = free_block[7];
    *((int**)(free_block[6] + 3)) = free_block[5];

    *free_block[7] = -MEMORY_SIZE_LITTLE;
    *(free_block[7] + MEMORY_SIZE_LITTLE - 1) = -MEMORY_SIZE_LITTLE;
    *((int**)(free_block[7] + 1)) = free_block[8];
    *((int**)(free_block[7] + 3)) = free_block[6];

    *free_block[8] = -MEMORY_SIZE;
    *(free_block[8] + MEMORY_SIZE - 1) = -MEMORY_SIZE;
    *((int**)(free_block[8] + 1)) = free_block[9];
    *((int**)(free_block[8] + 3)) = free_block[7];

    *free_block[9] = -MEMORY_SIZE_LITTLE;
    *(free_block[9] + MEMORY_SIZE_LITTLE - 1) = -MEMORY_SIZE_LITTLE;
    *((int**)(free_block[9] + 1)) = end_mem;
    *((int**)(free_block[9] + 3)) = free_block[0];

    *AVAIL = -MEMORY_SIZE;
    *(AVAIL + MEMORY_SIZE - 1) = -MEMORY_SIZE;

    *end_mem = -MEMORY_SIZE;
    *(end_mem + MEMORY_SIZE - 1) = -MEMORY_SIZE;


    *((int**)(AVAIL + 1)) = free_block[0];
    *((int**)(AVAIL + 3)) = end_mem;

    *((int**)(end_mem + 1)) = AVAIL;
    *((int**)(end_mem + 3)) = free_block[9];

    printf("AVAIL: %p\n", AVAIL);
    print_AVAIL();

    for(int i = 0; i < 500; i++) {
        printf("\nИтерация номер: %d", i + 1);
        for (int j = 0; j < 1000; j++) {
            block_lifetime[j]--;
            if (block_lifetime[j] == 0) {
                my_free(mem_block[j]);
                mem_block[j] = NULL;
            }
        }
        mem_block[i] = my_malloc(rand() % 1000 + 16);

        mem_block[i] != NULL ? (block_lifetime[i] = rand() % 2500 + 1) : (no_memory++);

        printf("\n");

        for (int j = 0; j < i+ 1; j++) {
            if (mem_block[j] != NULL) {
                printf("MEM BLOCK %d: %p / %d / %d\n", j, mem_block[j], *(mem_block[j] - 1),
                       *(mem_block[j] + *(mem_block[j] - 1) - 2));
            } else {
                printf("MEM BLOCK %d: %p\n", j, mem_block[j]);
            }
        }
        print_AVAIL();
    }
    printf("Не хватило места для %d\n", no_memory);
    return 0;
}


// Коментарии к проверке на работу malloc() и free() с помощью граничного метода

// 11 ячееек размерок 10.000 байт
// Ячейки размером от 20 до 2.500 байт
// С временем жизни от 1 до 500
// На 1000 итераций NULL выдало 481 раз
// При чем за первые 100 запросов было всего 2 NULL
// За следующие 100 было 58 NULL
// За 500 итераций было 212 NULL

// 11 ячееек размерок 10.000 байт
// Ячейки размером от 16 до 1.000 байт
// С временем жизни от 1 до 1.000 итераций
// На 1000 итераций NULL выдало 408 раз
// При чем за первые 100 запросов было всего 0 NULL
// За следующие 100 было 0 NULL
// За 500 итераций было 165 NULL

// 5 Ячеек размером 10.000 байт
// 5 Ячеек размером 1.0000 байт
// 1 ячейка размером 20.000 байт
// Ячейки размером от 16 до 3.000 байт
// С временем жизни от 1 до 2.000 итераций
// На 1000 итераций NULL выдало 863 раз
// При чем за первые 100 запросов было всего 44 NULL
// За следующие 100 было 87 NULL
// За 500 итераций было 411 NULL

// 11 ячееек размерок 20.000 байт
// Ячейки размером от 16 до 3.000 байт
// С временем жизни от 1 до 2.000 итераций
// На 1000 итераций NULL выдало 660 раз
// При чем за первые 100 запросов было всего 0 NULL
// За следующие 100 было 40 NULL
// За 500 итераций было 281 NULL

// 10 ячееек размерок 500 байт
// 1 ячейка размерок 100.000 байт
// Ячейки размером от 16 до 1.000 байт
// С временем жизни от 1 до 2.500 итераций
// На 1000 итераций NULL выдало 586 раз
// При чем за первые 100 запросов было всего 0 NULL
// За следующие 100 было 4 NULL
// За 500 итераций было 209 NULL