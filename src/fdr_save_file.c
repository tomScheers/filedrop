#include "filedrop.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool fdr_save_file(fdr_file *received_file) {
  bool ret_status = true;
  FILE *file_d = fopen(received_file->f_name, "wb");

  if (!file_d) {
    perror("fopen");
    ret_status = false;
    goto ret;
  }

  if (fwrite(received_file->f_data, 1, received_file->f_data_len, file_d) <
          received_file->f_data_len &&
      ferror(file_d)) {
    perror("fwrite");
    ret_status = false;
    goto ret;
  }

ret:
  free(received_file->f_data);
  free(received_file);
  fclose(file_d);
  return ret_status;
}
