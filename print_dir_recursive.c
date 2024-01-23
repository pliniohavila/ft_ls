#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>

#define MAX_PATH 50
typedef struct dirent* dirent;

void    _ls(const char *dirname);
void    _ls_v(const char *dirname);
void    resize_paths_vector(char ***paths, int *size);

int     main(void)
{
    _ls_v(".");
    return (0);
}

void    _ls_v(const char *dirname)
{
    DIR         *dir;
    char        **paths;
    int         path_len;
    dirent      entity;
    char        path[MAX_PATH];
    int         size;

    size = 16;
    if ((paths =  (char**)malloc(sizeof(char*) * size)) == NULL)
    {
        perror("Error in paths allocation\n");
        exit(EXIT_FAILURE);
    }
    printf("\n%s:\n", dirname);
    dir =  opendir(dirname); 
    if (dir == NULL)
    {
        printf("[ERROR]: %s \'%s\'\n", strerror(errno), dirname); 
        exit(EXIT_FAILURE);
    }
    path_len = 0; 
    entity = readdir(dir);
    while (entity != NULL)
    {
        printf("%s\t", entity->d_name);
        if (entity->d_type == DT_DIR && strcmp(entity->d_name, ".") != 0 && strcmp(entity->d_name, "..") != 0)
        {
            memset(path, 0, MAX_PATH);
            strcat(path, dirname);
            strcat(path, "/");
            strcat(path, entity->d_name);
            if (path_len == (size - 1))
                resize_paths_vector(&paths, &size);
            paths[path_len] = strdup(path);
            if (paths[path_len] == NULL)
            {
                perror("Error duplicating path");
                exit(EXIT_FAILURE);
            }
            path_len++;
        }
        entity = readdir(dir);
    }
    for (int i = 0; i < path_len; i++)
    {
        _ls_v(paths[i]);
        free(paths[i]);
    }
    free(paths);
    printf("\n");
    closedir(dir);
}

void    resize_paths_vector(char ***paths, int *size)
{
    char    **tmp;
    int     new_size;

    new_size = *size * 2;
    if ((tmp =  (char**)malloc(sizeof(char*) * new_size)) == NULL)
    {
        perror("Error in paths allocation\n");
        free(*paths);
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while (i < *size)
    {
        tmp[i] = (*paths)[i];
        i++;
    }
    free(*paths);
    *size = new_size;
    *paths = tmp;
}