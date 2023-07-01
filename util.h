#ifndef UTIL_H
#define UTIL_H
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void fatal(const char *msg);

off_t map4read(const char **restrict dst, const char *name);

long long scan_num();

void print_num(long long n);

#endif
