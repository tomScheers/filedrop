#include "filedrop.h"

#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

fdr_file *fdr_receive_file(struct in_addr ip_addr, uint16_t port) {
  fdr_file *file;
  int sock;
  struct sockaddr_in serv_addr;
  size_t f_name_len;

  sock = socket(AF_INET, SOCK_STREAM, 0);

  if (!sock) {
    perror("socket");
    goto e3;
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port);
  serv_addr.sin_addr = ip_addr;

  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
    perror("connect");
    goto e3;
  }

  file = malloc(sizeof(*file));

  if (!file) {
    perror("malloc");
    goto e3;
  }

  if (recv(sock, &file->f_data_len, sizeof(file->f_data_len), 0) == -1) {
    perror("recv");
    goto e2;
  }

  if (recv(sock, &f_name_len, sizeof(f_name_len), 0) == -1) {
    perror("recv");
    goto e2;
  }

  file->f_data = malloc(file->f_data_len);
  if (!file->f_data) {
    perror("malloc");
    goto e2;
  }

  if (recv(sock, file->f_name, f_name_len, 0) == -1) {
    perror("recv");
    goto e3;
  }

  if (recv(sock, file->f_data, file->f_data_len, 0) == -1) {
    perror("recv");
    goto e3;
  }

  if (!file) {
    perror("malloc");
    goto e1;
  }

  file->f_name[f_name_len] = '\0';

  close(sock);
  return file;

e1:
  free(file->f_data);
e2:
  free(file);
e3:
  close(sock);
  return NULL;
}
