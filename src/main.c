#include "filedrop.h"

#include <stdio.h>
#include <stdlib.h>
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
    fdr_file *file = fdr_parse_file(argv[2]);
    if (!file) {
      return 1;
    }

    printf("File content: %s\n", file->f_data);
    printf("File length: %zu\n", file->f_data_len);
    printf("File name: %s\n", file->f_name);

    fdr_send_file(file);

    free(file->f_data);
    free(file);
  } else if (strcmp(argv[1], "receive") == 0) {
    fdr_file *received_file = fdr_receive_file();

    FILE *file_d = fopen(received_file->f_name, "wb");

    if (!file_d) {
      perror("fopen");
      free(received_file->f_name);
      free(received_file->f_data);
      free(received_file);
      return EXIT_FAILURE;
    }

    fwrite(received_file->f_data, 1, received_file->f_data_len, file_d);

    free(received_file->f_name);
    free(received_file->f_data);
    free(received_file);
    fclose(file_d);
  }
  return 0;
}
