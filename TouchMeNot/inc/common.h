/**
 * @file common.h
 * @author Deepesh
 *         Madhumitha
 * @brief 
 * @version 0.1
 * @date 2020-05-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>
#include <semaphore.h>
#include <mqueue.h>

#include <sys/time.h>
#include <errno.h>
#include <time.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <unordered_map>


#include"logging.h"

using namespace cv;
using namespace std; 

//#define EXECUTION_TIME
#define STDOUT      printf
#define MQ_OPTION  "/message_queue_option"
typedef enum threads_e{

    THREAD_SEQUENCER,
    THREAD_HAND_GESTURE,
    THREAD_QT,
    THREAD_MAIN
}thread_e;

typedef enum option_e{

    OPTION_0,
    OPTION_1,
    OPTION_2,
    OPTION_3,
    OPTION_4,
    OPTION_5
}option_e;

#define NUM_OF_THREADS  (THREAD_MAIN)




typedef struct ThreadParams{

    thread_e ThreadID;
}ThreadParams;

typedef struct Option{

    option_e option;
}Option;

extern bool run;
extern sem_t SemHandDetect;
extern sem_t Semaphores[NUM_OF_THREADS];
extern mqd_t QueueOption;
extern volatile bool LookingforOption;
extern pthread_mutex_t windowLock;
extern Mat *question;
extern volatile bool start_hand_detection;
extern volatile bool start_sending;

#define SEND_OPTION(queue,Option)           (mq_send(queue,(char*)&Option,sizeof(Option),0))
#define RECEIVE_OPTION(queue,Option)        (mq_receive(queue,(char*)&Option,sizeof(Option),NULL))

#endif  // COMMON_H