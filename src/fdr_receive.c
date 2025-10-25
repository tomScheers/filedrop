#include "filedrop.h"

#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

fdr_file *fdr_receive_file() {
  int sock = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in serv_addr;

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);
  serv_addr.sin_addr.s_addr = INADDR_ANY;

  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
    perror("connect");
    close(sock);
    return NULL;
  }

  size_t f_data_len;
  size_t f_name_len;
  char *f_name;
  unsigned char *f_data;

  recv(sock, &f_data_len, sizeof(f_data_len), 0);
  recv(sock, &f_name_len, sizeof(f_name_len), 0);

  f_name = malloc(f_name_len + 1);
  f_data = malloc(f_data_len);

  recv(sock, f_name, f_name_len, 0);
  recv(sock, f_data, f_data_len, 0);

  printf("data_len %zu\n", f_data_len);
  printf("name_len %zu\n", f_name_len);
  printf("f_name %.*s\n", (int)f_name_len, f_name);
  printf("f_data %.*s\n", (int)f_data_len, f_data);

  fdr_file *file = malloc(sizeof(*file));

  file->f_data = f_data;
  file->f_name = f_name;
  file->f_name[f_name_len] = '\0';
  file->f_data_len = f_data_len;

  close(sock);

  return file;
}
