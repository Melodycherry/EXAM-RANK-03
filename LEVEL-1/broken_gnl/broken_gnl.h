#ifndef BROKEN_GNL_H
#define BROKEN_GNL_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

#include <fcntl.h>
#include <stddef.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/uio.h>
#include <unistd.h>

char    *get_next_line(int fd);
#endif