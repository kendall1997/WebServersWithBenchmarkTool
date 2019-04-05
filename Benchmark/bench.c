#include <stdio.h> 
#include <curl/curl.h>
#include <time.h>
#include <string.h>
 

struct summary {
	double ResponseTime;
	double size;
    char* DateStart;
    char* DateEnd;
    char* TypeOfFile;
    char* name;
};
 
struct FtpFile {
  const char *filename;
  FILE *stream;
};
 
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

struct summary pull(char* url){

  CURL *curl;
  CURLcode res;
  double seconds;
  double size;

  char *filename = (char*) (strrchr(url, '/') + 1);
  char* ext = (char*) (strrchr(url, '.') + 1);

  struct FtpFile ftpfile = {
    "10MB.zip", /* name to store the file as if successful */ 
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
    
    curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &size);
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
  size = size/(1024*1024);
  printf("fecha: %s\n", asctime(localtime(&start)));
  printf("fecha: %s\n", asctime(localtime(&end)));
  
  struct summary tmp;
    tmp.ResponseTime = seconds;
    tmp.size = size;
    tmp.DateStart = asctime(localtime(&start));
    tmp.DateEnd = asctime(localtime(&end));
    tmp.name = filename;
    tmp.TypeOfFile = ext;
	return tmp;

}
 
 
int main(void)
{
    char* url = "http://autogestion.metrotel.com.ar/speedtest/archivo10MB.zip";
    struct summary data = pull(url);
    
    printf("time: %f\n", data.ResponseTime);
    printf("size: %.0f MB\n", data.size);
    printf("Date Start: %s\n", data.DateStart);
    printf("Date End: %s \n", data.DateEnd);
    printf("name: %s\n", data.name);
    printf("Type of File: %s \n", data.TypeOfFile);
}