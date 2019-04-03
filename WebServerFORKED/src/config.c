// Costa Rica Institute of Technology
// Computer Engineering
// Operating Systems
// Kendall González León
// 2015087861

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <config.h>

/**
 * @brief      Gets the configuration from file.
 *
 * @param      filename  The filename to look into
 *
 * @return     The configuration struct.
 */
struct config get_config(char const *filename){
  struct config configstruct;
  FILE *file = fopen (filename, "r");

  if (file != NULL){ 
    char line[MAXBUF];
    int i = 0;

    while(fgets(line, sizeof(line), file) != NULL){
      char *cfline;
      cfline = strstr((char *)line,DELIM);
      cfline = cfline + strlen(DELIM);

      if (i == 0){
        memcpy(configstruct.port,cfline,strlen(cfline));
        //configstruct.port[strlen(cfline)-1] = NULL;
        configstruct.port[strcspn(configstruct.port, "\n")] = '\0';
        //printf("%s\n",configstruct.port);
      } else if (i == 1){
        memcpy(configstruct.folder,cfline,strlen(cfline));
        //configstruct.folder[strlen(cfline)-1] = NULL;
        configstruct.folder[strcspn(configstruct.folder, "\n")] = '\0';
        //printf("%s\n",configstruct.folder);
      } else if (i == 2){
        if(strcmp(line, "\n") == 0){
          char* syspath = "/var/log/syslog";
          memcpy(configstruct.log,syspath,strlen(syspath));
        }else{
          memcpy(configstruct.log,cfline,strlen(cfline));
          //configstruct.log[strlen(cfline)-1] = NULL;
          configstruct.log[strcspn(configstruct.log, "\n")] = '\0';
          //printf("%s\n",configstruct.log);          
        }
      } else if (i == 3){
        memcpy(configstruct.scheduler,cfline,strlen(cfline));
        //configstruct.folder[strlen(cfline)-1] = NULL;
        configstruct.scheduler[strcspn(configstruct.scheduler, "\n")] = '\0';
        //printf("%s\n",configstruct.folder);
      }
      i++;
    } // End while
    fclose(file);
  } // End if file
  
  return configstruct;
}