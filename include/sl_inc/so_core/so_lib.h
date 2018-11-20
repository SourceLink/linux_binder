#ifndef SO_LIB_H_
#define SO_LIB_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <unistd.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <sys/ioctl.h> 
#include <fcntl.h>
#include <linux/fs.h> 
#include <errno.h> 
#include <stdarg.h>
#include <stdio.h>
#include <pthread.h>
#include <math.h>

#include "so_file.h"
#include "so_debug.h"

#define EXPORT
#define ARRAY_SIZE(a)               (sizeof(a) / sizeof((a)[0]))

enum {DISABLE = 0, ENABLE = ~DISABLE};

extern int open_hardware(const char *dev_name, int flags);
extern int write_hardware(int dev_fd, const void * data, size_t len);
extern int read_hardware(int dev_fd, void *buf, size_t len);
extern void close_hardware(int dev_fd);
#ifdef __cplusplus
}
#endif

#endif
