// Costa Rica Institute of Technology
// Computer Engineering
// Operating Systems
// Kendall González León
// 2015087861

#include <stdio.h>
#include <middleware.h>
#include <log4us.h>
#include <config.h>

/**
 * @brief      Env definition
 */
static struct config environment;

/**
 * @brief      Method sign
 */
void start();


/**
 * @brief      Method sign
 *
 * @param[in]  argc  The argc - amount of parameters
 * @param      argv  The argv - array with the parameters
 */
void loadConfig(int argc, char const *argv[]);

/**
 * @brief      Main input of the software
 *
 * @param[in]  argc  amount of parameters
 * @param      argv  Array with the parameters
 *
 * @return     Success or fail code
 */
int main(int argc, char const *argv[]){
  loadConfig(argc, argv);
  setuplog4us(environment.log);
  start();
  return 0;
}

/**
 * @brief      Starts the webserver library
 */
void start(){
  log4us("Initializing master scheduler");
  startScheduler(environment);  
}

/**
 * @brief      Loads the configuration from file, if does not exists the argument, then default is config.conf in
 * the same folder
 *
 * @param[in]  argc  The argc
 * @param      argv  The argv
 */
void loadConfig(int argc, char const *argv[]) {
  if(argc == 2){
    environment = get_config(argv[1]);
  }else{
    environment = get_config("config.conf");
  }
}