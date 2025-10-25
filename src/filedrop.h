#ifndef FILEDROP_H
#define FILEDROP_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define PORT 1283

typedef struct {
  size_t f_data_len;
  unsigned char *f_data;
  char *f_name;
} fdr_file;

fdr_file *fdr_parse_file(char *file_path);
bool fdr_send_file(fdr_file *file_path);
fdr_file *fdr_receive_file();

#endif
