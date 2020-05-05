#include "memalloc.h"
#include <stdio.h>
#include <stdlib.h>
#define  MEMORY_SIZE 1000

int *AVAIL, *memory_block_1, *memory_block_2, *memory_block_3, *end_mem;

void print_AVAIL() {
    // Указатель на первую свободную ячейку
    int *pointer = *((int**)end_mem + 4);
    // Вывожу свободные ячейки
    for (int index = 1; pointer != end_mem  && index < 10; index++, pointer = *((int**)pointer + 4)) {
        // Порядок ячейки, указатель на нее и размер
        printf("%i: %p / %d / %d\n", index,  pointer, *pointer, *(pointer - *pointer - 4));
    }
}

void *my_malloc(size_t size) {
    // Увеличиваем размер с учетом блоков с информацией
    size += 8;
    int *tmp_AVAIL = *((int**)end_mem + 4);
    int **Q = &(*((int**)tmp_AVAIL + 12)), *pointer = *((int**)(*Q) + 4);
    // Иду по свободным ячейкам, пока не дойду до конца
    while (pointer != end_mem) {
        //printf("%p\n", AVAIL);
        int pointer_size = -(*pointer);
        // Если ячейка больше либо равна нужному размеру, то берем ее
        if (pointer_size >= size) {
            int *L;
            size_t K = -(*pointer) - size;
            // Реализация шага А4'
            if (K <= 10) {
                printf("TEST1\n");
                // 1)Если размер ячейки чуть больше нужного
                L = pointer;
                // Помечаем ячейку как занятую
                *L = pointer_size; // Сохранаю информацию о размере в начало
                *(L + pointer_size - 4) = pointer_size; // Сохранаю информацию о размере в конец
                int *pointer_first = *((int**)pointer + 4), *pointer_second = *((int**)pointer + 12);
                *((int**)pointer_first + 12) = pointer_second;
                *((int**)pointer_second + 4) = pointer_first;
            }
            else {
                printf("TEST2\n");
                // 2)Если размер ячейки больше нужного нам размера
                *pointer = -K;
                *((pointer + K - 4)) = -K;
                L = pointer + K;
                // Помечаем ячейку как занятую
                *L = size; // Сохранаю информацию о размере в начало
                *(L + size - 4) = size; // Сохранаю информацию о размере в конец
            }
            return L + 4;
        }
        // Если размер ячейки не подошел
        Q = &pointer;
        pointer = *((int**)pointer + 4);
    }
    printf("TEST3\n");
    return NULL;
}

void my_free(void* ptr) {
    // Перемащаю указатель на начало
    int zero = 0,*pointer_zero = (int*)ptr - 4, *pointer_left = &zero, *pointer_right = &zero;
    *pointer_zero = -*pointer_zero;
    *(pointer_zero - *pointer_zero - 4) = *pointer_zero;
    // Свободна ли левая ячейка
    if (*(pointer_zero - 4) < 0) {
        pointer_left = pointer_zero + *(pointer_zero - 4);
    }
    // Свободна ли правая ячейка
    if (*(pointer_zero - *pointer_zero) < 0) {
        pointer_right = pointer_zero - *pointer_zero;
    }
    if (*pointer_left < 0 && *pointer_right == 0) {
        // Если свободна левая, а правая занята
        *(pointer_zero - *pointer_zero - 4) += *pointer_left;
        *pointer_left = *(pointer_zero - *pointer_zero - 4);
        return;
    } else if (*pointer_left == 0 && *pointer_right < 0) {
        // Если свободна правая, а левая занаята
        int *before_right = *((int**)pointer_right + 12);
        //Изменяю размер ячеек
        *(pointer_right - *pointer_right - 4) += *pointer_zero;
        *pointer_zero = *(pointer_right - *pointer_right - 4);
        // Изменяю указатели
        *((int**)pointer_zero + 4) = *((int**)pointer_right + 4);
        *((int**)pointer_zero + 12) = *((int**)pointer_right + 12);
        *((int**)before_right + 4) = pointer_zero;
        return;
    } else if (*pointer_left < 0 && *pointer_right < 0) {
        // Если свободна левая и правая
        int *pointer_first = *((int**)pointer_right + 4), *pointer_second = *((int**)pointer_right + 12);
        //*before_right = *((int**)pointer_right + 12);
        // Удаляю правую ячейку из свободных
        *((int**)pointer_first + 12) = pointer_second;
        *((int**)pointer_second + 4) = pointer_first;
        // Изменяю размер и указатели
        *pointer_zero += *pointer_right;
        *(pointer_zero - *pointer_zero - 4) = *pointer_left + *pointer_zero;
        *pointer_left = *(pointer_zero - *pointer_zero - 4);
        //*((int**)before_right + 4) = pointer_left;
        return;
        //pointer = pointer - *pointer;
    } else {
        // Если обе заняты
        int *tmp_AVAIL = *((int**)end_mem + 4);
        if (end_mem == *((int**)tmp_AVAIL + 4)) {
            // Если только 1 свободная ячейка
            *((int**)end_mem + 4) = pointer_zero;
            *((int**)tmp_AVAIL + 12) = pointer_zero;
            *((int**)pointer_zero + 4) = tmp_AVAIL;
            *((int**)pointer_zero + 12) = end_mem;
            return;
        } else {
            // Добавляю новую ячейку к свободным
            *((int**) pointer_zero + 4) = tmp_AVAIL;
            *((int**) pointer_zero + 12) = *((int**)tmp_AVAIL + 12);
            int *before_AVAIL = *((int**) tmp_AVAIL + 12);
            *((int**) tmp_AVAIL + 12) = pointer_zero;
            *((int**)before_AVAIL + 4) = pointer_zero;
            //AVAIL = pointer_zero;
            return;
        }
    }

}

