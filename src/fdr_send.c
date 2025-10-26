#include "filedrop.h"

#include <fcntl.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

bool fdr_send_file(fdr_file *file, uint16_t port) {
  int clientSock;
  int servSock;
  struct sockaddr_in servAddr;

  servSock = socket(AF_INET, SOCK_STREAM, 0);
  if (servSock == -1) {
    perror("socket");
    return false;
  }

  int opt = 1;

  // Make it so that you can immediately reuse the socket after it has been
  // closed
  if (setsockopt(servSock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
    perror("setsockopt");
    goto e2;
  }

  servAddr.sin_family = AF_INET;
  servAddr.sin_port = htons(port);
  servAddr.sin_addr.s_addr = INADDR_ANY;

  if (bind(servSock, (struct sockaddr *)&servAddr, sizeof(servAddr)) == -1) {
    perror("bind");
    goto e2;
  }

  if (listen(servSock, 1) == -1) {
    perror("listen");
    goto e2;
  }

  clientSock = accept(servSock, NULL, NULL);
  if (clientSock == -1) {
    perror("accept");
    goto e1;
  }

  if (send(clientSock, &file->f_data_len, sizeof(file->f_data_len), 0) == -1) {
    perror("send");
    goto e1;
  }

  size_t f_name_len = strlen(file->f_name);

  if (send(clientSock, &f_name_len, sizeof(f_name_len), 0) == -1) {
    perror("send");
    goto e1;
  }

  if (send(clientSock, file->f_name, f_name_len, 0) == -1) {
    perror("send");
    goto e1;
  }

  if (send(clientSock, file->f_data, file->f_data_len, 0) == -1) {
    perror("send");
    goto e1;
  }

  close(servSock);
  close(clientSock);
  return true;

e1:
  close(clientSock);
e2:
  close(servSock);
  return false;
}
