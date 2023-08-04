#include <sys/types.h>

#include "mac.h"
#include "util.h"

int main(int argc, char *argv[]) {
  if (argc != 2)
    fatal("unsupported number of arguments");

  const char *text;
  off_t sz = map4read(&text, argv[1]);

  struct Machine mac;

  mac_init(&mac);

  enum EXECUTION_RESULT er = mac_execute(&mac, text, sz);
  switch (er) {
  case ER_OK:
	break;
  case ER_ERR_INVALID_INSTRUCTION:
    fatal("invalid instruction");
    break;
  case ER_ERR_INVALID_TEXT_ADDRESS:
    fatal("invalid text address");
    break;
  case ER_ERR_DIVISION_BY_ZERO:
    fatal("division by zero");
    break;
  }
  return 0;
}
