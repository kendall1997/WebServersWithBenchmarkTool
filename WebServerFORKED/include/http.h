// Costa Rica Institute of Technology
// Computer Engineering
// Operating Systems
// Kendall González León
// 2015087861

#ifndef HTTP_MODULE_H
#define HTTP_MODULE_H

#include <netdb.h>

#define CONNMAX 10000

void serve_forever(const char *PORT);

//Server control functions

void serve_forever(const char *PORT);

// Client request

/*char    *method,    // "GET" or "POST"
        *uri,       // "/index.html" things before '?'
        *qs,        // "a=1&b=2"     things after  '?'
        *prot;      // "HTTP/1.1"
*/ // Need to be local
//char    *payload;     // for POST // need to be local on each thread
//int      payload_size; // need to be local on each thread

char *request_header(const char* name);


static int listenfd, clients[CONNMAX];
static void startServer(const char *);
void respond(int);

typedef struct { char *name, *value; } header_t;
static header_t reqhdr[17] = { {"\0", "\0"} };
// static int clientfd; // need to be local on each thread

// static char *buf; // need to be local on each thread
static char* www;

void startHTTP(char* port,char* public_html);

// some interesting macro for `route()`
#define ROUTE_START()       if (0) {
#define ROUTE(METHOD,URI)   } else if (strcmp(URI,uri)==0&&strcmp(METHOD,method)==0) {
#define ROUTE_GET(URI)      ROUTE("GET", URI) 
#define ROUTE_POST(URI)     ROUTE("POST", URI) 
#define ROUTE_END()         } else printf(\
                                "HTTP/1.1 500 Not Handled\r\n\r\n" \
                                "The server has no handler to the request.\r\n" \
                            );

#endif
