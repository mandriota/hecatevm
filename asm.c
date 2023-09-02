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
#include "asm.h"
#include "mac.h"

#include <inttypes.h>

void read_file(struct Parser *restrict p) {
  p->ptr = 0;
  p->page.len = fread(p->page.data, 1, p->page.cap, p->src);
}

void read_char(struct Parser *restrict p) {
  ++p->col;
  if (p->page.data[p->ptr] == '\n') {
	p->col = 0;
	++p->row;
  }
  ++p->ptr;

  if (p->ptr == p->page.len)
    read_file(p);
}

void skip_line(struct Parser *restrict p) {
  while (p->ptr < p->page.len && p->page.data[p->ptr] != '\n')
	read_char(p);
}

void skip_whitespaces(struct Parser *restrict p) {
  while (p->ptr < p->page.len && iswhitespace(p->page.data[p->ptr]))
    read_char(p);
  if (p->ptr >= p->page.len || p->page.data[p->ptr] != ';') return;
  
  skip_line(p);
  skip_whitespaces(p);
}

int read_word(struct Parser *restrict p) {
  skip_whitespaces(p);
  int len = 0;
  
  while (p->ptr < p->page.len && len <= 10 && !iswhitespace(p->page.data[p->ptr])) {
	p->word[len++] = p->page.data[p->ptr];
    read_char(p);
  }
  return len;
}

enum PARSING_RESULT next_opcode(struct Parser *restrict p) {
  if (p->page.len == 0) read_file(p);
  int len = read_word(p);

  if (len == 0) return PR_ERR_EOF;
  if (len > 10 || len < 6 || p->word[1] != '.') return PR_ERR_INVALID_NAME;

  int arg = p->word[0];
  if (arg >= '0' && arg <= '9') 
	arg = arg - '0';
  else if (arg >= 'A' && arg <= 'F')
	arg = arg - 'A' + 10;
  else return PR_ERR_INVALID_ARG;
  arg <<= 4;

  int shift = (10-len)*8;
  switch (*(uint64_t *)(p->word+2) << shift >> shift) {
  case 0x4d4d492e52544553:
	return arg | OP_SETR_IMM;
  case 0x4d4d492e43544553:
	return arg | OP_SETC_IMM;
  case 0x54544553:
	return arg | OP_SETT;
  case 0x54455354:
	return arg | OP_TSET;
  case 0x4c2e54455354:
    return arg | OP_TSET_L;
  case 0x452e54455354:
	return arg | OP_TSET_E;
  case 0x472e54455354:
	return arg | OP_TSET_G;
  case 0x4d4d492e54455354:
	return arg | OP_TSET_IMM;
  case 0x504d4354:
	return arg | OP_TCMP;
  case 0x44444154:
	return arg | OP_TADD;
  case 0x42555354:
	return arg | OP_TSUB;
  case 0x4c554d54:
	return arg | OP_TMUL;
  case 0x56494454:
	return arg | OP_TDIV;
  case 0x54454754:
	return arg | OP_TGET;
  case 0x54555054:
	return arg | OP_TPUT;
  }
  
  return PR_ERR_INVALID_NAME;
}
