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

#define MAX_PATH 50
// int stat(const char *filename, struct stat *buf);
typedef struct dirent* dirent;

void    file_props(struct stat stats, const char *file);

int     main(void)
{
    // DIR     *
    char        *file;
    struct stat stats;

    file = "a.out";
    if (stat(file, &stats) == 0)
        file_props(stats, file);
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

// struct timespec {
//     time_t   tv_sec;        /* seconds */
//     long     tv_nsec;       /* nanoseconds */
// };

void    file_props(struct stat stats, const char *file)
{
    char            buf[10];
    struct passwd   *user_info;
    struct group    *group_info;
    // struct tm      *tm;
    // char            datestring[256];

    strmode(stats.st_mode, buf);
    //   nlink_t   st_nlink;
    printf("-%s ", buf);
    printf("%lu ", stats.st_nlink);
    user_info = getpwuid(stats.st_uid);
    group_info = getgrgid(stats.st_gid);
    if (user_info == NULL || group_info == NULL)
    {
        printf("[ERROR]: %s'\n", strerror(errno)); 
        exit(EXIT_FAILURE);
    }
    printf("%s ", user_info->pw_name);
    printf("%s ", group_info->gr_name);
    printf("%ld ", stats.st_size);
    printf("%s ", ctime(&stats.st_mtim.tv_sec));
    // printf("-%s %lu %s\n", buf, stats.st_nlink, file);
    printf("%s\n", file);
}