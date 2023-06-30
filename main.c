#include "mac.h"

int main(int argc, char *argv[]) {
  if (argc != 2)
    fatal("unsupported number of arguments");

  const char *text;
  off_t sz = map4read(&text, argv[1]);

  struct Machine mac;

  mac_init(&mac);

  enum EXECUTION_ERR eerr = mac_execute(&mac, text, sz);
  // TODO: add execution error handling
  return 0;
}
