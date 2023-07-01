#include "util.h"
#include <stdio.h>

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

struct stat stat_info;

off_t map4read(const char **__restrict dst, const char *name) {
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

#define iswhitespace(c) (c == ' ' || c == '\n' || c == '\r' || c == '\t')

inline long long scan_num() {
  long long n = 0;
  int first_cc;
  do
    first_cc = getchar_unlocked();
  while (iswhitespace(first_cc));

  n = first_cc != '-' ? first_cc - '0' : 0;

  for (int cc = getchar_unlocked(); cc >= '0' && cc <= '9';
       cc = getchar_unlocked())
    n = n * 10 + cc - '0';

  n = first_cc == '-' ? -n : n;
  return n;
}

inline void print_num(long long n) {
  if (n == 0) {
    putchar_unlocked('0');
    return;
  }
  if (n < 0)
    putchar('-');
  for (long long i = 1000000000000000000; i; i /= 10)
    if (n / i != 0)
      putchar_unlocked(n / i % 10 + '0');
}
