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
#include "mac.h"
#include "asm.h"
#include "util.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>

void sub_run(int argc, char *argv[]);

void sub_asm(int argc, char *argv[]);

void sub_help();

int main(int argc, char *argv[]) {
  if (argc < 2) {
	sub_help();
  } else if (argc == 2 || !strcmp(argv[1], "run")) {
    sub_run(argc-1, argv+1);
  } else if (!strcmp(argv[1], "asm")) {
	sub_asm(argc-1, argv+1);
  } else fatal("undefined subcommand");
}

void sub_run(int argc, char *argv[]) {
  char *text;
  off_t sz = map4read(&text, argv[argc-1]);

  struct Machine mac;

  mac_init(&mac);

  enum EXECUTION_RESULT er = mac_execute(&mac, text, sz);
  switch (er) {
  case ER_OK:
	break;
  case ER_ERR_INVALID_INSTRUCTION:
    fatal("invalid instruction");
  case ER_ERR_INVALID_TEXT_ADDRESS:
    fatal("invalid text address");
  case ER_ERR_DIVISION_BY_ZERO:
    fatal("division by zero");
  }

  if (munmap((void *) text, sz))
	fatal("error while munmapping");
}

void sub_asm(int argc, char *argv[]) {
  int opt;
  char * dst_filename = "out.hcvm";

  opterr = 0;

  while ((opt = getopt(argc, argv, "o:")) != EOF) {
	switch (opt) {
	case 'o':
	  dst_filename = optarg;
	  break;
	case '?':
	  fatal("illegal option");
	default:
	  fatal("getopt returned unexpected value");
	}
  }

  char src_buf[1<<14];
  char dst_buf[1<<14];
  int dst_buf_ptr = 0;

  FILE * src_fs = fopen(argv[optind], "r");
  FILE * dst_fs = fopen(dst_filename, "w");
  if (src_fs == NULL || dst_fs == NULL) {
	fatal("error while openning file");
  }
  
  struct Parser parser = {
	.src = src_fs,
	.page.data = src_buf,
	.page.cap = sizeof src_buf,
	.page.len = 0,
  };

  int op;
  size_t n = 0;
  while ((op = next_opcode(&parser)) >= 0) {
	#ifdef DEBUG_H
	printf("%zu <%zu:%zu>\t%d\t%d\t%s %d\n",
		   parser.ptr, parser.row+1,parser.col,
		   op, op&0xF, opcodes_stringify[op&0xF], op>>4);
	#endif
	dst_buf[dst_buf_ptr] = op;
	
	++dst_buf_ptr;
	if (dst_buf_ptr >= sizeof dst_buf) {
	  n += fwrite(dst_buf, 1, sizeof dst_buf, dst_fs);
	  dst_buf_ptr = 0;
	}
  }

  if (dst_buf_ptr != 0)
	n += fwrite(dst_buf, 1, dst_buf_ptr, dst_fs);

  fclose(src_fs);
  fclose(dst_fs);
  
  printf("<%zu:%zu>\n", parser.row+1, parser.col);
  
  switch (op) {
  case PR_ERR_INVALID_NAME:
	fatal("invalid name");
  case PR_ERR_INVALID_ARG:
	fatal("invalid arg");
  }

  printf("Generated %zu-byte file.\n", n);
}

void sub_help() {
  puts("Hecate Virtual Machine. (c) 2023 Mark Mandriota");
  puts("");
  puts("Usage:");
  puts("");
  puts("\thcvm <source binary>");
  puts("");
  puts("Subcommands:");
  puts("");
  puts("\thcvm asm [-o <destination binary>] <source assembler>");
  puts("");
  puts("Translates hecate assembler source to hecate binary destination file");
  puts("");
  puts("\thcvm run <source binary>");
  puts("");
  puts("Alias for main command. Runs hecate binary.");
  puts("");
}
