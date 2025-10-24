#include "filedrop.h"

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s [send/receive] [options]", argv[0]);
    return 0;
  }

  if (strcmp(argv[1], "send") == 0) {
    if (argc < 3) {
      printf("Usage: %s %s [file] [options]", argv[0], argv[1]);
      return 0;
    }
    fd_send_file(argv[3]);
  } else if (strcmp(argv[1], "receive") == 0) {
    FILE* received_file = fd_receive_file();
  }
  return 0;
}
