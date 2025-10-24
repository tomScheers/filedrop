#ifndef FILEDROP_H
#define FILEDROP_H

#include <stdbool.h>
#include <stdio.h>

bool fd_send_file(char* file_path);
FILE* fd_receive_file();

#endif
