#include "filedrop.h"
#include <stdlib.h>
#include <string.h>

#define DEFAULT_PORT 1283
#define DEFAULT_RECV_IP "127.0.0.1" // Localhost

static void help_menu_sending();
static void help_menu_receiving();

struct SendSettings parse_send_settings(int argc, char **argv,
                                        enum ArgParseStatus *status) {
  struct SendSettings settings = {.file_path = NULL, .port = DEFAULT_PORT};
  *status = OK;

  for (int i = 2; i < argc; ++i) {
    if (strcmp(argv[i], "-p") == 0) {
      if (i + 1 >= argc) {
        fprintf(stderr, "Option -p must have an argument\n");
        *status = ERR;
        return settings;
      }
      int64_t tmp_port = atoi(argv[++i]);
      if (tmp_port <= 0 || tmp_port > 65535) {
        fprintf(stderr, "%s is not a valid port number\n", argv[i]);
        *status = ERR;
        return settings;
      }
      settings.port = tmp_port;
    } else if (argv[i][0] != '-') {
      // Runs if the option doesn't start with a dash
      // signalling it isn't a flag
      settings.file_path = argv[i];
    } else if (strcmp(argv[i], "-h") == 0) {
      help_menu_sending();
      *status = HELP_MENU;
      return settings;
    } else {
      fprintf(stderr, "\"%s send\" doesn't take \"%s\" as a flag.\n", argv[0],
              argv[i]);
      *status = ERR;
      return settings;
    }
  }
  return settings;
}

struct ReceiveSettings parse_recv_settings(int argc, char **argv,
                                           enum ArgParseStatus *status) {
  struct ReceiveSettings settings = {.port = DEFAULT_PORT,
                                     .output_file_path = NULL};
  inet_pton(AF_INET, DEFAULT_RECV_IP, &settings.ipv4_addr);

  *status = OK;

  for (int i = 2; i < argc; ++i) {
    if (strcmp(argv[i], "-o") == 0) {
      if (i + 1 >= argc) {
        fprintf(stderr, "Option -o must have an argument\n");
        *status = ERR;
        return settings;
      }
      settings.output_file_path = argv[++i];
    } else if (strcmp(argv[i], "-ip") == 0) {
      if (i + 1 >= argc) {
        fprintf(stderr, "Option -ip must have an argument\n");
        *status = ERR;
        return settings;
      }
      int inet_pton_status = inet_pton(AF_INET, argv[++i], &settings.ipv4_addr);
      if (inet_pton_status == 0) {
        fprintf(stderr, "%s is not a valid ip4v address\n", argv[i]);
        *status = ERR;
        return settings;
      } else if (inet_pton_status == -1) {
        perror("inet_pton");
        *status = ERR;
        return settings;
      }
    } else if (strcmp(argv[i], "-p") == 0) {
      if (i + 1 >= argc) {
        fprintf(stderr, "Option -p must have an argument\n");
        *status = ERR;
        return settings;
      }
      int64_t tmp_port = atoi(argv[++i]);
      if (tmp_port <= 0 || tmp_port > 65535) {
        fprintf(stderr, "%s is not a valid port number\n", argv[i]);
        *status = ERR;
        return settings;
      }
      settings.port = tmp_port;
    } else if (strcmp(argv[i], "-h") == 0) {
      help_menu_receiving();
      *status = HELP_MENU;
      return settings;
    } else {
      fprintf(stderr, "\"%s receive\" doesn't take \"%s\" as a flag.\n",
              argv[0], argv[i]);
      *status = ERR;
      return settings;
    }
  }

  return settings;
}

static void help_menu_sending() {
  puts("Usage: filedrop send [OPTIONS] [FILE]");
  puts("Options:");
  puts("-p\tPort on which the file will be send.");
  puts("-h\tOpens this help menu.");
}

static void help_menu_receiving() {
  puts("Usage: filedrop receive [OPTIONS]");
  puts("Options:");
  puts("-p\tPort on which the file will be received.");
  puts("-ip\tIP address of the sender, will default to localhost.");
  puts("-o\tOutput file path, defaults to the file name of the sender.");
  puts("-h\tOpens this help menu.");
}
