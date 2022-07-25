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
  for (unsigned int i = 0;; ++i) {
    char input = (char)fgetc(stdin);
    ssize_t nwrote = send(sockfd, &input, sizeof(input), MSG_NOSIGNAL);
    if (nwrote == -1) {
      printf("Write error: %s\n", strerror(errno));
      return -1;
    }
  }

  return 0;
}
