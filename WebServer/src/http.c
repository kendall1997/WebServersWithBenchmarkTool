// Costa Rica Institute of Technology
// Computer Engineering
// Operating Systems
// Kendall González León
// 2015087861

#define LENGTH 1024 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <signal.h>

#include <http.h>
#include <middleware.h>
#include <mime.h>
#include <log4us.h>

/**
 * @brief      WebServer's Start function 
 */
void startHTTP(char* port, char* public_html){
  log4us("HTTP module initializing");
  log4us("WebServer listening on port: ");
  log4us(port);
  www = public_html;
  serve_forever(port);
}

/**
 * @brief      This method will start listening for new connections
 *
 * @param[in]  PORT  The port
 */
void serve_forever(const char *PORT){
  struct sockaddr_in clientaddr;
  socklen_t addrlen;
    
  int slot=0;

  // Setting all elements to -1: signifies there is no client connected
  int i;
  for(i = 0; i<CONNMAX; i++){
    clients[i]=-1;    
  }

  // Rise Bind
  startServer(PORT); 
    
  // Ignore SIGCHLD to avoid zombie threads
  signal(SIGCHLD,SIG_IGN);

  // ACCEPT connections
  while (1){
    addrlen = sizeof(clientaddr);
    clients[slot] = accept (listenfd, (struct sockaddr *) &clientaddr, &addrlen);

    if (clients[slot]<0){
      perror("accept() error");
    }else{
      // Due to is sequential, the FIFO policy is implemeted here
      scheduler(slot);
    }
    while (clients[slot]!=-1) slot = (slot+1)%CONNMAX;
  }
}

/**
 * @brief      Starts a server.
 *
 * @param[in]  port  The port
 */
void startServer(const char *port){
  // Needed structs finded in sys/types
  struct addrinfo hints, *res, *p;

  // getaddrinfo for host
  memset (&hints, 0, sizeof(hints));
  // set socket types
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  // Try to reserve the host
  /*
   Given node and service, which identify an Internet host and a  service,
   getaddrinfo()  returns  one  or more addrinfo structures, each of which
   contains an Internet address that can be specified in a call to bind(2)
   or  connect(2).   The getaddrinfo() function combines the functionality
   provided by the gethostbyname(3) and getservbyname(3) functions into  a
   single  interface,  but  unlike  the latter functions, getaddrinfo() is
   reentrant and allows programs to eliminate  IPv4-versus-IPv6  dependen‐
   cies.
  */
  if (getaddrinfo( NULL, port, &hints, &res) != 0){
    perror ("getaddrinfo() error");
    exit(1);
  }
  
  // socket and bind
  for (p = res; p!=NULL; p=p->ai_next){
    int option = 1;
    listenfd = socket (p->ai_family, p->ai_socktype, 0);
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
    if (listenfd == -1) continue;
    if (bind(listenfd, p->ai_addr, p->ai_addrlen) == 0) break;
  }
  if (p==NULL){
    perror ("socket() or bind()");
    exit(1);
  }

  /*
       The hints argument points to an addrinfo structure that specifies  cri‐
       teria  for selecting the socket address structures returned in the list
       pointed to by res.  If hints is not  NULL  it  points  to  an  addrinfo
       structure  whose ai_family, ai_socktype, and ai_protocol specify crite‐
       ria that limit the set of socket addresses returned  by  getaddrinfo().
  */
  freeaddrinfo(res);

  // listen for incoming connections
  if ( listen (listenfd, 1000000) != 0 ){
    perror("listen() error");
    exit(1);
  }
}

/**
 * @brief      Parses the information received from the user in HTTP 1.1 protocol
 *
 * @param[in]  name  Header to be obtained from headers
 *
 * @return     Pointer to the memory location that has the value of the requested header
 */
char *request_header(const char* name){
  header_t *h = reqhdr;
  while(h->name) {
      if (strcmp(h->name, name) == 0) return h->value;
      h++;
  }
  // If there is not that header, then return null
  return NULL;
}

/**
 * @brief      Method in charge to respond each request made to the webserver
 *
 * @param[in]  n     Id returned by accept method that will be stored into the clients array slot
 */
