//
// Created by Захар Захаров on 24.10.2019.
//

#include "memalloc.h"


void delete_free_block(int* pointer) {
    int *pointer_first = *((int**)(pointer + 4)), *pointer_second = *((int**)(pointer + 12));
    *((int**)(pointer_first + 12)) = pointer_second;
    *((int**)(pointer_second + 4)) = pointer_first;
}

void print_AVAIL() {
    // Указатель на первую свободную ячейку
    int *pointer = *((int**)(end_mem + 4));
    // Вывожу свободные ячейки
    printf("\n");

    for (int index = 1; pointer != end_mem; index++, pointer = *((int**)(pointer + 4))) {
        // Порядок ячейки, указатель на нее и размер
        printf("%i: %p / %d / %d\n", index, pointer, *pointer, *(pointer - *pointer - 4));

    }
}

void *my_malloc(size_t size) {
    // Увеличиваем размер с учетом блоков с информацией
    size += 8;
    //int *tmp_AVAIL = *((int**)(end_mem + 4));
    int **Q = &end_mem, *pointer = *((int**)(end_mem + 4));
    //int **Q = &(*((int**)tmp_AVAIL + 12)), *pointer = *((int**)(*Q) + 4);
    // Иду по свободным ячейкам, пока не дойду до конца
    while (pointer != end_mem) {
        //printf("%p\n", AVAIL);
        int pointer_size = -(*pointer);
        // Если ячейка больше либо равна нужному размеру, то берем ее
        if (pointer_size >= size && pointer_size > 0) {
            int *L;
            size_t K = -(*pointer) - size;
            // Реализация шага А4'
            if (K <= 26) {
                printf(" TEST1\n");
                // 1)Если размер ячейки чуть больше нужного
                L = pointer;
                // Помечаем ячейку как занятую
                *L = pointer_size; // Сохранаю информацию о размере в начало
                *(L + pointer_size - 4) = pointer_size; // Сохранаю информацию о размере в конец
                delete_free_block(pointer); //Удаляю ячейку из свободных
            }
            else {
                printf(" TEST2\n");
                // 2)Если размер ячейки больше нужного нам размера
                *pointer = -K;
                *(pointer + K - 4) = -K;
                L = pointer + K;
                // Помечаем ячейку как занятую
                *L = size; // Сохранаю информацию о размере в начало
                *(L + size - 4) = size; // Сохранаю информацию о размере в конец
            }
            return L + 4;
        }
        // Если размер ячейки не подошел
        Q = &pointer;
        pointer = *((int**)(pointer + 4));
    }
    printf(" TEST3\n");
    return NULL;
}

void my_free(void* ptr) {
    // Перемащаю указатель на начало
    int zero = 0, *pointer_zero = (int*)ptr - 4, *pointer_left = &zero, *pointer_right = &zero;
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
        printf(" TEST1 FREEEEEE\n");
        // Если свободна левая, а правая занята
        *(pointer_zero - *pointer_zero - 4) += *pointer_left;
        *pointer_left = *(pointer_zero - *pointer_zero - 4);
        return;
    } else if (*pointer_left == 0 && *pointer_right < 0) {
        printf(" TEST2 FREEEEEE\n");
        // Если свободна правая, а левая занаята
        int *before_right = *((int**)(pointer_right + 12));
        int *after_right = *((int**)(pointer_right + 4));
        //Изменяю размер ячеек
        *(pointer_right - *pointer_right - 4) += *pointer_zero;
        *pointer_zero = *(pointer_right - *pointer_right - 4);
        // Изменяю указатели
        *((int**)(pointer_zero + 4)) = *((int**)(pointer_right + 4));
        *((int**)(pointer_zero + 12)) = *((int**)(pointer_right + 12));
        *((int**)(before_right + 4)) = pointer_zero;
        *((int**)(after_right+ 12)) = pointer_zero;
        return;
    } else if (*pointer_left < 0 && *pointer_right < 0) {
        // Если свободна левая и правая
        printf(" TEST3 FREEEEEE\n");
        delete_free_block(pointer_right); //Удаляю правую ячейку из свободных
        // Изменяю размер и указатели
        *pointer_zero += *pointer_right;
        *(pointer_zero - *pointer_zero - 4) = *pointer_left + *pointer_zero;
        *pointer_left = *(pointer_zero - *pointer_zero - 4);
        return;
    } else {
        // Если обе заняты
        int *tmp_AVAIL = *((int**)(end_mem + 4));
        if (end_mem == *((int**)(end_mem + 4))) {
            printf(" TEST4.1 FREEEEEE\n");
            // Если только 1 свободная ячейка
            *((int**)(end_mem + 4)) = pointer_zero;
            *((int**)(tmp_AVAIL + 12)) = pointer_zero;
            *((int**)(pointer_zero + 4)) = tmp_AVAIL;
            *((int**)(pointer_zero + 12)) = end_mem;
            return;
        } else {
            printf(" TEST4.2 FREEEEEE\n");
            // Добавляю новую ячейку к свободным
            int *before_AVAIL = *((int**)(tmp_AVAIL + 12));
            *((int**)(pointer_zero + 4)) = tmp_AVAIL;
            *((int**)(pointer_zero + 12)) = end_mem;
            *((int**)(tmp_AVAIL + 12)) = pointer_zero;
            *((int**)(end_mem + 4)) = pointer_zero;
            //AVAIL = pointer_zero;
            return;
        }
    }
}