#include "common.h"
#include "tcp.h"

int main(int argc, char** argv) {
  printf("TCP Server Application:\n");
  if (argc < 5) {
    printf("%s <host> <port> <bufsize> <sleep_ms>", argv[0]);
    return -1;
  }
  char* host = argv[1];
  unsigned short port = (unsigned short)atoi(argv[2]);
  unsigned long bufsize = parse_sizestr(argv[3]);
  unsigned int sleep_ms = parse_timestr(argv[4]);

  // Create TCP Server
  AUTO_CLOSE int sockfd = create_server(host, port);
  if (sockfd < 0) {
    return -1;
  }
  AUTO_FREE char* buf = (char*)malloc(bufsize);
  if (buf == NULL) {
    printf("Malloc failed\n");
    return -1;
  }
  // infinite loop for chat
  printf("[ ID ]  Interval  Bandwidth\n");
  for (unsigned int i = 0;; ++i) {
    // read the message from client and copy it to buffer
    ssize_t nread = recv(sockfd, buf, bufsize, 0);
    if (nread == -1) {
      printf("Read error: %s\n", strerror(errno));
      return -1;
    } else if (nread == 0) {
      printf("Socket closed on other side\n");
      return -1;
    }
    // print number of bytes read
    char bw[10] = {0};
    to_bandwidth((float)nread / (float)(sleep_ms)*1000, bw, sizeof(bw));
    printf("[%4u]  %6ums  %9s\n", i, sleep_ms, bw);
    fflush(stdout);
    msleep(sleep_ms);
  }

  return 0;
}