int main (void) {
    int *a, *b, *c, *d;
    AVAIL = calloc(MEMORY_SIZE, 1);
    end_mem = calloc(MEMORY_SIZE, 1);
    memory_block_1 = calloc(MEMORY_SIZE, 1);
    memory_block_2 = calloc(MEMORY_SIZE, 1);
    memory_block_3 = calloc(MEMORY_SIZE, 1);

    *AVAIL = -MEMORY_SIZE;
    *(AVAIL + MEMORY_SIZE - 4) = -MEMORY_SIZE;

    *end_mem = -MEMORY_SIZE;
    *(end_mem + MEMORY_SIZE - 4) = -MEMORY_SIZE;


    *((int**)AVAIL + 4) = memory_block_1;
    *((int**)AVAIL + 12) = end_mem;

    *((int**)end_mem + 4) = AVAIL;
    *((int**)end_mem + 12) = memory_block_3;

    //memory_block_1 = calloc(MEMORY_SIZE, 1);
    *memory_block_1 = -MEMORY_SIZE;
    *(memory_block_1 + MEMORY_SIZE - 4) = -MEMORY_SIZE;
    *((int**)memory_block_1 + 4) = memory_block_2;
    *((int**)memory_block_1 + 12) = AVAIL;

    //memory_block_2 = calloc(MEMORY_SIZE, 1);
    *memory_block_2 = -MEMORY_SIZE;
    *(memory_block_2 + MEMORY_SIZE - 4) = -MEMORY_SIZE;
    *((int**)memory_block_2 + 4) = memory_block_3;
    *((int**)memory_block_2 + 12) = memory_block_1;

    //memory_block_3 = calloc(MEMORY_SIZE, 1);
    *memory_block_3 = -MEMORY_SIZE;
    *(memory_block_3 + MEMORY_SIZE - 4) = -MEMORY_SIZE;
    *((int**)memory_block_3 + 4) = end_mem;
    *((int**)memory_block_3 + 12) = memory_block_2;

    printf("AVAIL: %p\n", AVAIL);
    //print_AVAIL();
    printf("\n");

    a = my_malloc(992);
    b = my_malloc(992);
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
    return 0;
}

/*
int main (void) {
    int *a, *b, *c;

    AVAIL = calloc(MEMORY_SIZE, 1);
    end_mem = calloc(MEMORY_SIZE, 1);

    *AVAIL = -MEMORY_SIZE;
    *(AVAIL + MEMORY_SIZE - 4) = -MEMORY_SIZE;
    *((int**)AVAIL + 4) = end_mem;
    *((int**)AVAIL + 12) = end_mem;

    *end_mem = -MEMORY_SIZE;
    *(end_mem + MEMORY_SIZE - 4) = -MEMORY_SIZE;
    *((int**)end_mem + 4) = AVAIL;
    *((int**)end_mem + 12) = AVAIL;


    printf("AVAIL: %p\n", AVAIL);
    print_AVAIL();
    printf("\n");

    a = my_malloc(692);
    b = my_malloc(192);
    c = my_malloc(92);

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
    my_free(c);
    print_AVAIL();
    my_free(b);
    print_AVAIL();
    my_free(a);
    print_AVAIL();

    return 0;
}
*/