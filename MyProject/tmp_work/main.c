#include "memalloc.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *mas, *tmp, *test;
    mas = my_malloc(sizeof(int)*10);
    tmp = malloc(sizeof(int)*10);
    test = mas;
    for (int i = 0; i < 10; i++) {
        tmp[i] = i + 1;
        mas[i] = i + 1;
        printf("%d, %d\n", mas[i], tmp[i]);
        printf("%p / %p\n", mas + i, tmp + i);
    }
    my_free(mas);
    free(tmp);
    return 0;
}