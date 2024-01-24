#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>

#define MAX_PATH 50
typedef struct dirent* dirent;
typedef struct  flags
{
    int     a_flag;
    int     R_flag;
    int     l_flag;
    int     t_flag;
    int     r_flag;
}       FLAGS;

void    ft_ls(const char *dirname, FLAGS*);
void    _ls_v(const char *dirname);
void    init_flags_struc(FLAGS*);
void    resize_paths_vector(char ***paths, int *size);
void    get_options(char *dirname, char **argv, int argc, FLAGS*);

int     main(int argc, char **argv)
{
    FLAGS       op_flags;
    char        dirname[PATH_MAX];

    memset(dirname, 0, PATH_MAX);
    strcpy(dirname, ".");
    if (argc > 1)
    {
        init_flags_struc(&op_flags);
        get_options(dirname, argv, argc, &op_flags);
    }
    ft_ls(dirname, &op_flags);
    return (0);
}

void    get_options(char *dirname, char **argv, int argc, FLAGS *op_flags)
{
    int     i;

    i = 0;
    while (i++ < (argc - 1))
    {
        if (argv[i][0] == '.' || argv[i][0] == '/') 
            strcpy(dirname, argv[i]);
        if (argv[i][0] == '-')
        {
            if (argv[i][1] == 'a')
                op_flags->a_flag = 1; 
            if (argv[i][1] == 'R')
                op_flags->R_flag = 1; 
            if (argv[i][1] == 'l')
                op_flags->l_flag = 1; 
            if (argv[i][1] == 't')
                op_flags->t_flag = 1; 
            if (argv[i][1] == 'r')
                op_flags->r_flag = 1; 
        }
    }
}

void    ft_ls(const char *dirname, FLAGS *op_flags)
{
    DIR         *dir_ptr;
    dirent      entry;

    dir_ptr = opendir(dirname);
    if (dir_ptr == NULL)
    {
        printf("[ERROR]: %s \'%s\'\n", strerror(errno), dirname); 
        exit(EXIT_FAILURE);
    }
    errno = 0;
    entry = readdir(dir_ptr);
    while (entry != NULL)
    {
        if (op_flags->a_flag)
        {
            printf("%s  ", entry->d_name);
        }
        else 
        {
            if (entry->d_name[0] != '.')
                printf("%s  ", entry->d_name);
        }
        entry = readdir(dir_ptr);
    }
    if (errno)
    if (errno != 1)
    {
        perror(strerror(errno));
        exit(EXIT_FAILURE);
    }
}

void    init_flags_struc(FLAGS *op_flags)
{
    *op_flags = (FLAGS){ 
        .a_flag = 0, 
        .R_flag = 0, 
        .l_flag = 0, 
        .t_flag = 0, 
        .r_flag = 0 
    };
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
    printf("\nReading files and directories from %s:\n", dirname);
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