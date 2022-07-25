#include "common.h"
#include "tcp.h"

int main(int argc, char** argv) {
  printf("TCP Client Application:\n");
  if (argc < 3) {
    printf("%s <host> <port>", argv[0]);
    return -1;
  }
  char* host = argv[1];
  unsigned short port = (unsigned short)atoi(argv[2]);

  // Create TCP Client
  AUTO_CLOSE int sockfd = create_client(host, port);
  if (sockfd < 0) {
    return -1;
  }

  // infinite loop for chat
  setbuf(stdout, NULL);
  char input[65536] = {0};
  for (unsigned int i = 0;; ++i) {
    if (fgets(input, ARRAY_LEN(input), stdin) == NULL) {
      printf("Input error: %s\n", strerror(errno));
      return -1;
    }
    // read the message from client and copy it to buffer
    if (send_message(sockfd, input, (unsigned short)strlen(input)) == -1) {
      printf("Write error: %s\n", strerror(errno));
      return -1;
    }
  }

  return 0;
}
