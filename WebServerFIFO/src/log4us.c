// Costa Rica Institute of Technology
// Computer Engineering
// Operating Systems
// Kendall González León
// 2015087861

#include <stdio.h>
#include <time.h>

#include <log4us.h>

/**
 * @brief      Handle the info logs in the system
 */
void log4us(char* event){
	FILE *out = fopen(logPath, "a");  
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	fprintf(out,"[INFO : %d-%d-%d %d:%d:%d] %s\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, event);
	printf("[INFO : %d-%d-%d %d:%d:%d] %s\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, event);
	fclose(out);
}

/**
 * @brief      Sets the path to look for
 *
 * @param      plogPath  The plog path
 */
void setuplog4us(char* plogPath){
	logPath = plogPath;
	printf("%s %s\n", "Saving log to", logPath);
}