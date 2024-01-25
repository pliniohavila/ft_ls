#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
// #include <time.h>

#define MAX_PATH 50
// int stat(const char *filename, struct stat *buf);

typedef struct dirent* dirent;

void    file_props(struct stat stats);

int     main(void)
{
    // DIR     *
    char        *file;
    struct stat stats;

    file = "a.out";
    if (stat(file, &stats) == 0)
        file_props(stats);
    else 
        return (1);
    return (0);
}

void strmode(mode_t mode, char * buf) {
    const char chars[] = "rwxrwxrwx";
    for (size_t i = 0; i < 9; i++) {
        buf[i] = (mode & (1 << (8-i))) ? chars[i] : '-';
    }
    buf[9] = '\0';
}

void    file_props(struct stat stats)
{
    // printf("%10.10s", sperm (stats.st_mode));
    // printf("%4lu", stats.st_nlink);
    char    buf[10];

    printf("SIZEOF ST_MODE: %lu\n", sizeof(stats.st_mode));
    strmode(stats.st_mode, buf);
    printf("%04o is %s\n", stats.st_mode, buf);
    // for (size_t i = 0; i < sizeof(stats.st_mode); i++) {
    //     strmode(stats.st_mode[i], buf);
    //     printf("%04o is %s\n", stats.st_mode[i], buf);
    // }
}