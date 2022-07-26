#ifndef TCP_H
#define TCP_H
#include "common.h"
int create_server(const char* host, unsigned short port) {
  // socket create and verification
  AUTO_CLOSE int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    printf("Socket creation failed...\n");
    return -1;
  }
  printf("Socket successfully created..\n");
  int reuse = 1;
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse,
                 sizeof(reuse)) < 0) {
    printf("setsockopt(SO_REUSEADDR) failed");
    return -1;
  }

#ifdef SO_REUSEPORT
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, (const char*)&reuse,
                 sizeof(reuse)) < 0) {
    printf("setsockopt(SO_REUSEPORT) failed");
    return -1;
  }
#endif

  struct sockaddr_in servaddr = {.sin_family = AF_INET,
                                 .sin_addr.s_addr = inet_addr(host),
                                 .sin_port = htons(port)};

  // Binding newly created socket to given IP and verification
  if ((bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))) != 0) {
    printf("Socket bind failed...\n");
    return -1;
  }
  printf("Socket successfully bound..\n");

  // Now server is ready to listen and verification
  if ((listen(sockfd, 1)) != 0) {
    printf("Listen failed...\n");
    return -1;
  }
  printf("Server listening..\n");

  struct sockaddr_in client_addr = {0};
  unsigned int len = sizeof(client_addr);
  // Accept the data packet from client and verification
  int connfd = accept(sockfd, (struct sockaddr*)&client_addr, &len);
  if (connfd < 0) {
    printf("Server accept failed...\n");
    return -1;
  }
  printf("Server accepted connection from %s:%d...\n",
         inet_ntoa(client_addr.sin_addr), client_addr.sin_port);
  return connfd;
}

int create_client(const char* host, unsigned short port) {
  // socket create and verification
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    printf("Socket creation failed...\n");
    return -1;
  }
  printf("Socket successfully created..\n");

  // assign IP, PORT
  struct sockaddr_in servaddr = {.sin_family = AF_INET,
                                 .sin_addr.s_addr = inet_addr(host),
                                 .sin_port = htons(port)};

  // Connect newly created socket to given IP and verification
  if ((connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))) != 0) {
    printf("Socket connect failed...\n");
    close(sockfd);
    return -1;
  }
  printf("Socket successfully connected..\n");
  return sockfd;
}

// Sends a message to the socket with message size prefix
ssize_t send_message(int sockfd, char* msg, unsigned short msgsize) {
  unsigned short nmsgsize = htons(msgsize);
  ssize_t nwrote =
      send(sockfd, &nmsgsize, sizeof(nmsgsize), MSG_NOSIGNAL | MSG_MORE);
  if (nwrote == -1) {
    return -1;
  }

  return send(sockfd, msg, msgsize, MSG_NOSIGNAL);
}

// Receives a message to the socket with message size prefix
ssize_t receive_message(int sockfd, char msg[65536], unsigned short* msgsize) {
  unsigned short nmsgsize = 0;
  ssize_t nread = recv(sockfd, &nmsgsize, sizeof(nmsgsize), MSG_WAITALL);
  if (nread <= 0) {
    return nread;
  }
  *msgsize = ntohs(nmsgsize);

  memset(msg, 0, *msgsize + 1);
  return recv(sockfd, msg, *msgsize, MSG_WAITALL);
}
#endif
