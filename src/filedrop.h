#ifndef FILEDROP_H
#define FILEDROP_H

#include <arpa/inet.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

struct ReceiveSettings {
  char *output_file_path; // defaults to stdout if NULL
  struct in_addr ipv4_addr;
  uint16_t port;
};

struct SendSettings {
  char *file_path;
  uint16_t port;
};

typedef struct {
  size_t f_data_len;
  unsigned char *f_data;
  char f_name[FILENAME_MAX];
} fdr_file;

fdr_file *fdr_parse_file(char *file_path);
fdr_file *fdr_receive_file(struct in_addr ip_addr, uint16_t port);

bool fdr_send_file(fdr_file *file_path, uint16_t port);
bool fdr_save_file(fdr_file *received_file, char *output_file_path);

int send_file_handle(struct SendSettings settings);
int receive_file_handle(struct ReceiveSettings settings);

struct SendSettings parse_send_settings(int argc, char **argv, int *error);
struct ReceiveSettings parse_recv_settings(int argc, char **argv, int *error);

#endif
