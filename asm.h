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
#ifndef ASM_H
#define ASM_H

#include "util.h"

#include <stdio.h>

struct Parser {
  struct String page;
  char word[16];
  FILE * src;
  size_t ptr;
  size_t row;
  size_t col;
};

enum PARSING_RESULT {
  PR_ERR_EOF = -3,
  PR_ERR_INVALID_NAME,
  PR_ERR_INVALID_ARG,
};

enum PARSING_RESULT next_opcode(struct Parser *restrict p);

#endif
