printf("\n[%s:%d] PATH[%d]: %s\n", __FILE__, __LINE__, path_len - 1, paths[path_len - 1]);
    printf("\n[%s:%d] PATH[%d]: %s\n", __FILE__, __LINE__, path_len - 1, paths[0]);

    printf("%hhd %s\t", entity->d_type, entity->d_name);

    // printf("\n\n");
    // printf("Directories:\n");
    // for (int i = 0; i < path_len; i++)
    // {
    //     printf("%s ", paths[i]);
    //     // free(paths[i]);
    // }

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

// int stat(const char *filename, struct stat *buf);

// struct timespec {
//     time_t   tv_sec;        /* seconds */
//     long     tv_nsec;       /* nanoseconds */
// };