void respond(int n){
    // variable where the status of the receive information will be stored, error if is lower than 0
    int rcvd;

    char    *method,    // "GET" or "POST"
            *uri,       // "/index.html" things before '?'
            *qs,        // "a=1&b=2"     things after  '?'
            *prot;      // "HTTP/1.1"

    char    *payload;     // for POST // need to be local on each thread
    int      payload_size;

    // buffer where the request data will be stored
    char* buf = (char*) malloc(65535);

    // receive data from client's socket
    rcvd=recv(clients[n], buf, 65535, 0);

    if (rcvd<0){    // receive error
      fprintf(stderr,("recv() error\n"));      
    } else if (rcvd==0) { // receive socket closed
      fprintf(stderr,"Client disconnected upexpectedly.\n");
    } else { // message received
      buf[rcvd] = '\0';

      // get the HTTP verb: GET, POST, UPDATE, DELETE, OPTIONS, etc.
      method = strtok(buf,  " \t\r\n");
      // get the object location resource, requested by the user
      uri    = strtok(NULL, " \t");
      // post data if exists
      prot   = strtok(NULL, " \t\r\n"); 

      // debug output
      fprintf(stderr, "\x1b[32m --> [%s] %s\x1b[0m\n", method, uri);
      
      // parse GET parameters
      if ((qs = strchr(uri, '?')))
      {
          *qs++ = '\0'; //split URI
      } else {
          qs = uri - 1; //use an empty string
      }

      // set headers struct
      header_t *h = reqhdr;

      // dto variables
      char *t, *t2;

      // initialize if does not go into the loop
      t="";
      // this loop will print all the headers sent by the users
      while(h < reqhdr+16) {
          char *k,*v,*t;
          k = strtok(NULL, "\r\n: \t"); if (!k) break;
          v = strtok(NULL, "\r\n");     while(*v && *v==' ') v++;
          h->name  = k;
          h->value = v;
          h++;
          fprintf(stderr, "[Header] %s: %s\n", k, v);
          //log4us(v);
          t = v + 1 + strlen(v);
          if (t[1] == '\r' && t[2] == '\n') break;
      }
      // now the *t shall be the beginning of user payload
      t++; 
      t2 = request_header("Content-Length"); 
      // post data sent by user
      payload = t;
      payload_size = t2 ? atol(t2) : (rcvd-(t-buf));


      // delete / from path
      if (uri[0] == '/') uri++;

      // default path
      if(strcmp(uri, "") == 0){
        uri = "index.html";
      }

      // create full path from base directory
      char* base = www;
      char* path = (char*) malloc(strlen(base)+strlen(uri));
      strcpy(path, base);
      strcat(path, uri);

      // debug message
      char* basemessage = "New Request on: ";
      char* message = malloc(strlen(basemessage) + strlen(uri));
      strcpy(message, basemessage);
      strcat(message, uri);

      // Log the request
      log4us(message);

      // free message memory
      free(message);

      // get file extension
      char* ext = (char*) (strrchr(uri, '.') + 1);

      // Required structures to open the file in disk
      char* fs_name = path;
      char sdbuf[LENGTH]; 
      FILE *fs = fopen(fs_name, "r");

      // get the client socket id
      int clientfd = clients[n];

      // File exists?
      if(fs == NULL){
        char* ok = "HTTP/1.1 404 Not Found\r\n";
        char* ct = "Content-Type: text/html; charset=utf-8\r\n\r\n";

        send(clientfd, ok, strlen(ok), 0);
        send(clientfd, ct, strlen(ct), 0);


      }else{

          // Ok response for HTTP protocol

          char* ok = "HTTP/1.1 200 OK\r\n";
          char* ct = "";


          // set the content type based on the extension
          ct = getMimeType(ext);

          // send header to user

          send(clientfd, ok, strlen(ok), 0);
          send(clientfd, ct, strlen(ct), 0);

          // Added support to php
          if (strcmp(ext,"php") == 0) {
            // buffers
            char* command = calloc(300, sizeof(char));
            // compose paths
            sprintf(command, "php %s", fs_name);
            int size_retrieved;

            fs = popen(command, "r");
            while ((size_retrieved = fread(sdbuf,sizeof(char),LENGTH, fs)) >0){
              if(send(clientfd, sdbuf, size_retrieved, 0) < 0){
                printf("ERROR: Failed to send file %s.\n", fs_name);
               break;
              }
            }
            fclose(fs);


            free(command);
            
          }else{
            // send data to user by spliting the requested file.
            bzero(sdbuf, LENGTH); 
            int fs_block_sz; 
            while((fs_block_sz = fread(sdbuf, sizeof(char), LENGTH, fs))>0){
              if(send(clientfd, sdbuf, fs_block_sz, 0) < 0){
                printf("ERROR: Failed to send file %s.\n", fs_name);
               break;
              }
              bzero(sdbuf, LENGTH);
            }
          }

        }

        // Closing Socket
        // HTTP protocol closes the connection when data delivered
        shutdown(clientfd, SHUT_RDWR);
        close(clientfd);
        clients[n]=-1;

        // Release Buffer memory
        free(buf);
        free(path);
      }

      
}