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

int     main(void)
{
    _ls_v(".");
    return (0);
}

void    _ls_v(const char *dirname)
{
    DIR         *dir;
    char        *paths[10];
    int         path_len;
    dirent      entity;
    char        path[MAX_PATH];

    printf("Reading files from %s:\n", dirname);
    dir =  opendir(dirname); 
    if (dir == NULL)
    {
        printf("[ERROR]: %s \'%s\'\n", strerror(errno), dirname); 
        exit(1);
    }
    entity = readdir(dir);
    path_len = 0; 
    while (entity != NULL)
    {
        // printf("%hhd %s\t", entity->d_type, entity->d_name);
        // if (entity->d_type == DT_DIR && strcmp(entity->d_name, ".") != 0 && strcmp(entity->d_name, "..") != 0)
        if (entity->d_type == DT_DIR)
        {
            memset(path, 0, MAX_PATH);
            strcat(path, dirname);
            strcat(path, "/");
            strcat(path, entity->d_name);
            // printf("\n[%s:%d] PATH: %s\n", __FILE__, __LINE__, path);
            paths[path_len] = path;
            path_len++;
            printf("\n[%s:%d] PATH[%d]: %s\n", __FILE__, __LINE__, path_len - 1, paths[path_len - 1]);
        }
        entity = readdir(dir);
    }
    printf("\n");
    // printf("\n[%s:%d] PATH[0]: %s\n", __FILE__, __LINE__, paths[2]);
    printf("\nDirectorys:\n");
    for (int i = 0; i < path_len; i++)
        printf("%s ", paths[i]);
    printf("\n");
    closedir(dir);
}

void    _ls(const char *dirname)
{
    DIR         *dir;
    // char        *path;
    dirent      entity;
    char        path[MAX_PATH];

    printf("Reading files from %s:\n", dirname);
    dir =  opendir(dirname); 
    if (dir == NULL)
    {
        printf("[ERROR]: %s \'%s\'\n", strerror(errno), dirname); 
        exit(1);
    }
    entity = readdir(dir);
    while (entity != NULL)
    {
        // if (entity->d_type == DT_DIR && strcmp(entity->d_name, ".") != 0 && strcmp(entity->d_name, ".."))
        if (entity->d_type == DT_DIR && strcmp(entity->d_name, ".") != 0 && strcmp(entity->d_name, "..") != 0)
        {
            memset(path, 0, MAX_PATH);
            strcat(path, dirname);
            strcat(path, "/");
            strcat(path, entity->d_name);
            _ls(path);
        }
        else 
        {
            printf("- %hhd %s\n", entity->d_type, entity->d_name);
        }
        entity = readdir(dir);
    }
    printf("\n\n");
    closedir(dir);
}