#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
// #include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include "ft_ls.h"

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

void    print_dir_entry(const char *dirname, char *e_name, FLAGS *op_flags)
{
    char    e_path_name[PATH_MAX];
    
    memset(e_path_name, 0, MAX_PATH);
    strcat(e_path_name, dirname);
    strcat(e_path_name, "/");
    strcat(e_path_name, e_name);
    if (op_flags->a_flag)
    {
        if (op_flags->l_flag)
            print_l_flag(e_path_name, e_name);
        else
            printf("%s  ", e_name);
    }
    else 
    {
        if (e_name[0] != '.')
        {
            if (op_flags->l_flag)
                print_l_flag(e_path_name, e_name);
            else
                printf("%s  ", e_name);
        }
    }
}

void    print_l_flag(char *e_path_name, char *e_name)
{
    struct stat stats;

    if (stat(e_path_name, &stats) == 0)
    {
        print_e_props(stats, e_name);
    }
    else 
    {
        printf("[ERROR]: %s'\n", strerror(errno)); 
        exit(errno);
    }
}

void    print_e_props(struct stat stats, const char *e_name)
{
    char            buf[10];
    struct passwd   *user_info;
    struct group    *group_info;
    char            date_string[256];

    strmode(stats.st_mode, buf);
    printf("-%s ", buf);
    printf("%lu ", stats.st_nlink);
    user_info = getpwuid(stats.st_uid);
    group_info = getgrgid(stats.st_gid);
    if (user_info == NULL || group_info == NULL)
    {
        printf("[ERROR]: %s'\n", strerror(errno)); 
        exit(errno);
    }
    printf("%s ", user_info->pw_name);
    printf("%s ", group_info->gr_name);
    printf("%ld ", stats.st_size);
    strncpy(date_string, (ctime(&stats.st_mtim.tv_sec)) + 4, 12);
    printf("%s ", date_string);
    printf("%s\n", e_name);
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
        print_dir_entry(dirname, entry->d_name, op_flags);
        entry = readdir(dir_ptr);
    }
    if (errno != 0)
    {
        perror(strerror(errno));
        exit(EXIT_FAILURE);
    }
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

void    strmode(mode_t mode, char *buf) 
{
    char        chars[10];
    size_t      i;

    strcpy(chars, "rwxrwxrwx");
    i = 0;
    while (i < 9) 
    {
        buf[i] = (mode & (1 << (8-i))) ? chars[i] : '-';
        i++;
    }
    buf[9] = '\0';
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