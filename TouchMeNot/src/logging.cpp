/**
 * @file logging.c
 * @author Deepesh
 *         Madhumitha
 * @brief 
 * @version 0.1
 * @date 2020-04-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <stdarg.h>
#include"logging.h"
#include"common.h"




const char* level[LEVEL] = { "TRACE" , "INFO", "DEBUG", "ERROR"};


double getTimeMsec()
{
  struct timespec evt_time = {0, 0};
  clock_gettime(CLOCK_REALTIME, &evt_time);
  return ((evt_time.tv_sec) * 1000.0) + ((evt_time.tv_nsec) / 1000000.0);
}


void LOG(LogLevel level_t, char *fmt,...){
    char ucData[60];
    va_list args;
   // pthread_mutex_lock(&windowLock);
    va_start(args,fmt);
    vsprintf(ucData, fmt, args);
    va_end(args);
    STDOUT("[%lf]\t[%s]\t%s",getTimeMsec(),level[level_t],ucData);
   // pthread_mutex_unlock(&windowLock);
}





