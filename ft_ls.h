#ifndef FT_LS_H
#define FT_LS_H

#include <dirent.h>
#include <sys/types.h>
#include "ft_ls.h"

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

void    ft_ls(const char*, FLAGS*);
void    _ls_v(const char*);
void    init_flags_struc(FLAGS*);
void    resize_paths_vector(char***, int *);
void    get_options(char*, char**, int, FLAGS*);
void    print_dir_entry(const char *, char*, FLAGS*);
void    print_l_flag(char*, char*);
void    strmode(mode_t, char*);
void    print_e_props(struct stat, const char*);

#endif