#include "filedrop.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    fd_file* file = fd_parse_file(argv[2]);
    if (!file) {
      return 1;
    }
    printf("File content: %s\n", file->f_data);
    printf("File length: %zu\n", file->f_data_len);
    printf("File name: %s\n", file->f_name);
    free(file->f_data);
    free(file);
  } else if (strcmp(argv[1], "receive") == 0) {
    // FILE* received_file = fd_receive_file();
  }
  return 0;
}
