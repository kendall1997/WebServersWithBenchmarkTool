
#ifndef PULL_H
#define PULL_H

#include <stdio.h> 

//Struct that stores the information of the requests of server

struct summary {
  char* TypeOfFile;
  char* name;
  double size;
  double speedmed;
  double ini_request;
  time_t DateStart;
  time_t DateEnd;
  int ResponseTime;
};

//Struct that stores the data received
struct FtpFile {
  const char *filename;
  FILE *stream;
};

//Function that stores the data received
static size_t my_fwrite(void *buffer, size_t size, size_t nmemb, void *stream);

//Struct that is responsible for making requests to the server and return the requested data
struct summary* pull(char* url);

#endif