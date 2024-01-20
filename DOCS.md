dirent
Data structure for a directory entry

Synopsis:
#include <dirent.h>

struct dirent {
#if _FILE_OFFSET_BITS - 0 == 64
    ino_t           d_ino;     /* File serial number. */
    off_t           d_offset;
#elif !defined(_FILE_OFFSET_BITS) || _FILE_OFFSET_BITS == 32
#if defined(__LITTLEENDIAN__)
    ino_t           d_ino;     /* File serial number. */
    ino_t           d_ino_hi;
    off_t           d_offset;
    off_t           d_offset_hi;
#elif defined(__BIGENDIAN__)
    ino_t           d_ino_hi;
    ino_t           d_ino;     /* File serial number. */
    off_t           d_offset_hi;
    off_t           d_offset;
#else
 #error endian not configured for system
#endif
#else
 #error _FILE_OFFSET_BITS value is unsupported
#endif
    _Int16t             d_reclen;
    _Int16t             d_namelen;
    char                d_name[1];
};
Description:
The dirent structure describes an entry in a directory. The members include:

d_ino
A mountpoint-unique file serial number. This serial number is often used in various disk-checking utilities for such operations as determining infinite-loop directory links. (Note that the inode value cannot be zero, which would indicate that the inode represents an unused entry.)
d_offset
In some filesystems, this member identifies the directory entry itself; in others, it's the offset of the next directory entry. For a disk-based filesystem, this value might be the actual offset into the on-disk directory structure.
d_reclen
The size of this directory entry and any other associated information (such as an optional struct stat structure appended to the struct dirent entry).
d_namelen
The size of the d_name member. Since the size is calculated using strlen(), the \0 string terminator, which must be present, isn't counted.
d_name
The actual name of that directory entry.

#ifdef __USE_BSD
/* File types for `d_type'.  */
enum
  {
    DT_UNKNOWN = 0,
# define DT_UNKNOWN	DT_UNKNOWN
    DT_FIFO = 1,
# define DT_FIFO	DT_FIFO
    DT_CHR = 2,
# define DT_CHR		DT_CHR
    DT_DIR = 4,
# define DT_DIR		DT_DIR
    DT_BLK = 6,
# define DT_BLK		DT_BLK
    DT_REG = 8,
# define DT_REG		DT_REG
    DT_LNK = 10,
# define DT_LNK		DT_LNK
    DT_SOCK = 12,
# define DT_SOCK	DT_SOCK
    DT_WHT = 14
# define DT_WHT		DT_WHT
  };