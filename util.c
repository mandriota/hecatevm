// Copyright 2023 Mark Mandriota
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <sys/fcntl.h>

void fatal(const char *msg) {
  if (errno != 0)
    perror(msg);
  else {
    fwrite("error: ", 1, 7, stdout);
    fwrite(msg, 1, strlen(msg), stdout);
    putchar('\n');
  }

  exit(errno);
}

off_t map4read(char **restrict dst, const char *name) {
  static struct stat stat_info;
  
  int fd = open(name, O_RDONLY, 0);
  if (fd < 0)
    fatal("while openning file descriptor");

  if (fstat(fd, &stat_info) != 0)
    fatal("while reading file stats");

  off_t fsz = stat_info.st_size;

  *dst = mmap(NULL, fsz, PROT_READ, MAP_PRIVATE, fd, 0);
  if (*dst == MAP_FAILED)
    fatal("while mapping file");
  close(fd);

  return fsz;
}

long long scan_num() {
  long long n = 0;
  int first_cc;
  do
    first_cc = getchar_unlocked();
  while (iswhitespace(first_cc));

  n = isdigit(first_cc) ? first_cc - '0' : 0;

  for (int cc = getchar_unlocked(); isdigit(cc); cc = getchar_unlocked())
    n = n * 10 + cc - '0';

  n = first_cc == '-' ? -n : n;
  return n;
}

ssize_t to_string(char *restrict dst, ssize_t dst_sz, long long n) {
  assert(dst && "dst must not be NULL");
  assert(dst_sz >= 2 && "dst size must be at least 2 byte");

  ssize_t p = 0;

  if (n == 0) {
    dst[p++] = '0';
    return p;
  }

  if (n < 0) {
    dst[p++] = '-';
    n = -n;
  }

  for (long long i = 1000000000000000000; i; i /= 10) {
    if (n / i == 0) continue;
	
    if (p < dst_sz)
      dst[p++] = n / i % 10 + '0';
    else
      fatal("dst is too small");
  }

  return p;
}
