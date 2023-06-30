#include "mac.h"
#include "util.h"

int main(int argc, char *argv[]) {
  if (argc != 2)
    fatal("unsupported number of arguments");

  const char *text;
  off_t sz = map4read(&text, argv[1]);

  struct Machine mac;

  m_init(&mac);

  enum EXECUTION_ERR eerr = m_execute(&mac, text, sz);
  return 0;
}
