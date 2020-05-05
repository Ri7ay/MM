//
// Created by Захар Захаров on 24.10.2019.
//

#include "memalloc.h"

// Создание струкртуры которая хранит размер свободной ячейки,
// и указатель на следующую ячейку
struct mem_block {
    char TAG;
    size_t size;
    struct mem_block *next;
};

// Список AVAIL
// Как его поставить на 1 свободную ячейку в памяти?
static struct mem_block AVAIL = {'-', 0, 0};

void *my_malloc(size_t size) {
    // Увеличиваю размер с учетом блока с информацией
    size += 2 * sizeof(struct mem_block);
    struct mem_block **Q = &(AVAIL.next);
    struct mem_block *pointer = *Q;
    //Иду по свободным ячейкам, пока не дойду до конца
    while (pointer != 0) {
        // Если ячейка больше либо равна нужному размеру, то берем ее
        if (pointer->size >= size) {
            struct mem_block *L;
            size_t K = pointer->size - size;
            // Реализация шага А4'
            if (K <= 10) {
                // 1) Если размер ячейки чуть больше нужного
                (*Q)->next = pointer->next;
                L = pointer;
                // Помечаем ячейку как занятую
                L->TAG = '+';
                (L + L->size - sizeof(struct mem_block))->TAG = '+'; // Нужна ли нам 2 ячейка в конце?
                (L + L->size - sizeof(struct mem_block))->size = pointer->size; // Сохранаю информацию о размере
                // 2 Вариант (L + L->size - 1)->TAG = '+';
            }
            else {
                // 2) Если размер ячейки больше нужного нам размера
                pointer->size = K;
                L = pointer + K;
                L->size = size;
                // Помечаем ячейку как занятую
                L->TAG = '+';
                (L + size - sizeof(struct mem_block))->TAG = '+'; // Нужна ли нам 2 ячейка в конце?
                (L + size - sizeof(struct mem_block))->size = size; // Сохранаю информацию о размере
                // 2 Вриант (L + size - 1)->TAG = '+';
            }
            return L + sizeof(struct mem_block);
        }
        // Если размер ячейки не подошел
        Q = &(pointer->next);
        pointer = *Q;
    }
    // Если нет нужной нам ячейки, то запрашиывает память у ОС
    pointer = (struct mem_block*)sbrk(size);
    // Записываю нужную информацию в 1 слово
    pointer->size = size;
    pointer->TAG = '+';
    (pointer + size - sizeof(struct mem_block))->TAG = '+';
    return pointer + sizeof(struct mem_block);
}

// Не готово от слова совсем(((
void my_free(void* ptr) {
    struct mem_block* pointer = (struct mem_block*)(ptr - sizeof(struct mem_block)), *last_block = pointer + pointer->size;
    pointer->TAG = '-';
    last_block->TAG = '-';
    last_block->size = pointer->size;
    pointer->next = AVAIL.next;
    last_block = (pointer + 1)->next;
    AVAIL.next = pointer;
}