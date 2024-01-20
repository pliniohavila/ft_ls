#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void    resize_vector(int **vector, int *size);

int     main(void)
{
    int     size;
    int     *vec;
    int     len;

    size = 3;
    len = 0;
    vec = (int*)malloc(sizeof(int) * 3);
    if (vec == NULL)
        exit(1);
    memset(vec, 0, sizeof(int) * size);
    for (int i = 0, j = 10; i < 8; i++, j--)
    {
        if (i == size - 1)
        {
            resize_vector(&vec, &size);
        }
        vec[i] = j;
        len++;
    }
    // printf("[DEBUG %s:%d] SIZE: %d\n", __FILE__, __LINE__, size);
    for (int i = 0; i < len; i++)
        printf("%d ", vec[i]);
    printf("\n");
    free(vec);
    return (0);
}

void    resize_vector(int **vector, int *size)
{
    int    *tmp;
    int     new_size;

    new_size = *size * 2;
    // printf("[DEBUG %s:%d] new_size: %d\n", __FILE__, __LINE__, new_size);
    tmp = malloc(sizeof(int) * new_size);
    if (!tmp)
    {
        free(*vector);
        exit(1);
    }
    int i = 0;
    while (i < *size)
    {
        tmp[i] = (*vector)[i];
        i++;
    }
    free(*vector);
    *size = new_size;
    *vector = tmp;
}