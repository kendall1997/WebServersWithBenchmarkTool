// Costa Rica Institute of Technology
// Computer Engineering
// Operating Systems
// Kendall González León
// 2015087861

#ifndef CONFIG_H
#define CONFIG_H

#define MAXBUF 1024 
#define DELIM "="

struct config
{
   char port[MAXBUF];
   char log[MAXBUF];
   char folder[MAXBUF];
   char scheduler[MAXBUF];
   int pool;
};

struct config get_config(char const *filename);

#endif
