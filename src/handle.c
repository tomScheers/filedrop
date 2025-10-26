#include "filedrop.h"

#include <stdbool.h>
#include <stdlib.h>

int send_file_handle(struct SendSettings settings) {
  fdr_file *file = fdr_parse_file(settings.file_path);

  if (!file) {
    return EXIT_FAILURE;
  }

  if (fdr_send_file(file, settings.port) == false) {
    free(file->f_data);
    free(file);
    return EXIT_FAILURE;
  }

  free(file->f_data);
  free(file);
  return EXIT_SUCCESS;
}

int receive_file_handle(struct ReceiveSettings settings) {
  fdr_file *received_file = fdr_receive_file(settings.ipv4_addr, settings.port);

  if (!received_file)
    return EXIT_FAILURE;

  bool save_status = fdr_save_file(received_file, settings.output_file_path);

  if (save_status == false)
    return EXIT_FAILURE;

  return EXIT_SUCCESS;
}
