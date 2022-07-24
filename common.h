#ifndef COMMON_H
#define COMMON_H
#include <arpa/inet.h>
#include <errno.h>
#include <math.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

void cleanup_close(int* fd) {
  if (fd != NULL && *fd >= 0) {
    printf("Closing fd\n");
    close(*fd);
  }
}
#define AUTO_CLOSE __attribute__((cleanup(cleanup_close)))

void cleanup_free(void* mem) {
  if (mem != NULL && *(void**)mem != NULL) {
    printf("Freeing buffer\n");
    free(*(void**)mem);
  }
}
#define AUTO_FREE __attribute__((cleanup(cleanup_free)))

#define ARRAY_LEN(arr) (sizeof(arr) / sizeof(arr[0]))
int nanosleep(const struct timespec* req, struct timespec* rem);
/* msleep(): Sleep for the requested number of milliseconds. */
int msleep(unsigned int msec) {
  struct timespec ts;
  ts.tv_sec = msec / 1000;
  ts.tv_nsec = (msec % 1000) * 1000000;
  return nanosleep(&ts, &ts);
}

const char* bandwidths[] = {"B/s", "KB/s", "MB/s", "GB/s", "TB/s", "PB/s"};
// Receives bandwidth as float and returns str rep: "4.0KB/s"
int to_bandwidth(float bandwidth, char* s, size_t size) {
  unsigned int i = 0;
  for (i = 0; ((bandwidth / pow(1024, i)) > 1000.0) && i < sizeof(bandwidths);
       ++i) {
  }
  return snprintf(s, size, "%4.1f%s", bandwidth / pow(1024, i), bandwidths[i]);
}

const char* times[] = {"ms", "s"};
// Returns the ms value of time in str representation
unsigned int parse_timestr(const char* s) {
  char* endptr;
  double ret = strtod(s, &endptr);
  for (unsigned int i = 0; i < ARRAY_LEN(times); ++i) {
    if (strcmp(endptr, times[i]) == 0) {
      ret *= pow(1000, i);
      break;
    }
  }
  return (unsigned int)ret;
}

const char* sizebit[] = {"b", "k", "m", "g"};
const char* sizebyte[] = {"B", "K", "M", "G"};
// Returns the ms value of time in str representation
unsigned long parse_sizestr(const char* s) {
  char* endptr;
  unsigned long ret = strtoul(s, &endptr, 10);
  for (unsigned int i = 0; i < ARRAY_LEN(sizebit); ++i) {
    if (strcmp(endptr, sizebit[i]) == 0) {
      ret *= (unsigned long)pow(1000, i);
      ret /= 8;
      break;
    }
  }
  for (unsigned int i = 0; i < ARRAY_LEN(sizebyte); ++i) {
    if (strcmp(endptr, sizebyte[i]) == 0) {
      ret *= (unsigned long)pow(1000, i);
      break;
    }
  }
  return ret;
}
#endif
