
#ifndef PULL_H
#define PULL_H

#include <stdio.h> 

struct summary {
  char* TypeOfFile;
  char* name;
  double size;
  time_t DateStart;
  time_t DateEnd;
  int ResponseTime;
};

struct FtpFile {
  const char *filename;
  FILE *stream;
};

static size_t my_fwrite(void *buffer, size_t size, size_t nmemb, void *stream);
struct summary* pull(char* url);

#endif