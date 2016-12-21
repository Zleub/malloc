#ifndef MALLOC_H
# define MALLOC_H

#include <unistd.h>
#include <errno.h>
#include <limits.h>

#include <libft.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
#include <sys/mman.h>

#define SPRINTF(args...) { char str[1024] = {0}; sprintf(str, args); ft_putstr(str); }

#define LARGE 4096

void free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);

#endif
