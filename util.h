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
#ifndef UTIL_H
#define UTIL_H

#include <sys/types.h>

#define whitespaces ' ', '\n', '\r', '\t'
#define iswhitespace(c) (c == ' ' || c == '\n' || c == '\r' || c == '\t')
#define isdigit(c) (c >= '0' && c <= '9')

struct String {
  char * data;
  size_t len;
  size_t cap;
};

void fatal(const char *msg);

off_t map4read(char **restrict dst, const char *name);

long long scan_num();

ssize_t to_string(char *restrict dst, ssize_t dst_sz, long long n);

long long hsum(const char *s, size_t sz);

#endif
