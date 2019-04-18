#include <stdio.h> 
#include <curl/curl.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
 

#include <agent.h>
 

 
static size_t my_fwrite(void *buffer, size_t size, size_t nmemb, void *stream)
{
  struct FtpFile *out = (struct FtpFile *)stream;
  if(!out->stream) {
    /* open file for writing */ 
    out->stream = fopen(out->filename, "wb");
    if(!out->stream)
      return -1; /* failure, can't open file to write */ 
  }
  return fwrite(buffer, size, nmemb, out->stream);
}

struct summary* pull(char* url){

  CURL *curl;
  CURLcode res;
  double seconds;
  double size;
  double speedmed;
  double ini_request;

  char *filename = (char*) (strrchr(url, '/') + 1);
  char* ext = (char*) (strrchr(url, '.') + 1);

  struct FtpFile ftpfile = {
    "/dev/null", /* name to store the file as if successful */ 
    NULL
  };

  const time_t start = time(NULL);
  curl_global_init(CURL_GLOBAL_DEFAULT);
 
  curl = curl_easy_init();
  if(curl) {
    /*
     * You better replace the URL with one that works!
     */ 
    curl_easy_setopt(curl, CURLOPT_URL, url);
    //curl_easy_setopt (curl, CURLOPT_USERAGENT, "Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:66.0) Gecko/20100101 Firefox/66.0");
    /* Define our callback to get called when there's data to be written */ 
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_fwrite);
    /* Set a pointer to our struct to pass to the callback */ 
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ftpfile);
 
    /* Switch on full protocol/debug output */ 
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
 
    res = curl_easy_perform(curl);
    
    curl_easy_getinfo(curl, CURLINFO_SIZE_DOWNLOAD, &size);

    curl_easy_getinfo(curl, CURLINFO_SPEED_DOWNLOAD, &speedmed);

    curl_easy_getinfo(curl, CURLINFO_CONNECT_TIME, &ini_request);

    /* always cleanup */ 
    curl_easy_cleanup(curl);
 
    if(CURLE_OK != res) {
      /* we failed */ 
      fprintf(stderr, "curl told us %d\n", res);
    }
  }
 
  if(ftpfile.stream)
    fclose(ftpfile.stream); /* close the local file */ 
 
  curl_global_cleanup();
  
  const time_t end = time(NULL);


  seconds = (end - start);
  size = size/(1000*1000);
  speedmed = speedmed/(1000*1000);
  
  struct summary* tmp = malloc(sizeof(struct summary));

  tmp->ResponseTime = (int) seconds;
  tmp->size = size;
  tmp->speedmed = speedmed;
  tmp->ini_request = ini_request;
  tmp->DateEnd = end;
  tmp->DateStart = start;
  tmp->name = filename;
  tmp->TypeOfFile = ext;

	
  return tmp;

}
