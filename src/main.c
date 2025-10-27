#include "filedrop.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int send_file_handle(struct SendSettings settings);
int receive_file_handle(struct ReceiveSettings settings);

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s [send/receive] [options]\n", argv[0]);
    return EXIT_SUCCESS;
  }

  if (strcmp(argv[1], "send") == 0) {
    if (argc < 3) {
      printf("Usage: %s %s [file] [options]\n", argv[0], argv[1]);
      return EXIT_SUCCESS;
    }

    enum ArgParseStatus status;
    struct SendSettings settings = parse_send_settings(argc, argv, &status);

    if (status == ERR)
      return EXIT_FAILURE;

    if (status == HELP_MENU)
      return EXIT_SUCCESS;

    if (settings.file_path == NULL) {
      fprintf(stderr, "Send requires a file path to send\n");
      return EXIT_FAILURE;
    }

    printf("port: %d\n", settings.port);
    printf("file: %s\n", settings.file_path);
    return send_file_handle(settings);

  } else if (strcmp(argv[1], "receive") == 0) {

    enum ArgParseStatus status;

    struct ReceiveSettings settings = parse_recv_settings(argc, argv, &status);

    if (status == ERR)
      return EXIT_FAILURE;

    if (status == HELP_MENU)
      return EXIT_SUCCESS;

    printf("port: %d\n", settings.port);
    printf("output_path: %s\n", settings.output_file_path);
    printf("ip: %s\n", inet_ntoa(settings.ipv4_addr));

    return receive_file_handle(settings);

  } else {
    printf("Usage: %s [send/receive] [options]\n", argv[0]);
    return EXIT_SUCCESS;
  }
}
