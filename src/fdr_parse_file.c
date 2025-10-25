#include "filedrop.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

fdr_file *fdr_parse_file(char *file_path) {
  FILE *file;
  fdr_file *transfer_file;

  file = fopen(file_path, "rb");
  if (file == NULL) {
    return NULL;
  }

  transfer_file = malloc(sizeof(*transfer_file));
  if (!transfer_file) {
    perror("malloc");
    goto e2;
  }

  if (fseek(file, 0, SEEK_END) == -1) {
    perror("fseek");
    goto e1;
  }

  long pos = ftell(file); // A long because ftell returns -1 on error, and if
                          // set to size_t it'll wrap
  if (pos == -1L) {
    perror("ftell");
    goto e1;
  }

  rewind(file);
  transfer_file->f_data_len = pos;

  transfer_file->f_data = malloc(transfer_file->f_data_len + 1);
  if (!transfer_file) {
    perror("malloc");
    goto e1;
  }

  size_t read_bytes =
      fread(transfer_file->f_data, 1, transfer_file->f_data_len, file);
  if (read_bytes < transfer_file->f_data_len) {
    if (ferror(file)) {
      perror("fread");
      goto e1;
    } else if (feof(file)) {
      transfer_file->f_data_len =
          read_bytes; // If data was partially read, set the data_len to the
                      // amount of partially read bytes
    }
  }

  transfer_file->f_data[transfer_file->f_data_len] = '\0';

  fclose(file);

  char *name = strrchr(file_path, '/');
  name = name ? name + 1 : file_path;
  strncpy(transfer_file->f_name, name, strlen(name));
  transfer_file->f_name[strlen(name)] = '\0';

  return transfer_file;

e1:
  free(transfer_file->f_data);
e2:
  free(transfer_file);
  fclose(file);
  return NULL;
}
