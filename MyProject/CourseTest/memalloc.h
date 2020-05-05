//
// Created by Захар Захаров on 24.10.2019.
//

#ifndef MYPROJECT_MEMALLOC_H
#define MYPROJECT_MEMALLOC_H

#include <stdio.h>

int *AVAIL, *free_block[10], *end_mem;

void print_AVAIL();
void *my_malloc(size_t size);
void my_free(void *first_byte);


#endif //MYPROJECT_MEMALLOC_H
