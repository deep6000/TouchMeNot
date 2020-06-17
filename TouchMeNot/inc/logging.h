
/**
 * @file logging.h
 * @author Deepesh 
 *         Madhumitha 
 * @brief 
 * @version 0.1
 * @date 2020-05-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef LOGGING_H
#define LOGGING_H

#include<stdio.h>
#include<string.h>

typedef enum LogLevel{

    TRACE,
    INFO,
    DEBUG,
    ERROR,
    LEVEL
}LogLevel;

 

void LOG(LogLevel level_t, char* fmt, ...);

double getTimeMsec();



#endif