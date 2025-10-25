#include "filedrop.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

fdr_file *fdr_parse_file(char *file_path) {
  FILE *file = fopen(file_path, "rb");
  if (file == NULL) {
    return NULL;
  }
  fdr_file *transfer_file = malloc(sizeof(*transfer_file));

  fseek(file, 0, SEEK_END);
  transfer_file->f_data_len = ftell(file);
  rewind(file);
  if (transfer_file->f_data_len < 0) {
    fclose(file);
    free(transfer_file);
    return NULL;
  }

  transfer_file->f_data = malloc(transfer_file->f_data_len + 1);
  fread(transfer_file->f_data, 1, transfer_file->f_data_len, file);
  transfer_file->f_data[transfer_file->f_data_len] = '\0';

  fclose(file);

  char *name = strrchr(file_path, '/');
  name = name ? name + 1 : file_path;
  transfer_file->f_name = name;

  return transfer_file;
}
