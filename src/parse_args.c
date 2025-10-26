#include "filedrop.h"

#include <stdlib.h>
#include <string.h>

#define DEFAULT_PORT 1283
#define DEFAULT_RECV_IP "127.0.0.1" // Localhost

struct SendSettings parse_send_settings(int argc, char **argv, int *error) {
  struct SendSettings settings = {.file_path = NULL, .port = DEFAULT_PORT};
  *error = 0;

  for (int i = 2; i < argc; ++i) {
    if (strcmp(argv[i], "-p") == 0) {
      if (i + 1 >= argc) {
        fprintf(stderr, "Option -p must have an argument\n");
        *error = 1;
        return settings;
      }
      int64_t tmp_port = atoi(argv[++i]);
      if (tmp_port <= 0 || tmp_port > 65535) {
        fprintf(stderr, "%s is not a valid port number\n", argv[i]);
        *error = 1;
        return settings;
      }
      settings.port = tmp_port;
    } else if (argv[i][0] != '-') {
      // Runs if the option doesn't start with a dash
      // signalling it isn't a flag
      settings.file_path = argv[i];
    }
  }
  return settings;
}

struct ReceiveSettings parse_recv_settings(int argc, char **argv, int *error) {
  struct ReceiveSettings settings = {.port = DEFAULT_PORT,
                                     .output_file_path = NULL};
  inet_pton(AF_INET, DEFAULT_RECV_IP, &settings.ipv4_addr);

  *error = 0;

  for (int i = 2; i < argc; ++i) {
    if (strcmp(argv[i], "-o") == 0) {
      if (i + 1 >= argc) {
        fprintf(stderr, "Option -o must have an argument\n");
        *error = 1;
        return settings;
      }
      settings.output_file_path = argv[++i];
    } else if (strcmp(argv[i], "-ip") == 0) {
      if (i + 1 >= argc) {
        fprintf(stderr, "Option -ip must have an argument\n");
        *error = 1;
        return settings;
      }
      int inet_pton_status = inet_pton(AF_INET, argv[++i], &settings.ipv4_addr);
      if (inet_pton_status == 0) {
        fprintf(stderr, "%s is not a valid ip4v address\n", argv[i]);
        *error = 1;
        return settings;
      } else if (inet_pton_status == -1) {
        perror("inet_pton");
        *error = 1;
        return settings;
      }
    } else if (strcmp(argv[i], "-p") == 0) {
      if (i + 1 >= argc) {
        fprintf(stderr, "Option -p must have an argument\n");
        *error = 1;
        return settings;
      }
      int64_t tmp_port = atoi(argv[++i]);
      if (tmp_port <= 0 || tmp_port > 65535) {
        fprintf(stderr, "%s is not a valid port number\n", argv[i]);
        *error = 1;
        return settings;
      }
      settings.port = tmp_port;
    }
  }

  return settings;
}
