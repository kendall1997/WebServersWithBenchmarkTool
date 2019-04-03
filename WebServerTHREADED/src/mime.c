// Costa Rica Institute of Technology
// Computer Engineering
// Operating Systems
// Kendall González León
// 2015087861

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * @brief      Gets the mime type.
 *
 * @param      ext   The file extension
 *
 * @return     The mime type.
 */
char* getMimeType(char* ext){
  char* ct = "";

  // set mime type based on extension
  if(strcmp(ext,"html") == 0){
    ct = "Content-Type: text/html; charset=utf-8\r\n\r\n";
  }else if(strcmp(ext,"a") == 0){
    ct = "Content-type : application/octet-stream\r\n\r\n";
  }else if(strcmp(ext,"jpg") == 0){
    ct = "Content-type : image/jpg\r\n\r\n";
  }else if(strcmp(ext,"png") == 0){
    ct = "Content-type : image/png\r\n\r\n";
  }else if(strcmp(ext,"art") == 0){
    ct = "Content-type : image/x-jg\r\n\r\n";
  }else if(strcmp(ext,"asf") == 0){
    ct = "Content-type : video/x-ms-asf\r\n\r\n";
  }else if(strcmp(ext,"asx") == 0){
    ct = "Content-type : video/x-ms-asf\r\n\r\n";
  }else if(strcmp(ext,"au") == 0){
    ct = "Content-type : audio/basic\r\n\r\n";
  }else if(strcmp(ext,"avi") == 0){
    ct = "Content-type : video/avi\r\n\r\n";
  }else if(strcmp(ext,"avs") == 0){
    ct = "Content-type : video/avs-video\r\n\r\n";
  }else if(strcmp(ext,"bin") == 0){
    ct = "Content-type : application/octet-stream\r\n\r\n";
  }else if(strcmp(ext,"bmp") == 0){
    ct = "Content-type : image/bmp\r\n\r\n";
  }else if(strcmp(ext,"book") == 0){
    ct = "Content-type : application/book\r\n\r\n";
  }else if(strcmp(ext,"bz") == 0){
    ct = "Content-type : application/x-bzip\r\n\r\n";
  }else if(strcmp(ext,"bz2") == 0){
    ct = "Content-type : application/x-bzip2\r\n\r\n";
  }else if(strcmp(ext,"c") == 0){
    ct = "Content-type : text/plain\r\n\r\n";
  }else if(strcmp(ext,"c++") == 0){
    ct = "Content-type : text/plain\r\n\r\n";
  }else if(strcmp(ext,"class") == 0){
    ct = "Content-type : application/java\r\n\r\n";
  }else if(strcmp(ext,"com") == 0){
    ct = "Content-type : application/octet-stream\r\n\r\n";
  }else if(strcmp(ext,"cpp") == 0){
    ct = "Content-type : text/x-c\r\n\r\n";
  }else if(strcmp(ext,"dl") == 0){
    ct = "Content-type : video/dl\r\n\r\n";
  }else if(strcmp(ext,"doc") == 0){
    ct = "Content-type : application/msword\r\n\r\n";
  }else if(strcmp(ext,"dv") == 0){
    ct = "Content-type : video/x-dv\r\n\r\n";
  }else if(strcmp(ext,"dvi") == 0){
    ct = "Content-type : application/x-dvi\r\n\r\n";
  }else if(strcmp(ext,"fli") == 0){
    ct = "Content-type : video/fli\r\n\r\n";
  }else if(strcmp(ext,"gz") == 0){
    ct = "Content-type : application/x-gzip\r\n\r\n";
  }else if(strcmp(ext,"gzip") == 0){
    ct = "Content-type : application/x-gzip\r\n\r\n";
  }else if(strcmp(ext,"h") == 0){
    ct = "Content-type : text/plain\r\n\r\n";
  }else if(strcmp(ext,"htmls") == 0){
    ct = "Content-type : text/html\r\n\r\n"; 
  }else if(strcmp(ext,"html") == 0){
    ct = "Content-type : text/html\r\n\r\n";
  }else if(strcmp(ext,"php") == 0){
    ct = "Content-type : text/html\r\n\r\n";
  }else if(strcmp(ext,"it") == 0){
    ct = "Content-type : audio/it\r\n\r\n";
  }else if(strcmp(ext,"isu") == 0){
    ct = "Content-type : video/x-isvideo\r\n\r\n";
  }else if(strcmp(ext,"java") == 0){
    ct = "Content-type : text/x-java-source\r\n\r\n"; 
  }else if(strcmp(ext,"jpeg") == 0){
    ct = "Content-type : image/jpeg\r\n\r\n"; 
  }else if(strcmp(ext,"js") == 0){
    ct = "Content-type : application/javascript\r\n\r\n";
  }else if(strcmp(ext,"la") == 0){
    ct = "Content-type : audio/nspaudio\r\n\r\n";
  }else if(strcmp(ext,"latex") == 0){
    ct = "Content-type : application/x-latex\r\n\r\n";
  }else if(strcmp(ext,"map") == 0){
    ct = "Content-type : application/x-navimap\r\n\r\n";
  }else if(strcmp(ext,"mid") == 0){
    ct = "Content-type : audio/midi\r\n\r\n";
  }else if(strcmp(ext,"midi") == 0){
    ct = "Content-type : audio/midi\r\n\r\n"; 
  }else if(strcmp(ext,"mjpg") == 0){
    ct = "Content-type : video/x-motion-jpeg\r\n\r\n"; 
  }else if(strcmp(ext,"mp3") == 0){
    ct = "Content-type : video/mpeg\r\n\r\n"; 
  }else if(strcmp(ext,"mpeg") == 0){
    ct = "Content-type : video/mpeg\r\n\r\n"; 
  }else if(strcmp(ext,"mv") == 0){
    ct = "Content-type : video/x-sgi-movie\r\n\r\n";
  }else if(strcmp(ext,"nap") == 0){
    ct = "Content-type : image/naplps\r\n\r\n";
  }else if(strcmp(ext,"ppt") == 0){
    ct = "Content-type : application/powerpoint\r\n\r\n";
  }else if(strcmp(ext,"py") == 0){
    ct = "Content-type : text/x-script.phyton\r\n\r\n";
  }else if(strcmp(ext,"qt") == 0){
    ct = "Content-type : video/quicktime\r\n\r\n";
  }else if(strcmp(ext,"sh") == 0){
    ct = "Content-type : text/x-script.sh\r\n\r\n";
  }else if(strcmp(ext,"tgz") == 0){
    ct = "Content-type : application/x-compressed\r\n\r\n";
  }else if(strcmp(ext,"wav") == 0){
    ct = "Content-type : audio/wav\r\n\r\n";
  }else if(strcmp(ext,"web") == 0){
    ct = "Content-type : application/vnd.xara\r\n\r\n";
  }else if(strcmp(ext,"word") == 0){
    ct = "Content-type : application/msword\r\n\r\n";
  }else if(strcmp(ext,"xls") == 0){
    ct = "Content-type : application/excel\r\n\r\n";
  }else if(strcmp(ext,"xml") == 0){
    ct = "Content-type : application/xml\r\n\r\n";
  }else if(strcmp(ext,"zip") == 0){
    ct = "Content-type : application/x-compressed\r\n\r\n";
  }else{
    ct = "Content-type : application/octet-stream\r\n\r\n";
  }

  return ct;
}