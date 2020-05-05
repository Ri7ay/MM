#include "memalloc.h"
#include <stdio.h>
#include <stdlib.h>
#define  MEMORY_SIZE 10000

int main (void) {
    int *a, *b, *c, *d, *mem_block[1000], block_lifetime[1000], no_memory = 0;

    for (int i = 0; i < 1000; i++) {
        block_lifetime[i] = 0;
    }

    AVAIL = calloc(4 * MEMORY_SIZE, sizeof(int));
    end_mem = calloc(4 * MEMORY_SIZE, sizeof(int));

    for (int i = 0; i < 10; i++) {
        // Создаю свободные ячейки
        free_block[i] = calloc(MEMORY_SIZE, sizeof(int));
    }

    *free_block[0] = -MEMORY_SIZE;
    *(free_block[0] + MEMORY_SIZE - 4) = -MEMORY_SIZE;
    *((int**)(free_block[0] + 4)) = free_block[1];
    *((int**)(free_block[0] + 12)) = AVAIL;


    *free_block[1] = -MEMORY_SIZE;
    *(free_block[1] + MEMORY_SIZE - 4) = -MEMORY_SIZE;
    *((int**)(free_block[1] + 4)) = free_block[2];
    *((int**)(free_block[1] + 12)) = free_block[0];

    *free_block[2] = -MEMORY_SIZE;
    *(free_block[2] + MEMORY_SIZE - 4) = -MEMORY_SIZE;
    *((int**)(free_block[2] + 4)) = free_block[3];
    *((int**)(free_block[2] + 12)) = free_block[1];

    *free_block[3] = -MEMORY_SIZE;
    *(free_block[3] + MEMORY_SIZE - 4) = -MEMORY_SIZE;
    *((int**)(free_block[3] + 4)) = free_block[4];
    *((int**)(free_block[3] + 12)) = free_block[2];

    *free_block[4] = -MEMORY_SIZE;
    *(free_block[4] + MEMORY_SIZE - 4) = -MEMORY_SIZE;
    *((int**)(free_block[4] + 4)) = free_block[5];
    *((int**)(free_block[4] + 12)) = free_block[3];

    *free_block[5] = -MEMORY_SIZE;
    *(free_block[5] + MEMORY_SIZE - 4) = -MEMORY_SIZE;
    *((int**)(free_block[5] + 4)) = free_block[6];
    *((int**)(free_block[5] + 12)) = free_block[4];

    *free_block[6] = -MEMORY_SIZE;
    *(free_block[6] + MEMORY_SIZE - 4) = -MEMORY_SIZE;
    *((int**)(free_block[6] + 4)) = free_block[7];
    *((int**)(free_block[6] + 12)) = free_block[5];

    *free_block[7] = -MEMORY_SIZE;
    *(free_block[7] + MEMORY_SIZE - 4) = -MEMORY_SIZE;
    *((int**)(free_block[7] + 4)) = free_block[8];
    *((int**)(free_block[7] + 12)) = free_block[6];

    *free_block[8] = -MEMORY_SIZE;
    *(free_block[8] + MEMORY_SIZE - 4) = -MEMORY_SIZE;
    *((int**)(free_block[8] + 4)) = free_block[9];
    *((int**)(free_block[8] + 12)) = free_block[7];

    *free_block[9] = -MEMORY_SIZE;
    *(free_block[9] + MEMORY_SIZE - 4) = -MEMORY_SIZE;
    *((int**)(free_block[9] + 4)) = end_mem;
    *((int**)(free_block[9] + 12)) = free_block[0];

    *AVAIL = -MEMORY_SIZE;
    *(AVAIL + MEMORY_SIZE - 4) = -MEMORY_SIZE;

    *end_mem = -MEMORY_SIZE;
    *(end_mem + MEMORY_SIZE - 4) = -MEMORY_SIZE;


    *((int**)(AVAIL + 4)) = free_block[0];
    *((int**)(AVAIL + 12)) = end_mem;

    *((int**)(end_mem + 4)) = AVAIL;
    *((int**)(end_mem + 12)) = free_block[9];


    printf("AVAIL: %p\n", AVAIL);
    print_AVAIL();
    /*
    a = my_malloc(980);
    b = my_malloc(392);
    c = my_malloc(102);
    d = my_malloc(202);

    printf("\n");
    if (a != NULL) {
        printf("a: %p / %d / %d\n", a, *(a - 4), *(a + *(a - 4) - 8));
    } else {
        printf("a: %p\n", a);
    }
    if (b != NULL) {
        printf("b: %p / %d / %d\n", b, *(b - 4), *(b + *(b - 4) - 8));
    } else {
        printf("b: %p\n", b);
    }
    if (c != NULL) {
        printf("c: %p / %d / %d\n", c, *(c - 4), *(c + *(c - 4) - 8));
    } else {
        printf("c: %p\n", c);
    }
    if (d != NULL) {
        printf("d: %p / %d / %d\n", d, *(d - 4), *(d + *(d - 4) - 8));
    } else {
        printf("d: %p\n", d);
    }
    printf("\n");

    print_AVAIL();
    my_free(b);
    print_AVAIL();
    my_free(a);
    print_AVAIL();
    my_free(c);
    print_AVAIL();
    my_free(d);
    print_AVAIL();

    printf("\nTESTS:");
    */
    for(int i = 0; i < 1000; i++) {
        printf("\nИтерация номер: %d", i + 1);
        for (int j = 0; j < 1000; j++) {
            block_lifetime[j]--;
            if (block_lifetime[j] == 0) {
                my_free(mem_block[j]);
                mem_block[j] = NULL;
            }
        }
        mem_block[i] = my_malloc(rand() % 2500 + 20);
        //mem_block[i] = my_malloc();

        if (mem_block[i] != NULL) {
            //block_lifetime[i] = 10;
            block_lifetime[i] = rand() % 1000;
        } else {
            no_memory++;
        }

        printf("\n");

        for (int j = 0; j < i + 1; j++) {
            if (mem_block[j] != NULL) {
                printf("MEM BLOCK %d: %p / %d / %d\n", j, mem_block[j], *(mem_block[j] - 4),
                       *(mem_block[j] + *(mem_block[j] - 4) - 8));
            } else {
                printf("MEM BLOCK %d: %p\n", j, mem_block[j]);
            }
        }
        print_AVAIL();
    }
    printf("Не хватило места для %d\n", no_memory);
    return 0;
}

