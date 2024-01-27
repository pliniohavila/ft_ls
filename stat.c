#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

// #define MAX_PATH 50
typedef struct dirent* dirent;

void    print_e_props(struct stat stats, const char *file);

int     main(void)
{
    char        *file;
    struct stat stats;

    file = "a.out";
    if (stat(file, &stats) == 0)
        print_e_props(stats, file);
    else 
        return (1);
    return (0);
}

void strmode(mode_t mode, char *buf) 
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

void    print_e_props(struct stat stats, const char *file)
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
    printf("%s\n", file);
}