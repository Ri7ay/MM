//
// Created by Захар Захаров on 24.10.2019.
//

#ifndef MYPROJECT_MEMALLOC_H
#define MYPROJECT_MEMALLOC_H

#include <stdio.h>
#include <unistd.h>

struct mem_block;
void my_free(void *first_byte);
void *my_malloc(size_t size);


#endif //MYPROJECT_MEMALLOC_H