/*
int main (void) {
    int *a, *b, *c;

    AVAIL = calloc(MEMORY_SIZE, sizeof(int));
    end_mem = calloc(MEMORY_SIZE, sizeof(int));

    *AVAIL = -MEMORY_SIZE;
    *(AVAIL + MEMORY_SIZE - 4) = -MEMORY_SIZE;
    *((int**)(AVAIL + 4)) = end_mem;
    *((int**)(AVAIL + 12)) = end_mem;

    *end_mem = -MEMORY_SIZE;
    *(end_mem + MEMORY_SIZE - 4) = -MEMORY_SIZE;
    *((int**)(end_mem + 4)) = AVAIL;
    *((int**)(end_mem + 12)) = AVAIL;


    printf("AVAIL: %p\n", AVAIL);
    print_AVAIL();
    printf("\n");

    a = my_malloc(9980);
    b = my_malloc(1920);
    c = my_malloc(920);

    printf("\n");

    if (a != NULL) {
        printf("a: %p / %d / %d\n", a, *(a - 4), *(a + *(a - 4) - 8));
    } else {
        printf("a: %p\n", a);
    }
    if (b != NULL) {
        printf("b: %p / %d / %d\n", b, *(b - 4), *(b + *(b - 4) - 8));
    } else {
        printf("b: %p\n", b);
    }
    if (c != NULL) {
        printf("c: %p / %d / %d\n", c, *(c - 4), *(c + *(c - 4) - 8));
    } else {
        printf("c: %p\n", c);
    }

    printf("\n");

    print_AVAIL();
    my_free(a);
    print_AVAIL();
    //my_free(a);
    //print_AVAIL();
    //my_free(c);
    //print_AVAIL();

    return 0;
}
*/