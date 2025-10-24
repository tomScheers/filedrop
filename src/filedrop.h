#ifndef FILEDROP_H
#define FILEDROP_H

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

typedef struct {
  size_t f_data_len;
  unsigned char* f_data;
  char* f_name;
} fd_file;

fd_file* fd_parse_file(char* file_path);
bool fd_send_file(fd_file* file_path);
FILE* fd_receive_file();

#endif
