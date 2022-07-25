#include "common.h"
#include "tcp.h"

int main(int argc, char** argv) {
  printf("TCP Server Application:\n");
  if (argc < 3) {
    printf("%s <host> <port>", argv[0]);
    return -1;
  }
  char* host = argv[1];
  unsigned short port = (unsigned short)atoi(argv[2]);

  // Create TCP Server
  AUTO_CLOSE int sockfd = create_server(host, port);
  if (sockfd < 0) {
    return -1;
  }

  // infinite loop for chat
  setbuf(stdout, NULL);
  for (unsigned int i = 0;; ++i) {
    char msg = 0;
    ssize_t nread = recv(sockfd, &msg, sizeof(msg), 0);
    if (nread == -1) {
      printf("Read error: %s\n", strerror(errno));
      return -1;
    } else if (nread == 0) {
      printf("Socket closed on other side\n");
      return -1;
    }
    printf("%c", msg);
  }

  return 0;
}
